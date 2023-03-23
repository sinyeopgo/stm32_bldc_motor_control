#include <string.h>
#include <stdlib.h>
#include "ringbuffer.h"
#include "stm32f1xx_peripheral_setting.h"
#include "motor_controll.h"

extern TIM_HandleTypeDef htim1;

/*********************************************************************************
* 문자 링버퍼 head와 tail초기화
*********************************************************************************/
void ring_char_init( ring_t *ring, uint8_t* buffer,int size)
{
 	memset(ring,0,sizeof(ring_t));
	ring->buffer = buffer;
	ring->max_size = size;
}

/*********************************************************************************
* 문자 링버퍼에 값이 들어있는지 확인
*********************************************************************************/
uint8_t ring_exists( ring_t *ring)
{
	return ring->tag_head != ring->tag_tail;
}

/*********************************************************************************
* 링버퍼에 문자 저장
*********************************************************************************/
void ring_put_char( ring_t *ring, unsigned char data)
{
	ring->buffer[ring->tag_head] = data;
	ring->tag_head = ( ring->tag_head +1) % ring->max_size;
	if ( ring->tag_head == ring->tag_tail)
	{
    		ring->tag_tail = ( ring->tag_tail +1) % ring->max_size; 
  	}
}

/*********************************************************************************
* 링버퍼안에 있는 문자 출력
*********************************************************************************/
unsigned char ring_get_char( ring_t *ring)
{
  	unsigned char data;
	
	data = ring->buffer[ring->tag_tail];
	ring->tag_tail = ( ring->tag_tail +1) % ring->max_size;
	return data;
}

int uart1_interpreter(ring_t* ring, uint8_t* Uart3_Buff)
{
	static uint32_t uart_idx1 = 0;
	uint8_t receive_data;

        receive_data = ring_get_char(ring);
        //HAL_UART_Transmit(&huart3, &receive_data , 1, 100);
        switch(receive_data)
        {
                case LF:
                        Uart3_Buff[uart_idx1] = receive_data;
                        Uart3_Buff[uart_idx1++] = '\0';
                        uart_idx1 =0;
                        //uart1_massage_passer();
                        HAL_UART_Transmit(&huart3, Uart3_Buff , strlen((char const*)Uart3_Buff), 100);
                        return 1;
                        break;
                default:
                        if(uart_idx1 >strlen((char const*)Uart3_Buff)) uart_idx1 =0;
                        else Uart3_Buff[uart_idx1++] = receive_data;
                        return 0;
                        break;
        }//switch(receive_data)
}

/*********************************************************************************
* 문자열 링버퍼 head와 tail초기화
*********************************************************************************/
//void ring_init( ring_str_t *ring)
//{
//  ring->tag_head = ring->tag_tail = 0;
//}
//
///*********************************************************************************
//* 문자열 링버퍼에 값이 들어있는지 확인
//*********************************************************************************/
//int ring_exists( ring_str_t *ring)
//{
//  return ring->tag_head != ring->tag_tail;
//}
//
///*********************************************************************************
//* 링버퍼에 문자열 저장
//*********************************************************************************/
//void ring_put( ring_str_t *ring, char *data, int sz_data)
//{
//  if ( MAX_RING_DATA_SIZE < sz_data)    sz_data = MAX_RING_DATA_SIZE; 
//
//  ring->item[ring->tag_head].sz_data = sz_data;
//  memcpy( ring->item[ring->tag_head].data, data, sizeof( ring->item[ring->tag_head].data));
//
//  ring->tag_head = ( ring->tag_head +1) % MAX_RING_SIZE;
//  if ( ring->tag_head == ring->tag_tail){
//    ring->tag_tail = ( ring->tag_tail +1) % MAX_RING_SIZE;
//  }
//}
//
///*********************************************************************************
//* 링버퍼안에 있는 문자열 출력
//*********************************************************************************/
//int ring_get( ring_str_t *ring, char *buff, int sz_buff)
//{
//
//  if ( ring->tag_head == ring->tag_tail)
//  {
//    return 0;
//  }
//
//  memset( buff, 0, sz_buff);
//  int sz_data = ring->item[ring->tag_tail].sz_data;
//  if ( sz_buff < sz_data)   sz_data= sz_buff;
//  memcpy( buff, ring->item[ring->tag_tail].data, sz_data);
//
//  ring->tag_tail = ( ring->tag_tail +1) % MAX_RING_SIZE;
//
//  return sz_data;
//}

