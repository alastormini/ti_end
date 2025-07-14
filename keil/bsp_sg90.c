#include "bsp_sg90.h"
#include "board.h"
#include "stdio.h"
unsigned int Servo_Angle = 0;//舵机角度
//计时器中结构体

motorcontrol motors[4];
/******************************************************************
       配置占空比 范围 0 ~ (per-1)
   t = 0.5ms——————-舵机会转动 0 °
   t = 1.0ms——————-舵机会转动 45°
   t = 1.5ms——————-舵机会转动 90°
   t = 2.0ms——————-舵机会转动 135°
   t = 2.5ms——————-舵机会转动180°
******************************************************************/


/******************************************************************
 * 函 数 名 称：Set_Servo_Angle
 * 函 数 说 明：设置角度
 * 函 数 形 参：angle=要设置的角度，范围0-180
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void Set_Servo_Angle(unsigned int servo,unsigned int angle)
{
      uint32_t period = 400;
      if(angle > 180)
      {
            angle = 180; // 限制角度在0到180度之间
      }

      Servo_Angle = angle;

      // 计算PWM占空比
      // 0.5ms对应的计数 = 10
      // 2.5ms对应的计数 = 50
      float min_count = 10.0f;
      float max_count = 50.0f;
      float range = max_count - min_count;
      float ServoAngle = min_count + (((float)angle / 180.0f) * range);
	if(servo==1)
	{
		DL_TimerG_setCaptureCompareValue(PWM_INST, (unsigned int)(ServoAngle + 0.5f), GPIO_PWM_C1_IDX);
	}
	if(servo==2)
	{
		DL_TimerG_setCaptureCompareValue(PWM_INST, (unsigned int)(ServoAngle + 0.5f), GPIO_PWM_C2_IDX);
	}
	if(servo==3)
	{
		DL_TimerG_setCaptureCompareValue(PWM_INST, (unsigned int)(ServoAngle + 0.5f), GPIO_PWM_C3_IDX);
	}
	if(servo==4)
	{
		DL_TimerG_setCaptureCompareValue(servo1_INST, (unsigned int)(ServoAngle + 0.5f), GPIO_servo1_C1_IDX);
	}

}



/******************************************************************
 * 函 数 名 称：读取当前角度
 * 函 数 说 明：Get_Servo_Angle
 * 函 数 形 参：无
 * 函 数 返 回：当前角度
 * 作       者：LC
 * 备       注：使用前必须确保之前使用过
                void Set_Servo_Angle(unsigned int angle)
                函数设置过角度
******************************************************************/
unsigned int Get_Servo_Angle(void)
{
      return Servo_Angle;
}


void TIMER_0_INST_IRQHandler(void) {
    // 每10ms触发一次
    static uint32_t tick_counter = 0;
    tick_counter++;
			// 检查是否需要更新舵机角度
		if (motors[0].state == ROTATING_STATE) {
			// 每100ms更新一次角度 (10 * 10ms = 100ms)
			if (tick_counter % 2 == 0) {
				// 增加角度（每10ms增加1度）
				if (motors[0].current_angle > motors[0].target_angle) {
					motors[0].current_angle--;
					Set_Servo_Angle(1,motors[0].current_angle);
					motors[0].rotation_counter++;
				} 
				// 完成旋转
				else {
					motors[0].state = IDLE_STATE;  // 返回空闲状态
				}
			}
		}
		if (motors[1].state == ROTATING_STATE) {
			// 每100ms更新一次角度 (10 * 10ms = 100ms)
			if (tick_counter % 2 == 0) {
				// 增加角度（每10ms增加1度）
				if (motors[1].current_angle > motors[1].target_angle) {
					motors[1].current_angle--;
					Set_Servo_Angle(2,motors[1].current_angle);
					motors[1].rotation_counter++;
				} 
				// 完成旋转
				else {
					motors[1].state = IDLE_STATE;  // 返回空闲状态
				}
			}
		}

			if (motors[2].state == ROTATING_STATE) {
			// 每100ms更新一次角度 (10 * 10ms = 100ms)
			if (tick_counter % 2 == 0) {
				// 增加角度（每10ms增加1度）
				if (motors[2].current_angle > motors[2].target_angle) {
					motors[2].current_angle--;
					Set_Servo_Angle(3,motors[2].current_angle);
					motors[2].rotation_counter++;
				} 
				// 完成旋转
				else {
					motors[2].state = IDLE_STATE;  // 返回空闲状态
				}
			}
		}

		if (motors[3].state == ROTATING_STATE) {
			// 每100ms更新一次角度 (10 * 10ms = 100ms)
			if (tick_counter % 2 == 0) {
				// 增加角度（每10ms增加1度）
				if (motors[3].current_angle > motors[3].target_angle) {
					motors[3].current_angle--;
					Set_Servo_Angle(4,motors[3].current_angle);
					motors[3].rotation_counter++;
				} 
				// 完成旋转
				else {
					motors[3].state = IDLE_STATE;  // 返回空闲状态
				}
			}
		}
}
