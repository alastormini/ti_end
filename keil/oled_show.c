#include "stdlib.h"
#include "ti_msp_dl_config.h"
#include "key.h"
#include "oled.h"
#include "board.h"
#include "oled_show.h"
#include "string.h"
#include "bsp_sg90.h"
#include "uart.h"
// 用户数据
uint8_t Key_Num;
uint8_t select_flag;

//0xAA 0x01 0x01 0x  0xFF

// 按键检测相关
unsigned char keynum = 1;
unsigned char user_pwd[2] = {0};
unsigned char flag1 = 0;
unsigned char key4_flag;
unsigned char key1_flag;
unsigned char range1 = 1;
unsigned char inputflag;
unsigned char oled_flag;
uint8_t KeyNum;
uint16_t i;

//坐标发送函数 
//模式1坐标1：0xAA 0x01 0x01 keynum 0xFF
//模式1坐标2：0xAA 0x01 0x02 keynum 0xFF

void send_uart_packet(uint8_t cmd, uint8_t keynum)
{
    uint8_t packet[] = {0xAA, 0x01, cmd, keynum, 0xFF};
    int len = sizeof(packet) / sizeof(packet[0]);

    for (int i = 0; i < len; i++) {
        uart_send_char(UART_1_INST, packet[i]);
    }
}

//oled通过按键设置坐标1，2同时发送位置信息给无人机
//key1确定  key2数字递增  key3数字递减  key4模式选择

void oled_progress(void)
{
	KeyNum=Key_GetNum();
//->按键确定
	if (KeyNum == 1)
	{
		if(key1_flag==1)
		{
			range1++;
			switch(select_flag%3)
			{
				case 1:
					if(range1==2)//range1=1进入模式1位置选择 =2发送坐标1 =3发送坐标2清零
					{
						OLED_Clear();
						OLED_ShowString(0,0, (uint8_t *)"model.position1", 16, 1);
						OLED_ShowNum(0, 20, keynum, 2, 16, 1);
						OLED_Refresh();
						key4_flag=1;
					}
					if(range1==3)//range1=1进入模式1位置选择 =2发送坐标1 =3发送坐标2清零
					{
						OLED_Clear();
						send_uart_packet(01,keynum);
						OLED_ShowString(0,0, (uint8_t *)"model.position2", 16, 1);
						keynum=1;
						OLED_ShowNum(0, 20, keynum, 2, 16, 1);
						OLED_Refresh();
					}
					if(range1==4)
					{
						send_uart_packet(02,keynum);
						keynum=1;
						oled_first();
						range1=0;
						key1_flag=0;
					}
				
					break;
				case 2:
						OLED_Clear();
						uint8_t packet2[] = {0xAA, 0x02, 0xFF};
						int len = sizeof(packet2) / sizeof(packet2[0]);

						for (int i = 0; i < len; i++) {
							uart_send_char(UART_1_INST, packet2[i]);
						}
						oled_first();
						range1=0;
						key1_flag=0;
					break;
				case 0:
						oled_first();
						range1=0;
						key1_flag=0;
					break;
				
				default:
					break;
			}
		}
	}

		//下一位->数字递减
	if (KeyNum == 5&&key4_flag==1)
	{
		if (keynum > 1) {
			keynum--;
		}
		OLED_ShowNum(0, 20, keynum, 2, 16, 1);
		OLED_Refresh();
	}
	//上一位->数字递增
	if (KeyNum == 2&&key4_flag==1)
	{
		
		keynum++;
		if(keynum == 13){keynum=1;}
		OLED_ShowNum(0, 20, keynum, 2, 16, 1);
		OLED_Refresh();
	}
	//数据发送给无人机->模式选择
	if (KeyNum == 4&&key4_flag==0)
	{
		key1_flag=1;
		select_flag++;
		switch(select_flag%3)
		{
			case 1:
				OLED_Clear();
				OLED_ShowString(0,0, (uint8_t *)"mode l ", 16, 1);
				break;
			case 2:
				OLED_Clear();
				OLED_ShowString(0,0, (uint8_t *)"mode 2 ", 16, 1);
				break;
			case 0:
				OLED_Clear();
				OLED_ShowString(0,0, (uint8_t *)"mode 3 ", 16, 1);
				break;
		}
	}
		OLED_Refresh();
}

//oled初始化页面，显示可选的三种模式

void oled_first(void)
{
	OLED_Clear();
	key4_flag=0;
	select_flag=0;
	OLED_ShowString(0,0, (uint8_t *)"please select", 16, 1);
	OLED_ShowString(0,16, (uint8_t *)"mode", 16, 1);
	OLED_ShowString(0,32, (uint8_t *)"1  2  3", 16, 1);
}



//按键检测

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
	if (DL_GPIO_readPins(KEY_PORT, KEY_KEY1_PIN)>0)
	{
		return 1;
	}
	if (DL_GPIO_readPins(KEY_PORT, KEY_KEY6_PIN)>0)
	{
		return 6;
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
