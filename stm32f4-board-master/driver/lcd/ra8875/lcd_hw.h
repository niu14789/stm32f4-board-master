/*
*********************************************************************************************************
*
*	模块名称 : TFT液晶显示器驱动模块
*	文件名称 : LCD_tft_lcd.h
*	版    本 : V2.0
*	说    明 : 头文件
*
*	Copyright (C), 2010-2011, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/


#ifndef _BSP_TFT_LCD_H
#define _BSP_TFT_LCD_H

/* 定义LCD显示区域的分辨率 */
#define LCD_30_HEIGHT	240		/* 3.0寸宽屏 高度，单位：像素 */
#define LCD_30_WIDTH	400		/* 3.0寸宽屏 宽度，单位：像素 */

#define LCD_43_HEIGHT	272		/* 4.3寸宽屏 高度，单位：像素 */
#define LCD_43_WIDTH	480		/* 4.3寸宽屏 宽度，单位：像素 */

#define LCD_70_HEIGHT	480		/* 7.0寸宽屏 高度，单位：像素 */
#define LCD_70_WIDTH	800		/* 7.0寸宽屏 宽度，单位：像素 */

/* 支持的驱动芯片ID */
enum
{
	IC_5420		= 0x5420,
	IC_4001		= 0x4001,
	IC_61509 	= 0xB509,
	IC_8875 	= 0x0075
};

#define CHIP_STR_5420	"SPFD5420A"
#define CHIP_STR_4001	"OTM4001A"
#define CHIP_STR_61509	"R61509V"
#define CHIP_STR_8875	"RA8875"

/*
	LCD 颜色代码，CL_是Color的简写
	16Bit由高位至低位， RRRR RGGG GGGB BBBB

	下面的RGB 宏将24位的RGB值转换为16位格式。
	启动windows的画笔程序，点击编辑颜色，选择自定义颜色，可以获得的RGB值。

	推荐使用迷你取色器软件获得你看到的界面颜色。
*/
#define RGB(R,G,B)	(((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))	/* 将8位R,G,B转化为 16位RGB565格式 */
#define RGB565_R(x)  ((x >> 8) & 0xF8)
#define RGB565_G(x)  ((x >> 3) & 0xFC)
#define RGB565_B(x)  ((x << 3) & 0xF8)
enum
{
	CL_WHITE        = RGB(255,255,255),	/* 白色 */
	CL_BLACK        = RGB(  0,  0,  0),	/* 黑色 */
	CL_RED          = RGB(255,	0,  0),	/* 红色 */
	CL_GREEN        = RGB(  0,255,  0),	/* 绿色 */
	CL_BLUE         = RGB(  0,	0,255),	/* 蓝色 */
	CL_YELLOW       = RGB(255,255,  0),	/* 黄色 */

	CL_GREY			= RGB( 98, 98, 98), 	/* 深灰色 */
	CL_GREY1		= RGB( 150, 150, 150), 	/* 浅灰色 */
	CL_GREY2		= RGB( 180, 180, 180), 	/* 浅灰色 */
	CL_GREY3		= RGB( 200, 200, 200), 	/* 最浅灰色 */
	CL_GREY4		= RGB( 230, 230, 230), 	/* 最浅灰色 */

	CL_BUTTON_GREY	= RGB( 220, 220, 220), /* WINDOWS 按钮表面灰色 */

	CL_MAGENTA      = 0xF81F,	/* 红紫色，洋红色 */
	CL_CYAN         = 0x7FFF,	/* 蓝绿色，青色 */

	CL_BLUE1        = RGB(  0,  0, 240),		/* 深蓝色 */
	CL_BLUE2        = RGB(  0,  0, 128),		/* 深蓝色 */
	CL_BLUE3        = RGB(  68, 68, 255),		/* 浅蓝色1 */
	CL_BLUE4        = RGB(  0, 64, 128),		/* 浅蓝色1 */

	/* UI 界面 Windows控件常用色 */
	CL_BTN_FACE		= RGB(236, 233, 216),	/* 按钮表面颜色(灰) */
	CL_BOX_BORDER1	= RGB(172, 168,153),	/* 分组框主线颜色 */
	CL_BOX_BORDER2	= RGB(255, 255,255),	/* 分组框阴影线颜色 */


	CL_MASK			= 0x9999	/* 颜色掩码，用于文字背景透明 */
};

/* 编辑框风格 */
enum
{
	EDIT_BORDER_COLOR		= CL_BLUE2,		/* 编辑框四个边的颜色 */
	EDIT_BACK_COLOR			= CL_WHITE,			/* 编辑框背景 */
};

