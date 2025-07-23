#include "board.h"
#include "stdio.h"
#include "bsp_sg90.h"
#include <stdlib.h>
#include "buzzer.h"
#include "oled_show.h"
#include "oled.h"
#include "uart.h"

servos servo[4];
typedef struct {
    uint8_t flag;
    int count;
    int bfw;
    int bfr;
	int buflen;
} UART_RxBuffer;
uint8_t uart1_receivedData[4][80];
uint8_t uart3_receivedData[4][80];
UART_RxBuffer uart1_rx = {0};
UART_RxBuffer uart3_rx = {0};
uint8_t oled_pack_flag;

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
//串口1数据接收帧头0xAA 帧尾0xFF
void UART_1_INST_IRQHandler(void) 
{
	uint8_t res;
	switch(DL_UART_getPendingInterrupt(UART_1_INST)) 
	{
		case DL_UART_IIDX_RX:
			res= DL_UART_Main_receiveData(UART_1_INST);
				if(uart1_rx.flag==0&&res==0xAA)
				{
					uart1_rx.flag=1;
					uart1_rx.count=0;
				}
				if(uart1_rx.flag==1)
				{
					//开始接收储存数据
					uart1_receivedData[uart1_rx.bfw][uart1_rx.count]=res;
						uart1_rx.count++;
					if(uart1_rx.flag==1&&res==0xFF)
					{
						uart1_rx.flag=0;
						uart1_rx.bfw=(uart1_rx.bfw+1)&(4-1);
						uart1_rx.buflen+=1;			
						uart1_rx.count=0;
					}
					if(uart1_rx.count>=80)
					{
						uart1_rx.flag=0;
						uart1_rx.count=0;
					}
					break;
		
				default:
					break;
				
				}
	}
}
//串口3数据接收帧头0xAA 帧尾0xFF
void UART_3_INST_IRQHandler(void) {
	
	uint8_t res;
	switch(DL_UART_getPendingInterrupt(UART_3_INST)) 
	{
		case DL_UART_IIDX_RX:
			res= DL_UART_Main_receiveData(UART_3_INST);
				if(uart3_rx.flag==0&&res==0xAA)
				{
					uart3_rx.flag=1;
					uart3_rx.count=0;
				}
				if(uart3_rx.flag==1){
				//开始接收储存数据
				uart3_receivedData[uart3_rx.bfw][uart3_rx.count]=res;
					uart3_rx.count++;
				if(uart3_rx.flag==1&&res==0xFF)
				{
					uart3_rx.flag=0;
					uart3_rx.bfw=(uart3_rx.bfw+1)&(4-1);
					uart3_rx.buflen+=1;			
					uart3_rx.count=0;
				}
				if(uart3_rx.count>=80)
				{
					uart3_rx.flag=0;
					uart3_rx.count=0;
				}
			break;
			
		default:
			break;
		}
	}
}

