/*
 * main.c
 *
 * this is the skeleton for task 2
 *
 * author:    Dr. Alex Shenfield
 * date:      04/09/2018
 * purpose:   55-604481 embedded computer networks : lab 102
 */

// include the basic headers and hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "stm32746g_discovery_lcd.h"
#include "adc.h"
#include "gpio.h"

// include the stdio library
#include "stdio.h"

// map pot to PA_0
gpio_pin_t pot = {PA_0, GPIOA, GPIO_PIN_0};

// LCD DEFINES

// CODE

// this is the main method
int main()
{
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
		// format a string based around the adc value and print to lcd
		char str[16]; //define a 16 bit string
		uint16_t adc_val = read_adc(pot); // put adc value into adc_val
		sprintf(str, "ADC=%3d%%", (adc_val*100)/4070); //print adc_val and store in str
		BSP_LCD_DisplayStringAtLine(2, (uint8_t *)str); //display str at line 1
		HAL_Delay (200);
	}
}
