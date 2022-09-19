#include "Barry_Ryan_EEEE663_main_P1.h"
#include "stm32l476xx.h"
#include "clock.h"
#include "led.h"
#include "timer.h"
#include "stdbool.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <uart.h>


char *message; // message to print to the user
char buffer[20] = {0}; // holds the user response
uint32_t default_arrival = 1000;
uint32_t lower_limit = 1000 - 50; // the default lower limit in the problem statement
uint32_t new_lower_limit = 1000 - 50;
int n;
char *msg = "";
char rxByte;
int input = 0;
int count[101] = {0};
//////////////////////////////////////////////////////////////
// Embedded code usually consists of 2 components
//  - The init section is run once at startup and initializes all low level drivers and modules
//  - The main loop runs forever and calls the application tasks repeatedly.
////////////////

int main(void){



	////////////////////////
	// Initialization executed once at startup
	////////////////////////
	clock_init();
	USART2_Init(115200);
	TIM_Init();

//	bool i = power_on_self_test();
//	while( power_on_self_test() != 0 )
//		;

	//////////////////////
	// Main loop that runs forever
	//////////////////////
	while (1){
		// 1. Print "Enter expected period or <CR> if no change". Wait for user response
		get_line(buffer, sizeof(buffer));

		// 2. Set a new expected interval time based on user input
		get_limit(buffer, &lower_limit);

		// 3. measure 1000 pulses
		init_measurement( lower_limit );
		make_measurements( lower_limit );

		// 4. Print time/count for non-zero counts
		print_measurements( lower_limit );
	}
}
	////////////////////////
	// Function implementation stubs
	////////////////////////

	// runs the power on self-test. Returns true if the test passes, false otherwise
	_Bool power_on_self_test( void ){
		/* start a timer and count to 100 ms
		 *
		 * Capture every time there's an incoming signal and count to 100 ms
		 *
		 * Take a time stamp and add to the current counter value and compare
		 * the difference to the time stamp to find when it reaches 100 ms.
		 * Monitor the input capture to make sure it's 100 ms.
		 *
		 * Read the digital status register, store the bit in the status register
		 *
		 * Code shouldn't go beyond POST if it is failing. Build a while loop and
		 * store the time stamp in the while loop. While in the while loop measure
		 * the status of the pin. If there isn't a 100 ms signal tell the user to
		 * set the signal to go (make sure it is running)
		 *
		 */


		return 0;
	}

	// initializes all variabes prior to a measurement.
	int init_measurement( uint32_t limit ){

		return 0;
	}

	int make_measurements( uint32_t limit ){
//		while(TIM2_get_count() & (input + 50) < input + 50){
////			if()
//		}

//		if(count)
		return 0;
	}

	// print the non-zero bucket times and counts
	int print_measurements( uint32_t limit ){
		for(int i = -50; i <= 50; i++){
			n = sprintf((char *)buffer, "\n\r%-5d%6d", input + i, count[i+50]);
			USART_Write(USART2, buffer, n);
		}
		return 0;
	}

	// Captures 1 line of text from the console. Returns nul terminated string when \n is entered
	void get_line( void *buffer, int max_length ){

		// 1. Print "Enter expected period or <CR> if no change". Wait for user response
		int msg;
		input = 0;
		// Tells the user the default arrival time (initialized at the top of the file)
		n = sprintf((char *)buffer, "\n\rDefault Period: %lu ms", default_arrival);
		USART_Write(USART2, buffer, n);
		// User prompt to enter a custom period
		message = "\n\rEnter expected period between 100 Hz and 10,000 Hz or <CR> if no change.";
		n = sprintf((char *)buffer, "%s\n\r", message);

		// Reads numbers typed from the computer and displays them to the terminal as they are typed
		while(rxByte != 13){
			USART_Write(USART2, buffer, n);
			rxByte = USART_Read(USART2);
			switch(rxByte-48){ // 48 needs to be subtracted from rxByte to translate from ASCII char to decimal
				case 0 :
					msg = 0;
					input = input*10 + msg;
					n = sprintf((char *)buffer, "%d", msg);
					break;
				case 1 :
					msg = 1;
					input = input*10 + msg;
					n = sprintf((char *)buffer, "%d", msg);
					break;
				case 2 :
					msg = 2;
					input = input*10 + msg;
					n = sprintf((char *)buffer, "%d", msg);
					break;
				case 3 :
					msg = 3;
					input = input*10 + msg;
					n = sprintf((char *)buffer, "%d", msg);
					break;
				case 4 :
					msg = 4;
					input = input*10 + msg;
					n = sprintf((char *)buffer, "%d", msg);
					break;
				case 5 :
					msg = 5;
					input = input*10 + msg;
					n = sprintf((char *)buffer, "%d", msg);
					break;
				case 6 :
					msg = 6;
					input = input*10 + msg;
					n = sprintf((char *)buffer, "%d", msg);
					break;
				case 7 :
					msg = 7;
					input = input*10 + msg;
					n = sprintf((char *)buffer, "%d", msg);
					break;
				case 8 :
					msg = 8;
					input = input*10 + msg;
					n = sprintf((char *)buffer, "%d", msg);
					break;
				case 9 :
					msg = 9;
					input = input*10 + msg;
					n = sprintf((char *)buffer, "%d", msg);
					break;
			}
		}
		// Check that the user value is within range and display the requirement if it is not
		if((input < 100 || input > 10000) && input != 0){
			n = sprintf((char *)buffer, "\n\n\rPeriod must be an integer between 100 Hz and 10 kHz\n");
			USART_Write(USART2, buffer, n);
			get_line(buffer, sizeof(buffer));
		}
		// Display the selected value
		else if(input == 0){
			input = default_arrival;
			n = sprintf((char *)buffer, "\n\rChosen period: %d", input);
			USART_Write(USART2, buffer, n);
		}
		else{
			n = sprintf((char *)buffer, "\n\rChosen period: %d", input);
			USART_Write(USART2, buffer, n);
		}


		return;
	}

	// Parses a line of user input into a new lower limit (unchanged if no response or invalid response)
	void get_limit ( void *buffer, uint32_t *lower_limit ){
		// input obtained within get_line
		// Assign the new lower limit based on the user input
		if(input - 50 != lower_limit){
			new_lower_limit = input - 50;
		}
		return;
	}


