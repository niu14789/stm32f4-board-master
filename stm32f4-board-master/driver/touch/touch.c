/*
 * touch.c
 *
 *  Created on: 2016锟斤拷10锟斤拷12锟斤拷
 *      Author: Administrator
 */

#include "stm32f4xx.h"
#include "fs.h"
#include "touch.h"

#include "gui_config.h"

struct file * touch2_device_open(struct file * filp);

static struct file touch_file;

#define  CMD_RDX (0xD0)
#define  CMD_RDY (0x90)

struct file_operations touch2_ops =
{
  touch2_device_open,
};
struct inode inode_touch2 =
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	&touch2_ops,
	NULL,
	NULL,
	touch2_init,
	"touch2"
};

FS_REGISTER(FS_INPUT("touch2.d"),inode_touch2);

struct file * touch2_device_open(struct file * filp)
{
	touch_file.f_inode = &inode_touch2;
	if(OK == touch2_init())
	{
		return &touch_file;
	}else
	{
		return NULL;
	}
	/* open always ok */
}

int touch2_init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	
	if(inode_touch2.i_flags & __FS_IS_INODE_INIT)
	{
		if(inode_touch2.i_flags & __FS_IS_INODE_OK)
		{
			return OK;//has been inited
		}else
		{
			return ERR;//but fail
		}
	}

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOH, ENABLE);//使锟斤拷GPIOB,C,F时锟斤拷

	//GPIOB1,2锟斤拷始锟斤拷锟斤拷锟斤拷
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8;//PB1/PB2 锟斤拷锟斤拷为锟斤拷锟斤拷锟斤拷锟斤拷
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//锟斤拷锟斤拷模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//锟斤拷锟斤拷锟斤拷锟�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//锟斤拷锟斤拷
	GPIO_Init(GPIOH, &GPIO_InitStructure);//锟斤拷始锟斤拷

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PB0锟斤拷锟斤拷为锟斤拷锟斤拷锟斤拷锟�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//锟斤拷锟侥Ｊ�
	GPIO_Init(GPIOB, &GPIO_InitStructure);//锟斤拷始锟斤拷

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PC13锟斤拷锟斤拷为锟斤拷锟斤拷锟斤拷锟�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//锟斤拷锟侥Ｊ�
	GPIO_Init(GPIOF, &GPIO_InitStructure);//锟斤拷始锟斤拷

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PF11锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//锟斤拷锟侥Ｊ�
	GPIO_Init(GPIOH, &GPIO_InitStructure);//锟斤拷始锟斤拷

	gui_touch_dev_register(gui_dev_ops_g()->gui_device_msg.xsize,
			               gui_dev_ops_g()->gui_device_msg.ysize,
						   read_ad_x,
						   read_ad_y);
	inode_touch2.i_flags =  __FS_IS_INODE_OK|__FS_IS_INODE_INIT;
   return 0;
}

#define PEN  		(GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_6))//PHin(6)  	//T_PEN
#define DOUT 		(GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_8))//PHin(8)   	//T_MISO

unsigned short read_ad_x(void)
{
	if(PEN==0)
	{
	    return TP_Read_XOY(CMD_RDY);
	}
	else
	{
		return 0;
	}
}
unsigned short read_ad_y(void)
{
	if(PEN==0)
	{
	    return TP_Read_XOY(CMD_RDX);
	}
	else
	{
		return 0;
	}
}


//#define TDIN 		PHout(7)  	//T_MOSI
//#define TCLK 		PBout(0)  	//T_SCK
//#define TCS  		PFout(11)  	//T_CS

