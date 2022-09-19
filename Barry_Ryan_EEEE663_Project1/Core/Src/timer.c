#include "stm32l476xx.h"
/*
 * timer.c
 *
 *  Created on: Sep 17, 2022
 *      Author: Ryan Barry
 */


// initializes the timer (Similar to USART2_Init(). Place in timer.c)
void TIM_Init(void){
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;	// enable clock for this timer in the clock control
	TIM2->PSC = 16;							// load the prescaler value -- divide 16 MHz clock down to 1 MHz
	TIM2->EGR |= TIM_EGR_UG ;				// force an update event to make the prescaler load take effect
	TIM2->CCMR1 &= ~(0x11);					// Configure the channel as an input
	TIM2->CCMR1 |= 0x01;
	TIM2->CCER &= ~(0x111 << 1);			// Set trigger to rising edge by clearing CC1P, CCNP, and CCNP
	TIM2->CCER |= 0x1;						// Enable capture by setting the CC1E bit
	TIM2->CR1 |= TIM_CR1_CEN ;				// now start the timer
	return;
}

// Returns the current count value from timer TIM2.
//
// DO NOT CHANGE this function.
static uint32_t TIM2_get_count()
{
	return TIM2->CNT ;
}
