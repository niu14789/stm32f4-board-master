/*
 * bmp.c
 *
 *  Created on: 2016年10月16日
 *      Author: Administrator
 */


#include "fs.h"
#include "bmp.h"
#include "gui.h"
#include "gui_config.h"


/*-----------------*/
#define MAX_READ_LEN_BMP  (3200)
char buffer_bmp[MAX_READ_LEN_BMP];//
/*
 * draw a bmp to lcd
 *
 * */
int gui_draw_bmp( const struct gui_msg_t * p_msg , unsigned int __MODE__)
{
   struct file *fd;
   int ret;
   BITMAPINFO * bmpinfo;
   static unsigned short pic_width , pic_height;
   unsigned char color_byte; //8 16 32bit color byte
   int i,j,k;
   unsigned short color;
   unsigned char alphabend;

   gui_device *gui_device_t;

   gui_device_t = gui_dev_ops_g();
   /* open pic */
   fd = open( p_msg->pic_path , __FS_OPEN_EXISTING | __FS_READ );

   if(fd == NULL)
   {
	   printf_d("can not open bmp file->%s\n",p_msg->pic_path);
	   return ERR;
   }

   ret = read(fd,buffer_bmp,512);

   if( ret != 512 )
   {
	   printf_d("read %s fail\n",p_msg->pic_path);
	   return ERR;
   }

   bmpinfo = (BITMAPINFO *)buffer_bmp;

   color_byte = bmpinfo->bmiHeader.biBitCount / 8; //should be 1,2,4

   if( color_byte != 4 )
   {
	   printf_d("can not support this %dbit bmp format\n" , color_byte * 4 );
	   return ERR;
   }

   pic_width  = bmpinfo->bmiHeader.biWidth;     //get bmp width
   pic_height = bmpinfo->bmiHeader.biHeight;	//get bmp height

   lseek(fd,bmpinfo->bmfHeader.bfOffBits,0);

   for( i = 0 ; i < 240 ; i++ )
   {
	   for( j = 0 ; j < 320 ; j++)
	   {
// 			 
					ret = read(fd,buffer_bmp,4);

					if(ret != 4 )
					 return ERR;
// 					
//        for( k = 0 ; k < 320 ; k ++ )
// 			 {
					color      =  buffer_bmp[0]>>3;		   		 	//B
					color     +=  (((unsigned short)buffer_bmp[1])<<3)&0X07E0;	//G
					color     +=  (((unsigned short)buffer_bmp[2])<<8)&0XF800;	//R
					alphabend  =  buffer_bmp[3];			        //ALPHA通道

					gui_device_t->gui_dev_ops_g.put_pixel(p_msg->x + j,p_msg->y + i,color);
// 		   } 
	   }
   }


   return 0;
}










