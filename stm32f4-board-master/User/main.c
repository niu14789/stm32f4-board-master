

#include "stm32f4xx.h"
#include "led.h"

#include "key.h"
#include "rtc.h"
#include "stm32_usart.h"
#include "fs.h"
#include "stdio.h"

#include "lcd_hw.h"
#include "gui.h"

int delay_ms(struct file * filp);
int delay_ms1(void);

extern int32_t write(int fd, FAR const char *buffer, uint32_t buflen);

int lcd_fd = 0;

struct file_operations f_ops =
{
  delay_ms,
};

struct inode inode_start = 
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	&f_ops,
	NULL,
	NULL,
	delay_ms1,
	NULL
};

FS_REGISTER_START("/etc/inode_start.d",inode_start);

int delay_ms(struct file * filp)
{
  return 0;
}

int delay_ms1(void)
{
	u16 i,j;

	int t = 100;

	for(i=0;i<40000;i++)
		 for(j=0;j<t;j++);

    return OK;
}


extern int button_create(uint16_t BUTTON_POS_X,uint16_t BUTTON_POS_Y,uint16_t BUTTON_SIZE_X,uint16_t BUTTON_SIZE_Y,char *caption,char mode );
extern void rect_move(unsigned short next_xpos,unsigned short next_ypos,unsigned color);
void slider_create(uint16_t x,uint16_t y,uint16_t x_size,uint16_t y_size,uint16_t focus);


extern int gui_server(void);

void fd_delay(unsigned int t)
{
	while(t--);
}

int main(void)
{
	 int x=0,y=0,xs=5,ys=3;
	 unsigned short r=122,g=90,b=12;

   fs_init();

   lcd_fd = open("/etc/lcd.d",__ONLYREAD);
	 
	 if(lcd_fd)
	 {
		 write(lcd_fd,"2",1);
		 write(lcd_fd,"this is a test",14);
	 }

	 slider_create(50,180,400,50,0);
	 
	 gui_create();
	 
		 
	 while(1)
	 {
		 gui_server();

		 rect_move(x,y,RGB(r,g,b));
		 x+=xs;
		 y+=ys;
		 if(y>=262)
		 {
			 ys = -3;
		 }
		 if(y<1)
			 ys = 3;
		 
		 if(x>=470)
			 xs = -5;
		 if(x<1)
			 xs = 5;
		 
		 r++;
		 g++;
		 b++;
		 
		 fd_delay(0xffff);
	 }
}



#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{ 	
	while (1)
	{
	}
}
#endif

