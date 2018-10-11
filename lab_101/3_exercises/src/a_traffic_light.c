/*
 * a_traffic_lights.c
 *
 * this is the main application skeleton for the student exercises in task 3
 *
 */

// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"

// map the led to GPIO PA8
gpio_pin_t led1 = {PI_1, GPIOI, GPIO_PIN_1}; //red traffic light
gpio_pin_t led2 = {PB_14, GPIOI, GPIO_PIN_14};//mber traffic light
gpio_pin_t led3 = {PB_15, GPIOI, GPIO_PIN_15}; //een traffic light

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	
	// initialise the gpio pins
  init_gpio(led1, OUTPUT);
	init_gpio(led2, OUTPUT);
	init_gpio(led3, OUTPUT);
	
	// loop forever ...
  while(1)
  {
    // red on
    write_gpio(led1, HIGH);
		write_gpio(led2, LOW);
		write_gpio(led3, LOW);
		
		// wait for 1 second
    HAL_Delay(1000);
		
		//red & amber on
		write_gpio(led2, HIGH);
		
		// wait for 1 second
    HAL_Delay(1000);
		
		// green on
		write_gpio(led1, LOW);
		write_gpio(led2, LOW);
		write_gpio(led3, HIGH);
    
    // wait for 5 seconds
    HAL_Delay(5000);
		
		// amber on
		write_gpio(led2, HIGH);
		write_gpio(led3, LOW);
		
		///wait for one second
		HAL_Delay(1000);
  }
}
