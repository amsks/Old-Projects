#include "pushbutton.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
//#include "stdint.h"


// initialization of Port D, Pin 12 for on board Green LED
// pass 1 as a parameter for AF mode, 0 for OUTPUT mode

void greenled_init(uint8_t mode/*, Task *x */)
{
  GPIO_InitTypeDef ledinit;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  if(mode)
  {
	  ledinit.GPIO_Mode  = GPIO_Mode_AF;
	  GPIO_PinAFConfig(LED_PORT, GPIO_PinSource12, GPIO_AF_TIM4);
  }

  else
  {
	  ledinit.GPIO_Mode  = GPIO_Mode_OUT;
  }

  ledinit.GPIO_Pin   = LED_GREEN;
  ledinit.GPIO_OType = GPIO_OType_PP;
  ledinit.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  ledinit.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_Init(LED_PORT, &ledinit);
}

// initialization of Port D, Pin 13 for on board Orange LED
void orangeled_init(uint8_t mode/* Task *x */)
{
  GPIO_InitTypeDef ledinit;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  if(mode)
    {
	  ledinit.GPIO_Mode  = GPIO_Mode_AF;
  	  GPIO_PinAFConfig(LED_PORT, GPIO_PinSource13, GPIO_AF_TIM4);
    }

  else
  {
	  ledinit.GPIO_Mode  = GPIO_Mode_OUT;
  }

  ledinit.GPIO_Pin   = LED_ORANGE;
  ledinit.GPIO_OType = GPIO_OType_PP;
  ledinit.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  ledinit.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_Init(LED_PORT, &ledinit);
}

// initialization of Port D, Pin 14 for on board Red LED
void redled_init(uint8_t mode/*, Task *x */)
{
  GPIO_InitTypeDef ledinit;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  if(mode)
    {
	  ledinit.GPIO_Mode  = GPIO_Mode_AF;
  	  GPIO_PinAFConfig(LED_PORT, GPIO_PinSource14, GPIO_AF_TIM4);
    }

  else
  {
	  ledinit.GPIO_Mode  = GPIO_Mode_OUT;
  }

  ledinit.GPIO_Pin   = LED_RED;
  ledinit.GPIO_OType = GPIO_OType_PP;
  ledinit.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  ledinit.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_Init(LED_PORT, &ledinit);
}

// initialization of Port D, Pin 15 for on board Blue LED
void blueled_init(uint8_t mode/* Task *x */)
{
  GPIO_InitTypeDef ledinit;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  if(mode)
    {
	  ledinit.GPIO_Mode  = GPIO_Mode_AF;
  	  GPIO_PinAFConfig(LED_PORT, GPIO_PinSource15, GPIO_AF_TIM4);
    }

  else
  {
	  ledinit.GPIO_Mode  = GPIO_Mode_OUT;
  }

  ledinit.GPIO_Pin   = LED_BLUE;
  ledinit.GPIO_OType = GPIO_OType_PP;
  ledinit.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  ledinit.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_Init(LED_PORT, &ledinit);
}

void pushbutton_init(/* Task *x */)
{
  GPIO_InitTypeDef ledinit;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  ledinit.GPIO_Pin   = PUSHBUTTON;
  ledinit.GPIO_Mode  = GPIO_Mode_IN;
  ledinit.GPIO_OType = GPIO_OType_PP;
  ledinit.GPIO_PuPd  = GPIO_PuPd_DOWN;
  ledinit.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_Init(GPIOA, &ledinit);

}

void led_on( uint16_t ledcolor/*, Task *x */)
{
  GPIO_WriteBit( LED_PORT, ledcolor, LED_ON ) ;
}

void led_off( uint16_t ledcolor/*, Task *x */ )
{
  GPIO_WriteBit( LED_PORT, ledcolor, LED_OFF ) ;
}

void led_toggle(uint16_t ledcolor/*, Task *x */)
{
  GPIO_ToggleBits (LED_PORT, ledcolor );
}

void delay(uint32_t delaytime)
{
	while(delaytime--);
}


