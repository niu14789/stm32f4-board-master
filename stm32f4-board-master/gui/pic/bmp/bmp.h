/*
 * bmp.h
 *
 *  Created on: 2016年10月16日
 *      Author: Administrator
 */

#ifndef GUI_PIC_BMP_BMP_H_
#define GUI_PIC_BMP_BMP_H_

#define ECLIPSE_DEBUG  __packed

//BMP信息头
typedef ECLIPSE_DEBUG struct
{
    unsigned int biSize ;		   	//说明BITMAPINFOHEADER结构所需要的字数。
    long  biWidth ;		   	//说明图象的宽度，以象素为单位
    long  biHeight ;	   	//说明图象的高度，以象素为单位
    unsigned short  biPlanes ;	   		//为目标设备说明位面数，其值将总是被设为1
    unsigned short  biBitCount ;	   	//说明比特数/象素，其值为1、4、8、16、24、或32
    unsigned int biCompression ;  	//说明图象数据压缩的类型。其值可以是下述值之一：
	//BI_RGB：没有压缩；
	//BI_RLE8：每个象素8比特的RLE压缩编码，压缩格式由2字节组成(重复象素计数和颜色索引)；
    //BI_RLE4：每个象素4比特的RLE压缩编码，压缩格式由2字节组成
  	//BI_BITFIELDS：每个象素的比特由指定的掩码决定。
    unsigned int biSizeImage ;		//说明图象的大小，以字节为单位。当用BI_RGB格式时，可设置为0
    long  biXPelsPerMeter ;	//说明水平分辨率，用象素/米表示
    long  biYPelsPerMeter ;	//说明垂直分辨率，用象素/米表示
    unsigned int biClrUsed ;	  	 	//说明位图实际使用的彩色表中的颜色索引数
    unsigned int biClrImportant ; 	//说明对图象显示有重要影响的颜色索引的数目，如果是0，表示都重要。
}BITMAPINFOHEADER ;
//BMP头文件
typedef ECLIPSE_DEBUG struct
{
    unsigned short  bfType ;     //文件标志.只对'BM',用来识别BMP位图类型
    unsigned int  bfSize ;	  //文件大小,占四个字节
    unsigned short  bfReserved1 ;//保留
    unsigned short  bfReserved2 ;//保留
    unsigned int  bfOffBits ;  //从文件开始到位图数据(bitmap data)开始之间的的偏移量
}BITMAPFILEHEADER ;
//彩色表
typedef ECLIPSE_DEBUG struct
{
    unsigned char rgbBlue ;    //指定蓝色强度
    unsigned char rgbGreen ;	//指定绿色强度
    unsigned char rgbRed ;	  	//指定红色强度
    unsigned char rgbReserved ;//保留，设置为0
}RGBQUAD ;
//位图信息头
typedef ECLIPSE_DEBUG struct
{
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;
	unsigned int RGB_MASK[3];			//调色板用于存放RGB掩码.
	//RGBQUAD bmiColors[256];
}BITMAPINFO;


#endif /* GUI_PIC_BMP_BMP_H_ */
