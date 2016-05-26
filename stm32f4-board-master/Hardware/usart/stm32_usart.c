




#include "stm32f4xx.h"                  /* STM32F4xx Definitions              */

#include "STM32_USART.h"
#include "fs.h"


typedef struct stm32_usart{
	
	
  GPIO_TypeDef* gpio_tx;
	
	uint8_t GPIO_PinSource_tx;
	
	uint16_t GPIO_Pin_tx;
	
	GPIO_TypeDef* gpio_rx;
	
	uint8_t GPIO_PinSource_rx;
	
	uint16_t GPIO_Pin_rx;
	
	uint32_t rcc_gpio_tx;
	
	uint32_t rcc_gpio_rx;
	
	uint8_t  gpio_af;
	
	uint32_t rcc_usart;

}stm32_usart_def;


static stm32_usart_def stm32_usart_unit;

static struct stm32_usart *stm32_usart_ops(USART_TypeDef* USARTx,uint32_t txrx)
{
	 
	 stm32_usart_unit.gpio_rx=(GPIO_TypeDef *)(((txrx&0x0000f000)>>4));
	 stm32_usart_unit.GPIO_PinSource_tx=(uint8_t)((txrx&0x0f000000)>>24);
	 stm32_usart_unit.gpio_tx=(GPIO_TypeDef *)((txrx&0x00000f00)+GPIOA_BASE);
	 stm32_usart_unit.GPIO_PinSource_rx=(uint8_t)((txrx&0x000f0000)>>16);
	 stm32_usart_unit.rcc_gpio_tx=(uint32_t)((txrx&0x000000f0)>>4);
	 stm32_usart_unit.rcc_gpio_rx=(uint32_t)(txrx&0x0000000f);
	 stm32_usart_unit.GPIO_Pin_tx=1<<stm32_usart_unit.GPIO_PinSource_tx;
	 stm32_usart_unit.GPIO_Pin_rx=1<<stm32_usart_unit.GPIO_PinSource_rx;
	if (USARTx == USART1)
  {
     stm32_usart_unit.rcc_usart=RCC_APB2Periph_USART1;
     stm32_usart_unit.gpio_af=GPIO_AF_USART1;
  }
  else if (USARTx == USART2)
  {
     stm32_usart_unit.rcc_usart=RCC_APB1Periph_USART2;
     stm32_usart_unit.gpio_af=GPIO_AF_USART2;
  }
  else if (USARTx == USART3)
  {
    stm32_usart_unit.rcc_usart=RCC_APB1Periph_USART3;
    stm32_usart_unit.gpio_af=GPIO_AF_USART3;
  }    
  else if (USARTx == UART4)
  {
    stm32_usart_unit.rcc_usart=RCC_APB1Periph_UART4;
    stm32_usart_unit.gpio_af=GPIO_AF_UART4;
  }
  else if (USARTx == UART5)
  {
    stm32_usart_unit.rcc_usart=RCC_APB1Periph_UART5;
    stm32_usart_unit.gpio_af=GPIO_AF_UART5;
  }     
  else
  {
    if (USARTx == USART6)
    { 
      stm32_usart_unit.rcc_usart=RCC_APB2Periph_USART6;
      stm32_usart_unit.gpio_af=GPIO_AF_USART6;
    }
  }
	 return &stm32_usart_unit;
}

