/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ringbuffer.h"
#include "motor_controll.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_peripheral_setting.h"
#include "pwm.h"
#include <string.h>

TIM_HandleTypeDef htim1;
UART_HandleTypeDef huart3;

uint8_t data;
ring_t ring_inf;
uint8_t uart_buf[50]={0,};

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART3)
  {
    ring_put_char( &ring_inf, data);
    HAL_UART_Receive_IT(&huart3, &data, 1);
  }
}
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART3_UART_Init();
  ring_char_init(&ring_inf,uart_buf,50);
  motor_init();
  HAL_UART_Receive_IT(&huart3, &data, 1);
  
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);

  while (1)
  {
    if(ring_exists(&ring_inf))
    {
      if(uart1_interpreter(&ring_inf,uart_buf))
      {
        state_motor(uart_buf,motor_controller(uart_buf));
        memset(uart_buf,0,sizeof(uint8_t)*50);
      }
    }
}