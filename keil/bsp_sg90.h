/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 立创论坛：https://oshwhub.com/forum
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-08     LCKFB-LP    first version
 */

#ifndef _BSP_SG90_H
#define _BSP_SG90_H

#include "board.h"
typedef enum {
    IDLE_STATE,          // 空闲状态
    ROTATING_STATE       // 旋转状态
} RotationState;

typedef struct{
	volatile uint8_t target_angle;//目标角度
	volatile uint8_t current_angle ;//现在角度
	volatile uint32_t rotation_counter ;//计数器
	volatile uint8_t state;//状态
}motorcontrol;

extern motorcontrol motors[];

unsigned int Get_Servo_Angle(void);
void Set_Servo_Angle(unsigned int servo,unsigned int angle);


#endif

