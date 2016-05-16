/*
*********************************************************************************************************
*
*	ģ������ : RA8875оƬ����ģ��������ģ��
*	�ļ����� : LCD_RA8875.h
*	��    �� : V1.6
*	˵    �� : ͷ�ļ�
*
*	Copyright (C), 2010-2011, ���������� www.armfly.com
*
*********************************************************************************************************
*/


#ifndef _LCD_RA8875_H
#define _LCD_RA8875_H

#include "lcd_hw.h"
#include "stm32f4xx.h"

/* ѡ��RA8875�Ľӿ�ģʽ, �����Ӳ��ƥ�� */
//#define IF_SPI_EN			/* SPI�ӿ� */
#define IF_8080_EN		/* 8080 ���߽ӿ� */


#ifdef IF_SPI_EN	/* 4-Wire SPI ���� (��Ҫ�ı�RA8875���ϵ�2������λ��) */
	/*
	��1��������STM32-V5������,STM32F407IGT6
		PD3/LCD_BUSY		--- ����оƬæ       ��RA8875����RA8875оƬ��æ�ź�)
		PF6/LCD_PWM			--- LCD����PWM����  ��RA8875������˽ţ�������RA8875����)

		PI10/TP_NCS			--- ����оƬ��Ƭѡ		(RA8875������SPI�ӿڴ���оƬ��
		PB3/SPI3_SCK		--- ����оƬSPIʱ��		(RA8875������SPI�ӿڴ���оƬ��
		PB4/SPI3_MISO		--- ����оƬSPI������MISO(RA8875������SPI�ӿڴ���оƬ��
		PB5/SPI3_MOSI		--- ����оƬSPI������MOSI(RA8875������SPI�ӿڴ���оƬ��

		PC3/TP_INT			--- ����оƬ�ж� ������RA8875������RA8875������ж�)
	*/
	#define RA8875_CS_0()	GPIOH->BSRRH = GPIO_Pin_6
	#define RA8875_CS_1()	GPIOH->BSRRL = GPIO_Pin_6

	#define SPI_WRITE_DATA	0x00
	#define SPI_READ_DATA	0x40
	#define SPI_WRITE_CMD	0x80
	#define SPI_READ_STATUS	0xC0
#else		/* 8080���� ��������RA8875��ȱʡģʽ�� */
	/*
		������STM32-V5��������߷�����

		PD0/FSMC_D2
		PD1/FSMC_D3
		PD4/FSMC_NOE		--- �������źţ�OE = Output Enable �� N ��ʾ����Ч
		PD5/FSMC_NWE		--- д�����źţ�WE = Output Enable �� N ��ʾ����Ч
		PD8/FSMC_D13
		PD9/FSMC_D14
		PD10/FSMC_D15
		PD13/FSMC_A18		--- ��ַ RS
		PD14/FSMC_D0
		PD15/FSMC_D1

		PE4/FSMC_A20		--- ����Ƭѡһ������
		PE5/FSMC_A21		--- ����Ƭѡһ������
		PE7/FSMC_D4
		PE8/FSMC_D5
		PE9/FSMC_D6
		PE10/FSMC_D7
		PE11/FSMC_D8
		PE12/FSMC_D9
		PE13/FSMC_D10
		PE14/FSMC_D11
		PE15/FSMC_D12

		PG12/FSMC_NE4		--- ��Ƭѡ��TFT, OLED �� AD7606��

		PC3/TP_INT			--- ����оƬ�ж� ������RA8875������RA8875������ж�)

		---- ������ TFT LCD�ӿ������ź� ��FSMCģʽ��ʹ�ã�----
		PD3/LCD_BUSY		--- ����оƬæ       ��RA8875����RA8875оƬ��æ�ź�)
		PF6/LCD_PWM			--- LCD����PWM����  ��RA8875������˽ţ�������RA8875����)

		PI10/TP_NCS			--- ����оƬ��Ƭѡ		(RA8875������SPI�ӿڴ���оƬ��
		PB3/SPI3_SCK		--- ����оƬSPIʱ��		(RA8875������SPI�ӿڴ���оƬ��
		PB4/SPI3_MISO		--- ����оƬSPI������MISO(RA8875������SPI�ӿڴ���оƬ��
		PB5/SPI3_MOSI		--- ����оƬSPI������MOSI(RA8875������SPI�ӿڴ���оƬ��
	*/
	#define RA8875_BASE		((uint32_t)(0x6C000000 | 0x00000000))

	#define RA8875_REG		*(__IO uint16_t *)(RA8875_BASE +  (1 << (6 + 1)))	/* FSMC 16λ����ģʽ�£�FSMC_A18���߶�Ӧ�����ַA19 */
	#define RA8875_RAM		*(__IO uint16_t *)(RA8875_BASE)

	#define RA8875_RAM_ADDR		RA8875_BASE
