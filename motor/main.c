#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "stdio.h"
#include "delay.h"
#include "tim.h"
#include "motor.h"
#include "TCRT.h"
#include "avoid.h"
void delay(int n)
{
	int i;
	while(n--)
		for(i=0; i<8050; i++);
}

void Mode_Unauto(u8 cmd, u16 speed);

int main()
{
	//更换中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);


	delay_init();
	Motor_Init();
	Usart1_Init(9600);
  Usart2_Init(9600);
  Usart3_Init(9600);
	Motor_Go();
	Motor_SpeedSet(0, 0);
 //LED_Init();

	 Tracing_Init();
	 Avoid_init();
	
	
	u8 flag_mode = 0;
	u8 flag_unauto_cmd = 0;
	u16 speed_cmd = 0;
  
	while(1)//防止跑飞
	{
		if(1 == global_flag_recv)
		{
			flag_mode = global_recv_buff[1];
			flag_unauto_cmd = global_recv_buff[2];
			speed_cmd = (global_recv_buff[3] << 8) + global_recv_buff[4];
			global_flag_recv = 0;
			
			if(flag_mode == 0x22)
						Serial_SendNumber(speed_cmd);  

		}
		
		switch(flag_mode)
		{
			case 0x11:
				//手动模式
          Mode_Unauto(flag_unauto_cmd, speed_cmd);
				break;
			
			case 0x22:
					Track(speed_cmd);
				break;
			
			case 0x33:
           Avoid(speed_cmd);
				break;
		}
	}
}


void Mode_Unauto(u8 cmd, u16 speed)
{
 
	switch(cmd)
	{
		case 0x11:
			//前进
			Motor_Go();
			Motor_SpeedSet(speed, speed);
			break;
		case 0x00:
			//停止
			Motor_Go();
			Motor_SpeedSet(0, 0);
			break;		
    	case 0x22:
			//右转
			Motor_Right();
			Motor_SpeedSet(speed, speed);
      break;
     case 0x33:
			//左转
			Motor_Left();
			Motor_SpeedSet(speed, speed);
      break;
    	case 0x44:
			//后退
			Motor_Back();
			Motor_SpeedSet(speed, speed);
      break;
		default:
			break;
	}

}