void stm32_usart_init(USART_TypeDef* USARTx,uint32_t txrx,uint32_t baudrate)
{
 
  GPIO_InitTypeDef GPIO_InitStructure;                                          
	USART_InitTypeDef USART_InitStructure;                                       
	
	
  RCC_AHB1PeriphClockCmd(stm32_usart_ops(USARTx,txrx)->rcc_gpio_tx,ENABLE); 
  RCC_AHB1PeriphClockCmd(stm32_usart_ops(USARTx,txrx)->rcc_gpio_rx,ENABLE); 
	
	if( USARTx == USART1 )
		RCC_APB2PeriphClockCmd(stm32_usart_ops(USARTx,txrx)->rcc_usart,ENABLE); 
	else if( USARTx == USART6 )
	  RCC_APB2PeriphClockCmd(stm32_usart_ops(USARTx,txrx)->rcc_usart,ENABLE);                        
  else
		RCC_APB1PeriphClockCmd(stm32_usart_ops(USARTx,txrx)->rcc_usart,ENABLE); 
				     
	GPIO_InitStructure.GPIO_Pin=stm32_usart_unit.GPIO_Pin_tx;  //PB6 tx 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;                               
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;                                    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;								  
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;						          
	GPIO_Init(stm32_usart_unit.gpio_tx,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=stm32_usart_unit.GPIO_Pin_rx;                                     	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;                                    
	GPIO_Init(stm32_usart_unit.gpio_rx,&GPIO_InitStructure); 
	
 	GPIO_PinAFConfig(stm32_usart_unit.gpio_tx,stm32_usart_unit.GPIO_PinSource_tx,stm32_usart_unit.gpio_af);						  
  GPIO_PinAFConfig(stm32_usart_unit.gpio_rx,stm32_usart_unit.GPIO_PinSource_rx,stm32_usart_unit.gpio_af);			     

	USART_DeInit( USARTx );

	USART_InitStructure.USART_BaudRate=115200;                                    
	USART_InitStructure.USART_Parity=USART_Parity_No;                            
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;                     
	USART_InitStructure.USART_StopBits=USART_StopBits_1;                          
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USARTx, &USART_InitStructure);		
	USART_Cmd(USARTx,ENABLE);  
 {
		float temp;
		u16 mantissa;
		u16 fraction;	
		u32	pclk2=42;
		u32 bound=baudrate;
	 
		if( USARTx == USART1 )
			pclk2=84;
		else if( USARTx == USART6 )
			pclk2=84;                  
		else
			pclk2=42;
		
		temp=(float)(pclk2*1000000)/(bound*16);
		mantissa=temp;				 
		fraction=(temp-mantissa)*16; 	 
		mantissa<<=4;
		mantissa+=fraction; 
	 
		USARTx->BRR = mantissa;
		
	 } 
}

void stm32_usart_dma(USART_TypeDef* USARTx,DMA_Stream_TypeDef* DMAy_Streamx,uint16_t message,uint8_t *dmabuf,uint32_t DMA_IT,uint8_t USART_IRQn)
{
  
	u8 Director , mode , ndtr;
	
	Director  =   ( message & 0x8000 )?1:0;
	mode = ( message & 0x4000 )?1:0;
	ndtr = message & 0x00ff ;
	
	
	USARTx->CR1|=1<<2;                       //RX en
	USARTx->CR3|=1<<6;                       //DMA RX EN 
	USARTx->CR3|=1<<7;
	
	RCC->AHB1ENR|=1<<22;                   //Enable DMA2 22 clock; DMA1 21
	RCC->AHB1ENR|=1<<21;                   //Enable DMA2 22 clock; DMA1 21
	DMAy_Streamx->CR&=0;                 //en clear;
	while((DMAy_Streamx->CR)&0x00000001);
	
	if( USARTx == USART6) 
	   DMAy_Streamx->CR|=5<<25;               //channel 4,stream 5 ,USART4->RX
	else
		 DMAy_Streamx->CR|=4<<25;               //channel 4,stream 5 ,USART4->RX
	
	DMAy_Streamx->CR|=2<<16;               //Priority level->Very high
	DMAy_Streamx->CR|=0x0<<10;             //memory and peripheral data size
	DMAy_Streamx->CR|=1<<10;               //memory address pointer incremented after each data transfer
	DMAy_Streamx->CR&=~(1<<9);             //peripheral address pointer is fixed
	DMAy_Streamx->CR|=(mode<<8);                //circular mode enable
	DMAy_Streamx->CR|=Director<<6;                //Peripheral to Memory,[7,6]->00 ptom ,01 mtp, 11 mtm
	DMAy_Streamx->FCR=0x00000000;
	
	DMAy_Streamx->NDTR=ndtr;                //Number of data items to transfer
	DMAy_Streamx->PAR=(uint32_t)&USARTx->DR;
	DMAy_Streamx->M0AR=(uint32_t)dmabuf;
	
  if( DMA_IT )
	{
		
	   DMA_ITConfig(DMAy_Streamx,DMA_IT,ENABLE);            //DMA enable	
		
	}
     DMA_Cmd(DMAy_Streamx, ENABLE);
	if( DMA_IT )
	{
		{
			NVIC_InitTypeDef NVIC_InitStructure;
			/* Enable the DMA Stream IRQ Channel */
			NVIC_InitStructure.NVIC_IRQChannel = USART_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);     
		}
  } 
}

