/*
 * stm32f4xx.h
 *
 *  Created on: Jan 24, 2025
 *      Author: 35596
 */

#ifndef INC_STM32F4XX_H_
#define INC_STM32F4XX_H_
#include <stdint.h>

/*Cortex m4 NVIC configurations*/
//ISER register
#define NVIC_ISER0                      ((volatile uint32_t *)0xE000E100)
#define NVIC_ISER1                      ((volatile uint32_t *)0xE000E104)
#define NVIC_ISER2                      ((volatile uint32_t *)0xE000E108)
#define NVIC_ISER3                      ((volatile uint32_t *)0xE000E10C)

//ICER register
#define NVIC_ICER0                      ((volatile uint32_t *)0XE000E180)
#define NVIC_ICER1                      ((volatile uint32_t *)0XE000E184)
#define NVIC_ICER2                      ((volatile uint32_t *)0XE000E188)
#define NVIC_ICER3                      ((volatile uint32_t *)0XE000E18C)

//Priority registers configuration
#define NVIC_PRIO_BASEADDRS             ((volatile uint32_t *)0xE000E400)

#define CM4_INT_PRI_BIT_IMPLEMENTATION  4

#define  IRQ_NO_EXTI0                          6 /*position*/
#define  IRQ_NO_EXTI1                          7
#define  IRQ_NO_EXTI2                          8
#define  IRQ_NO_EXTI3                          9
#define  IRQ_NO_EXTI4                          10
#define  IRQ_NO_EXTI9_5                        23
#define  IRQ_NO_EXTI15_10                      40



/*MCU Memory Addresses*/
#define FLASH_BASEADDRS					0x08000000U /*512KB*/
#define SRAM_BASEADDRS					0x20000000U /*64KB*/
#define ROM_BASEADDRS                   0x1FFF0000U /*System Memory 30KB*/

/*Peripheral Bus Addresses*/
#define PERI_BASEADDRS					0x40000000U
#define APB1_BASEADDRS					PERI_BASEADDRS
#define APB2_BASEADDRS					0x40010000U
#define AHB1_BASEADDRS					0x40020000U
#define AHB2_BASEADDRS					0x50000000U

/*GPIO Bases Addresses*/
#define GPIOA_BASEADDRS					(AHB1_BASEADDRS + 0x0000)
#define GPIOB_BASEADDRS					(AHB1_BASEADDRS + 0x0400)
#define GPIOC_BASEADDRS					(AHB1_BASEADDRS + 0x0800)

/*I2C Bases Addresses*/
#define I2C1_BASEADDRS					(APB1_BASEADDRS + 0x5400)
#define I2C2_BASEADDRS					(APB1_BASEADDRS + 0x5800)
#define I2C3_BASEADDRS					(APB1_BASEADDRS + 0x5C00)

/*SPI Base address*/
#define SPI1_BASEADDRS					(APB2_BASEADDRS + 0x3000)
#define SPI2_BASEADDRS					(APB1_BASEADDRS + 0x3800)
#define SPI3_BASEADDRS					(APB1_BASEADDRS + 0x3C00)
#define SPI4_BASEADDRS					(APB2_BASEADDRS + 0x3400)

/*APB2 Bases Addresses*/
#define EXTI_BASEADDRS					(APB2_BASEADDRS + 0x3C00)

/*RCC Base Address*/
#define RCC_BASEADDRS					(AHB1_BASEADDRS + 0x3800)

/*SYSCFG Base Address*/
#define SYSCFG_BASEADDRS                (APB2_BASEADDRS + 0x3800)

#define NUCLEO_BOARD_F401RE_CLK_SETTING        8000000U //8 MHz MCO ST-Link
#define NUCLEO_BOARD_F401RE_CLK_TIME           125U //nanoseconds (1/NUCLEO_BOARD_CLK_SETTING)

/*Peripheral definition structure*/
//GPIO
typedef struct
{
	volatile uint32_t MODER; 			/*GPIO port mode register, offset 0x00*/
	volatile uint32_t OTYPER;			/*GPIO port output type register, offset 0x04*/
	volatile uint32_t OSPEEDR;			/*GPIO port output speed register, offset 0x08*/
	volatile uint32_t PUPDR;			/*GPIO port pull-up/pull-down register register, offset 0x0C*/
	volatile uint32_t IDR;				/*GPIO port input data register, offset 0x10*/
	volatile uint32_t ODR;				/*GPIO port output data register, offset 0x14*/
	volatile uint32_t BSRR;				/*GPIO port bit set/reset register, offset 0x18*/
	volatile uint32_t LCKR;				/*GPIO port configuration lock register, offset 0x1C*/
	volatile uint32_t AFR[2];			/*AFR[0]: GPIO alternate function low register,  offset 0x20
										  AFR[1]: GPIO alternate function high register, offset 0x24*/
}GPIO_RegDef_t;

