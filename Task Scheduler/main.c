/*
 * 		Author		:	Aditya Mohan
 * 		Date		:	28 - oct - 2016
 * 		Description :	A simple task scheduler that switches between four tasks in a Round-Robin arrangement, with an assumption of non
 * 						floating point arithmetic
 */


#include "stm32f4xx.h"
#include "pushbutton.h"

#define LED0 (1<<7)
#define LED1 (1<<8)
#define LED2 (1<<9)
#define LED3 (1<<10)

/* Macros for word accesses */
#define HW32_REG (ADDRESS) (*((volatile unsigned long *) ADDRESS))

/* Use Breakpoint to stop when error is detected (KEIL MDK specific intrinsic) */

/* it can be changed to while(1) XXif needed */
#define stop_cpu __breakpoint(0)

void LED_initialize ( void ) ; 				// Initialize LED
void task0 ( void ) ; 						// Toggle LED0
void task1 ( void ) ; 						// Toggle LED1
void task2 ( void ) ; 						// Toggle LED2
void task3 ( void ) ;				 	    // Toggle LED3

// Event to tasks
volatile uint32_t systick_count=0;

// Stack for each task (8Kbytes each - 1024 x 8 bytes)
long long task0_stack[1024], task1_stack[1024], task2_stack[1024], task3_stack[1024];

// Data use by OS
uint32_t curr_task=0; 	// Current task
uint32_t next_task=1;       // Next task
uint32_t PSP_array[4]; 	// Process Stack Pointer for each task

// -------------------------------------------------------------
// Start of main program

int main(void)
{
    SCB -> CCR |= SCB_CCR_STKALIGN_Msk; 													// Enable double word stack alignment
    																						//(recommended in Cortex-M3 r1p1, default in Cortex-M3 r2px and Cortex-M4)
    greenled_init(1);
    orangeled_init(1);
    redled_init(1);
    blueled_init(1);

    //LED_initialize();
    /*-----------------------Starting the task scheduler---------------------------- */

    /* ---------------------------- Task 0 ------------------------------------------*/
    // Create stack frame for task0
    PSP_array [ 0 ] = ( (unsigned int) task0_stack ) + ( sizeof (task0_stack) ) - 16*4;
    HW32_REG ( ( PSP_array [ 0 ] + ( 14<<2 ) ) )  = ( unsigned long ) task0;

    // initial Program Counter
    HW32_REG ( (PSP_array[0] +  ( 15<<2 ) ) ) = 0x01000000; 		// initial xPSR
    /* ----------------------------------------------------------------------------*/

    /* ---------------------------- Task 1 ------------------------------------------*/
    // Create stack frame for task1
    PSP_array [ 1 ] = ( ( unsigned int ) task1_stack ) + ( sizeof (task1_stack) ) - 16*4;
    HW32_REG ( ( PSP_array [ 1 ] +  ( 14<<2 ) ) ) = ( unsigned long ) task1;

    // initial Program Counter
    HW32_REG ( ( PSP_array [ 1 ] + ( 15<<2 ) ) ) = 0x01000000; // initial xPSR
    /* --------------------------*/


    /* ---------------------------- Task 0 ------------------------------------------*/
    // Create Stack frame for task 2
    PSP_array [ 2 ] = ( ( unsigned int ) task2_stack ) + ( sizeof (task2_stack) ) - 16*4;
    HW32_REG ( ( PSP_array [ 2 ] +  ( 14<<2 ) ) ) = ( unsigned long ) task2;

    // initial Program Counter
    HW32_REG ( ( PSP_array [ 2 ] + ( 15<<2 ) ) ) = 0x01000000; // initial xPSR
    /* --------------------------*/


    /* ---------------------------- Task 0 ------------------------------------------*/
    // Create stack frame for task3
    PSP_array [ 3 ] =  ( ( unsigned int ) task3_stack ) + ( sizeof (task3_stack) ) - 16*4;
    HW32_REG ( ( PSP_array [ 3 ] + ( 14<<2 ) ) ) = ( unsigned long ) task3;
    // initial Program Counter
    HW32_REG ( ( PSP_array [ 3 ] + ( 15<<2 ) ) ) = 0x01000000; // initial xPSR
    /* --------------------------*/


    curr_task = 0 ; 											// Switch to task #0 (Current task)
    __set_PSP ( ( PSP_array [ curr_task ] + 16*4 ) ) ;          // Set PSP to top of task 0 stack

    NVIC_SetPriority ( PendSV_IRQn, 0xFF ) ;                    // Set PendSV to lowest possible priority

    SysTick_Config ( 168000 ) ;                                 // 1000 Hz SysTick interruption 168MHz core clock

    __set_CONTROL ( 0x3 ) ;                                     // Switch to use Process Stack, unprivileged state

    __ISB ( ) ;                                                 // Execute ISB after changing CONTROL (architectural recommendation)

    task0 ( ) ;                                                 // Start task 0

    while ( 1 )
    {
    	//stop_cpu;	// Should not be here according to the warning
    };
}

