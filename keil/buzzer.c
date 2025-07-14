#include "buzzer.h"
#include "board.h"
#include "ti_msp_dl_config.h"

//蜂鸣器响的次数，400ms秒响一次
void buzzer(unsigned int i)
{
	for(int j=0;j<i;j++)
	{
		DL_GPIO_setPins(buzzer_PORT,buzzer_beep_PIN);
		delay_ms(200);
		DL_GPIO_clearPins(buzzer_PORT,buzzer_beep_PIN);
		delay_ms(200);
	}
}

