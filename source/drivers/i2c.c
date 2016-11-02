/*
 * File:	i2c.c
 * Purpose:	Inter-Integrated Circuit
 *
 * Notes:		
 */

#include "common.h"
#include "i2c.h"
/******************************************************************************/
/*!
 * I2C Initialization
 * Set Baud Rate and turn on I2C0
 */
void i2c_init(void)
{
    // open the clock gate
#if(0==I2C_CHANNEL)
    SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;
#elif(1==I2C_CHANNEL)
    SIM_SCGC4 |= SIM_SCGC4_I2C1_MASK;
#else
#error "Definition I2C_CHANNEL ERROR ! "
#endif
    
    /* configure the port for I2C function */
    I2C_SCL_PCR = PORT_PCR_MUX(I2C_SCL_ALTn);
    I2C_SDA_PCR = PORT_PCR_MUX(I2C_SDA_ALTn);
    
    /* set MULT and ICR */
    I2C_F_REG(I2C_CHAN_PTR) = I2C_F_MULT(0x01) | I2C_F_ICR(I2C_BAUD_ICR);
    
    /* enable I2C */
    I2C_C1_REG(I2C_CHAN_PTR) = I2C_C1_IICEN_MASK;
}

/******************************************************************************/
#define i2c_Start()             {I2C_C1_REG(I2C_CHAN_PTR) |= I2C_C1_TX_MASK;\
                                 I2C_C1_REG(I2C_CHAN_PTR) |= I2C_C1_MST_MASK;}

#define i2c_Stop()              {I2C_C1_REG(I2C_CHAN_PTR) &= ~I2C_C1_MST_MASK;\
                                 I2C_C1_REG(I2C_CHAN_PTR) &= ~I2C_C1_TX_MASK;}

#define i2c_Wait()              {while((I2C_S_REG(I2C_CHAN_PTR) & I2C_S_IICIF_MASK)==0);\
                                 I2C_S_REG(I2C_CHAN_PTR) |= I2C_S_IICIF_MASK;}

#define i2c_write_byte(data)    I2C_D_REG(I2C_CHAN_PTR) = (data);

#define i2c_read_byte(data)     data = I2C_D_REG(I2C_CHAN_PTR);

#define i2c_RepeatedStart()     I2C_C1_REG(I2C_CHAN_PTR) |= I2C_C1_RSTA_MASK;

#define i2c_DisableAck()        I2C_C1_REG(I2C_CHAN_PTR) |= I2C_C1_TXAK_MASK;

#define i2c_EnterRxMode()       {I2C_C1_REG(I2C_CHAN_PTR) &= ~I2C_C1_TX_MASK;\
                                 I2C_C1_REG(I2C_CHAN_PTR) &= ~I2C_C1_TXAK_MASK;}

/******************************************************************************/
void i2c_write_register(uint8 register_address, uint8 data)
{
    /* start */
    i2c_Start();
    /* send data to slave */
    i2c_write_byte(DEVICE_ADDRESS & 0xfe);
    i2c_Wait();
    /* Write Register Address */
    i2c_write_byte(register_address);
    i2c_Wait();
    /* Write data */
    i2c_write_byte(data);
    i2c_Wait();
    /* stop */
    i2c_Stop();
    Delay_T3_uS(50);
}

/******************************************************************************/
void i2c_write_reg2byte(uint8 register_address, uint8 data1, uint8 data2)
{
    /* start */
    i2c_Start();
    /* send data to slave */
    i2c_write_byte(DEVICE_ADDRESS & 0xfe);
    i2c_Wait();
    /* Write Register Address */
    Delay_T3_uS(500);
    i2c_write_byte(register_address);
    i2c_Wait();
    /* Write data */
    i2c_write_byte(data1);
    i2c_Wait();
    /* Write data */
    i2c_write_byte(data2);
    i2c_Wait();
    /* stop */
    i2c_Stop();
    Delay_T3_uS(50);
}

/******************************************************************************/
void i2c_write_regNsame(uint8 register_address, uint8 data, uint8 n)
{
    /* start */
    i2c_Start();
    /* send data to slave */
    i2c_write_byte(DEVICE_ADDRESS & 0xfe);
    i2c_Wait();
    /* Write Register Address */
    i2c_write_byte(register_address);
    i2c_Wait();
    /* Write data */
    while(n--)
    {
        i2c_write_byte(data);
        i2c_Wait();
    }
    /* stop */
    i2c_Stop();
    Delay_T3_uS(50);
}

/******************************************************************************/
uint8 i2c_read_register(uint8 register_address)
{
    uint8 rec_data;
    /* start */
    i2c_Start();
    /* Send Slave Address */
    i2c_write_byte(DEVICE_ADDRESS & 0xfe);
    i2c_Wait();
    /* Write Register Address */
    i2c_write_byte(register_address);
    i2c_Wait();
    /* Do a repeated start */
    i2c_RepeatedStart();
    /* Send Slave Address */
    i2c_write_byte(DEVICE_ADDRESS | 0x01);
    i2c_Wait();
    /* Put in Rx Mode */
    i2c_EnterRxMode();
    /* Turn off ACK since this is second to last byte being read*/
    i2c_DisableAck();
    /* Dummy read */
    i2c_read_byte(rec_data); 
    i2c_Wait();
    /* Send stop since about to read last byte */
    i2c_Stop();
    /* Read byte */
    i2c_read_byte(rec_data);
    Delay_T3_uS(50);
    
    return rec_data;
}

/******************************************************************************/
