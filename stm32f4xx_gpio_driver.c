/*
 * stm32f4xx_gpio_driver.c
 *
 *  Created on: Jan 26, 2025
 *      Author: 35596
 */

#include "stm32f4xx_gpio_driver.h"

void GPIO_PeriClkCtrl(GPIO_RegDef_t *pvGPIOx,uint8_t EnDis)
{
	if(EnDis == ENABLE)
	{
		if( pvGPIOx == GPIOA )
		{
			GPIOA_PCLK_EN();
		}
		else if( pvGPIOx == GPIOB )
		{
			GPIOB_PCLK_EN();
		}
		else if( pvGPIOx == GPIOC )
		{
			GPIOC_PCLK_EN();
		}
	}
	else
	{
		if( pvGPIOx == GPIOA )
		{
			GPIOA_PCLK_DI();
		}
		else if( pvGPIOx == GPIOB )
		{
			GPIOB_PCLK_DI();
		}
		else if( pvGPIOx == GPIOC )
		{
			GPIOC_PCLK_DI();
		}
	}
}
void GPIO_Init(GPIO_Handle_t *pvGPIO_handle)
{
	uint32_t temp = 0;
	//mode configuration
	if(pvGPIO_handle->GPIO_PinConfg.pinMode <= GPIO_ANALOG)
	{
		temp = (pvGPIO_handle->GPIO_PinConfg.pinMode << ( 2 * pvGPIO_handle->GPIO_PinConfg.pinNumber));
		pvGPIO_handle->pvGPIOx->MODER |= temp;

		//output type configuration
		temp = 0;
		temp = (pvGPIO_handle->GPIO_PinConfg.pinOPType << pvGPIO_handle->GPIO_PinConfg.pinNumber);
		pvGPIO_handle->pvGPIOx->OTYPER |= temp;

		//speed configuration
		temp = 0;
		temp = (pvGPIO_handle->GPIO_PinConfg.pinSpeed << ( 2 * pvGPIO_handle->GPIO_PinConfg.pinNumber));
		pvGPIO_handle->pvGPIOx->OSPEEDR |= temp;
	}
	else /*EXTI : Interrupt related initialization*/
	{
		if(pvGPIO_handle->GPIO_PinConfg.pinMode == GPIO_EXTI_FT)
		{
			EXTI-> EXTI_FTSR |= (1<<pvGPIO_handle->GPIO_PinConfg.pinNumber);
			EXTI-> EXTI_RTSR &= ~(1<<pvGPIO_handle->GPIO_PinConfg.pinNumber);//clear RTSR
		}
		else if(pvGPIO_handle->GPIO_PinConfg.pinMode == GPIO_EXTI_RT)
		{
			EXTI-> EXTI_RTSR |= (1<<pvGPIO_handle->GPIO_PinConfg.pinNumber);
			EXTI-> EXTI_FTSR &= ~(1<<pvGPIO_handle->GPIO_PinConfg.pinNumber); // clear FTSR
		}
		/*configure interrupt mask register*/
		EXTI->EXTI_IMR |= (1<<pvGPIO_handle->GPIO_PinConfg.pinNumber);

		/*configure SYSCFG control register*/
		uint8_t temp1 = pvGPIO_handle->GPIO_PinConfg.pinNumber / 4;
		uint8_t temp2 = pvGPIO_handle->GPIO_PinConfg.pinNumber % 4;
		//Enable syscfg clock before EXTICR configuration
		SYSCFG_PCLK_EN();
		SYSCFG->SYSCFG_EXTICR[temp1] |= SYSCFG_EXTICR_PORT_SELECT(pvGPIO_handle->pvGPIOx) << (temp2 * 4);

	}

	//pull up-down configuration
	temp = 0;
	temp = (pvGPIO_handle->GPIO_PinConfg.pinPuPd << ( 2 * pvGPIO_handle->GPIO_PinConfg.pinNumber));
	pvGPIO_handle->pvGPIOx->PUPDR |= temp;


}
 void GPIO_DeInit(GPIO_RegDef_t *pvGPIOx)
 {
	 if(pvGPIOx == GPIOA)
	 {
		 GPIOA_RESET();
	 }
	 else if(pvGPIOx == GPIOB)
	 {
		 GPIOB_RESET();
	 }
 }
 void GPIO_PinWrite(GPIO_RegDef_t *pvGPIOx,uint8_t PinNumber,uint8_t value)
 {
	 if(value == RESET)
	 {
		 pvGPIOx->ODR |= (1<<PinNumber);
	 }
	 else
	 {
		 pvGPIOx->ODR &= ~(1<<PinNumber);
	 }
 }
 uint8_t GPIO_PinRead(GPIO_RegDef_t *pvGPIOx,uint8_t PinNumber)
 {
	 uint16_t temp = 0;
	 temp = pvGPIOx->IDR;
	 if(temp & (1<<PinNumber))
	 {
		 return SET;
	 }
	 return RESET;
 }
 void GPIO_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnDis)
 {
	 if(EnDis)
	 {
		 if(IRQNumber < 32)
		 {
			 *NVIC_ISER0 |= (1<<IRQNumber);
		 }
		 else if(IRQNumber >= 32 && IRQNumber < 64)
		 {
			 *NVIC_ISER1 |= (1<<(IRQNumber % 32));
		 }
		 else if(IRQNumber >=64 && IRQNumber < 96)
		 {
			 *NVIC_ISER2 |= (1<<(IRQNumber % 64));
		 }
		 else if(IRQNumber >=96 && IRQNumber < 128)
		 {
			 *NVIC_ISER3 |= (1<<(IRQNumber % 96));
		 }
	 }
	 else
	 {
		 if(IRQNumber < 32)
		 {
			 *NVIC_ICER0 |= (1<<IRQNumber);
		 }
		 else if(IRQNumber >= 32 && IRQNumber < 64)
		 {
			 *NVIC_ICER1 |= (1<<(IRQNumber % 32));
		 }
		 else if(IRQNumber >=64 && IRQNumber < 96)
		 {
			 *NVIC_ICER2 |= (1<<(IRQNumber % 64));
		 }
		 else if(IRQNumber >=96 && IRQNumber < 128)
		 {
			 *NVIC_ICER3 |= (1<<(IRQNumber % 96));
		 }
	 }
 }
 void GPIO_IRQPriorityConfig(uint8_t IRQPriority)
 {
	 uint8_t pri_reg_number=0;
	 uint8_t pri_reg_section =0;
	 uint8_t shift_amount = 0;
	 pri_reg_number = IRQPriority / 4;
	 pri_reg_section = IRQPriority % 4;
	 shift_amount = (8 * pri_reg_section)+ (8-CM4_INT_PRI_BIT_IMPLEMENTATION);
	 *(NVIC_PRIO_BASEADDRS + (4 *pri_reg_number)) |= (IRQPriority << shift_amount );
 }
 void GPIO_IRQHandler(uint8_t PinNumber)
 {
	 //check if interrupt is pended
	 if(EXTI->EXTI_PR & ( 1<<PinNumber ))
	 {
		 //clear the pend register
		 EXTI->EXTI_PR |= ( 1<<PinNumber );
	 }
 }
