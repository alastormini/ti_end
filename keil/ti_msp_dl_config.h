/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM */
#define PWM_INST                                                           TIMA0
#define PWM_INST_IRQHandler                                     TIMA0_IRQHandler
#define PWM_INST_INT_IRQN                                       (TIMA0_INT_IRQn)
#define PWM_INST_CLK_FREQ                                                  20000
/* GPIO defines for channel 1 */
#define GPIO_PWM_C1_PORT                                                   GPIOA
#define GPIO_PWM_C1_PIN                                            DL_GPIO_PIN_7
#define GPIO_PWM_C1_IOMUX                                        (IOMUX_PINCM14)
#define GPIO_PWM_C1_IOMUX_FUNC                       IOMUX_PINCM14_PF_TIMA0_CCP1
#define GPIO_PWM_C1_IDX                                      DL_TIMER_CC_1_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_C1_CMPL_PORT                                              GPIOA
#define GPIO_PWM_C1_CMPL_PIN                                       DL_GPIO_PIN_4
#define GPIO_PWM_C1_CMPL_IOMUX                                    (IOMUX_PINCM9)
#define GPIO_PWM_C1_CMPL_IOMUX_FUNC              IOMUX_PINCM9_PF_TIMA0_CCP1_CMPL

/* GPIO defines for channel 2 */
#define GPIO_PWM_C2_PORT                                                   GPIOB
#define GPIO_PWM_C2_PIN                                           DL_GPIO_PIN_20
#define GPIO_PWM_C2_IOMUX                                        (IOMUX_PINCM48)
#define GPIO_PWM_C2_IOMUX_FUNC                       IOMUX_PINCM48_PF_TIMA0_CCP2
#define GPIO_PWM_C2_IDX                                      DL_TIMER_CC_2_INDEX
/* GPIO defines for channel 2 */
#define GPIO_PWM_C2_CMPL_PORT                                              GPIOA
#define GPIO_PWM_C2_CMPL_PIN                                      DL_GPIO_PIN_11
#define GPIO_PWM_C2_CMPL_IOMUX                                   (IOMUX_PINCM22)
#define GPIO_PWM_C2_CMPL_IOMUX_FUNC             IOMUX_PINCM22_PF_TIMA0_CCP2_CMPL

/* GPIO defines for channel 3 */
#define GPIO_PWM_C3_PORT                                                   GPIOB
#define GPIO_PWM_C3_PIN                                           DL_GPIO_PIN_24
#define GPIO_PWM_C3_IOMUX                                        (IOMUX_PINCM52)
#define GPIO_PWM_C3_IOMUX_FUNC                       IOMUX_PINCM52_PF_TIMA0_CCP3
#define GPIO_PWM_C3_IDX                                      DL_TIMER_CC_3_INDEX
/* GPIO defines for channel 3 */
#define GPIO_PWM_C3_CMPL_PORT                                              GPIOA
#define GPIO_PWM_C3_CMPL_PIN                                      DL_GPIO_PIN_18
#define GPIO_PWM_C3_CMPL_IOMUX                                   (IOMUX_PINCM40)
#define GPIO_PWM_C3_CMPL_IOMUX_FUNC             IOMUX_PINCM40_PF_TIMA0_CCP3_CMPL


/* Defines for servo1 */
#define servo1_INST                                                        TIMA1
#define servo1_INST_IRQHandler                                  TIMA1_IRQHandler
#define servo1_INST_INT_IRQN                                    (TIMA1_INT_IRQn)
#define servo1_INST_CLK_FREQ                                               20000
/* GPIO defines for channel 1 */
#define GPIO_servo1_C1_PORT                                                GPIOB
#define GPIO_servo1_C1_PIN                                        DL_GPIO_PIN_18
#define GPIO_servo1_C1_IOMUX                                     (IOMUX_PINCM44)
#define GPIO_servo1_C1_IOMUX_FUNC                    IOMUX_PINCM44_PF_TIMA1_CCP1
#define GPIO_servo1_C1_IDX                                   DL_TIMER_CC_1_INDEX
/* GPIO defines for channel 1 */
#define GPIO_servo1_C1_CMPL_PORT                                           GPIOA
#define GPIO_servo1_C1_CMPL_PIN                                   DL_GPIO_PIN_16
#define GPIO_servo1_C1_CMPL_IOMUX                                (IOMUX_PINCM38)
#define GPIO_servo1_C1_CMPL_IOMUX_FUNC          IOMUX_PINCM38_PF_TIMA1_CCP1_CMPL




/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG0)
#define TIMER_0_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                           (399U)
/* Defines for TIMER_1 */
#define TIMER_1_INST                                                     (TIMG6)
#define TIMER_1_INST_IRQHandler                                 TIMG6_IRQHandler
#define TIMER_1_INST_INT_IRQN                                   (TIMG6_INT_IRQn)
#define TIMER_1_INST_LOAD_VALUE                                           (799U)



