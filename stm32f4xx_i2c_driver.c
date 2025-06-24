/*
 * stm32f4xx_i2c_driver.c
 *
 *  Created on: Feb 17, 2025
 *      Author: 35596
 */
#include "stm32f4xx_i2c_driver.h"

static uint8_t I2C_checkFlags(I2C_RegDef_t *pvI2Cx,I2C_SR1_Flags_t flag);
static void I2C_GenerateStartCondition(I2C_RegDef_t *pvI2Cx);
static void I2C_ExecuteAddressphase(I2C_RegDef_t *pvI2Cx,uint8_t address);
static void I2C_ClearADDRFlag(I2C_RegDef_t *pvI2Cx);
static void I2C_GenerateStopCondition(I2C_RegDef_t *pvI2Cx);

static uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
static uint16_t APB1_PreScaler[4] = {2,4,8,16};

void I2C_Init(I2C_handle *pvI2C_handle)
{
	uint32_t tempreg = 0;
	uint16_t ccr_value = 0;

	//enable the clock for i2c peripheral
	I2C_PeriClkCtrl(pvI2C_handle->pvI2Cx,ENABLE);

	//ack control bit
	tempreg |= pvI2C_handle->I2C_Cfg.I2C_AckControl << 10;
	pvI2C_handle->pvI2Cx->I2C_CR1 = tempreg;

	//configure FREQ field of CR2
	tempreg = 0;
	tempreg |= RCC_GetPCLK1Value() / 1000000U;
	pvI2C_handle->pvI2Cx->I2C_CR2 = (tempreg & 0x3F);

	//program the device own address
	tempreg=0;
	tempreg |= (pvI2C_handle->I2C_Cfg.I2C_device_address << 1);
	tempreg |= (1<<14);//refer bit field 14 of OAR1 reg
	pvI2C_handle->pvI2Cx->I2C_OAR1 = tempreg;

 	//CCR calculations
	tempreg = 0;
	if(pvI2C_handle->I2C_Cfg.I2C_scl_speed <= I2C_SPEED_SM)
	{
		//standard mode
		ccr_value = RCC_GetPCLK1Value() / (2 * pvI2C_handle->I2C_Cfg.I2C_scl_speed);
		tempreg |= ( ccr_value & 0xFFF);
	}
	else
	{
		//fast mode
		tempreg |= (1<<15);
		tempreg |= (pvI2C_handle->I2C_Cfg.I2C_FM_mode_dutyCycle << 14);
		if(pvI2C_handle->I2C_Cfg.I2C_FM_mode_dutyCycle == I2C_FM_DUTY_2)
		{
			ccr_value = RCC_GetPCLK1Value() / (3 * pvI2C_handle->I2C_Cfg.I2C_scl_speed);
		}
		else
		{
			ccr_value = RCC_GetPCLK1Value() / (25 * pvI2C_handle->I2C_Cfg.I2C_scl_speed);
		}
		tempreg |= ( ccr_value & 0xFFF);
	}
	pvI2C_handle->pvI2Cx->I2C_CCR = tempreg;

	//TRISE calculation
	tempreg = 0;
	if(pvI2C_handle->I2C_Cfg.I2C_scl_speed <= I2C_SPEED_SM)
	{
		//standard mode
		tempreg = (RCC_GetPCLK1Value() / (1000000))+1;
	}
	else
	{
		//FAST mode
		tempreg = ((RCC_GetPCLK1Value()*300) / (1000000000))+1;
	}
	pvI2C_handle->pvI2Cx->I2C_TRISE = (tempreg & 0x3F);
}
void I2C_MasterSendData(I2C_handle *pvI2C_handle,uint8_t *pTxBuffer, uint16_t len,uint8_t address)
{
	//Generate start condition
	I2C_GenerateStartCondition(pvI2C_handle->pvI2Cx);

	//wait for SB flag to be set
	while(!I2C_checkFlags(pvI2C_handle->pvI2Cx,SB));

	// write address to the DR register
	//7-bit address and set write bit for master transmission
	I2C_ExecuteAddressphase(pvI2C_handle->pvI2Cx,address);

	//Reading I2C_SR2 after reading I2C_SR1 clears the ADDR flag, even if the ADDR flag was
	//set after reading I2C_SR1.
	while(!I2C_checkFlags(pvI2C_handle->pvI2Cx,ADDR));

	I2C_ClearADDRFlag(pvI2C_handle->pvI2Cx);

	//shift register and data register empty
	//write the data to data register
	while(len)
	{

		while(!I2C_checkFlags(pvI2C_handle->pvI2Cx,TxE));
		pvI2C_handle->pvI2Cx->I2C_DR = *pTxBuffer;
		pTxBuffer++;
		len--;
	}

	while(!I2C_checkFlags(pvI2C_handle->pvI2Cx,TxE));
	//byte transmission finished
	while(!I2C_checkFlags(pvI2C_handle->pvI2Cx,BTF));
	//Give stop condition
	I2C_GenerateStopCondition(pvI2C_handle->pvI2Cx);
}

