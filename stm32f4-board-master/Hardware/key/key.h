
#ifndef __KEY_H__
#define __KEY_H__

#define KEY0  (GPIOD->IDR&(1<<7))?1:0
#define KEY1  (GPIOG->IDR&(1<<9))?1:0
#define KEY2  (GPIOA->IDR&(1<<0))?0:1


  void key_init(void);
#endif
