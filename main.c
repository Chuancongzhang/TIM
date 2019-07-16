#include "stm32f10x.h"
	
//void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM2, TIM_FLAG_Update) != RESET)
//	{
//		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
////		GPIO_Write(GPIOC, ~GPIO_ReadInputData(GPIOC));
//	}
//}

//void Tim2_Init(u32 Period, u32 Prescaler)
//{
//  //时钟开启TIM2
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

//	//结构体_定时器基础-声明
//	TIM_TimeBaseInitTypeDef TIM_TBIS;

//	TIM_DeInit(TIM2);
//  //自动重装载寄存器的值
//	TIM_TBIS.TIM_Period = Period;
//  //时钟预分频数
//	TIM_TBIS.TIM_Prescaler = Prescaler;
//  //向上计数模式
//	TIM_TBIS.TIM_CounterMode = TIM_CounterMode_Up;
//  //采样分频
//	TIM_TBIS.TIM_ClockDivision = TIM_CKD_DIV1;
//  //结构体_定时器基础-结束配置
//	TIM_TimeBaseInit(TIM2, &TIM_TBIS);

//	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
// //开关_定时器总开关
//	TIM_Cmd(TIM2, ENABLE);
//	
//	NVIC_InitTypeDef NVIC_InitS;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//	NVIC_InitS.NVIC_IRQChannel = TIM2_IRQn;
//	NVIC_InitS.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitS.NVIC_IRQChannelSubPriority = 0;
//	NVIC_Init(&NVIC_InitS);
//}

void TIM2_Delay_ms(uint16_t ms)
{
 //时钟开启TIM2
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 //结构体_定时器基础-声明
 TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
 //结构体_定时器基础-定时器分频设置，时钟预分频数为36000
 TIM_TimeBaseInitStruct.TIM_Prescaler= 35999;
 //结构体_定时器基础-定时器顶端设置
 TIM_TimeBaseInitStruct.TIM_Period=ms*2;
 //结构体_定时器基础-结束配置
 TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
 //设定定时时间到来以后停止定时器计数
 TIM_SelectOnePulseMode(TIM2, TIM_OPMode_Single);
 //开启SR中的UI标志
 TIM_ClearFlag(TIM2, TIM_IT_Update);
 //开关_定时器总开关
 TIM_Cmd(TIM2, ENABLE);
 //检测定时时间是否到来
 while(TIM_GetFlagStatus(TIM2, TIM_IT_Update)==RESET);
 //软件清除更新标志
 TIM_ClearFlag(TIM2, TIM_IT_Update);
}

int main()
{
	GPIO_InitTypeDef GPIO_InitS;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitS.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitS.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitS.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitS);
	GPIO_Write(GPIOC, 0xffff);
	
	//Tim2_Init(10000, 7199); //1s定时
	//Tim2_Init(599, 99); //833us 定时
	while (1)
	{
		GPIO_Write(GPIOC, 0xffff);
		TIM2_Delay_ms(1000);
		GPIO_Write(GPIOC, 0x0000);
		TIM2_Delay_ms(1000);
//		if (TIM_GetITStatus(TIM2, TIM_FLAG_Update) != RESET)
//		{
//			TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
//			GPIO_Write(GPIOC, ~GPIO_ReadInputData(GPIOC));
//			//value = value+1;
//		}
		
	}
//	return 0;
}

