

#include "stm32f4xx.h"

static void TIM2_NVIC_Configration(void);

void tim2_init(u16 Arr,u16 Psc)
{
   RCC->APB1ENR|=1<<0;//enable tim2 clock
   TIM2->ARR=Arr;
   TIM2->PSC=Psc;

   TIM2->DIER|=1<<0;   //enable interrupt
   TIM2->DIER|=1<<6;   //awalys

   TIM2->CR1|=0x01;	   //enable tim2
   TIM2_NVIC_Configration();
}

static void TIM2_NVIC_Configration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  

  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;

  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}