// ------------------------------------------------------------
void task0 ( void ) 										// Toggle LED #0
{
    while (1)
    {
    	if ( systick_count & 0x80 )
	{
	    GPIOD -> BSRRL = LED0;								// Set LED 0
	}
    	else
	{
	    GPIOD -> BSRRH = LED0;
	} 														// Clear LED 0
    };
}

// ------------------------------------------------------------
void task1	( void ) 										// Toggle LED #1
{
    while (1)
    {
	if ( systick_count & 0x100 )
	{
	    GPIOD -> BSRRL = LED1;								// Set LED 1
	}
        else
	{
	    GPIOD -> BSRRH = LED1;
	} 														// Clear LED 1
    };
}

// ------------------------------------------------------------
void task2(void) 											// Toggle LED #2
{
    while (1)
    {
	if ( systick_count & 0x200 )
	{
	    GPIOD -> BSRRL = LED2;								// Set LED 2
	}
        else
	{
	    GPIOD -> BSRRH = LED2;
	} 														// Clear LED 2
    };
}

// ------------------------------------------------------------
void task3(void) // Toggle LED #3
{
    while (1)
    {
	if ( systick_count & 0x400 )
	{
	    GPIOD -> BSRRL = LED3;								// Set LED 3
	}
        else
	{
	    GPIOD -> BSRRH = LED3;  								// Clear LED 3
	}
    };
}

// ------------------------------------------------------------

void PendSV_Handler (void)
{ // Context switching code

asm (
		"MRS R0, PSP \n	"											// Get current process stack pointer value
		"STMDB R0!,{R4-R11}\n" 											// Save R4 to R11 in task stack (8 regs)
		"LDR R1,=__cpp(&curr_task)\n"
		"LDR R2,[R1]\n" 												// Get current task ID
		"LDR R3,=__cpp(&PSP_array)\n"
		"STR R0,[R3, R2, LSL #0x2]\n" 									// Save PSP value into PSP_array

	        // -------------------------
		 // Load next context
		"LDR R4,=__cpp(&next_task)\n"
		"LDR R4,[R4]\n" 												// Get next task ID
		"STR R4,[R1]\n" 												// Set curr_task = next_task
		"LDR R0,[R3, R4, LSL #0x2]\n" 									// Load PSP value from PSP_array
		"LDMIA R0!,{R4-R11}\n" 											// Load R4 to R11 from task stack (8 regs)
		"MSR PSP, R0\n" 												// Set PSP to next task
		"BX LR\n" 														// Return
		"ALIGN 4\n"
	) ;
}
    // ------------------------------------------------------------
void SysTick_Handler(void) // 1KHz
{
    // Increment systick counter for LED blinking
    systick_count++;

    // Simple task round robin scheduler
    switch( curr_task )
    {
     case(0): next_task=1; break;
     case(1): next_task=2; break;
     case(2): next_task=3; break;
     case(3): next_task=0; break;
     default: next_task=0;

     //stop_cpu;		// Should not be here
     break;
    }

    if ( curr_task != next_task )									// Context switching needed
    {
      SCB -> ICSR |= SCB_ICSR_PENDSVSET_Msk ; 						// Set PendSV to pending
    }

    return;
}

// ------------------------------------------------------------
void LED_initialize(void)
{
    // Configure LED outputs
RCC -> AHB1ENR |= RCC_AHB1ENR_GPIODEN ; // Enable Port D clock

// Set pin 12, 13, 14, 15 as general purpose output mode(pull-push)
GPIOD -> MODER |= ( GPIO_MODER_MODER7_0 |
				    GPIO_MODER_MODER8_0 |
				    GPIO_MODER_MODER9_0 |
				    GPIO_MODER_MODER10_0
				  ) ;

// GPIOE->OTYPER |= 0; // No need to change - use pull-push output
GPIOD -> OSPEEDR |= ( GPIO_OSPEEDER_OSPEEDR7 | // 100MHz operations
					  GPIO_OSPEEDER_OSPEEDR8 |
					  GPIO_OSPEEDER_OSPEEDR9 |
					  GPIO_OSPEEDER_OSPEEDR10
				     ) ;
GPIOD -> PUPDR = 0 ; // No pull up , no pull down

return;
}