//解析数据包
//帧头0xAA 编号 状态 帧尾0xFF
//编号0x01~0x04舵机 0x05~0x06激光 0x07蜂鸣器 0x09oled信息接收
//舵机打开				0xAA 01~04 0x01 FF
//360舵机正转-停止-反转  0xAA 01~04 0x02 FF
//180舵机控制摄像头90    0xAA 01~04 0x03 FF
//激光打开	 			0xAA 05~06 0x01 FF
//激光关闭				0xAA 05~06 0x00 FF
//蜂鸣器响				0xAA 08    次数 FF
//oled信息接收			0xAA 09	   模式 数据 成功/失败    FF
//示例：激光5打开		0xAA 05~06 0x01 FF
void uart_process(void)
{
	if(uart1_rx.buflen)
	{
		char buf[40];
        sprintf(buf, "%02X %02X %02X %02X %02X\n", uart1_receivedData[uart1_rx.bfr][0],uart1_receivedData[uart1_rx.bfr][1], uart1_receivedData[uart1_rx.bfr][2],uart1_receivedData[uart1_rx.bfr][3],uart1_receivedData[uart1_rx.bfr][4]);
        uart_send_string(UART_1_INST, buf);
		
		if(uart1_receivedData[uart1_rx.bfr][0]==0xAA&&(uart1_receivedData[uart1_rx.bfr][3]==0xFF||uart1_receivedData[uart1_rx.bfr][5]==0xFF))
	{
		switch(uart1_receivedData[uart1_rx.bfr][1])
		{
			case 0x01://舵机一号
				if(uart1_receivedData[uart1_rx.bfr][2]==0x01)//舵机打开
				{
					// 开始旋转序列
					motors[0].state = ROTATING_STATE;
					motors[0].current_angle = 160;       // 从0°开始
					motors[0].target_angle = 100;
					motors[0].rotation_counter = 0;    // 重置计数器
					// 发送开始消息
					uart_send_string(UART_1_INST,"servo1 Start rotation: 160°→100°\n");
				}
				else if(uart1_receivedData[uart1_rx.bfr][2]==0x02)//舵机正转-停止-反转
				{
					servo[1].command_received = 1; // 设置标志
					servo[1].step = 0;             // 重置状态
				}
				else if(uart1_receivedData[uart1_rx.bfr][2]==0x03)//舵机旋转角度
				{
					// 开始旋转序列
					motors[0].state = ROTATING_STATE;
					motors[0].current_angle = 0;       // 从0°开始
					motors[0].target_angle = 90;
					motors[0].rotation_counter = 0;    // 重置计数器
					// 发送开始消息
					uart_send_string(UART_1_INST,"servo1 Start rotation\n");
				}
				break;
			case 0x02://舵机二号
				if(uart1_receivedData[uart1_rx.bfr][2]==0x01)//舵机打开
				{
					// 开始旋转序列
					motors[1].state = ROTATING_STATE;
					motors[1].current_angle = 160;       // 从160°开始
					motors[1].target_angle = 100;
					motors[1].rotation_counter = 0;    // 重置计数器
					// 发送开始消息
					uart_send_string(UART_1_INST,"servo2 Start rotation: 160°→100°\n");
				}
				else if(uart1_receivedData[uart1_rx.bfr][2]==0x02)
				{
					servo[2].command_received = 1; // 设置标志
					servo[2].step = 0;             // 重置状态
				}
				else if(uart1_receivedData[uart1_rx.bfr][2]==0x03)//舵机旋转角度
				{
					// 开始旋转序列
					motors[1].state = ROTATING_STATE;
					motors[1].current_angle = 0;       // 从0°开始
					motors[1].target_angle = 90;
					motors[1].rotation_counter = 0;    // 重置计数器
					// 发送开始消息
					uart_send_string(UART_1_INST,"servo2 Start rotation\n");
				}

				break;
			case 0x03://舵机三号
				if(uart1_receivedData[uart1_rx.bfr][2]==0x01)//舵机打开
				{
					// 开始旋转序列
					motors[2].state = ROTATING_STATE;
					motors[2].current_angle = 160;       // 从160°开始
					motors[2].target_angle = 100;
					motors[2].rotation_counter = 0;    // 重置计数器
					// 发送开始消息
					uart_send_string(UART_1_INST,"servo3 Start rotation: 160°→100°\n");
				}
				else if(uart1_receivedData[uart1_rx.bfr][2]==0x02)
				{
					servo[3].command_received = 1; // 设置标志
					servo[3].step = 0;             // 重置状态
				}
				else if(uart1_receivedData[uart1_rx.bfr][2]==0x03)
				{
					// 开始旋转序列
					motors[2].state = ROTATING_STATE;
					motors[2].current_angle = 0;       // 从0°开始
					motors[2].target_angle = 90;
					motors[2].rotation_counter = 0;    // 重置计数器
					// 发送开始消息
					uart_send_string(UART_1_INST,"servo3 Start rotation\n");
				}

				break;
			case 0x04://舵机四号
				if(uart1_receivedData[uart1_rx.bfr][2]==0x01)//舵机打开
				{
					motors[3].state = ROTATING_STATE;
					motors[3].current_angle = 160;       // 从160°开始
					motors[3].target_angle = 100;
					motors[3].rotation_counter = 0;    // 重置计数器
					// 发送开始消息
					uart_send_string(UART_1_INST,"servo3 Start rotation: 160°→100°\n");
				}
				else if(uart1_receivedData[uart1_rx.bfr][2]==0x02)
				{
					servo[4].command_received = 1; // 设置标志
					servo[4].step = 0;             // 重置状态
				}
				else if(uart1_receivedData[uart1_rx.bfr][2]==0x03)
				{
					// 开始旋转序列
					motors[3].state = ROTATING_STATE;
					motors[3].current_angle = 0;       // 从0°开始
					motors[3].target_angle = 90;
					motors[3].rotation_counter = 0;    // 重置计数器
					// 发送开始消息
					uart_send_string(UART_1_INST,"servo4 Start rotation\n");
				}
				break;
			case 0x05://激光一号
				if(uart1_receivedData[uart1_rx.bfr][2]==0x01)//激光打开
				{
					DL_GPIO_setPins(lazer_PORT,lazer_lazer1_PIN);
					uart_send_string(UART_3_INST,"lazer1 ready");
				}else{DL_GPIO_clearPins(lazer_PORT,lazer_lazer1_PIN);}
				break;
			case 0x06://激光二号
				if(uart1_receivedData[uart1_rx.bfr][2]==0x01)//激光打开
				{
					DL_GPIO_setPins(lazer_PORT,lazer_lazer2_PIN);
					uart_send_string(UART_1_INST,"lazer2 ready");
				}else{DL_GPIO_clearPins(lazer_PORT,lazer_lazer2_PIN);}
				break;
			case 0x07://蜂鸣器
				if(uart1_receivedData[uart1_rx.bfr][2])//蜂鸣器打开
				{
					
					buzzer(uart1_receivedData[uart1_rx.bfr][2]);//响几下
					uart_send_string(UART_1_INST,"buzzer ready");
				}
				break;
			case 0x08://串口屏
				sprintf(buf, "AA %02X %02X %02X %02X FF", uart1_receivedData[uart1_rx.bfr][2],uart1_receivedData[uart1_rx.bfr][3], uart1_receivedData[uart1_rx.bfr][4],uart1_receivedData[uart1_rx.bfr][5]);
				uart_send_string(UART_1_INST, buf);
				break;
			case 0x09://oled
				if(uart1_receivedData[uart1_rx.bfr][2])//串口接收到坐标信息
				{
					oled_show_uart1_bytes(uart1_rx.bfr);//oled最下面一行显示 模式 数据 1/0（发送成功/发送失败）
				}
				
				break;

			default:
				break;
		}
	uart1_rx.buflen -= 1; //该包数据已分析完缓存中数据包数减1
	uart1_rx.bfr = (uart1_rx.bfr + 1) & (4- 1); //移到下一读取索引位置
	}
	}

}

//oled显示无人机是否接受到数据
//模式 数据 1/0（成功/失败）
//示例：显示数据01，01，01success
//模式1，数据内容1，发送成功

void oled_show_uart1_bytes(uint8_t frameIndex)
{
    // 获取字节值
    uint8_t byte2 = uart1_receivedData[frameIndex][2];
    uint8_t byte3 = uart1_receivedData[frameIndex][3];
    uint8_t byte4 = uart1_receivedData[frameIndex][4];

    // 创建用于显示的字符串缓冲区
    char str[20];

    // 格式化为十六进制字符串
	if(byte4==0x01)
	{
    sprintf(str, "%02X,%02X,%02Xsuccess", byte2,byte3,byte4);
    OLED_ShowString(0, 50, (uint8_t *)str, 12, 1);  // 显示
	}else if(byte4==0x00){
	sprintf(str, "%02X,%02X,%02Xfailure", byte2,byte3,byte4);
    OLED_ShowString(0, 50, (uint8_t *)str, 12, 1);  // 显示
	}

    // 刷新显示
    OLED_Refresh();
}
