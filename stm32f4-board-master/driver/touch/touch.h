/*
 * touch.h
 *
 *  Created on: 2016��10��12��
 *      Author: Administrator
 */

#ifndef DRIVER_TOUCH_TOUCH_H_
#define DRIVER_TOUCH_TOUCH_H_



int touch2_init(void);
u8 TP_Read_XY(u16 *x,u16 *y);
u16 TP_Read_AD(u8 CMD);
unsigned short TP_Read_XOY(u8 xy);
void TP_Write_Byte(u8 num);
u8 TP_Read_XY(u16 *x,u16 *y);
void delay_us(unsigned int t);
u8 TP_Scan(u8 tp);
void exit_interrupt_init( void );
#endif /* DRIVER_TOUCH_TOUCH_H_ */
