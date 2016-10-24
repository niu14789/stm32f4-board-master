/*
 * e2p.h
 *
 *  Created on: 2016年10月24日
 *      Author: YJ-User17
 */

#ifndef DRIVER_E2P_E2P_H_
#define DRIVER_E2P_E2P_H_

#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767

#define EE_TYPE AT24C02

int e2p_init(void);
void AT24CXX_Read(unsigned short ReadAddr,unsigned char *pBuffer,unsigned short NumToRead);
void AT24CXX_Write(unsigned short WriteAddr,unsigned char *pBuffer,unsigned short NumToWrite);
unsigned char AT24CXX_Check(void);
struct file * e2p_device_open(struct file * filp);
uint32_t e2p_device_read(FAR struct file *filp, FAR char *buffer, uint32_t buflen);
int32_t e2p_device_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen);

#endif /* DRIVER_E2P_E2P_H_ */



