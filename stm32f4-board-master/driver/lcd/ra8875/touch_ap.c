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

/*
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
	
	/* ���� PC7 Ϊ��������ģʽ�����ڴ����ж� */
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
*********************************************************************************************************
*	�� �� ��: bsp_InitTouch
*	����˵��: ����STM32�ʹ�����صĿ��ߣ�ʹ��Ӳ��SPI1, Ƭѡ���������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
// static void TSC2046_InitHard(void)
// {
// /*
// ��1��������STM32-X2, X4 ������ + 3.0����ʾģ�飬 ��ʾģ���ϵĴ���оƬΪ TSC2046�������оƬ
// 	PA8   --> TP_CS
// 	PD3   --> TP_BUSY
// 	PA5   --> TP_SCK
// 	PA6   --> TP_MISO
// 	PA7   --> TP_MOSI
// 	PC7   --> TP_PEN_INT
// */

// 	GPIO_InitTypeDef  GPIO_InitStructure;
// 	SPI_InitTypeDef   SPI_InitStructure;

// 	/* ����GPIOʱ�� */
// 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOI, ENABLE);

// 	/* ���� SPI3 ����ʱ�� */
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

// 	/* ���� PB3��PB4��PB5 Ϊ����������������� SCK, MISO and MOSI */
// 	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
// 	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
// 	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);	
// 	
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
// 	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
// 	GPIO_Init(GPIOB,&GPIO_InitStructure);

// 	/* ���� PI10 ��Ϊ������������� TP_CS  */
// 	TSC2046_CS_1();
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
// 	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
// 	GPIO_Init(GPIOI, &GPIO_InitStructure);

// 	/* ���� PD3 ����Ϊ�������룬���� TP_BUSY */
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
// 	GPIO_Init(GPIOD, &GPIO_InitStructure);


// 	/* ���� SPI1����ģʽ */
// 	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
// 	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
// 	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
// 	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
// 	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
// 	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; 		/* �������Ƭѡ */
// 	/*
// 		SPI_BaudRatePrescaler_64 ��ӦSCKʱ��Ƶ��Լ1M
// 		TSC2046 ��SCKʱ�ӵ�Ҫ�󣬸ߵ�ƽ�͵͵�ƽ��С200ns������400ns��Ҳ����2.5M

// 		ʾ����ʵ��Ƶ��
// 		SPI_BaudRatePrescaler_64 ʱ��SCKʱ��Ƶ��Լ 1.116M
// 		SPI_BaudRatePrescaler_32 ʱ��SCKʱ��Ƶ���� 2.232M
// 	*/
// 	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
// 	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
// 	SPI_InitStructure.SPI_CRCPolynomial = 7;
// 	SPI_Init(SPI1,&SPI_InitStructure);

// 	/* ʹ�� SPI1 */
// 	SPI_Cmd(SPI1,ENABLE);
// }

// /*
// *********************************************************************************************************
// *	�� �� ��: SPI_ShiftByte
// *	����˵��: ��SPI���߷���һ���ֽڣ�ͬʱ���ؽ��յ����ֽ�
// *	��    �Σ���
// *	�� �� ֵ: ��
// *********************************************************************************************************
// */
// static uint8_t SPI_ShiftByte(uint8_t _ucByte)
// {
// 	uint8_t ucRxByte;

// 	/* �ȴ����ͻ������� */
// 	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

// 	/* ����һ���ֽ� */
// 	SPI_I2S_SendData(SPI1, _ucByte);

// 	/* �ȴ����ݽ������ */
// 	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

// 	/* ��ȡ���յ������� */
// 	ucRxByte = SPI_I2S_ReceiveData(SPI1);

// 	/* ���ض��������� */
// 	return ucRxByte;
// }

// /*
// *********************************************************************************************************
// *	�� �� ��: SpiDelay
// *	����˵��: ��SPI���߷���һ���ֽڣ�ͬʱ���ؽ��յ����ֽ�
// *	��    �Σ���
// *	�� �� ֵ: ��
// *********************************************************************************************************
// */
// void SpiDelay(uint32_t DelayCnt)
// {
// 	uint32_t i;

// 	for(i=0;i<DelayCnt;i++);
// }

// /*
// *********************************************************************************************************
// *	�� �� ��: TSC2046_ReadAdc
// *	����˵��: ѡ��һ��ģ��ͨ��������ADC��������ADC�������
// *	��    �Σ�_ucCh = 0 ��ʾXͨ���� 1��ʾYͨ��
// *	�� �� ֵ: 12λADCֵ
// *********************************************************************************************************
// */
// uint16_t TSC2046_ReadAdc(uint8_t _ucCh)
// {
// 	uint16_t usAdc;

// 	TSC2046_CS_0();		/* ʹ��TS2046��Ƭѡ */

// 	/*
// 		TSC2046 �����֣�8Bit��
// 		Bit7   = S     ��ʼλ��������1
// 		Bit6:4 = A2-A0 ģ������ͨ��ѡ��A2-A0; ����6��ͨ����
// 		Bit3   = MODE  ADCλ��ѡ��0 ��ʾ12Bit;1��ʾ8Bit
// 		Bit2   = SER/DFR ģ��������ʽ��  1��ʾ�������룻0��ʾ�������
// 		Bit1:0 = PD1-PD0 ����ģʽѡ��λ
// 	*/
// 	SPI_ShiftByte((1 << 7) | (_ucCh << 4));			/* ѡ��ͨ��1, ����Xλ�� */

// 	/* ��ADC���, 12λADCֵ�ĸ�λ�ȴ���ǰ12bit��Ч�����4bit��0 */
// 	usAdc = SPI_ShiftByte(0x00);		/* ���͵�0x00����Ϊ����ֵ�������� */
// 	usAdc <<= 8;
// 	usAdc += SPI_ShiftByte(0x00);		/* ���12λ��ADC����ֵ */

// 	usAdc >>= 3;						/* ����3λ������12λ��Ч���� */

// 	TSC2046_CS_1();					/* ����Ƭѡ */

// 	return (usAdc);
// }



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

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