#endif

enum
{
	RA_FONT_16 = 0,		/* RA8875 ���� 16���� */
	RA_FONT_24 = 1,		/* RA8875 ���� 24���� */
	RA_FONT_32 = 2		/* RA8875 ���� 32���� */
};

/* ���ַŴ���� */
enum
{
	RA_SIZE_X1 = 0,		/* ԭʼ��С */
	RA_SIZE_X2 = 1,		/* �Ŵ�2�� */
	RA_SIZE_X3 = 2,		/* �Ŵ�3�� */
	RA_SIZE_X4 = 3		/* �Ŵ�4�� */
};

/* �ɹ��ⲿģ����õĺ��� */
void RA8875_InitHard(void);
uint16_t RA8875_ReadID(void);
uint8_t RA8875_IsBusy(void);
void RA8875_Layer1Visable(void);
void RA8875_Layer2Visable(void);
void RA8875_DispOn(void);
void RA8875_DispOff(void);
void RA8875_PutPixel(uint16_t _usX, uint16_t _usY, uint16_t _usColor);
void RA8875_SetCursor(uint16_t _usX, uint16_t _usY);
uint16_t RA8875_GetPixel(uint16_t _usX, uint16_t _usY);
void RA8875_SetFrontColor(uint16_t _usColor);
void RA8875_SetBackColor(uint16_t _usColor);
void RA8875_SetFont(uint8_t _ucFontType, uint8_t _ucLineSpace, uint8_t _ucCharSpace);
void RA8875_SetTextZoom(uint8_t _ucHSize, uint8_t _ucVSize);
void RA8875_DispAscii(uint16_t _usX, uint16_t _usY, char *_ptr);
void RA8875_DispStr(uint16_t _usX, uint16_t _usY, char *_ptr);
void RA8875_ClrScr(uint16_t _usColor);
void RA8875_DrawBMP(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t *_ptr);
void RA8875_DrawLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2 , uint16_t _usColor);
void RA8875_DrawRect(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t _usColor);
void RA8875_FillRect(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t _usColor);
void RA8875_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor);
void RA8875_FillCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor);
void RA8875_SetDispWin(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth);
void RA8875_QuitWinMode(void);
void RA8875_CtrlGPO(uint8_t _pin, uint8_t _value);
void RA8875_SetBackLight(uint8_t _bright);

void RA8875_TouchInit(void);
uint16_t RA8875_TouchReadX(void);
uint16_t RA8875_TouchReadY(void);

/* ����UCGUI/emWin�Ľӿں��� */
void BTE_SetTarBlock(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint8_t _ucLayer);
void BTE_SetOperateCode(uint8_t _ucOperate);
void BTE_Start(void);
void BTE_Wait(void);
void RA8875_DrawVLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usY2 , uint16_t _usColor);
void RA8875_DrawHColorLine(uint16_t _usX1 , uint16_t _usY1, uint16_t _usWidth, uint16_t *_pColor);
void RA8875_DrawHLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usColor);
void LCD_ShowString(u16 x,u16 y,u16 x1,u16 y1,u8 f , u8 *tbuf );//30,180,210,16,16,tbuf


void RA8875_InitSPI(void);
void RA8875_Sleep(void);

/* ����3����������ֱ��д�Դ棬��������ͷֱ��DMA����ʾ��. ��֧��SPI�ӿ�ģʽ */
void RA8875_StartDirectDraw(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth);
uint32_t RA8875_GetDispMemAddr(void);
void RA8875_QuitDirectDraw(void);

#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
