#include <ioCC2530.h>             //����CC2530����Ӧ��ͷ�ļ���������SFR�Ķ��壩

/*----------------------------------------------------------------------------*/
/*                            macro declaration 	                      */
/*----------------------------------------------------------------------------*/
#define D7    P0_4              //����D7ΪP1_0�ڿ���
#define D6    P0_5              //����D6ΪP1_1�ڿ���

#define uint   unsigned  int
#define uchar  unsigned  char

#define CLKSPD  ( CLKCONCMD & 0x07 )    //getting the clock division factor

void xtal_init(void);
void led_init(void);
void ext_init(void);
void time1_init(void);
void uart0_init(unsigned char StopBits,unsigned char Parity);
void watchdog_init(void);
void sleepTimer_init(void);
void halWait(unsigned char wait);
void Delay_us(void);    