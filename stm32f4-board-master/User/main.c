

#include "stm32f4xx.h"
#include "led.h"

#include "key.h"
#include "rtc.h"
#include "stm32_usart.h"
#include "fs.h"
#include "stdio.h"

#include "lcd_hw.h"
#include "gui.h"

static unsigned int sram_test[0xffff] __attribute__((at(0x68000000)));

int delay_ms(struct file * filp);
int delay_ms1(void);

int lcd_fd = 0;

extern window_hwnd  window_handler;

int delay_ms1(void)
{
	u16 i,j;

	int t = 100;

	for(i=0;i<40000;i++)
		 for(j=0;j<t;j++);

    return OK;
}
int refresh(void);
extern void rect_move(unsigned short next_xpos,unsigned short next_ypos,unsigned color);
void slider_create(uint16_t x,uint16_t y,uint16_t x_size,uint16_t y_size,uint16_t focus);
extern void TOUCH_InitHard(void);
extern int TOUCH_SCAN(void);
extern int gui_server(void);
int gui_key_event_check(char *buffer);
int touch_calibration(void);
void touch_test(void);
void FSMC_SRAM_Init(void);
extern struct gui_handler * button_create(struct gui_msg_t*p_msg,int (*callback)(enum event_type,void *data));

window_hwnd * window_create(window_hwnd * hwnd,struct gui_msg_t*p_msg,int (*callback)(enum event_type,void *data));

void fd_delay(unsigned int t)
{
	while(t--);
}


gui_message gui_msg_tmp =
	{
		0,
		0,
		120,
		80,
		"main_window",
		"/sdcard/main.bmp",
		0,
		0,
		__GUI_WIDGET_MODE_0     | /* pic mode , with caption */
		__GUI_WIDGET_TYPE_OCT   | /* right angle mode */
		__GUI_WIDGET_FRAME_NONE | /* without frame */
		__GUI_WIDGET_THEME_0    | /* theme 0 */
		__GUI_WIDGET_HANDLE       /* no ues */
	};
	
int main(void)
{

 	  int x=0,y=0,xs=5,ys=3;
	
//	  struct file *fd1,*fd2,*fd3,*fd4,*fd5;
	
 	  unsigned short r=122,g=90,b=12;
      char device_availdable_list[20];
//      char key_buffer[3];
 	struct gui_msg_t bu_rect={
  200,50,20,20,"test"
	};
    system_initialization(device_availdable_list);
#if 1

	 
 	 gui_create(device_availdable_list);

	
	gui_msg_tmp.x += 10;
	gui_msg_tmp.y += 10;
	
	window_create(&window_handler,&gui_msg_tmp,NULL);
	
	refresh();

	   stm32_usart_init(USART3,PB10_PB11,57600);


	 while(1)
 	 {
		 	gui_msg_tmp.x = x;
	    gui_msg_tmp.y = y;
	
	window_create(&window_handler,&gui_msg_tmp,NULL);
	
	refresh();
// 		 touch_test();
// 		 
// 		 gui_key_event_check(key_buffer);

 		 gui_server();

//		 rect_move(x,y,RGB(r,g,b));
		 x+=xs;
		 y+=ys;
		 if(y>=160)
		 {
			 ys = -3;
		 }
		 if(y<1)
			 ys = 3;
		 
		 if(x>=200)
			 xs = -5;
		 if(x<1)
			 xs = 5;
		 
		 r++;
		 g++;
		 b++;
		 
		 fd_delay(0xfffff);
 	 }
#else
{
	 unsigned short draw_t[480]={1,2,3,4,5,20,2,6,2,5,4,8,3,6,9,5,2,8,4,1,2,5,3,6,9,8,5,2,1,4,7,8,9,6,3,2,5,4,1,2,3,6,9,85,2,14,7,8,5,4,6,45,25,5,35,88,64,6,6,64,6};
	 int i;
		 RA8875_ClrScr(0xffff);
	 RA8875_DrawLine(0,0,200,200,0);
		 
	 for( i=0;i<480;i++)
	 {
			RA8875_DrawLine(i,136-draw_t[i],i+1,136-draw_t[i+1],0x0); 
	 }
}
	 while(1);
		 


#endif

	 
}



#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{ 	
	while (1)
	{
	}
}
#endif

