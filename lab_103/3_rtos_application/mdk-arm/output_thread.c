/*
 * main.c
 *
 * this is the main analog blink application (this code is dependent on the
 * extra shu libraries such as the pinmappings list, the clock configuration
 * library, the gpio library, and the adc library)
 *
 * author:    Dr. Alex Shenfield
 * date:      01/09/2018
 * purpose:   55-604481 embedded computer networks : lab 101
 */

// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "adc.h"
#include "gpio.h"
#include "stm32746g_discovery_lcd.h"

// include the serial configuration files
#include "serial.h"

// map the led to GPIO PA8 and the potentiometer to PA0
gpio_pin_t led = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t pot = {PA_0, GPIOA, GPIO_PIN_0};

// declare our utility functions
void configure_gpio(void);

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  // HAL_Init();
  // init_sysclk_216MHz();
  //
  // initialise the uart, adc and gpio pins
  // init_uart(9600);
	//  init_adc(pot);
	//  init_gpio(led, OUTPUT);
	//  
	//  // print an initial status message
	//  printf("we are alive!\r\n");
	//  
  // loop forever ...
	
	  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	
	// initialise the adc
	init_adc(pot);
	
  // initialise the lcd
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

  // set the background colour to blue and clear the lcd
  BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
  BSP_LCD_Clear(LCD_COLOR_GREEN);
  
  // set the font to use
  BSP_LCD_SetFont(&Font24); 
  
  // print the welcome message ...
  BSP_LCD_SetTextColor(LCD_COLOR_RED);
    
  // delay a little ...
  HAL_Delay(500);
	
  while(1)
  {
    // toggle the led pin
    toggle_gpio(led);
    
    // read the potentiometer and echo that value to the terminal
		// format string based around adc value and print on lcd
		char str[16]; //define 16 bit string
		uint16_t adc_val = read_adc(pot); //put adc value into adc_val
    sprintf(str, "potentiometer value = %d : delay time = %d ms\r\n",
			adc_val, (adc_val/2)), 
		BSP_LCD_DisplayStringAtLine(2, (uint8_t *)str); //display str at line 2
    
    // delay for the appropriate time
    HAL_Delay(adc_val / 2);
  }
}
