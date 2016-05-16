
#ifndef __KEY_H__
#define __KEY_H__

#define KEY0  (GPIOD->IDR&(1<<7))?1:0
#define KEY1  (GPIOG->IDR&(1<<9))?1:0
#define KEY2  (GPIOA->IDR&(1<<0))?0:1

	int key_device_open(struct file * filp);
	int32_t key_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen);
	int32_t key_read(FAR struct file *filp, FAR char *buffer, uint32_t buflen);
	int key_init(void);

#endif
