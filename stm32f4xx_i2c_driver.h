/*
 * stm32f4xx_i2c_driver.h
 *
 *  Created on: Feb 17, 2025
 *      Author: 35596
 */

#ifndef INC_STM32F4XX_I2C_DRIVER_H_
#define INC_STM32F4XX_I2C_DRIVER_H_
#include "stm32f4xx.h"

#define MAX_RISE_TIME_SM 1000U  //nanoseconds
#define MAX_RISE_TIME_FM 300U   //nanoseconds

#define I2C_START_BIT      8
#define I2C_STOP_BIT       9
#define I2C_ACK_BIT        10
#define I2C_PE_BIT         0          //peripheral enable

#define I2C_SPEED_SM       100000    //STANDARD mode speed
#define I2C_SPEED_FM       400000    //FAST mode speed

#define I2C_FM_DUTY_2      0    //Fast mode duty cycle is 2
#define I2C_FM_DUTY_16_9   1    //Fast mode duty cycle is 16/9

#define I2C_ACK_ENABLE     1
#define I2C_ACK_DISABLE    0

//@i2c_SR1_register flags
typedef enum
{
	SB, 	  //start bit
	ADDR,     //Address sent (master mode)/matched (slave mode)
	BTF,      // Byte transfer finished
	ADD10,    // 10-bit header sent (Master mode)
	STOPF,    // Stop detection (slave mode)
	RxNE,     // Data register not empty (receivers)
	TxE,      // Data register empty (transmitters)
	BERR,     // Bus error
	ARLO,     // Arbitration lost (master mode)
	AF,       // Acknowledge failure
	OVR,      // Overrun/Underrun
	PECERR,   // PEC Error in reception
	Reserved, // must be kept at reset value
	TIMEOUT,  // Timeout or Tlow error
	SMBALERT, // SMBus alert

}I2C_SR1_Flags_t;

typedef struct
{
	uint32_t I2C_scl_speed;             //STANDARD =100kHz, FAST= more than 100 KHz
	uint8_t  I2C_AckControl;  		    //@i2c_modes
	uint8_t  I2C_FM_mode_dutyCycle; 	//@i2c_duty_cycle
	uint8_t  I2C_device_address;        //i2c device address
}I2C_Confg_t;

typedef struct
{
	I2C_RegDef_t *pvI2Cx;
	I2C_Confg_t  I2C_Cfg;
}I2C_handle;

void I2C_Init(I2C_handle *pvI2C_handle);
void I2C_DeInit(I2C_handle *pvI2C_handle);
void I2C_MasterSendData(I2C_handle *pvI2C_handle,uint8_t *pTxBuffer, uint16_t len,uint8_t address);
void I2C_PeriClkCtrl(I2C_RegDef_t *pvI2Cx,uint8_t EnDis);
uint32_t RCC_GetPCLK1Value(void);
uint32_t RCC_GetPLLOutput();
#endif /* INC_STM32F4XX_I2C_DRIVER_H_ */
