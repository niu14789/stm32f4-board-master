
#include "stm32f4xx_it.h"
#include <stdio.h>
#include "led.h"
#define ERR_INFO "\r\nEnter HardFault_Handler, System Halt.\r\n"

void lcd_printf(char *data,...);


void EXTI0_IRQHandler( void )
{
	//static u16 cnt=0;
  //lcd_printf("Om exit test ->Interrupt Routine->%d\r\n",cnt++);
	LED0^=1;
  EXTI_ClearITPendingBit( EXTI_Line0 );
}
void TIM2_IRQHandler(void)//1s
{
//	static u16 cnt=0;
  if(TIM2->SR&0x0001)
  {
//    lcd_printf("Om timer test ->time count->%d\r\n",cnt++);
		LED0^=1;
  }
	TIM2->SR&=~(1<<0);
}

void NMI_Handler(void)
{
}



void SysTick_Handler(void)
{
	
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}


void MemManage_Handler(void)
{
  while (1)
  {
  }
}


void BusFault_Handler(void)
{
  while (1)
  {
  }
}


void UsageFault_Handler(void)
{
  while (1)
  {
  }
}


void SVC_Handler(void)
{
}


void DebugMon_Handler(void)
{
}


void PendSV_Handler(void)
{
}

