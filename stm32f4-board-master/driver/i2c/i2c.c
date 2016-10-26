/*
 * i2c.c
 *
 *  Created on: 2016年10月24日
 *      Author: YJ-User17
 */
#include "stm32f4xx.h"
#include "fs.h"
#include "i2c.h"

static struct file i2c_file;

static struct file_operations i2c_ops =
{
  i2c_device_open,
};

static dev_i2c_def dev_i2c = {
	i2c_init,
	i2c_start,
	i2c_stop,
	i2c_wait_ack,
	i2c_ack,
	i2c_nack,
	i2c_send_byte,
	i2c_read_byte
};

static struct inode inode_i2c =
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	&i2c_ops,
	NULL,
	&dev_i2c,
	i2c_init,
	"i2c"
};

FS_REGISTER(FS_DRV("i2c.d"),inode_i2c);

struct file * i2c_device_open(struct file * filp)
{
	/* open always ok */
	i2c_file.f_inode = &inode_i2c;
	i2c_file.f_oflags = filp->f_oflags;
	i2c_init();
	return &i2c_file;
}

int i2c_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	IIC_SCL_1;//;
	IIC_SDA_1;//;
	inode_i2c.i_flags = __FS_IS_INODE_OK | __FS_IS_INODE_INIT;
	return 0;
}


void delay_us_i2c(unsigned int t)
{
	t *= 50;
	while(t--);
}

void i2c_start(void)
{
	//;
	IIC_SDA_1;//;
	IIC_SCL_1;//;
	delay_us_i2c(4);
 	IIC_SDA_0;//;
	delay_us_i2c(4);
	IIC_SCL_0;//;
}

void i2c_stop(void)
{
	//;
	IIC_SCL_0;//;
	IIC_SDA_0;//;
 	delay_us_i2c(4);
	IIC_SCL_1;//;
	IIC_SDA_1;//;
	delay_us_i2c(4);
}

unsigned char i2c_wait_ack(void)
{
	unsigned char ucErrTime=0;
	IIC_SDA_1;//;delay_us_i2c(1);
	IIC_SCL_1;//;delay_us_i2c(1);
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			i2c_stop();
			return 1;
		}
	}
	IIC_SCL_0;//;
	return 0;
}

void i2c_ack(void)
{
	IIC_SCL_0;//;
	//;
	IIC_SDA_0;//;
	delay_us_i2c(2);
	IIC_SCL_1;//;
	delay_us_i2c(2);
	IIC_SCL_0;//;
}

void i2c_nack(void)
{
	IIC_SCL_0;//;
	//;
	IIC_SDA_1;//;
	delay_us_i2c(2);
	IIC_SCL_1;//;
	delay_us_i2c(2);
	IIC_SCL_0;//;
}

void i2c_send_byte(unsigned char txd)
{
    unsigned char t;
	//;
    IIC_SCL_0;//;
    for(t=0;t<8;t++)
    {
        if((txd&0x80)>>7)
        {
    	   IIC_SDA_1;
        }else
        {
        	 IIC_SDA_0;
        }
        txd<<=1;
		delay_us_i2c(2);
		IIC_SCL_1;//;
		delay_us_i2c(2);
		IIC_SCL_0;//;
		delay_us_i2c(2);
    }
}

unsigned char i2c_read_byte(unsigned char ack)
{
	unsigned char i,receive=0;

		for(i=0;i<8;i++ )
		{
			IIC_SCL_0;//;
			delay_us_i2c(2);
			IIC_SCL_1;//;
			receive<<=1;
			if(READ_SDA)receive++;
			delay_us_i2c(1);
		}
		if (!ack)
				i2c_nack();
		else
				i2c_ack();
    return receive;
}





