#ifdef USING_USART_PRINTF
		#include <stdarg.h>
		#define CMD_BUFFER_LEN 200
		extern int vsnprintf(char *str, unsigned int size,  const  char  *format,  va_list ap);
    va_list arg_ptrx;
     #ifdef USING_USART1_PRINTF
		  char buffer1[CMD_BUFFER_LEN+1]; 
     va_list arg_ptr1;
     #endif
     #ifdef USING_USART2_PRINTF
		  char buffer2[CMD_BUFFER_LEN+1]; 
     va_list arg_ptr2;
     #endif
     #ifdef USING_USART3_PRINTF
		  char buffer3[CMD_BUFFER_LEN+1]; 
     va_list arg_ptr3;
     #endif
     #ifdef USING_USART4_PRINTF
		  char buffer4[CMD_BUFFER_LEN+1]; 
     va_list arg_ptr4;
     #endif
     #ifdef USING_USART5_PRINTF
		  char buffer5[CMD_BUFFER_LEN+1]; 
			va_list arg_ptr5;
     #endif
     #ifdef USING_USART6_PRINTF
		  char buffer6[CMD_BUFFER_LEN+1]; 
			va_list arg_ptr6;
     #endif
    #ifdef USING_USARTX_PRINTF
		char buffer7[CMD_BUFFER_LEN+1]; 
		static  va_list arg_ptr;
		#endif
    #ifdef USING_USART1_PRINTF
			void usart1_printf(char * data, ...)
			{
					 u8 i=0 ;				
				
					 va_start(arg_ptr1,data);
				
					  vsnprintf(buffer1, CMD_BUFFER_LEN+1, data, arg_ptr1);
				
					 while( (i < CMD_BUFFER_LEN) && buffer1[i] )
					 {
							
						 while (!(USART1->SR & 0x0080))
						 {} 
						 USART1->DR = ((u8) buffer1[i++] & 0xFF);
					 }
					va_end(arg_ptr1);
			}
		#endif
			
			#ifdef USING_USART2_PRINTF
			void usart2_printf(char * data, ...)
			{
					 u8 i=0 ;				
				
					 va_start(arg_ptr2,data);
				
					  vsnprintf(buffer2, CMD_BUFFER_LEN+1, data, arg_ptr2);
				
					 while( (i < CMD_BUFFER_LEN) && buffer2[i] )
					 {
							
						 while (!(USART2->SR & 0x0080))
						 {} 
						 USART2->DR = ((u8) buffer2[i++] & 0xFF);
					 }
					va_end(arg_ptr2);
			}
		#endif
			
		#ifdef USING_USART3_PRINTF
			void usart3_printf(char * data, ...)
			{
					 u8 i=0 ;				
				
					 va_start(arg_ptr3,data);
				
					  vsnprintf(buffer3, CMD_BUFFER_LEN+1, data, arg_ptr3);
				
					 while( (i < CMD_BUFFER_LEN) && buffer3[i] )
					 {
							
						 while (!(USART3->SR & 0x0080))
						 {} 
						 USART3->DR = ((u8) buffer3[i++] & 0xFF);
					 }
					va_end(arg_ptr3);
			}
		#endif	
			
			#ifdef USING_USART4_PRINTF
			void usart4_printf(char * data, ...)
			{
					 u8 i=0 ;				
				
					 va_start(arg_ptr4,data);
				
					  vsnprintf(buffer4, CMD_BUFFER_LEN+1, data, arg_ptr4);
				
					 while( (i < CMD_BUFFER_LEN) && buffer4[i] )
					 {
							
						 while (!(UART4->SR & 0x0080))
						 {} 
						 UART4->DR = ((u8) buffer4[i++] & 0xFF);
					 }
					va_end(arg_ptr4);
			}
		#endif
			
			#ifdef USING_USART5_PRINTF
			void usart5_printf(char * data, ...)
			{
					 u8 i=0 ;				
				
					 va_start(arg_ptr5,data);
				
					  vsnprintf(buffer5, CMD_BUFFER_LEN+1, data, arg_ptr5);
				
					 while( (i < CMD_BUFFER_LEN) && buffer5[i] )
					 {
							
						 while (!(UART5->SR & 0x0080))
						 {} 
						 UART5->DR = ((u8) buffer5[i++] & 0xFF);
					 }
					va_end(arg_ptr5);
			}
		#endif
			
			#ifdef USING_USART6_PRINTF
			void usart6_printf(char * data, ...)
			{
					 u8 i=0 ;				
				
					 va_start(arg_ptr6,data);
				
					  vsnprintf(buffer6, CMD_BUFFER_LEN+1, data, arg_ptr6);
				
					 while( (i < CMD_BUFFER_LEN) && buffer6[i] )
					 {
							
						 while (!(USART6->SR & 0x0080))
						 {} 
						 USART6->DR = ((u8) buffer6[i++] & 0xFF);
					 }
					va_end(arg_ptr6);
			}
		#endif
			
			#ifdef USING_USARTX_PRINTF
			void usartx_printf(USART_TypeDef* USARTx,char * data, ...)
			{
					 u8 i=0 ;				
				
					 va_start(arg_ptr,data);
				
					  vsnprintf(buffer7, CMD_BUFFER_LEN+1, data, arg_ptr);
				
					 while( (i < CMD_BUFFER_LEN) && buffer7[i] )
					 {
							
						 while (!(USARTx->SR & 0x0080))
						 {} 
						 USARTx->DR = ((u8) buffer7[i++] & 0xFF);
					 }
					va_end(arg_ptr);
			}
			#endif
#endif
		
		
#if 1     //开启此宏 printf函数可用

#include "stdio.h"
#pragma import(__use_no_semihosting_swi)


extern int sendchar (int c);
extern int getkey   (void);


struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


int fputc(int c, FILE *f) {
  return (sendchar(c));
}


int fgetc(FILE *f) {
  return (getkey());
}


int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int c) {
  sendchar(c);
}


void _sys_exit(int return_code) {
label:  goto label;  /* endless loop */
}
/*----------------------------------------------------------------------------
  Write character to Serial Port
 *----------------------------------------------------------------------------*/
int sendchar (int c) {

#ifdef __DBG_ITM
  int i;
  ITM_SendChar (c & 0xFF);
  for (i = 10000; i; i--);
#else
  while (!(USART3->SR & 0x0080));
  USART3->DR = (c & 0xFF);
#endif  

  return (c);
}


/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
 *----------------------------------------------------------------------------*/
int getkey (void) {

#ifdef __DBG_ITM
  if (ITM_CheckChar())
    return ITM_ReceiveChar();
#else
  if (USART3->SR & 0x0020)
    return (USART3->DR);
#endif
  return (-1);
}
#endif



















