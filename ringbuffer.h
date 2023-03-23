#ifndef Ring_buf_h
#define Ring_buf_h
#include "stm32f1xx_hal.h"

#define MAX_RING_SIZE 5
#define MAX_RING_DATA_SIZE 2048

#define	STX		0x02
#define	ETX		0x03
#define	CR		0x0d
#define	LF		0x0a

typedef struct{
	int tag_head;
	int tag_tail;
	int max_size;
	uint8_t* buffer;
} ring_t;

//typedef struct{        
//  int sz_data;
//  unsigned char data[MAX_RING_DATA_SIZE];        
//} rign_item_t;
//
//typedef struct{
//  int tag_head;
//  int tag_tail;
//  rign_item_t item[MAX_RING_SIZE];
//} ring_str_t;

void ring_char_init( ring_t *ring, uint8_t* buffer,int size);
uint8_t ring_exists( ring_t *ring);
void ring_put_char( ring_t *ring, unsigned char data);
unsigned char ring_get_char( ring_t *ring);
int uart1_interpreter(ring_t* ring, uint8_t* Uart3_Buff);
//void ring_put( ring_t *ring, char *data, int sz_data);
//int ring_get( ring_t *ring, char *buff, int sz_buff);
//int ring_exists( ring_t *ring);
//void ring_init( ring_t *ring);
#endif