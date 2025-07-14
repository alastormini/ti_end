#include "stdlib.h"
#include "ti_msp_dl_config.h"
#include "key.h"
#include "oled.h"
#include "board.h"
#include "oled_show.h"
#include "string.h"
// 用户数据
uint8_t Key_Num;

// 按键检测相关
unsigned char keynum = 0;
unsigned char user_pwd[6] = {0};
unsigned char flag1 = 0;
unsigned char range1 = 0;
unsigned char inputflag;
uint8_t KeyNum;
uint16_t i;
void oled_send(void)
{
	char buffer[10];  // 足够放10个数字 

    for (int i = 0; i < 6; i++) {
        buffer[i] = '0' + user_pwd[i];  // 数字转字符
    }
    buffer[6] = '\0';  // 字符串结束符

    uart_send_string(UART_1_INST,buffer);
    uart_send_string(UART_1_INST,"\r\n");  // 换行，方便查看

}
void oled_progress(void)
{
	
		KeyNum=Key_GetNum();
	//数字递增
		if (KeyNum == 3)
		{
				keynum++;
				if(keynum<=10)
				{
						if(keynum==10)keynum=0;
						user_pwd[5]=keynum;
				}
				oled_show();
		}
		
		//下一位
		if (KeyNum == 2)
		{
					for(range1=0;range1<=4;range1++)
					{
						keynum=0;
						user_pwd[range1]=user_pwd[range1+1];
					}
					user_pwd[5]=0;
					oled_show();

		}
		//返回
		if (KeyNum == 5)
		{
					for(range1=5;range1>=1;range1--)
					{
						user_pwd[range1]=user_pwd[range1-1];	
					}
					user_pwd[0]=0;
					oled_show();

		}
		//数据发送给无人机
		if (KeyNum == 4)
		{
				OLED_Clear();


				OLED_Refresh();flag1++;
				if(flag1%2==0)
				{	
					memset(user_pwd, 0, sizeof(user_pwd));
					oled_show();
				}else{
					oled_send();
					OLED_ShowString(0,0,(uint8_t *)"Send complete",16,1);
				}

		}
			OLED_ShowNum(0,50,i++,5,12,1);
			OLED_Refresh();
}

void oled_show(void)
{
//	OLED_Refresh();
	unsigned char range;
	OLED_ShowString(0,0, (uint8_t *)"change position", 16, 1);
	for(range=0;range<=5;range++)
	{
		OLED_ShowNum(0+16*range, 20, user_pwd[range], 1, 16, 1);
	}
	OLED_Refresh();
}
uint8_t Key_GetState(void)
{
	if (DL_GPIO_readPins(KEY_PORT, KEY_KEY3_PIN)>0)
	{
		return 3;
	}
	if (DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN)>0)
	{
		return 2;
	}
	if (DL_GPIO_readPins(KEY_PORT, KEY_KEY4_PIN)>0)
	{
		return 4;
	}
	if (DL_GPIO_readPins(KEY_PORT, KEY_KEY5_PIN)>0)
	{
		return 5;
	}
	return 0;
}
uint8_t Key_GetNum(void)
{
	uint8_t Temp;
	if (Key_Num)
	{
		Temp = Key_Num;
		Key_Num = 0;
		return Temp;
	}
	return 0;
}

void TIMER_1_INST_IRQHandler(void)
{
	static uint8_t CurrState, PrevState;
    switch (DL_TimerG_getPendingInterrupt(TIMER_1_INST))
    {
        case DL_TIMER_IIDX_ZERO:
		PrevState = CurrState;
		CurrState = Key_GetState();
		
		if (CurrState != 0 && PrevState == 0)
		{
			Key_Num = CurrState;
		}	 
	}
}