#define GPIOA  (GPIO_RegDef_t*)GPIOA_BASEADDRS
#define GPIOB  (GPIO_RegDef_t*)GPIOB_BASEADDRS
#define GPIOC  (GPIO_RegDef_t*)GPIOC_BASEADDRS

//RCC
typedef struct
{
	volatile uint32_t CR;				/*GPIO port mode register, offset 0x00*/
	volatile uint32_t PLLCFGR;		    /*GPIO port mode register, offset 0x04*/
	volatile uint32_t CFGR;		    /*GPIO port mode register, offset 0x08*/
	volatile uint32_t CIR;		    /*GPIO port mode register, offset 0x0C*/
	volatile uint32_t AHB1RSTR;		    /*GPIO port mode register, offset 0x10*/
	volatile uint32_t AHB2RSTR;		    /*GPIO port mode register, offset 0x14*/
	uint32_t RESERVED0[2];		    /*GPIO port mode register, offset 0x1C*/
	volatile uint32_t APB1RSTR;		    /*GPIO port mode register, offset 0x20*/
	volatile uint32_t APB2RSTR;		    /*GPIO port mode register, offset 0x24*/
	uint32_t RESERVED1[2];		    /*GPIO port mode register, offset 0x2C*/
	volatile uint32_t AHB1ENR;		    /*GPIO port mode register, offset 0x30*/
	volatile uint32_t AHB2ENR;		    /*GPIO port mode register, offset 0x34*/
	uint32_t RESERVED2[2];		    /*GPIO port mode register, offset 0x3C*/
	volatile uint32_t APB1ENR;		    /*GPIO port mode register, offset 0x40*/
	volatile uint32_t APB2ENR;		    /*GPIO port mode register, offset 0x44*/
	uint32_t RESERVED3[2];		    /*GPIO port mode register, offset 0x4C*/
	volatile uint32_t AHB1LPENR;		    /*GPIO port mode register, offset 0x50*/
	volatile uint32_t AHB2LPENR;		    /*GPIO port mode register, offset 0x54*/
	uint32_t RESERVED4[2];		    /*GPIO port mode register, offset 0x5C*/
	volatile uint32_t APB1LPENR;		    /*GPIO port mode register, offset 0x60*/
	volatile uint32_t APB2LPENR;		    /*GPIO port mode register, offset 0x64*/
	uint32_t RESERVED5[2];		    /*GPIO port mode register, offset 0x6C*/
	volatile uint32_t BDCR;		    /*GPIO port mode register, offset 0x70*/
	volatile uint32_t CSR;		    /*GPIO port mode register, offset 0x74*/
	uint32_t RESERVED6[2];		    /*GPIO port mode register, offset 0x7C*/
	volatile uint32_t SSCGR;		    /*GPIO port mode register, offset 0x80*/
	volatile uint32_t PLLI2SCFGR;		    /*GPIO port mode register, offset 0x84*/
	uint32_t RESERVED7;		    /*GPIO port mode register, offset 0x88*/
	volatile uint32_t DCKCFGR;		    /*GPIO port mode register, offset 0x8C*/
}RCC_RegDef_t;

#define RCC  ((RCC_RegDef_t*)RCC_BASEADDRS)

//EXTI definition structure
typedef struct
{
	volatile uint32_t EXTI_IMR; //Interrupt mask register
	volatile uint32_t EXTI_EMR; //Event mask register
	volatile uint32_t EXTI_RTSR; //Rising trigger selection register
	volatile uint32_t EXTI_FTSR; //Falling trigger selection register
	volatile uint32_t EXTI_SWIER; //Software interrupt event register
	volatile uint32_t EXTI_PR; //Pending register
}EXTI_RegDef_t;

#define EXTI ((EXTI_RegDef_t*)EXTI_BASEADDRS)

//SYSCFG definition structure
typedef struct
{
	volatile uint32_t SYSCFG_MEMRMP; //SYSCFG memory map register
	volatile uint32_t SYSCFG_PMC; //SYSCFG peripheral mode configuration register
	volatile uint32_t SYSCFG_EXTICR[4]; //SYSCFG external interrupt configuration register 4
	volatile uint32_t SYSCFG_CMPCR; //Compensation cell control register

}SYSCFG_RegDef_t;

#define SYSCFG ((SYSCFG_RegDef_t*)SYSCFG_BASEADDRS)

/*Enable peripheral clock*/
#define GPIOA_PCLK_EN()	(RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()	(RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= (1<<2))
#define SYSCFG_PCLK_EN() (RCC->APB2ENR |= (1<<14))
#define I2C1_PCLK_EN() (RCC->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN() (RCC->APB1ENR |= (1<<22))
#define I2C3_PCLK_EN() (RCC->APB1ENR |= (1<<23))
#define SPI1_PCLK_EN() (RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN() (RCC->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN() (RCC->APB1ENR |= (1<<15))
#define SPI4_PCLK_EN() (RCC->APB2ENR |= (1<<13))

