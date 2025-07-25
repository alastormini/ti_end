/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 立创论坛：https://oshwhub.com/forum
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-26     LCKFB     first version
 */
#ifndef	__BOARD_H__
#define __BOARD_H__

#include "ti_msp_dl_config.h"
#define START_ANGLE_CMD  'A'  // 角度指令起始符


void board_init(void);

void delay_us(unsigned long __us);
void delay_ms(unsigned long ms);
void delay_1us(unsigned long __us);
void delay_1ms(unsigned long ms);

//串口发送函数
void uart_send_char(UART_Regs *uart,char ch);
void uart_send_string(UART_Regs *uart,char* str);

//void uart0_send_string(char* str);



#endif
