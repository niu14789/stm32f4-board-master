#ifndef _LCD_H
#define _LCD_H

// #include "stm32f4xx.h"

#define USE_LCD_PRINTF //使用lcd_printf函数
 
//LCD重要参数集
typedef struct
{
	unsigned short width;	//LCD宽度
	unsigned short height;	//LCD高度
	unsigned short id;			//LCD的ID
	unsigned char dir;			//横屏还是竖屏控制:0 竖屏,1 横屏
	unsigned short wramcmd;  //开始写gram指令
	unsigned short setxcmd; 	//设置X坐标指令
	unsigned short setycmd;  //设置Y坐标指令
} _lcd_dev;

extern _lcd_dev lcddev;  //管理LCD重要参数
extern unsigned short POINT_COLOR;  //默认红色;
extern unsigned short BACK_COLOR;	 //背景颜色,默认为白色

//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD端口定义---------------- 
#define LCD_LED	PB15  //LCD背光  PB15

//LCD地址结构体
typedef struct
{
	unsigned short LCD_REG;  //地址为0X6C00007E;  0111 1110  FSMC_A6为0 
	unsigned short LCD_RAM;  //地址为0x6C000080;  1000 0000  FSMC_A6为1
}LCD_TypeDef;

//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A6作为数据命令区分线 
//注意设置时STM32内部会右移一位对其! 111 1110=0X7E	
#define LCD_BASE		((unsigned int)(0x6C000000 | 0X0000007E))
#define LCD			((LCD_TypeDef *) LCD_BASE)

//扫描方向定义
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左	 

#define DFT_SCAN_DIR	L2R_U2D		//默认的扫描方向

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色

//GUI颜色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 

#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

int lcd_ili_init(void);
int  LCD_Init(void);													   	//初始化
void LCD_DisplayOn(void);													//开显示
void LCD_DisplayOff(void);													//关显示
void LCD_Clear(unsigned short Color);	 												//清屏
void LCD_SetCursor(unsigned short Xpos, unsigned short Ypos);										//设置光标
void LCD_DrawPoint(unsigned short x,unsigned short y);											//画点
void LCD_Fast_DrawPoint(unsigned short x,unsigned short y,unsigned short color);								//快速画点
unsigned short  LCD_ReadPoint(unsigned short x,unsigned short y); 											//读点 
void Draw_Circle(unsigned short x0,unsigned short y0,unsigned char r);										//画圆
void LCD_DrawLine_ili(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2,unsigned short color);
void LCD_DrawRectangle(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);		   				//画矩形
void LCD_Fill(unsigned short sx,unsigned short sy,unsigned short ex,unsigned short ey,unsigned short color);		   				//填充单色
void LCD_Color_Fill(unsigned short sx,unsigned short sy,unsigned short ex,unsigned short ey,unsigned short *color);				//填充指定颜色
void LCD_ShowChar(unsigned short x,unsigned short y,unsigned char num,unsigned char size,unsigned char mode);						//显示一个字符
void LCD_ShowNum(unsigned short x,unsigned short y,unsigned int num,unsigned char len,unsigned char size);  						//显示一个数字
void LCD_ShowxNum(unsigned short x,unsigned short y,unsigned int num,unsigned char len,unsigned char size,unsigned char mode);				//显示 数字
void LCD_ShowString_ili(unsigned short x,unsigned short y,unsigned short width,unsigned short height,unsigned char size,unsigned char *p);		//显示一个字符串,12/16字体

void LCD_WriteReg(unsigned short LCD_Reg, unsigned short LCD_RegValue);
unsigned short LCD_ReadReg(unsigned short LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(unsigned short RGB_Code);		  
void LCD_Scan_Dir(unsigned char dir);							//设置屏扫描方向
void LCD_Display_Dir(unsigned char dir);						//设置屏幕显示方向
void LCD_Set_Window(unsigned short sx,unsigned short sy,unsigned short width,unsigned short height);//设置窗口	
#ifdef USE_LCD_PRINTF
void lcd_printf(char *data,...);
#endif

//9320/9325 LCD寄存器  
#define R0             0x00
#define R1             0x01
#define R2             0x02
#define R3             0x03
#define R4             0x04
#define R5             0x05
#define R6             0x06
#define R7             0x07
#define R8             0x08
#define R9             0x09
#define R10            0x0A
#define R12            0x0C
#define R13            0x0D
#define R14            0x0E
#define R15            0x0F
#define R16            0x10
#define R17            0x11
#define R18            0x12
#define R19            0x13
#define R20            0x14
#define R21            0x15
#define R22            0x16
#define R23            0x17
#define R24            0x18
#define R25            0x19
#define R26            0x1A
#define R27            0x1B
#define R28            0x1C
#define R29            0x1D
#define R30            0x1E
#define R31            0x1F
#define R32            0x20
#define R33            0x21
#define R34            0x22
#define R36            0x24
#define R37            0x25
#define R40            0x28
#define R41            0x29
#define R43            0x2B
#define R45            0x2D
#define R48            0x30
#define R49            0x31
#define R50            0x32
#define R51            0x33
#define R52            0x34
#define R53            0x35
#define R54            0x36
#define R55            0x37
#define R56            0x38
#define R57            0x39
#define R59            0x3B
#define R60            0x3C
#define R61            0x3D
#define R62            0x3E
#define R63            0x3F
#define R64            0x40
#define R65            0x41
#define R66            0x42
#define R67            0x43
#define R68            0x44
#define R69            0x45
#define R70            0x46
#define R71            0x47
#define R72            0x48
#define R73            0x49
#define R74            0x4A
#define R75            0x4B
#define R76            0x4C
#define R77            0x4D
#define R78            0x4E
#define R79            0x4F
#define R80            0x50
#define R81            0x51
#define R82            0x52
#define R83            0x53
#define R96            0x60
#define R97            0x61
#define R106           0x6A
#define R118           0x76
#define R128           0x80
#define R129           0x81
#define R130           0x82
#define R131           0x83
#define R132           0x84
#define R133           0x85
#define R134           0x86
#define R135           0x87
#define R136           0x88
#define R137           0x89
#define R139           0x8B
#define R140           0x8C
#define R141           0x8D
#define R143           0x8F
#define R144           0x90
#define R145           0x91
#define R146           0x92
#define R147           0x93
#define R148           0x94
#define R149           0x95
#define R150           0x96
#define R151           0x97
#define R152           0x98
#define R153           0x99
#define R154           0x9A
#define R157           0x9D
#define R192           0xC0
#define R193           0xC1
#define R229           0xE5	
#endif
