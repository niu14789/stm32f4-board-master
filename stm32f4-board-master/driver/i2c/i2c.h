/*
 * i2c.h
 *
 *  Created on: 2016年10月24日
 *      Author: YJ-User17
 */

#ifndef DRIVER_I2C_I2C_H_
#define DRIVER_I2C_I2C_H_


////IO��������
//#define   {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9����ģʽ
//#define // {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9���ģʽ
////IO��������
//#define IIC_SCL    PBout(8) //SCL
//#define IIC_SDA    PBout(9) //SDA
//#define READ_SDA   PBin(9)  //����SDA

struct file * i2c_device_open(struct file * filp);

#define   IIC_SCL_0   GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define   IIC_SCL_1     GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define   IIC_SDA_0  GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define   IIC_SDA_1    GPIO_SetBits(GPIOB,GPIO_Pin_9)

#define READ_SDA  (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))


typedef struct dev{
	int (*init)(void);
	void (*start)(void);
	void (*stop)(void);
	unsigned char (*wait_ack)(void);
	void (*ack)(void);
	void (*nack)(void);
	void (*send_byte)(unsigned char);
	unsigned char (*read_byte)(unsigned char);
}dev_i2c_def;

int i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
unsigned char i2c_wait_ack(void);
void i2c_ack(void);
void i2c_nack(void);
void i2c_send_byte(unsigned char txd);
unsigned char i2c_read_byte(unsigned char ack);
void delay_us_i2c(unsigned int t);

#endif /* DRIVER_I2C_I2C_H_ */
