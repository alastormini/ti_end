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
	//oled初始显示
	DL_GPIO_clearPins(led_PORT,led_led1_PIN);
	DL_GPIO_clearPins(led_PORT,led_led2_PIN);
	DL_GPIO_clearPins(led_PORT,led_led3_PIN);

	oled_first();
      while(1)
      {
			oled_progress();
			uart_process();
			servo_progress2();
      }
}
