/*
 * bmp.h
 *
 *  Created on: 2016��10��16��
 *      Author: Administrator
 */

#ifndef GUI_PIC_BMP_BMP_H_
#define GUI_PIC_BMP_BMP_H_

#define ECLIPSE_DEBUG  __packed

//BMP��Ϣͷ
typedef ECLIPSE_DEBUG struct
{
    unsigned int biSize ;		   	//˵��BITMAPINFOHEADER�ṹ����Ҫ��������
    long  biWidth ;		   	//˵��ͼ��Ŀ�ȣ�������Ϊ��λ
    long  biHeight ;	   	//˵��ͼ��ĸ߶ȣ�������Ϊ��λ
    unsigned short  biPlanes ;	   		//ΪĿ���豸˵��λ��������ֵ�����Ǳ���Ϊ1
    unsigned short  biBitCount ;	   	//˵��������/���أ���ֵΪ1��4��8��16��24����32
    unsigned int biCompression ;  	//˵��ͼ������ѹ�������͡���ֵ����������ֵ֮һ��
	//BI_RGB��û��ѹ����
	//BI_RLE8��ÿ������8���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����(�ظ����ؼ�������ɫ����)��
    //BI_RLE4��ÿ������4���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����
  	//BI_BITFIELDS��ÿ�����صı�����ָ�������������
    unsigned int biSizeImage ;		//˵��ͼ��Ĵ�С�����ֽ�Ϊ��λ������BI_RGB��ʽʱ��������Ϊ0
    long  biXPelsPerMeter ;	//˵��ˮƽ�ֱ��ʣ�������/�ױ�ʾ
    long  biYPelsPerMeter ;	//˵����ֱ�ֱ��ʣ�������/�ױ�ʾ
    unsigned int biClrUsed ;	  	 	//˵��λͼʵ��ʹ�õĲ�ɫ���е���ɫ������
    unsigned int biClrImportant ; 	//˵����ͼ����ʾ����ҪӰ�����ɫ��������Ŀ�������0����ʾ����Ҫ��
}BITMAPINFOHEADER ;
//BMPͷ�ļ�
typedef ECLIPSE_DEBUG struct
{
    unsigned short  bfType ;     //�ļ���־.ֻ��'BM',����ʶ��BMPλͼ����
    unsigned int  bfSize ;	  //�ļ���С,ռ�ĸ��ֽ�
    unsigned short  bfReserved1 ;//����
    unsigned short  bfReserved2 ;//����
    unsigned int  bfOffBits ;  //���ļ���ʼ��λͼ����(bitmap data)��ʼ֮��ĵ�ƫ����
}BITMAPFILEHEADER ;
//��ɫ��
typedef ECLIPSE_DEBUG struct
{
    unsigned char rgbBlue ;    //ָ����ɫǿ��
    unsigned char rgbGreen ;	//ָ����ɫǿ��
    unsigned char rgbRed ;	  	//ָ����ɫǿ��
    unsigned char rgbReserved ;//����������Ϊ0
}RGBQUAD ;
//λͼ��Ϣͷ
typedef ECLIPSE_DEBUG struct
{
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;
	unsigned int RGB_MASK[3];			//��ɫ�����ڴ��RGB����.
	//RGBQUAD bmiColors[256];
}BITMAPINFO;


#endif /* GUI_PIC_BMP_BMP_H_ */
