
#ifndef __SD_INTERFACE_H__
#define __SD_INTERFACE_H__

  int sd_device_open(struct file * filp);
  int32_t sd_device_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen);
	
#endif

