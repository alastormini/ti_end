#include "board.h"
#include <stdio.h>
#include "bsp_sg90.h"
#include "uart.h"
#include "key.h"
#include "buzzer.h"
#include "oled.h"
#include "oled_show.h"
volatile unsigned char uart_data = 0;

int main(void)
{

    //�������ʼ��
	board_init();
	//oled��ʼ��ʾ
	oled_first();
      while(1)
      {
			oled_progress();
			uart_process();
			servo_progress2();
      }
}