u16 TP_Read_AD(u8 CMD)
{
	u8 count=0;
	u16 Num=0;
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);//TCLK=0;		//先拉低时钟
	GPIO_ResetBits(GPIOH,GPIO_Pin_7);//TDIN=0; 	//拉低数据线
	GPIO_ResetBits(GPIOF,GPIO_Pin_11);//TCS=0; 		//选中触摸屏IC
	TP_Write_Byte(CMD);//发送命令字
	delay_us(6);//ADS7846的转换时间最长为6us
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);//TCLK=0;
	delay_us(1);
	GPIO_SetBits(GPIOB,GPIO_Pin_0);//TCLK=1;		//给1个时钟，清除BUSY
	delay_us(1);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);//TCLK=0;
	for(count=0;count<16;count++)//读出16位数据,只有高12位有效
	{
		Num<<=1;
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);//TCLK=0;	//下降沿有效
		delay_us(1);
		GPIO_SetBits(GPIOB,GPIO_Pin_0);//TCLK=1;
 		if(DOUT)Num++;
	}
	Num>>=4;   	//只有高12位有效.
	GPIO_SetBits(GPIOF,GPIO_Pin_11);//TCS=1;		//释放片选
	return(Num);
}

#define READ_TIMES 5 	//读取次数
#define LOST_VAL 1	  	//丢弃值
unsigned short TP_Read_XOY(u8 xy)
{
	unsigned short i, j;
	unsigned short buf[READ_TIMES];
	unsigned short sum=0;
	unsigned short temp;
	for(i=0;i<READ_TIMES;i++)buf[i]=TP_Read_AD(xy);
	for(i=0;i<READ_TIMES-1; i++)//排序
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//升序排列
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;
}


void TP_Write_Byte(u8 num)
{
	u8 count=0;
	for(count=0;count<8;count++)
	{
		if(num&0x80)
			GPIO_SetBits(GPIOH,GPIO_Pin_7);//TDIN=1;
		else
			GPIO_ResetBits(GPIOH,GPIO_Pin_7);//TDIN=0;
		num<<=1;
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);//TCLK=0;
		delay_us(1);
		GPIO_SetBits(GPIOB,GPIO_Pin_0);//TCLK=1;		//上升沿有效
	}
}

u8 TP_Read_XY(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;
	xtemp=TP_Read_XOY(CMD_RDX);
	ytemp=TP_Read_XOY(CMD_RDY);
	//if(xtemp<100||ytemp<100)return 0;//读数失败
	*x=xtemp;
	*y=ytemp;
	return 1;//读数成功
}


void delay_us(unsigned int t)
{
	t *= 50;
	while(t--);
}

#define ERR_RANGE 50 //误差范围
u8 TP_Read_XY2(u16 *x,u16 *y)
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;
    flag=TP_Read_XY(&x1,&y1);
    if(flag==0)return(0);
    flag=TP_Read_XY(&x2,&y2);
    if(flag==0)return(0);
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前后两次采样在+-50内
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;
}

u8 TP_Scan(u8 tp)
{
	static unsigned short x,y;
	static struct file *fd = NULL;
	static int flag = 0;
	gui_msg_l0 touch_msg;
	
	if(fd == NULL)
		fd = open("/dev/queuel0.d",__FS_OPEN_EXISTING | __FS_WRITE);
	
	if(flag)
	{
		touch_msg.x_pos = 25;
		touch_msg.y_pos = 25;
		touch_msg.event_type = onfocus;
		write(fd,(const char *)&touch_msg,sizeof(touch_msg));
	}else
	{
		touch_msg.x_pos = 25;
		touch_msg.y_pos = 25;
		touch_msg.event_type = losefocus;
		write(fd,(const char *)&touch_msg,sizeof(touch_msg));
	}
	flag ^= 1;
	
	if(PEN==0)//有按键按下
	{
		TP_Read_XY2(&x,&y);//读取物理坐标
	}
	return 0;
}


void exit_interrupt_init( void )// PH6
{
  GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd =GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6;
	GPIO_Init(GPIOH,&GPIO_InitStructure);
	
	EXTI_ClearITPendingBit(EXTI_Line6);
  EXTI_InitStruct.EXTI_Line=EXTI_Line6;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOH,EXTI_PinSource6);
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


void EXTI9_5_IRQHandler(void)
{
	 TP_Scan(1);
	 EXTI_ClearITPendingBit( EXTI_Line6 );
}








