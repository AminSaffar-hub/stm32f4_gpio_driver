/**
  ******************************************************************************
  * @file    gpio.c
  * @author  Amin Saffar
  * @version V1.0.0
  * @date    19-06-2019
  *****************************************************************************
/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

// define for RCC clock enable
#define RCC_AHB1ENR (unsigned short int*) 0x40023830  
// define for rcc clock reset 
#define RCC_AHB1RSTR (unsigned short int*) 0x40023810 

/**
  * @brief  Deinitializes the gpio_x peripheral registers to their default reset values.
  * @param  gpio_x: where x can be (A..G) to select the GPIO peripheral.
  * @retval None
  */
//enable the clock of the gpiox
void GPIO_ClockEnable (unsigned int * gpio_x)
{

  if (gpio_x == GPIO_A)
  {
    
    *RCC_AHB1ENR |= (1<<0);
  }
  if (gpio_x == GPIO_B)
  {
    *RCC_AHB1ENR |= (1<<1);
  }
  if (gpio_x == GPIO_C)
  {
    *RCC_AHB1ENR |= (1<<2);
  }
  if (gpio_x == GPIO_D)
  {
    *RCC_AHB1ENR |= (1<<3);
  }
  if (gpio_x == GPIO_E)
  {
    *RCC_AHB1ENR |= (1<<4);
  }
  if (gpio_x == GPIO_F)
  {
    *RCC_AHB1ENR |= (1<<5);
  }
  
  if (gpio_x == GPIO_G)
  {
    *RCC_AHB1ENR |= (1<<6);
  }
  if (gpio_x == GPIO_H)
  {
    *RCC_AHB1ENR |= (1<<7);
  }
  if (gpio_x == GPIO_I)
  {
    *RCC_AHB1ENR |= (1<<8);
  }
}
/**
  * @brief  Deinitializes the gpio_x peripheral registers to their default reset values.
  * @param  gpio_x: where x can be (A..G) to select the GPIO peripheral.
  * @retval None
  */
//resets a gpiox rcc activation using the rcc reset register
void GPIO_DeInit(unsigned int * gpio_x)
{
      
  if (gpio_x == GPIO_A)
  {
    *RCC_AHB1RSTR |= (1<<0) ;
    
    *RCC_AHB1RSTR &= ~(1<<0);
    
  }
  if (gpio_x == GPIO_B)
  {
    *RCC_AHB1RSTR |= (1<<1) ;
    
    *RCC_AHB1RSTR &= ~(1<<1);
    
  }
  if (gpio_x == GPIO_C)
  {
    *RCC_AHB1RSTR |= (1<<2) ;
    
    *RCC_AHB1RSTR &= ~(1<<2);
    
  }
  if (gpio_x == GPIO_D)
  {
    *RCC_AHB1RSTR |= (1<<3) ;
    
    *RCC_AHB1RSTR &= ~(1<<3);
    
  }
  if (gpio_x == GPIO_E)
  {
    *RCC_AHB1RSTR |= (1<<4) ;
    
    *RCC_AHB1RSTR &= ~(1<<4);
    
  }
  if (gpio_x == GPIO_F)
  {
    *RCC_AHB1RSTR |= (1<<5) ;
    
    *RCC_AHB1RSTR &= ~(1<<5);
    
  }
  if (gpio_x == GPIO_G)
  {
    *RCC_AHB1RSTR |= (1<<6) ;
    
    *RCC_AHB1RSTR &= ~(1<<6);
    
  }
  if (gpio_x == GPIO_H)
  {
    *RCC_AHB1RSTR |= (1<<7) ;
    
    *RCC_AHB1RSTR &= ~(1<<7);
    
  }
  if (gpio_x == GPIO_I)
  {
    *RCC_AHB1RSTR |= (1<<8) ;
    
    *RCC_AHB1RSTR &= ~(1<<8);
    
  }
}

/**
  * @brief  Configure the gpio_x
  * @param  gpio_x: where x can be (A..G) to select the GPIO peripheral.
  * @param  Mode: can be INPUT, OUTPUT, AF or AN
  * @param  typeOutput: can be PP or OD
  * @param  pin: can be 0...15
  * @retval None
  */

