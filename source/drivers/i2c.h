/*
 * File:	i2c.h
 * Purpose:	Inter-Integrated Circuit
 *
 * Notes:		
 */

#ifndef __I2C_H__
#define __I2C_H__

/******************************************************************************/
// Function prototypes
void i2c_init(void);
void i2c_write_register(uint8 register_address, uint8 data);
void i2c_write_reg2byte(uint8 register_address, uint8 data1, uint8 data2);
void i2c_write_regNsame(uint8 register_address, uint8 data, uint8 n);
uint8 i2c_read_register(uint8 register_address);

/******************************************************************************/
// Config
#define I2C_BAUD_ICR    (0x26) // I2C baud rate config, determine the Divider factor
#define DEVICE_ADDRESS  (0x70)//(0x4c<<1) // the address of the i2c device

/******************************************************************************/
// Definition
#define I2C_CHANNEL     (0) // 0-1
#define I2C_CHAN_PTR    I2C0_BASE_PTR // I2C0_BASE_PTR - I2C1_BASE_PTR

#define I2C_SCL_PCR     PORTB_PCR2
#define I2C_SCL_ALTn    (2)
#define I2C_SDA_PCR     PORTB_PCR3
#define I2C_SDA_ALTn    (2)

/******************************************************************************/
#endif /* __I2C_H__ */
