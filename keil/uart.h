#ifndef	__UART_H__
#define __UART_H__

#include "ti_msp_dl_config.h"
void uart_send_char(UART_Regs *uart,char ch);
void uart_send_string(UART_Regs *uart,char* str);
void uart_process(void);
extern uint32_t servo1_start_tick ;
extern uint8_t servo1_step;
extern uint8_t servo1_command_received; // 新增标志位
extern uint8_t oled_pack_flag;
void oled_show_uart1_bytes(uint8_t frameIndex);

typedef struct {
    uint32_t start_tick;
    uint8_t step;
    uint8_t command_received;
} servos;
extern servos servo[];

#endif
