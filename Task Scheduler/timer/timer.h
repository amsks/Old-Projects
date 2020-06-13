#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include <stdint.h>



void timer_4_init();

void timer_4_ocinit();

void gpio_af_tim();

void timer2_init();

void timer2_oc();

#endif /* TIMER_H_ */
