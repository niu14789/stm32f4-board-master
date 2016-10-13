/*
 * touch.c
 *
 *  Created on: 2016��10��12��
 *      Author: Administrator
 */

#include "stm32f4xx.h"
#include "fs.h"
#include "touch.h"

struct inode inode_touch2 =
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	NULL,
	NULL,
	NULL,
	touch2_init,
	"touch2"
};

FS_REGISTER(FS_INPUT("touch2.d"),inode_touch2);


int touch2_init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOH, ENABLE);//ʹ��GPIOB,C,Fʱ��

	//GPIOB1,2��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8;//PB1/PB2 ����Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOH, &GPIO_InitStructure);//��ʼ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PB0����Ϊ�������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���ģʽ
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PC13����Ϊ�������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���ģʽ
	GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PF11�����������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���ģʽ
	GPIO_Init(GPIOH, &GPIO_InitStructure);//��ʼ��

//
//	TP_Read_XY(&tp_dev.x[0],&tp_dev.y[0]);//��һ�ζ�ȡ��ʼ��
//	AT24CXX_Init();		//��ʼ��24CXX
//	if(TP_Get_Adjdata())return 0;//�Ѿ�У׼
//	else			   //δУ׼?
//	{
//		LCD_Clear(WHITE);//����
//		TP_Adjust();  	//��ĻУ׼
//		TP_Save_Adjdata();
//	}
//	TP_Get_Adjdata();

   return 0;
}























