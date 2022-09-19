/*
 * timer.h
 *
 *  Created on: Sep 17, 2022
 *      Author: Ryan Barry
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_



// initializes the timer (Similar to USART2_Init)(. Place in timer.c)
void TIM_Init(void);

// Returns the current count value from timer TIM2.
static uint32_t TIM2_get_count();


#endif /* INC_TIMER_H_ */
