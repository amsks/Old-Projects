#include "timer.h"

void timer_4_init()
{
	TIM_TimeBaseInitTypeDef timerstruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);


	    timerstruct.TIM_Prescaler = 0;  /*Timer count frequency is set with:  timer_tick_frequency = Timer_default_frequency / (prescaler_set + 1) */
	    timerstruct.TIM_CounterMode = TIM_CounterMode_Up;  /* Count up */
	    timerstruct.TIM_Period = 8399; /* PWM_frequency = timer_tick_frequency / (TIM_Period + 1), TIM_Period must not exceed max value of timer i.e. 65535 */
	    timerstruct.TIM_ClockDivision = TIM_CKD_DIV1;
	    timerstruct.TIM_RepetitionCounter = 0;

	    /* Initialize TIM4 */
	    TIM_TimeBaseInit(TIM4, &timerstruct);
	    /* Start count on TIM4 */
	    TIM_Cmd(TIM4, ENABLE);
}

// output compare in timer 4. uses pwm
void timer_4_ocinit()
{
	    TIM_OCInitTypeDef tim4ocstruct;
	 /* Common settings */

	    /* PWM mode 2 = Clear on compare match */
	    /* PWM mode 1 = Set on compare match */
	    tim4ocstruct.TIM_OCMode = TIM_OCMode_PWM2;
	    tim4ocstruct.TIM_OutputState = TIM_OutputState_Enable;
	    tim4ocstruct.TIM_OCPolarity = TIM_OCPolarity_Low;

	/*
	    To get proper duty cycle, you have simple equation

	    pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 - 1

	    where DutyCycle is in percent, between 0 and 100%

	    25% duty cycle:     pulse_length = ((8399 + 1) * 25) / 100 - 1 = 2099
	    50% duty cycle:     pulse_length = ((8399 + 1) * 50) / 100 - 1 = 4199
	    75% duty cycle:     pulse_length = ((8399 + 1) * 75) / 100 - 1 = 6299
	    100% duty cycle:    pulse_length = ((8399 + 1) * 100) / 100 - 1 = 8399

	    Remember: if pulse_length is larger than TIM_Period, you will have output HIGH all the time
	*/
	    tim4ocstruct.TIM_Pulse = 2099; /* 25% duty cycle */
	    TIM_OC1Init(TIM4, &tim4ocstruct);
	    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	    tim4ocstruct.TIM_Pulse = 4199; /* 50% duty cycle */
	    TIM_OC2Init(TIM4, &tim4ocstruct);
	    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	    tim4ocstruct.TIM_Pulse = 6299; /* 75% duty cycle */
	    TIM_OC3Init(TIM4, &tim4ocstruct);
	    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	    tim4ocstruct.TIM_Pulse = 8399; /* 100% duty cycle */
	    TIM_OC4Init(TIM4, &tim4ocstruct);
	    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

}

/*
void gpio_af_tim()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	    /* Clock for GPIOD */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	    /* Alternating functions for pins */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

	    /* Set pins */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

}
*/
void timer2_init(){

	TIM_TimeBaseInitTypeDef tim2_struct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	tim2_struct.TIM_Prescaler=41999;
	tim2_struct.TIM_CounterMode=TIM_CounterMode_Up;
	tim2_struct.TIM_Period=1999;
	tim2_struct.TIM_ClockDivision =TIM_CKD_DIV1;
	tim2_struct.TIM_RepetitionCounter=0;

	TIM_TimeBaseInit(TIM2, &tim2_struct);

}
/*
void tim2_start(){
	TIM_Cmd(TIM2, ENABLE);
}

void tim2_stop(){
	TIM_Cmd(TIM2, DISABLE);
}

void timer2_oc(){

	TIM_OCInitTypeDef tim2_oc;

	TIM_OCStructInit (&tim2_oc);



}
*/