void GPIO_Init(unsigned int * gpio_x, char Mode, char type, short int pin)
{
 
  
  int mask_reset = (0x3 << pin*2);
    
  int mask_moder = (Mode << pin*2);
  
  unsigned int * moder_register =(unsigned int *)( gpio_x + MODER) ;  // c infernaaaaaaaaaaaaaal
  
  *moder_register &= ~mask_reset;
  *moder_register |= mask_moder;
  
    if (Mode == 0x02)
    {
      int mask_PP = (type << (pin));
      unsigned int* otyper_register = (unsigned int *)(gpio_x + OTYPER);
      *otyper_register |= mask_PP;
    }
    else if (Mode == 0x00)
    {
      int mask_PP = (type << (pin*2));
      unsigned int* pupdr_register = (unsigned int *)(gpio_x + PUPDR);
      *pupdr_register &= ~mask_reset;
      *pupdr_register |= mask_PP;
    }
     
  
 }

  
/**
  * @brief  Reads the specified input port pin.
  * @param  gpio_x: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to read.
  *   This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval The input port pin value.
  */
unsigned  char GPIO_ReadInputDataBit(unsigned int *  gpio_x, unsigned  short int GPIO_Pin)
{
  unsigned  char bitstatus = 0x00;
  
   unsigned int *IDR_register  = (unsigned int *)(gpio_x + IDR);
   if (*IDR_register && GPIO_Pin)
   {bitstatus = 0x01;
   return bitstatus ;}
   else 
   {bitstatus = 0x00;
   return bitstatus ;
   }
  
}

/**
  * @brief  Reads the specified GPIO input data port.
  * @param  gpio_x: where x can be (A..G) to select the GPIO peripheral.
  * @retval GPIO input data port value.
  */
unsigned  short int GPIO_ReadInputData(unsigned int *  gpio_x)
{
  
  unsigned int *IDR_register  = (unsigned int *) (gpio_x + IDR);
  return (*IDR_register);
}

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  gpio_x: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be one of GPIO_Pin_x where x can be (0..15).
  * @param  BitVal: specifies the value to be written to the selected bit.
  *   This parameter can be one of the BitAction enum values:
  *     @arg Bit_RESET: to clear the port pin
  *     @arg Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(unsigned int * gpio_x, unsigned  short int GPIO_Pin, char BitVal)
{
 
unsigned int *output_register =(unsigned int *) (gpio_x + ODR);  
if (BitVal != 0x0)
  *output_register |= GPIO_Pin;
else 
  *output_register &= ~GPIO_Pin; 
}
/**
  * @brief  Sets or clears the selected data port bit using bsrr register.
  * @param  gpio_x: where x can be (A..G) to select the GPIO peripheral.
  * @param  pin: specifies the port bit to be written.
  *   This parameter can be one of GPIO_Pin_x where x can be (0..15).
  * @param  BitVal: specifies the value to be written to the selected bit.
  *   This parameter can be one of the BitAction enum values:
  *     @arg Bit_RESET: to clear the port pin
  *     @arg Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit_BSRR(unsigned int * gpio_x, unsigned  short int pin, char BitVal)
{
  unsigned int *BSRR_register= (unsigned int *) (gpio_x + BSRR);
  if (BitVal != 0x0)
  { 
    int set_mask = (1<<pin);
    *BSRR_register |= set_mask;
  }
  else
  {
    int reset_set_mask = (1<<pin);
    *BSRR_register &= ~reset_set_mask; // Note: If both BSx and BRx are set, BSx has priority
    int reset_mask = (1 << (pin+16));
    *BSRR_register |= reset_mask ;
  }
    
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  gpio_x: where x can be (A..G) to select the GPIO peripheral.
  * @param  PortVal: specifies the value to be written to the port output data register.
  * @retval None
  */
void GPIO_Write(unsigned int * gpio_x, unsigned  short int PortVal)
{
  unsigned int *output_register = (unsigned int *)(gpio_x + ODR);
  *output_register |= PortVal;
}
/******************* (C) COPYRIGHT 2019 CSF *****END OF FILE*******************/