/* 按钮风格 */
enum
{
	BUTTON_BORDER_COLOR		= CL_BLUE2,			/* 按钮四个边的颜色 */
	BUTTON_BORDER1_COLOR	= CL_WHITE,			/* 按钮四个边内部2列的颜色 */
	BUTTON_BORDER2_COLOR	= CL_GREY1,			/* 按钮四个边内部2列的颜色 */
	BUTTON_BACK_COLOR		= CL_GREY3,			/* 按钮背景 */
	BUTTON_ACTIVE_COLOR		= CL_CYAN,			/* 激活的按钮背景 */
};

/* 窗口风格 */
enum
{
	WIN_BORDER_COLOR	= CL_BLUE4,		/* 窗口边框 */
	WIN_TITLE_COLOR		= CL_BLUE3,		/* 窗口标题蓝背景颜色 */
	WIN_CAPTION_COLOR	= CL_WHITE,		/* 窗口标题栏文字颜色 */
	WIN_BODY_COLOR		= CL_GREY2,		/* 窗体颜色 */
};

/* 检查框风格 */
enum
{
	CHECK_BOX_BORDER_COLOR	= CL_BLUE2,		/* 检查框四个边的颜色 */
	CHECK_BOX_BACK_COLOR	= CL_GREY3,		/* 检查框背景 */
	CHECK_BOX_CHECKED_COLOR	= CL_RED,		/* 检查框打勾的颜色 */

	CHECK_BOX_H			= 24,				/* 检查框高度 */
	CHECK_BOX_W			= 24,				/* 检查框高度 */
};

/* 字体代码 */
typedef enum
{
	FC_ST_16 = 0,		/* 宋体15x16点阵 （宽x高） */
	FC_ST_12 = 1		/* 宋体12x12点阵 （宽x高） */
}FONT_CODE_E;

/* 字体属性结构, 用于LCD_DispStr() */
typedef struct
{
	unsigned short FontCode;	/* 字体代码 0 表示16点阵 */
	unsigned short FrontColor;	/* 字体颜色 */
	unsigned short BackColor;	/* 文字背景颜色，透明 */
	unsigned short Space;		/* 文字间距，单位 = 像素 */
}FONT_T;

/* 控件ID */
typedef enum
{
	ID_ICON		= 1,
	ID_WIN		= 2,
	ID_LABEL	= 3,
	ID_BUTTON	= 4,
	ID_CHECK 	= 5,
	ID_EDIT 	= 6,
	ID_GROUP 	= 7,
}CONTROL_ID_T;

/* 图标结构 */
typedef struct
{
	unsigned char id;
	unsigned short Left;		/* 左上角X坐标 */
	unsigned short Top;		/* 左上角Y坐标 */
	unsigned short Height;	/* 图标高度 */
	unsigned short Width;		/* 图标宽度 */
	unsigned short *pBmp;		/* 指向图标图片数据 */
	char  Text[16];	/* 图标文本, 最多显示5个汉字16点阵 */
}ICON_T;

/* 窗体结构 */
typedef struct
{
	unsigned char id;
	unsigned short Left;
	unsigned short Top;
	unsigned short Height;
	unsigned short Width;
	unsigned short Color;
	FONT_T *Font;
	char *pCaption;
}WIN_T;

/* 文本标签结构 */
typedef struct
{
	unsigned char id;
	unsigned short Left;			/* 左上角X坐标 */
	unsigned short Top;			/* 左上角Y坐标 */
	unsigned short Height;		/* 高度 */
	unsigned short Width;			/* 宽度 */
	unsigned short MaxLen;		/* 字符串长度 */
	FONT_T *Font;			/* 字体 */
	char  *pCaption;
}LABEL_T;

/* 按钮结构 */
typedef struct
{
	unsigned char id;
	unsigned short Left;
	unsigned short Top;
	unsigned short Height;
	unsigned short Width;
	/* 按钮的颜色，由底层自动管理 */
	FONT_T *Font;			/* 字体 */
	char *pCaption;
	unsigned char Focus;			/* 焦点 */
}BUTTON_T;

/* 编辑框结构 */
typedef struct
{
	unsigned char id;
	unsigned short Left;
	unsigned short Top;
	unsigned short Height;
	unsigned short Width;
	unsigned short Color;
	FONT_T *Font;			/* 字体 */
	char   *pCaption;
	char Text[32];			/* 用于存放编辑内容 */
}EDIT_T;

