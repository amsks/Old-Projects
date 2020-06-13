#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

#include <stdint.h>

//typedef unsigned short int uint16_t;
// definition of LED_color pins

#define LED_GREEN   GPIO_Pin_12
#define LED_ORANGE  GPIO_Pin_13
#define LED_RED     GPIO_Pin_14
#define LED_BLUE    GPIO_Pin_15
#define PUSHBUTTON  GPIO_Pin_0

#define LED_ON		Bit_SET
#define LED_OFF		Bit_RESET
#define LED_PORT	GPIOD

#define OP			GPIO_Mode_OUT
#define AF			GPIO_Mode_AF

#define TIMER_2		TIM2
#define TIMER_3		TIM3
#define TIMER_4		TIM4

#define GPIOAFT2	GPIO_AF_TIM2
#define GPIOAFT3	GPIO_AF_TIM3
#define GPIOAFT4	GPIO_AF_TIM4

// pass 0 as argument for OUTPUT mode, 1 for AF mode which is compatible with timer 4
void greenled_init(uint8_t );
void orangeled_init(uint8_t );
void redled_init(uint8_t );
void blueled_init(uint8_t );
void pushbutton_init();

void led_on( uint16_t x);
void led_off( uint16_t x);
void led_toggle(uint16_t x);

void delay(uint32_t x);

#endif /* PUSHBUTTON_H_ */
