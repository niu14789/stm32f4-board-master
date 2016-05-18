/*
*********************************************************************************************************
*
*	模块名称 : 电阻式触摸板驱动模块
*	文件名称 : bsp_touch.h
*	版    本 : V1.0
*	说    明 : 头文件
*	修改记录 :
*		版本号  日期         作者    说明
*		v1.0    2012-12-17  Eric2013  ST固件库V1.0.2版本。
*	
*   QQ超级群：216681322
*   UCOS&UCGUI论坛：http://bbs.armfly.com/thread.php?fid=12
*   BLOG: http://blog.sina.com.cn/u/2565749395
*
*********************************************************************************************************
*/

#ifndef __BSP_TOUCH_H
#define __BSP_TOUCH_H

typedef struct
{
	
	int16_t usAdcNowX;
	int16_t usAdcNowY;
	
}TOUCH_T;

extern TOUCH_T g_tTP;

typedef struct
{
	int16_t usAdcX1;
	int16_t usAdcX2;
	int16_t usAdcY1;
	int16_t usAdcY2;
	int16_t XYChange;
	
}TOUCHSL_T;

extern TOUCHSL_T g_tTPSL;

/* 触摸事件 */
enum
{
	TOUCH_NONE = 0,		/* 无触摸 */
	TOUCH_DOWN = 1,		/* 按下 */
	TOUCH_MOVE = 2,		/* 移动 */
	TOUCH_RELEASE = 3	/* 释放 */
};

/* 供外部调用的函数声明 */
void TOUCH_InitHard(void);

int TOUCH_SCAN(void);

#endif


