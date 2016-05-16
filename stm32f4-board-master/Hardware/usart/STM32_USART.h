


#ifndef __STM32_USART_H__

#define __STM32_USART_H__

#include "stm32f4xx.h"

#define DMA_DIR_M2P  0x8000
#define DMA_DIR_P2M  0x0000

#define DMA_MODE_CIRCOLAR 0x4000
#define DMA_MODE_SINGLE   0x0000


#define USING_USART_PRINTF
#define USING_USARTX_PRINTF

#ifdef USING_USART_PRINTF
 	#define USING_USART1_PRINTF
//  	#define USING_USART2_PRINTF
//  	#define USING_USART3_PRINTF
//  	#define USING_USART4_PRINTF
//  	#define USING_USART5_PRINTF
 	//#define USING_USART6_PRINTF
#endif



#define PA9_PA10  0xA9AA0011
#define PA9_PB7   0xA9B70412
#define PB6_PB7   0xB6B74422
#define PB6_PA10  0xB6AA4021

#define PA2_PA3   0xA2A30011
#define PA2_PD6   0xA2D60C18
#define PD5_PD6   0xD5D6CC88
#define PD5_PA3   0xD5A3C081

#define PB10_PB11 0xBABB4422
#define PB10_PC11 0xBACB4824
#define PB10_PD9  0xBAD94C28
#define PC10_PB11 0xCABB8442
#define PC10_PC11 0xCACB8844
#define PC10_PD9  0xCAD98C48
#define PD8_PB11  0xD8BBC482
#define PD8_PC11  0xD8CBC884
#define PD8_PD9   0xD8D9CC88

#define PA0_PA1   0xA0A10011
#define PA0_PC11  0xA0CB0814
#define PC10_PA1  0xCAA18041

#define PC12_PD2  0xCCD28C48

#define PC6_PC7   0xC6C78844


#define USART1_TX  DMA2_Stream7 //4
#define USART1_RX  DMA2_Stream2 //4

#define USART2_TX  DMA1_Stream6 //4
#define USART2_RX  DMA1_Stream5 //4

#define USART3_TX  DMA1_Stream3 //4
#define USART3_RX  DMA1_Stream1 //4

#define UART4_TX  DMA1_Stream4 //4
#define UART4_RX  DMA1_Stream2 //4

#define UART5_TX  DMA1_Stream7 //4
#define UART5_RX  DMA1_Stream0 //4

#define USART6_TX  DMA2_Stream6 //5
#define USART6_RX  DMA2_Stream1 //5



/*----------interupt------------*/
#define USART1_TX_IRQ   DMA2_Stream7_IRQn //4
#define USART1_RX_IRQ   DMA2_Stream2_IRQn //4

#define USART2_TX_IRQ   DMA1_Stream6_IRQn //4
#define USART2_RX_IRQ   DMA1_Stream5_IRQn //4

#define USART3_TX_IRQ   DMA1_Stream3_IRQn //4
#define USART3_RX_IRQ   DMA1_Stream1_IRQn //4

#define UART4_TX_IRQ    DMA1_Stream4_IRQn //4
#define UART4_RX_IRQ    DMA1_Stream2_IRQn //4

#define UART5_TX_IRQ    DMA1_Stream7_IRQn //4
#define UART5_RX_IRQ    DMA1_Stream0_IRQn //4

#define USART6_TX_IRQ   DMA2_Stream6_IRQn //5
#define USART6_RX_IRQ   DMA2_Stream1_IRQn //5

void stm32_usart_init(USART_TypeDef* USARTx,uint32_t txrx,uint32_t baudrate);
void stm32_usart_dma(USART_TypeDef* USARTx,DMA_Stream_TypeDef* DMAy_Streamx,uint16_t message,uint8_t *dmabuf,uint32_t DMA_IT,uint8_t USART_IRQn);

#ifdef USING_USARTX_PRINTF
      void usartx_printf(USART_TypeDef* USARTx,char * data, ...);
#endif
#ifdef USING_USART1_PRINTF
			void usart1_printf(char * data, ...);
#endif
#ifdef USING_USART2_PRINTF
			void usart2_printf(char * data, ...);
#endif
#ifdef USING_USART3_PRINTF
			void usart3_printf(char * data, ...);
#endif
#ifdef USING_USART4_PRINTF
			void usart4_printf(char * data, ...);
#endif
#ifdef USING_USART5_PRINTF
			void usart5_printf(char * data, ...);
#endif
#ifdef USING_USART6_PRINTF
			void usart6_printf(char * data, ...);
#endif




#endif



