

#ifndef __DEC_CODE_H__
#define __DEC_CODE_H__

char RunDes(char *Out, char *In, int datalength, char *Key, char Type) ;
void getidkey(char *id);
extern  char idkey[8];
extern const char noidcode[24];//没有用到ID时的默认密钥

#endif


