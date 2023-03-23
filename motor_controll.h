#ifndef motor_controll_h
#define motor_controll_h
#include "stm32f1xx_hal.h"

#define CW 1
#define CCW 2
#define START 3 
#define STOP 4
#define MOTOR_INT_SPEED_PIN 5

#define MOTOR_CW_CCW_PIN GPIO_PIN_0
#define MOTOR_START_PIN GPIO_PIN_1
#define MOTOR_STOP_PIN GPIO_PIN_2

void motor_init();
int motor_controller(uint8_t* Uart3_Buff);
void state_motor(uint8_t* Uart3_Buff ,int motor_controll);
void motor_speed(int input_speed);

#endif