/* 检查框 CHECK BOX 结构 */
typedef struct
{
	unsigned char id;
	unsigned short Left;			/* 左上角X坐标 */
	unsigned short Top;			/* 左上角Y坐标 */
	unsigned short Height;		/* 高度 */
	unsigned short Width;			/* 宽度 */
	unsigned short Color;			/* 颜色 */
	FONT_T *Font;			/* 字体 */
	char  *pCaption;
	unsigned char Checked;		/* 1表示打勾 */
}CHECK_T;

/* 分组框GROUP BOX 结构 */
typedef struct
{
	unsigned char id;
	unsigned short Left;			/* 左上角X坐标 */
	unsigned short Top;			/* 左上角Y坐标 */
	unsigned short Height;		/* 高度 */
	unsigned short Width;			/* 宽度 */
	FONT_T *Font;			/* 字体 */
	char  *pCaption;
}GROUP_T;

/* 背景光控制 */
#define BRIGHT_MAX		255
#define BRIGHT_MIN		0
#define BRIGHT_DEFAULT	200
#define BRIGHT_STEP		5

/* 可供外部模块调用的函数 */
int LCD_InitHard(void);
void LCD_GetChipDescribe(char *_str);
unsigned short LCD_GetHeight(void);
unsigned short LCD_GetWidth(void);
void LCD_DispOn(void);
void LCD_DispOff(void);
void LCD_ClrScr(unsigned short _usColor);
void LCD_DispStr(unsigned short _usX, unsigned short _usY, char *_ptr, FONT_T *_tFont);
void LCD_PutPixel(unsigned short _usX, unsigned short _usY, unsigned short _usColor);
unsigned short LCD_GetPixel(unsigned short _usX, unsigned short _usY);
//void LCD_DrawLine(unsigned short _usX1 , unsigned short _usY1 , unsigned short _usX2 , unsigned short _usY2 , unsigned short _usColor);
void LCD_DrawPoints(unsigned short *x, unsigned short *y, unsigned short _usSize, unsigned short _usColor);
void LCD_DrawRect(unsigned short _usX, unsigned short _usY, unsigned short _usHeight, unsigned short _usWidth, unsigned short _usColor);
void LCD_DrawCircle(unsigned short _usX, unsigned short _usY, unsigned short _usRadius, unsigned short _usColor);
void LCD_DrawBMP(unsigned short _usX, unsigned short _usY, unsigned short _usHeight, unsigned short _usWidth, unsigned short *_ptr);
void LCD_SetBackLight(unsigned char _bright);
unsigned char LCD_GetBackLight(void);

void LCD_Fill_Rect(unsigned short _usX, unsigned short _usY, unsigned short _usHeight, unsigned short _usWidth, unsigned short _usColor);

void LCD_DrawWin(WIN_T *_pWin);
void LCD_DrawIcon(const ICON_T *_tIcon, FONT_T *_tFont, unsigned char _ucFocusMode);
void LCD_DrawEdit(EDIT_T *_pEdit);
void LCD_DrawButton(BUTTON_T *_pBtn);
void LCD_DrawLabel(LABEL_T *_pLabel);
void LCD_DrawCheckBox(CHECK_T *_pCheckBox);
void LCD_DrawGroupBox(GROUP_T *_pBox);

void LCD_DispControl(void *_pControl);

void LCD_DrawIcon32(const ICON_T *_tIcon, FONT_T *_tFont, unsigned char _ucFocusMode);
void LCD_DrawBmp32(unsigned short _usX, unsigned short _usY, unsigned short _usHeight, unsigned short _usWidth, unsigned char *_pBmp);

/* 下面3个变量，主要用于使程序同时支持不同的屏 */
extern unsigned short g_ChipID;			/* 驱动芯片ID */
extern unsigned short g_LcdHeight;		/* 显示屏分辨率-高度 */
extern unsigned short g_LcdWidth;			/* 显示屏分辨率-宽度 */
extern unsigned char g_ucGPIX;

/* 用于UCGUI和emWin的接口函数 */
void LCD_DrawLineV(unsigned short _usX1 , unsigned short _usY1 , unsigned short _usY2, unsigned short _usColor);
void LCD_DrawHColorLine(unsigned short _usX1 , unsigned short _usY1, unsigned short _usWidth, unsigned short *_pColor);
void LCD_DrawLineH(unsigned short _usX1 , unsigned short _usY1 , unsigned short _usX2, unsigned short _usColor);

#endif


