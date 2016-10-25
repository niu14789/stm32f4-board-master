/*
 * e2p.c
 *
 *  Created on: 2016骞�10鏈�24鏃�
 *      Author: YJ-User17
 */
#include "fs.h"
#include "i2c.h"
#include "e2p.h"
#include "string.h"

static struct file eeprom_file;

static dev_i2c_def * i2c_dev_p = NULL;

static unsigned short save_addr_default = 0;

static struct file_operations e2p_ops =
{
  e2p_device_open,
  e2p_device_write,
  e2p_device_read
};


static struct inode inode_e2p =
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	&e2p_ops,
	NULL,
	NULL,
	e2p_init,
	"eeprom"
};

FS_REGISTER(FS_EEPROM("eeprom.d"),inode_e2p);


int e2p_init(void)
{
	struct file * fd;

	fd = open(FS_DRV("i2c.d"),__FS_OPEN_EXISTING | __FS_WRITE );

	if(fd != NULL)
	{
		i2c_dev_p = (dev_i2c_def *)fd->f_inode->i_private;
		eeprom_file.f_oflags |= 0x4000;

		if(AT24CXX_Check() == 0)
		{
		   printf_d("eeprom dev init and check ok\n");
	       return OK; //ok
		}else
		{
		   printf_d("eeprom dev init and check fail\n");
		   return ERR; //err
		}
	}else
	{
		printf_d("eeprom : can not find the i2c driver\n");
		return ERR;
	}
}

struct file * e2p_device_open(struct file * filp)
{
	/* open always ok */
	eeprom_file.f_inode = &inode_e2p;
	eeprom_file.f_oflags |= filp->f_oflags;

	if(strstr(filp->f_path,"lcd2_default_cali.bin") != NULL)
	{
		save_addr_default = 0;
		return &eeprom_file;
	}
	else if(strstr(filp->f_path,"lcd1_default_cali.bin") != NULL)
	{
		save_addr_default = 20;
		return &eeprom_file;
	}else
	{
		return NULL;
	}
}

int32_t e2p_device_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen)
{
	 AT24CXX_Write(save_addr_default,(unsigned char *)buffer,buflen);
	 return 0;
}

uint32_t e2p_device_read(FAR struct file *filp, FAR char *buffer, uint32_t buflen)
{
	AT24CXX_Read(save_addr_default,(unsigned char *)buffer,buflen);
	return buflen;
}

/*------------------------------------------------------------------------------*/
void delay_us_e2p(unsigned int t)
{
	t *= 50;
	while(t--);
}

unsigned char AT24CXX_ReadOneByte(unsigned short ReadAddr)
{
	unsigned char temp=0;
    i2c_dev_p->start();//();
	i2c_dev_p->send_byte(0XA0+((ReadAddr/512)<<1));   
	i2c_dev_p->wait_ack();
    i2c_dev_p->send_byte(ReadAddr%512);  
	i2c_dev_p->wait_ack();
	i2c_dev_p->start();//();
	i2c_dev_p->send_byte(0XA1);          
	i2c_dev_p->wait_ack();
    temp=i2c_dev_p->read_byte(0);
    i2c_dev_p->stop();
	return temp;
}


void AT24CXX_WriteOneByte(unsigned short WriteAddr,unsigned char DataToWrite)
{
		i2c_dev_p->start();
		i2c_dev_p->send_byte(0XA0+((WriteAddr/512)<<1));   
		i2c_dev_p->wait_ack();
		i2c_dev_p->send_byte(WriteAddr%512);   
		i2c_dev_p->wait_ack();
		i2c_dev_p->send_byte(DataToWrite);   
		i2c_dev_p->wait_ack();
		i2c_dev_p->stop();
		delay_us_e2p(10000);
}


unsigned char AT24CXX_Check(void)
{
	unsigned char temp;

	temp = AT24CXX_ReadOneByte(511);

	if( temp == 0X5A )
	{
	   return 0;
	}
	else
	{
		AT24CXX_WriteOneByte(511,0X5A);
	    temp=AT24CXX_ReadOneByte(511);
		if( temp == 0X5A )
		{
		   return 0;
		}
	}
	return 1;
}


void AT24CXX_Read(unsigned short ReadAddr,unsigned char *pBuffer,unsigned short NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);
		NumToRead--;
	}
}


void AT24CXX_Write(unsigned short WriteAddr,unsigned char *pBuffer,unsigned short NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}









