#ifndef	__UART_H__
#define __UART_H__

#include "ti_msp_dl_config.h"
void uart_send_char(UART_Regs *uart,char ch);
void uart_send_string(UART_Regs *uart,char* str);
void process(void);

#endif
