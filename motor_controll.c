#include "motor_controll.h"
#include <string.h>
#include "stm32f1xx_peripheral_setting.h"

extern UART_HandleTypeDef huart3;

void motor_init()
{
  HAL_GPIO_WritePin(GPIOA,MOTOR_INT_SPEED_PIN,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA,MOTOR_CW_CCW_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,MOTOR_START_PIN,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA,MOTOR_STOP_PIN,GPIO_PIN_RESET);
  
}

int motor_controller(uint8_t* Uart3_Buff)
{ 
  if(strncmp((char const*)Uart3_Buff, "cw",2) == 0) return CW;
  else if(strncmp((char const*)Uart3_Buff, "ccw",3) == 0) return CCW;
  else if(strncmp((char const*)Uart3_Buff, "start",5) == 0) return START;
  else if(strncmp((char const*)Uart3_Buff, "stop",4) == 0) return STOP;
  else if(strncmp((char const*)Uart3_Buff, "speed",5) == 0) return MOTOR_INT_SPEED_PIN;
  else return -1;
}

void state_motor(uint8_t* Uart3_Buff ,int motor_controll)
{
  char* ptr;
  switch(motor_controll)
  {
  case CW:
    HAL_GPIO_WritePin(GPIOA,MOTOR_CW_CCW_PIN,GPIO_PIN_RESET);
    break;
  case CCW:
    HAL_GPIO_WritePin(GPIOA,MOTOR_CW_CCW_PIN,GPIO_PIN_SET);
    break;
  case START:
    HAL_GPIO_WritePin(GPIOA,MOTOR_STOP_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,MOTOR_START_PIN,GPIO_PIN_RESET);
    break;
  case STOP:
    HAL_GPIO_WritePin(GPIOA,MOTOR_START_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,MOTOR_STOP_PIN,GPIO_PIN_RESET);
    break;
 case MOTOR_INT_SPEED_PIN:
    strtok(Uart3_Buff, " ");
    ptr = strtok(NULL, " ");
    motor_speed(atoi(ptr));
    break;
  default:
    break;
  }
}
void motor_speed(int input_speed)
{
  if(input_speed; > 999) htim1.Instance->CCR3 = 999;
  else if (input_speed < 0) htim1.Instance->CCR3 = 0;
  else htim1.Instance->CCR3 = input_speed;
}