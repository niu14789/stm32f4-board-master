/*
*********************************************************************************************************
*
*	ģ������ : ����ʽ����������ģ��
*	�ļ����� : bsp_touch.h
*	��    �� : V1.1
*	˵    �� : ����TS2046оƬ �� RA8875���ô���
*	�޸ļ�¼ :
*		�汾��   ����         ����           ˵��
*       v1.0    2012-12-17   Eric2013  ST�̼���V1.0.2�汾
*       v1.1    2013-02-25   Eric2013  ST�̼���V1.3.0�汾
*
*********************************************************************************************************
*/

#include "stm32f4xx.h"
#include <stdio.h>

#include "bsp_touch.h"
#include "LCD_RA8875.h"
#include "bsp_timer.h"
#include "lcd_hw.h"

#include "fs.h"

float calibration_check( float *param, signed short len);

/*
 *
��1��������STM32-X2������ + 3.0����ʾģ�飬 ��ʾģ���ϵĴ���оƬΪ TSC2046�������оƬ
	PA8   --> TP_CS
	PD3   --> TP_BUSY
	PA5   --> TP_SCK
	PA6   --> TP_MISO
	PA7   --> TP_MOSI
	PC7   --> TP_PEN_INT

��2��������STM32������ + 4.3���7����ʾģ�飨����RA8875оƬ)
	RA8875���ô������ӿڣ����ֱ��ͨ��FSMC����RA8875��ؼĴ������ɡ�

	����2��У׼������У׼�󱣴�2��У׼���ADCֵ��ʵ�ʹ���ʱ������2��ֱ�߷��̼�����Ļ���ꡣ
	У׼�����б���ӿڣ���������Ҫ������ʾ��δ�����湦�ܡ�
	��ҿ����Լ��޸�  TOUCH_SaveParam() �� TOUCH_LoadParam() ��������ʵ�ֱ��湦�ܡ�

*/

/* TSC2046 Ƭѡ */
#define TSC2046_CS_1()	GPIOH->BSRRL = 	GPIO_Pin_6
#define TSC2046_CS_0()	GPIOH->BSRRH = 	GPIO_Pin_6
#define TOUCH_PressValid    GPIO_ReadInputDataBit(GPIOH, GPIO_Pin_6)

/* TSC2046 �ڲ�ADCͨ���� */
#define ADC_CH_X	1		/* Xͨ��������Xλ�� */
#define ADC_CH_Y	5		/* Yͨ��������Yλ�� */


/* ����ģ���õ���ȫ�ֱ��� */
TOUCH_T g_tTP;
TOUCHSL_T g_tTPSL;

//static void TSC2046_InitHard(void);
uint16_t TSC2046_ReadAdc(uint8_t _ucCh);
void TOUCH_LoadParam(void);
void TOUCH_SaveParam(void);
int32_t TOUCH_Abs(int32_t x);

static struct tp_cali_param{
	 float xa;
	 float xb;
	 float ya;
	 float yb;
}tp_cali;


/*
*********************************************************************************************************
*	�� �� ��: bsp_InitTouch
*	����˵��: ����STM32�ʹ�����صĿ��ߣ�ʹ��Ӳ��SPI1, Ƭѡ���������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void TOUCH_InitHard(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;
	 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* ���������費ʹ�� */
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	

	if (g_ChipID == IC_8875)
	{
		RA8875_TouchInit();
	}
	else
	{
	//	TSC2046_InitHard();
	}
}

/*
*********************************************************************************************************
*	�� �� ��: TOUCH_DataFilter
*	����˵��: ��ȡһ������ֵ(x����y)
*             ������ȡXPT2046_READ_TIMES������,����Щ������������,
*             Ȼ��ȥ����ͺ����XPT2046_LOST_VAL����,ȡƽ��ֵ
*	��    �Σ���
*	�� �� ֵ: ����������
*********************************************************************************************************
*/
/* ��ȡ���� */
#define XPT2046_READ_TIMES    5 
/* ����ֵ  */	
#define XPT2046_LOST_VAL      1	  	
uint16_t TOUCH_DataFilter(uint8_t _ucCh)
{
	uint16_t i, j;
	uint16_t buf[XPT2046_READ_TIMES];
	uint16_t usSum;
	uint16_t usTemp;

	/* ��ȡREAD_TIMES������*/
	for(i=0; i < XPT2046_READ_TIMES; i++)
	{
		if (g_ChipID == IC_8875)
	    {
			if(_ucCh == ADC_CH_X)
			{
				buf[i] = RA8875_TouchReadX();
			}
			else
			{
				buf[i] = RA8875_TouchReadY();	
			}
		}
		else
		{
		//	buf[i] = TSC2046_ReadAdc(_ucCh);	
		}	
	}
	
	/* �������� */		 		    
	for(i = 0; i < XPT2046_READ_TIMES - 1; i++)
	{
		for(j = i + 1; j < XPT2046_READ_TIMES; j++)
		{
			if(buf[i] > buf[j])
			{
				usTemp = buf[i];
				buf[i] = buf[j];
				buf[j] = usTemp;
			}
		}
	}
		  
	usSum = 0;

	/*��� */
	for(i = XPT2046_LOST_VAL; i < XPT2046_READ_TIMES - XPT2046_LOST_VAL; i++)
	{
		usSum += buf[i];
	}
	/*��ƽ�� */
	usTemp = usSum / (XPT2046_READ_TIMES - 2 * XPT2046_LOST_VAL);

	return usTemp; 
} 

