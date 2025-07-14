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

      //开发板初始化
	board_init();
	oled_show();

      while(1)
      {
		oled_progress();
		delay_ms(10);
		process();
      }
}
