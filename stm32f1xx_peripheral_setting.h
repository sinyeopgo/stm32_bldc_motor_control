#ifndef stm32f1xx_peripheral_setting_H
#define stm32f1xx_peripheral_setting_H

#define SYSTICK_TIMER_SET_1MS           1000
#define SYSTICK_TIMER_SET_100US         10000
#define SYSTICK_TIMER_SET_50US          20000
#define SYSTICK_TIMER_SET_10US          100000

extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart3;

void SystemClock_Config(void);
void MX_TIM1_Init(void);
void MX_USART3_UART_Init(void);
void MX_GPIO_Init(void);
void Error_Handler(void);

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line);
#endif

#endif