/*
*********************************************************************************************************
*	�� �� ��: TOUCH_ReadAdcXY
*	����˵��: ����2�ζ�ȡ������IC,�������ε�ƫ��ܳ���
*             ADC_ERR_RANGE,��������,����Ϊ������ȷ,�����������.	   
*             �ú����ܴ�����׼ȷ��
*	��    �Σ�x,y:��ȡ��������ֵ
*	�� �� ֵ: 0,ʧ��;1,�ɹ�
*********************************************************************************************************
*/
/* ��Χ */  
uint8_t ADC_ERR_RANGE = 5; 
uint8_t TOUCH_ReadAdcXY(int16_t *_usX, int16_t *_usY) 
{
	uint16_t iX1, iY1;
 	uint16_t iX2, iY2;
	uint16_t iX, iY;

 	iX1 = TOUCH_DataFilter(ADC_CH_X);
	iY1 = TOUCH_DataFilter(ADC_CH_Y);
	iX2 = TOUCH_DataFilter(ADC_CH_X);
	iY2 = TOUCH_DataFilter(ADC_CH_Y);
	
	iX = TOUCH_Abs(iX1 - iX2);
	iY = TOUCH_Abs(iY1 - iY2); 
	
	/* ǰ�����β�����+-ERR_RANGE�� */  
    if ((iX <= ADC_ERR_RANGE) && (iY <= ADC_ERR_RANGE))
    {       	
		*_usX = (iX1 + iX2) / 2;
		*_usY = (iY1 + iY2) / 2;	

		return 1;
    }
	else 
	{
		return 0;
	}	  
} 

/*
*********************************************************************************************************
*	�� �� ��: TOUCH_Scan
*	����˵��: �������¼������򡣸ú����������Ե��ã�ÿms����1��. �� bsp_Timer.c
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int TOUCH_SCAN(void)
{
	uint8_t s_invalid_count = 0;
	
	if(TOUCH_PressValid == 0)
	{			
		while(!TOUCH_ReadAdcXY(&g_tTP.usAdcNowX, &g_tTP.usAdcNowY)&&s_invalid_count < 20);
		{
			s_invalid_count++;
		}
		if(s_invalid_count >= 20)
		{
			g_tTP.usAdcNowX = -1;
			g_tTP.usAdcNowY = -1;	
		}
		else
		{
			return 0;
		}
	}
	else
	{
		g_tTP.usAdcNowX = -1;
		g_tTP.usAdcNowY = -1;	
	}
	return 1;
}
/*
 *   take the touch x y
 * */
int touch_take( signed short *x, signed short *y)
{
	uint8_t s_invalid_count = 0;

	if(TOUCH_PressValid == 0)
	{
		while(!TOUCH_ReadAdcXY(x,y)&&s_invalid_count < 20);
		{
			s_invalid_count++;
		}
		if(s_invalid_count >= 20)
		{
			*x = -1;
			*y = -1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		*x = -1;
		*y = -1;
	}
	return 1;
}

/*
*********************************************************************************************************
*	�� �� ��: TOUCH_Abs
*	����˵��: �������ֵ
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int32_t TOUCH_Abs(int32_t x)
{
	if (x >= 0)
	{
		return x;
	}
	else
	{
		return -x;
	}
}


/*
*********************************************************************************************************
*	�� �� ��: TOUCH_SaveParam
*	����˵��: ����У׼����	s_usAdcX1 s_usAdcX2 s_usAdcY1 s_usAdcX2
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void TOUCH_SaveParam(void)
{
#if 0
	/* ���������4���������� */
	uint16_t usBuf[5];

	usBuf[0] = g_tTP.usAdcX1;
	usBuf[1] = g_tTP.usAdcY1;

	usBuf[2] = g_tTP.usAdcX2;
	usBuf[3] = g_tTP.usAdcY2;

	usBuf[4] = g_tTP.XYChange;

#endif
}

/*
*********************************************************************************************************
*	�� �� ��: TOUCH_LoadParam
*	����˵��: ��ȡУ׼����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void TOUCH_LoadParam(void)
{
#if 0
	/* ���������5���������� */
	uint16_t usBuf[5];

	/* ReadParamToBuf() */

	g_tTP.usAdcX1 = usBuf[0];
	g_tTP.usAdcY1 = usBuf[1];

	g_tTP.usAdcX2 = usBuf[2];
	g_tTP.usAdcY2 = usBuf[3];


	g_tTP.XYChange = usBuf[4];
