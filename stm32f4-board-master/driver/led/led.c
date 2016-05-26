

#include "stm32f4xx.h"
#include "fs.h"

#include "led_gui.h"

int led_device_open(struct file * filp);
int32_t led_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen);
int led_init(void);

struct file_operations led_ops =
{
  led_device_open,
  led_write
};

struct inode inode_led = 
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	&led_ops,
	&led_gui_object,
	NULL,
	led_init,
	"led"
};

FS_REGISTER(FS_DEVICE("led.d"),inode_led);

int led_device_open(struct file * filp)
{
	/* open always ok */
	return 0;
}

int32_t led_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen)
{
	if(*buffer == '1')
	{
		GPIO_SetBits(GPIOG,GPIO_Pin_6|GPIO_Pin_7);
	}else if(*buffer == '2')
	{
		GPIO_ResetBits(GPIOG,GPIO_Pin_6);
	}else if(*buffer == '3')
	{
		GPIO_ResetBits(GPIOG,GPIO_Pin_7);
	}
	else
	{
		GPIO_SetBits(GPIOG,GPIO_Pin_6|GPIO_Pin_7);
	}
	/* open always ok */
	return 0;
}
/*

  开发板有三个LED灯，其中一个为红色的电源灯
	剩下的两个可用程序控制，连接的IO为PG6（蓝色）DS0PG7（翠绿色）DS1
	
*/
int led_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Enable the GPIO_LED Clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	return OK;
}

