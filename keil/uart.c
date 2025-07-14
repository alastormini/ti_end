#include "board.h"
#include "stdio.h"
#include "bsp_sg90.h"
#include <stdlib.h>
#include "buzzer.h"
uint8_t receivedData[4][80];
uint8_t flag=0;//接受标志
int buflen=0;//数据包数量
int count=0;;//接收数组字节数
int bfw=0;//写索引
int bfr=0;//读索引


void uart_send_char(UART_Regs *uart,char ch)
{
	//当串口0忙的时候等待，不忙的时候再发送传进来的字符
	while( DL_UART_isBusy(uart) == true );
	//发送单个字符
	DL_UART_Main_transmitData(uart, ch);

}
//串口发送字符串
void uart_send_string(UART_Regs *uart,char* str)
{
	//当前字符串地址不在结尾 并且 字符串首地址不为空
	while(*str!=0&&str!=0)
	{
		//发送字符串首地址中的字符，并且在发送完成之后首地址自增
		uart_send_char(uart,*str++);
	}
}

void UART_1_INST_IRQHandler(void) 
{
	uint8_t res;
	switch(DL_UART_getPendingInterrupt(UART_1_INST)) 
	{
		case DL_UART_IIDX_RX:
			res= DL_UART_Main_receiveData(UART_1_INST);
				if(flag==0&&res==0xAA)
				{
					flag=1;
					count=0;
				}
				if(flag==1)
				{
					//开始接收储存数据
					receivedData[bfw][count]=res;
						count++;
					if(flag==1&&res==0xFF)
					{
						flag=0;
						bfw=(bfw+1)&(4-1);
						buflen+=1;			
						count=0;
					}
					if(count>=80)
					{
						flag=0;
						count=0;
					}
					break;
		
				default:
					break;
				
				}
	}
}
void UART_3_INST_IRQHandler(void) {
	
	uint8_t res;
	switch(DL_UART_getPendingInterrupt(UART_3_INST)) 
	{
		case DL_UART_IIDX_RX:
			res= DL_UART_Main_receiveData(UART_3_INST);
				if(flag==0&&res==0xAA)
				{
					flag=1;
					count=0;
				}
				if(flag==1){
				//开始接收储存数据
				receivedData[bfw][count]=res;
					count++;
				if(flag==1&&res==0xFF)
				{
					flag=0;
					bfw=(bfw+1)&(4-1);
					buflen+=1;			
					count=0;
				}
				if(count>=80)
				{
					flag=0;
					count=0;
				}
			break;
			
		default:
			break;
		}
	}
}

//解析数据包
void process(void)
{
	if(buflen)
	{
		char buf[40];
        sprintf(buf, "%02X %02X %02X %02X\n", receivedData[bfr][0],receivedData[bfr][1], receivedData[bfr][2],receivedData[bfr][3]);
        uart_send_string(UART_1_INST, buf);
		switch(receivedData[bfr][1])
		{
			case 0x01://舵机一号
				if(receivedData[bfr][2]==0x01)//舵机打开
				{
				
					// 开始旋转序列
					motors[0].state = ROTATING_STATE;
					motors[0].current_angle = 160;       // 从0°开始
					motors[0].target_angle = 100;
					motors[0].rotation_counter = 0;    // 重置计数器
					// 发送开始消息
					uart_send_string(UART_1_INST,"servo1 Start rotation: 160°→100°\n");
				
				}
				break;
			case 0x02://舵机二号
				if(receivedData[bfr][2]==0x01)//舵机打开
				{
					// 开始旋转序列
					motors[1].state = ROTATING_STATE;
					motors[1].current_angle = 160;       // 从160°开始
					motors[1].target_angle = 100;
					motors[1].rotation_counter = 0;    // 重置计数器
					// 发送开始消息
					uart_send_string(UART_1_INST,"servo2 Start rotation: 160°→100°\n");

				}
				break;
			case 0x03://舵机三号
				if(receivedData[bfr][2]==0x01)//舵机打开
				{
					// 开始旋转序列
					motors[2].state = ROTATING_STATE;
					motors[2].current_angle = 160;       // 从160°开始
					motors[2].target_angle = 100;
					motors[2].rotation_counter = 0;    // 重置计数器
					// 发送开始消息
					uart_send_string(UART_1_INST,"servo3 Start rotation: 160°→100°\n");

				}
				break;
			case 0x04://舵机四号
				if(receivedData[bfr][2]==0x01)//舵机打开
				{
					motors[3].state = ROTATING_STATE;
					motors[3].current_angle = 160;       // 从160°开始
					motors[3].target_angle = 100;
					motors[3].rotation_counter = 0;    // 重置计数器
					// 发送开始消息
					uart_send_string(UART_1_INST,"servo4 Start rotation: 160°→100°\n");

				}
				break;
			case 0x05://激光一号
				if(receivedData[bfr][2]==0x01)//激光打开
				{
					DL_GPIO_setPins(lazer_PORT,lazer_lazer1_PIN);
					uart_send_string(UART_3_INST,"lazer1 ready");
				}else{DL_GPIO_clearPins(lazer_PORT,lazer_lazer1_PIN);}
				break;
			case 0x06://激光二号
				if(receivedData[bfr][2]==0x01)//激光打开
				{
					DL_GPIO_setPins(lazer_PORT,lazer_lazer2_PIN);
					uart_send_string(UART_1_INST,"lazer2 ready");
				}else{DL_GPIO_clearPins(lazer_PORT,lazer_lazer2_PIN);}
				break;
			case 0x07://蜂鸣器
				if(receivedData[bfr][2])//蜂鸣器打开
				{
					
					buzzer(receivedData[bfr][2]);//响几下
					uart_send_string(UART_1_INST,"buzzer ready");
				}
				break;
			case 0x08://串口屏
				sprintf(buf, "%02X %02X %02X %02X", receivedData[bfr][2],receivedData[bfr][3], receivedData[bfr][4],receivedData[bfr][5]);
				uart_send_string(UART_1_INST, buf);
				break;

			default:
				break;
		}
	 buflen -= 1; //该包数据已分析完缓存中数据包数减1
	bfr = (bfr + 1) & (4- 1); //移到下一读取索引位置
	}

}


