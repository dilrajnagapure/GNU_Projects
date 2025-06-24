/*
 * stm32f4xx_gpio_driver.h
 *
 *  Created on: Jan 26, 2025
 *      Author: 35596
 */

#ifndef INC_STM32F4XX_GPIO_DRIVER_H_
#define INC_STM32F4XX_GPIO_DRIVER_H_
#include "stm32f4xx.h"

/*GPIO Pin configuration, configures pin number,mode,speed etc*/
typedef struct
{
	uint8_t pinNumber; /*Refer @GPOI pin numbers*/
	uint8_t pinMode; /*Refer @type of GPIO modes*/
	uint8_t pinOPType; /*Refer @type of GPIO Output type*/
	uint8_t pinSpeed; /*Refer @type of GPIO output speed*/
	uint8_t pinPuPd; /*Refer @type of GPIO Pull up , pull down settings*/
	uint8_t pinAltFunMode; /*Refer @*/
}GPIO_PinConfg_t;

/*GPIO handle, consists GPIO base address and pin configuration*/
typedef struct
{
	GPIO_RegDef_t *pvGPIOx;
	GPIO_PinConfg_t GPIO_PinConfg;
}GPIO_Handle_t;

/*@type of GPIO modes*/
typedef enum
{
	GPIO_INPUT, /*input mode (Reset)*/
	GPIO_OUTPUT, /*Output mode*/
	GPIO_ALT_FUNC, /*Alternate function mode*/
	GPIO_ANALOG, /*Analog mode*/
	GPIO_EXTI_FT, /*EXTI faling trigger*/
	GPIO_EXTI_RT /*EXTI Rising trigger*/
}GPIO_ModeSettings_t;

/*@type of GPIO Output type*/
typedef enum
{
	GPIO_PUSHPULL, /*push pull (Reset)*/
	GPIO_OPENDRAIN, /*open drain mode*/
}GPIO_OutputTypeSettings_t;

/*@type of GPIO output speed*/
typedef enum
{
	GPIO_LOW_SPEED,
	GPIO_MEDIUM_SPEED,
	GPIO_HIGH_SPEED,
	GPIO_VERY_HIGH_SPEED
}GPIO_SpeedSettings_t;

/*@type of GPIO Pull up , pull down settings*/
typedef enum
{
	GPIO_NO_PUPD, /*No pull up down (Reset)*/
	GPIO_PULL_UP,
	GPIO_PULL_DN,
}GPIO_PUPDSettings_t;

/*@GPOI pin numbers*/
typedef enum
{
	PIN_NUMBER_0,
	PIN_NUMBER_1,
	PIN_NUMBER_2,
	PIN_NUMBER_3,
	PIN_NUMBER_4,
	PIN_NUMBER_5,
	PIN_NUMBER_6,
	PIN_NUMBER_7,
	PIN_NUMBER_8,
	PIN_NUMBER_9,
	PIN_NUMBER_10,
	PIN_NUMBER_11,
	PIN_NUMBER_12,
	PIN_NUMBER_13,
	PIN_NUMBER_14,
	PIN_NUMBER_15

}GPIO_PinNumber_t;

/*EXTIx[3:0]: EXTI x configuration
These bits are written by software to select the source input for the EXTIx external
interrupt.
0000: PA[x] pin
0001: PB[x] pin
0010: PC[x] pin
0011: PD[x] pin
0100: PE[x] pin
0101: Reserved
0110: Reserved
0111: PH[x] pin*/
typedef enum
{
	PA,
	PB,
	PC,
	PD,
	SYSCFG_EXTICR_RESERVED1,
	SYSCFG_EXTICR_RESERVED2,
	PE,
}SYSCFG_EXTICR_PortSettings_t;

#define SYSCFG_EXTICR_PORT_SELECT(x) (x==GPIOA ? 0 :\
									  x==GPIOB ? 1 :\
									  x==GPIOC ? 2 :\
									  0xff)

void GPIO_PeriClkCtrl(GPIO_RegDef_t *pvGPIOx,uint8_t EnDis);
void GPIO_Init(GPIO_Handle_t *pvGPIO_handle);
void GPIO_DeInit(GPIO_RegDef_t *pvGPIOx);
void GPIO_PinWrite(GPIO_RegDef_t *pvGPIOx,uint8_t PinNumber,uint8_t value);
void GPIO_PortWrite(GPIO_RegDef_t *pvGPIOx,uint8_t PinNumber,uint8_t value);
uint8_t GPIO_PinRead(GPIO_RegDef_t *pvGPIOx,uint8_t PinNumber);
uint16_t GPIO_PortRead(GPIO_RegDef_t *pvGPIOx);
void GPIO_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnDis);
void GPIO_IRQPriorityConfig(uint8_t IRQPriority);
void GPIO_IRQHandler(uint8_t PinNumber);
#endif /* INC_STM32F4XX_GPIO_DRIVER_H_ */
