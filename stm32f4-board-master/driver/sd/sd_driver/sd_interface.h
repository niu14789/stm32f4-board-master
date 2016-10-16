
#ifndef __SD_INTERFACE_H__
#define __SD_INTERFACE_H__

  struct file * sd_device_open(struct file * filp);
  int32_t sd_device_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen);
  int sd_init(void);
  int sd_device_multiple(void);
  int  sd_device_close(FAR struct file *filp);
  uint32_t sd_device_read(FAR struct file *filp, FAR char *buffer, uint32_t buflen);
  int32_t sd_device_lseek(FAR struct file *filp, unsigned int offset, unsigned int whence);
  int sd_path_transfer(FAR const char * filp , char * f_path , int len);
  int sd_device_mkdir( const char * dir );
#endif

