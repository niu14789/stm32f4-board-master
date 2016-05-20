

#include "stm32f4xx.h"
#include "fs.h"
#include "key.h"
#include "key_gui.h"

struct file_operations key_ops =
{
  key_device_open,
  key_write,
  key_read,
};

struct inode inode_key =
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	&key_ops,
	&key_gui_object,
	NULL,
	key_init,
	"key"
};

FS_REGISTER("/etc/key.d",inode_key);

int key_device_open(struct file * filp)
{
	/* open always ok */
	return 0;
}

int32_t key_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen)
{
	/* open always ok */
	return 0;
}
int32_t key_read(FAR struct file *filp, FAR char *buffer, uint32_t buflen)
{
	static char key_flag = 0;
	if(!KEY0)
	{
	   key_flag = 1;
	}else
	{
	  if(key_flag==1)
	  {
		  key_flag = 0;
		  buffer[0] = 1;
		  return OK;
	  }
	}
	if(!KEY1)
	{
	   key_flag = 2;
	}else
	{
	  if(key_flag==2)
	  {
		  key_flag = 0;
		  buffer[0] = 2;
		  return OK;
	  }
	}
	if(!KEY2)
	{
	   key_flag = 3;
	}else
	{
	  if(key_flag==3)
	  {
		  key_flag = 0;
		  buffer[0] = 3;
		  return OK;
	  }
	}
  return ERR;
}
int key_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* Enable the GPIO_key Clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG|RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure the GPIO_key pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  return 0;
}