static void I2C_GenerateStartCondition(I2C_RegDef_t *pvI2Cx)
{
	//Generate start condition
	pvI2Cx->I2C_CR1 |= (1 << I2C_START_BIT);

}
static void I2C_GenerateStopCondition(I2C_RegDef_t *pvI2Cx)
{
	//Generate start condition
	pvI2Cx->I2C_CR1 |= (1 << I2C_STOP_BIT);

}
static void I2C_ExecuteAddressphase(I2C_RegDef_t *pvI2Cx,uint8_t address)
{
	address |= (address<<1);
	address &= ~(1);
	pvI2Cx->I2C_DR |= address;
}

static void I2C_ClearADDRFlag(I2C_RegDef_t *pvI2Cx)
{
	uint32_t dummyRead = pvI2Cx->I2C_SR1;
	dummyRead = pvI2Cx->I2C_SR2;
	(void)dummyRead;
}
static uint8_t I2C_checkFlags(I2C_RegDef_t *pvI2Cx,I2C_SR1_Flags_t flag)
{
	if (pvI2Cx->I2C_SR1 & (1<<flag))
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}
void I2C_PeriClkCtrl(I2C_RegDef_t *pvI2Cx,uint8_t EnDis)
{
	if(EnDis == ENABLE)
	{
		if( pvI2Cx == I2C1 )
		{
			I2C1_PCLK_EN();
		}
		else if( pvI2Cx == I2C2 )
		{
			I2C2_PCLK_EN();
		}
		else if( pvI2Cx == I2C3 )
		{
			I2C3_PCLK_EN();
		}
	}
	else
	{
		if( pvI2Cx == I2C1 )
		{
			I2C1_PCLK_DI();
		}
		else if( pvI2Cx == I2C2 )
		{
			I2C2_PCLK_DI();
		}
		else if( pvI2Cx == I2C3 )
		{
			I2C3_PCLK_DI();
		}
	}
}
/*
 * Refer https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf
 * MCO from ST-LINK: MCO output of ST-LINK MCU is used as an input clock. This
 * frequency cannot be changed, it is fixed at 8 MHz and connected to
 * PF0/PD0/PH0-OSC_IN of the STM32 microcontroller.
 * The following configuration is needed:
 * – SB55 OFF and SB54 ON
 * – SB16 and SB50 ON
 * – R35 and R37 removed
 *
 * This function calculates the APB1 clock connected to I2C peripheral
 */

uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1=0,SystemClk=0;
	uint8_t clksrc=0,temp = 0;
	uint16_t ahbp = 0, apb1 = 0;

	//read system clock source
	clksrc = ((RCC->CFGR >> 2) & 0x3);
	if(clksrc == 0)
	{
		SystemClk = 16000000; //source is HSI
	}
	else if(clksrc == 1)
	{
		SystemClk = 8000000; //source is HSE
	}
	else if(clksrc == 2)
	{
		SystemClk = RCC_GetPLLOutput();// source is PLL
	}
	//read ahbp pre-scaler value
	temp = ((RCC->CFGR >> 4) & 0xF);
	if(temp<8)
	{
		ahbp = 1;
	}
	else
	{
		ahbp = AHB_PreScaler[temp-8];
	}

	//read apb1 pre-scaler value
	temp = ((RCC->CFGR >> 10) & 0x7);
	if(temp<4)
	{
		apb1 = 1;
	}
	else
	{
		apb1 = APB1_PreScaler[temp-4];
	}

	pclk1 = ((SystemClk/ahbp)/apb1);
	return pclk1;
}
/*
 * Not implemented
 */
uint32_t RCC_GetPLLOutput()
{
	return 0;
}
