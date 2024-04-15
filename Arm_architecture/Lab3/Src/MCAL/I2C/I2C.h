/*
 * I2C.h
 *
 *  Created on: Aug 31, 2023
 *      Author: adham
 */

#ifndef MCAL_I2C_I2C_H_
#define MCAL_I2C_I2C_H_

/****************************INCLUDES*****************************/
#include"../../includes/std_macros.h"
#include"../../includes/std_types.h"
#include"../../includes/stm32_f103_x6.h"
#include"../../MCAL/GPIO/GPIO.h"
/***********************************************************************/

/****************************Slave State ENUM***************************/
typedef enum
{
	I2C_EV_STOP ,
	I2C_EV_ADD_MATCHED,
	I2C_EV_DATA_REQ ,
	I2C_EV_DATA_RCV ,
};


/****************************I2C Slave Address Configuration*************/
typedef struct
{
	uint8_t SLAVE_ADDRESS_MDOE   ; //@ref:I2C_SLAVE_ADDRESS_MODE_SELECT  --> select between 8-bit address mode or 10-bit address mode
	uint8_t EN_DUAL_ADDRESS_MODE ; //@ref:DUAL_ADDRESS_MODE_STATE        --> enable/disable the dual address feature in SLAVE
	uint8_t ADDRESS_ONE			 ; //
	uint8_t ADDRESS_TWO			 ; // Both must be passed in the Application Layer
}I2C_Slave_Address_t;
/***********************************************************************/

/******************************Configuration Structure******************/
typedef struct
{
	uint32_t I2C_CLK_SPEED			                   ; //@ref:I2C_CLK_SPEED_SELECT     --> used to configure the I2C clock speed
	uint8_t  I2C_STRETCH_MODE		                   ; //@ref:I2C_CLK_STRTCH_SELECT    --> used to enable or disable the clock stretching
	uint8_t  I2C_ACK_MODE			                   ; //@ref:I2C_ACK_MODE_SELECT      --> used to configure the I2C controller to generate auto ack after riciving a byte or no
	uint8_t  I2C_GENERAL_CALL_MODE                     ; //@ref:I2C_GEN_CALL_MODE_SELECT --> used to enable or disable the General Call
	uint8_t I2C_MASTER_MODE                            ; //@ref:I2C_MASTER_MODE_SELECT   --> used to configure the I2C mode [SM - FM]
	I2C_Slave_Address_t I2C_ADDRESS                    ;
	void (*callBack)(I2C_Slave_Address_t state) = NULL ;// call back pointer for SLAVE -> works with Interrupt

}I2Cx_Config_t;



/*****************************CONFIGURATION MACROS References************************/
//@ref:I2C_MODE_SELECT
#define I2C_MASTER_MODE			0
#define I2C_SLAVE_MODE			1
//@ref:I2C_ACK_MODE_SELECT
#define I2C_NO_ACK_RET			0
#define I2C_ACK_RET				(1<<10)

#endif /* MCAL_I2C_I2C_H_ */
