/*
 * lcd_interface.h
 *
 *  Created on: 2016Äê5ÔÂ8ÈÕ
 *      Author: Administrator
 */

#ifndef __LCD_INTERFACE_H__
#define __LCD_INTERFACE_H__



int lcd_device_open(struct file * filp);
int32_t lcd_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen);


#endif /* __LCD_INTERFACE_H__*/