#endif
}




int touch_calibration(void)
{
// 	int fd=-1,lcd_fd,ret;
// 	float calibration_t[5];
// 	short touch_tmp[5];
// //	fd = open("/e2prom/calibration.d",__ONLYREAD);

// 	if(fd != ERR)
// 	{
// 		ret = read(fd,(char *)calibration_t,sizeof(calibration_t));
// 		if(ret!=ERR)
// 		{
// 			printf_d("e2prom read ok \n");
// 			if(calibration_t[4] == calibration_check(calibration_t,4))
// 			{
//                printf_d("check_ok\n");
//                tp_cali.xa = calibration_t[0];
//                tp_cali.xb = calibration_t[1];
//                tp_cali.ya = calibration_t[2];
//                tp_cali.yb = calibration_t[3];
//                return OK;
// 			}
// 		}
// 		else
// 			printf_d("e2prom read err ! please calibration again\n");
// 	}
// 	else
// 	  printf_d("can`t find the e2prom,I don`t know how to save and read it\n please calibration again\n");

//     lcd_fd = open("/etc/lcd.d",__ONLYREAD);

//     if(lcd_fd == ERR)
//     {
//     	printf_d("can`t find the lcd device please check\n");
//     	return ERR;
//     }

//     /* clear the lcd pad to white */
//     write(lcd_fd,"clear",6);
//     /* set the circle at 15 15 */
//     write(lcd_fd,"F0",2);
//     /* wait the touch it */
//     while(touch_take(&touch_tmp[0],&touch_tmp[1])!=0);
//     while(touch_take(&touch_tmp[4],&touch_tmp[4])!=1);
// 	/* set the circle at 465 272-15 */
// 	write(lcd_fd,"F1",2);
// 	/* wait the touch it */
// 	while(touch_take(&touch_tmp[2],&touch_tmp[3])!=0);
// 	while(touch_take(&touch_tmp[4],&touch_tmp[4])!=1);
		
	tp_cali.xa = -0.7839721f;///*450.0f/(float)(touch_tmp[2]-touch_tmp[0]);//*/
	tp_cali.xb = 508.1185f;///*15.0f - tp_cali.xa * (float)touch_tmp[0];//*/

	tp_cali.ya = -0.3310533f;///*242.0f/(float)(touch_tmp[3]-touch_tmp[1]);//*/
	tp_cali.yb = 302.6854f;///*15.0f - tp_cali.ya * (float)touch_tmp[1];//*/
	
	return 0;
}

float calibration_check( float *param,signed short len)
{
	float ret = 0 ,i;
	for(i=0;i<len;i++)
	{
		ret+=*param;
		param++;
	}
	return ret;
}

unsigned short change_ad(char xory,short data)
{
	unsigned short tmp;
	if(xory==0) /* x */
	{
		tmp = (unsigned short)((float)data * tp_cali.xa + tp_cali.xb);
	}else /* y */
	{
		tmp = (unsigned short)((float)data * tp_cali.ya + tp_cali.yb);
	}
	return tmp;
}

void touch_test()
{
//	extern void LCD_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor);
	short touch_tmp_x,touch_tmp_y;
	unsigned short touch_now_x,touch_now_y;
	static char flag_a = 1;
	gui_msg_l0 touch_msg;
	static int fd = 0;
	static unsigned short touch_last_x,touch_last_y; 
	if(touch_take(&touch_tmp_x,&touch_tmp_y)==0)
	{
		touch_now_x = change_ad(0,touch_tmp_x);
		touch_now_y = change_ad(1,touch_tmp_y);

		if(touch_now_x>480) touch_now_x = 480;
		if(touch_now_y>272) touch_now_y = 272;
		
		
		if(!fd)
		  fd = open("/dev/queuel0.d",__ONLYREAD);
		
		touch_msg.x_pos = touch_now_x;
		touch_msg.y_pos = touch_now_y;
		if(flag_a)
		{
			flag_a = 0;
			touch_last_x = touch_msg.x_pos;
			touch_last_y = touch_msg.y_pos;
			touch_msg.event_type = onfocus;
			write(fd,(const char *)&touch_msg,sizeof(touch_msg));
		}
//		LCD_DrawCircle(touch_now_x,touch_now_y,2,0x0);
	}
	else
	{
		if(0==flag_a)
		{
			flag_a = 1;
			touch_msg.x_pos = touch_last_x;
			touch_msg.y_pos = touch_last_y;
			touch_msg.event_type = losefocus;
			write(fd,(const char *)&touch_msg,sizeof(touch_msg));
		}
	}
}


/*************************************************************************/