/* Defines for UART_1 */
#define UART_1_INST                                                        UART1
#define UART_1_INST_FREQUENCY                                            4000000
#define UART_1_INST_IRQHandler                                  UART1_IRQHandler
#define UART_1_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_1_RX_PORT                                                GPIOA
#define GPIO_UART_1_TX_PORT                                                GPIOA
#define GPIO_UART_1_RX_PIN                                         DL_GPIO_PIN_9
#define GPIO_UART_1_TX_PIN                                         DL_GPIO_PIN_8
#define GPIO_UART_1_IOMUX_RX                                     (IOMUX_PINCM20)
#define GPIO_UART_1_IOMUX_TX                                     (IOMUX_PINCM19)
#define GPIO_UART_1_IOMUX_RX_FUNC                      IOMUX_PINCM20_PF_UART1_RX
#define GPIO_UART_1_IOMUX_TX_FUNC                      IOMUX_PINCM19_PF_UART1_TX
#define UART_1_BAUD_RATE                                                  (9600)
#define UART_1_IBRD_4_MHZ_9600_BAUD                                         (26)
#define UART_1_FBRD_4_MHZ_9600_BAUD                                          (3)
/* Defines for UART_3 */
#define UART_3_INST                                                        UART3
#define UART_3_INST_FREQUENCY                                            4000000
#define UART_3_INST_IRQHandler                                  UART3_IRQHandler
#define UART_3_INST_INT_IRQN                                      UART3_INT_IRQn
#define GPIO_UART_3_RX_PORT                                                GPIOA
#define GPIO_UART_3_TX_PORT                                                GPIOA
#define GPIO_UART_3_RX_PIN                                        DL_GPIO_PIN_13
#define GPIO_UART_3_TX_PIN                                        DL_GPIO_PIN_14
#define GPIO_UART_3_IOMUX_RX                                     (IOMUX_PINCM35)
#define GPIO_UART_3_IOMUX_TX                                     (IOMUX_PINCM36)
#define GPIO_UART_3_IOMUX_RX_FUNC                      IOMUX_PINCM35_PF_UART3_RX
#define GPIO_UART_3_IOMUX_TX_FUNC                      IOMUX_PINCM36_PF_UART3_TX
#define UART_3_BAUD_RATE                                                  (9600)
#define UART_3_IBRD_4_MHZ_9600_BAUD                                         (26)
#define UART_3_FBRD_4_MHZ_9600_BAUD                                          (3)





/* Port definition for Pin Group buzzer */
#define buzzer_PORT                                                      (GPIOA)

/* Defines for beep: GPIOA.27 with pinCMx 60 on package pin 31 */
#define buzzer_beep_PIN                                         (DL_GPIO_PIN_27)
#define buzzer_beep_IOMUX                                        (IOMUX_PINCM60)
/* Port definition for Pin Group KEY */
#define KEY_PORT                                                         (GPIOA)

/* Defines for KEY1: GPIOA.26 with pinCMx 59 on package pin 30 */
#define KEY_KEY1_PIN                                            (DL_GPIO_PIN_26)
#define KEY_KEY1_IOMUX                                           (IOMUX_PINCM59)
/* Defines for KEY2: GPIOA.25 with pinCMx 55 on package pin 26 */
#define KEY_KEY2_PIN                                            (DL_GPIO_PIN_25)
#define KEY_KEY2_IOMUX                                           (IOMUX_PINCM55)
/* Defines for KEY3: GPIOA.24 with pinCMx 54 on package pin 25 */
#define KEY_KEY3_PIN                                            (DL_GPIO_PIN_24)
#define KEY_KEY3_IOMUX                                           (IOMUX_PINCM54)
/* Defines for KEY4: GPIOA.23 with pinCMx 53 on package pin 24 */
#define KEY_KEY4_PIN                                            (DL_GPIO_PIN_23)
#define KEY_KEY4_IOMUX                                           (IOMUX_PINCM53)
/* Defines for KEY5: GPIOA.22 with pinCMx 47 on package pin 18 */
#define KEY_KEY5_PIN                                            (DL_GPIO_PIN_22)
#define KEY_KEY5_IOMUX                                           (IOMUX_PINCM47)
/* Defines for KEY6: GPIOA.21 with pinCMx 46 on package pin 17 */
#define KEY_KEY6_PIN                                            (DL_GPIO_PIN_21)
#define KEY_KEY6_IOMUX                                           (IOMUX_PINCM46)
/* Port definition for Pin Group lazer */
#define lazer_PORT                                                       (GPIOB)

/* Defines for lazer1: GPIOB.9 with pinCMx 26 on package pin 61 */
#define lazer_lazer1_PIN                                         (DL_GPIO_PIN_9)
#define lazer_lazer1_IOMUX                                       (IOMUX_PINCM26)
/* Defines for lazer2: GPIOB.8 with pinCMx 25 on package pin 60 */
#define lazer_lazer2_PIN                                         (DL_GPIO_PIN_8)
#define lazer_lazer2_IOMUX                                       (IOMUX_PINCM25)
/* Port definition for Pin Group OLED */
#define OLED_PORT                                                        (GPIOA)

/* Defines for SCL: GPIOA.0 with pinCMx 1 on package pin 33 */
#define OLED_SCL_PIN                                             (DL_GPIO_PIN_0)
#define OLED_SCL_IOMUX                                            (IOMUX_PINCM1)
/* Defines for SDA: GPIOA.1 with pinCMx 2 on package pin 34 */
#define OLED_SDA_PIN                                             (DL_GPIO_PIN_1)
#define OLED_SDA_IOMUX                                            (IOMUX_PINCM2)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_init(void);
void SYSCFG_DL_servo1_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_1_init(void);
void SYSCFG_DL_UART_1_init(void);
void SYSCFG_DL_UART_3_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