/*Disable peripheral clock*/
#define GPIOA_PCLK_DI()	(RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI()	(RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &= ~(1<<2))
#define SYSCFG_PCLK_DI() (RCC->APB2ENR &= ~(1<<14))
#define I2C1_PCLK_DI() (RCC->APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI() (RCC->APB1ENR &= ~(1<<22))
#define I2C3_PCLK_DI() (RCC->APB1ENR &= ~(1<<23))
#define SPI1_PCLK_DI() (RCC->APB2ENR &= ~(1<<12))
#define SPI2_PCLK_DI() (RCC->APB1ENR &= ~(1<<14))
#define SPI3_PCLK_DI() (RCC->APB1ENR &= ~(1<<15))
#define SPI4_PCLK_DI() (RCC->APB2ENR &= ~(1<<13))

#define ENABLE              1
#define DISABLE             0
#define SET                 ENABLE
#define RESET               DISABLE

#define GPIOA_RESET() do{(RCC->AHB1RSTR |= (1<<0)); (RCC->AHB1RSTR &= ~(1<<0));}while(0)
#define GPIOB_RESET() do{(RCC->AHB1RSTR |= (1<<1)); (RCC->AHB1RSTR &= ~(1<<1));}while(0)
#define GPIOC_RESET() do{(RCC->AHB1RSTR |= (1<<2)); (RCC->AHB1RSTR &= ~(1<<2));}while(0)

//I2C peripheral definition structure
typedef struct
{
	volatile uint32_t I2C_CR1;                         //Address offset: 0x00, I2C Control register 1 (I2C_CR1)
	volatile uint32_t I2C_CR2;                         //Address offset: 0x04, I2C Control register 2 (I2C_CR2)
	volatile uint32_t I2C_OAR1;                        //Address offset: 0x08, I2C Own address register 1(I2C_OAR1)
	volatile uint32_t I2C_OAR2;                        //Address offset: 0x0C, I2C Own address register 2 (I2C_OAR2)
	volatile uint32_t I2C_DR;                          //Address offset: 0x10, I2C Data register (I2C_DR)
	volatile uint32_t I2C_SR1;                         //Address offset: 0x14, I2C Status register 1 (I2C_SR1)
	volatile uint32_t I2C_SR2;                         //Address offset: 0x18, I2C Status register 2 (I2C_SR2)
	volatile uint32_t I2C_CCR;                         //Address offset: 0x1C, I2C Clock control register (I2C_CCR)
	volatile uint32_t I2C_TRISE;                       //Address offset: 0x20, I2C TRISE register (I2C_TRISE)
	volatile uint32_t I2C_FLTR;                        //Address offset: 0x24, I2C FLTR register (I2C_FLTR)

}I2C_RegDef_t;

#define  I2C1 ((I2C_RegDef_t*)I2C1_BASEADDRS)
#define  I2C2 ((I2C_RegDef_t*)I2C2_BASEADDRS)
#define  I2C3 ((I2C_RegDef_t*)I2C3_BASEADDRS)


//SPI peripheral definition structures
typedef struct
{
	volatile uint32_t SPI_CR1;                        //Address offset: 0x00, SPI control register 1 (SPI_CR1)
	volatile uint32_t SPI_CR2;                        //Address offset: 0x04, SPI control register 2 (SPI_CR2)
	volatile uint32_t SPI_SR;                         //Address offset: 0x08, SPI status register (SPI_SR)
	volatile uint32_t SPI_DR;                         //Address offset: 0x0C, SPI data register (SPI_DR)
	volatile uint32_t SPI_CRCPR;                      //Address offset: 0x10, SPI CRC polynomial register (SPI_CRCPR)
	volatile uint32_t SPI_RXCRCR;                     //Address offset: 0x14, SPI RX CRC register (SPI_RXCRCR)
	volatile uint32_t SPI_TXCRCR;                     //Address offset: 0x18, SPI TX CRC register (SPI_TXCRCR)
	volatile uint32_t SPI_I2SCFGR;                    //Address offset: 0x1C, SPI_I2S configuration register (SPI_I2SCFGR)
	volatile uint32_t SPI_I2SPR;                      //Address offset: 0x20, SPI_I2S prescaler register (SPI_I2SPR)
}SPI_RegDef_t;

#define  SPI1 ((SPI_RegDef_t*)SPI1_BASEADDRS)
#define  SPI2 ((SPI_RegDef_t*)SPI2_BASEADDRS)
#define  SPI3 ((SPI_RegDef_t*)SPI3_BASEADDRS)

#endif /* INC_STM32F4XX_H_ */
