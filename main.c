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
//  //ʱ�ӿ���TIM2
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

//	//�ṹ��_��ʱ������-����
//	TIM_TimeBaseInitTypeDef TIM_TBIS;

//	TIM_DeInit(TIM2);
//  //�Զ���װ�ؼĴ�����ֵ
//	TIM_TBIS.TIM_Period = Period;
//  //ʱ��Ԥ��Ƶ��
//	TIM_TBIS.TIM_Prescaler = Prescaler;
//  //���ϼ���ģʽ
//	TIM_TBIS.TIM_CounterMode = TIM_CounterMode_Up;
//  //������Ƶ
//	TIM_TBIS.TIM_ClockDivision = TIM_CKD_DIV1;
//  //�ṹ��_��ʱ������-��������
//	TIM_TimeBaseInit(TIM2, &TIM_TBIS);

//	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
// //����_��ʱ���ܿ���
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
 //ʱ�ӿ���TIM2
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 //�ṹ��_��ʱ������-����
 TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
 //�ṹ��_��ʱ������-��ʱ����Ƶ���ã�ʱ��Ԥ��Ƶ��Ϊ36000
 TIM_TimeBaseInitStruct.TIM_Prescaler= 35999;
 //�ṹ��_��ʱ������-��ʱ����������
 TIM_TimeBaseInitStruct.TIM_Period=ms*2;
 //�ṹ��_��ʱ������-��������
 TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
 //�趨��ʱʱ�䵽���Ժ�ֹͣ��ʱ������
 TIM_SelectOnePulseMode(TIM2, TIM_OPMode_Single);
 //����SR�е�UI��־
 TIM_ClearFlag(TIM2, TIM_IT_Update);
 //����_��ʱ���ܿ���
 TIM_Cmd(TIM2, ENABLE);
 //��ⶨʱʱ���Ƿ���
 while(TIM_GetFlagStatus(TIM2, TIM_IT_Update)==RESET);
 //���������±�־
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
	
	//Tim2_Init(10000, 7199); //1s��ʱ
	//Tim2_Init(599, 99); //833us ��ʱ
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

