

#include <iocc2530.h>
#include <stdio.h>
#define LED1  P0_4
#define LED2  P0_5

void hal_led_init(void)
{
    P0SEL &= ~0x30;          //P0.4 P0.5为普通 I/O 口
    P0DIR |= 0x30;           //输出
    LED1   = 0;       //默认将灯关闭
    LED2   = 0; 
}

void hal_led_off(int leds)
{
  if(leds==0x01)
    LED1=0;
  if(leds==0x02)
    LED2=0;
}


void hal_led_on(int leds)
{
  if(leds==0x01)
    LED1=1;
  if(leds==0x02)
    LED2=1;
}



/****************************************************************
*函数功能 ：初始化串口1										
*入口参数 ：无												
*返 回 值 ：无							
*说    明 ：19200-8-n-1						
****************************************************************/
void hal_uart_init(void)
{
    PERCFG = 0x00;				//位置1 P0口
    P0SEL |= 0x0C;				//P0用作串口
    P2DIR &= ~0XC0;                             //P0优先作为串口0

    U0CSR |= 0x80;				//UART方式
    U0CSR |= 0X40;				//允许接收
    
    U0GCR = 0x09;				//baud_e
    U0BAUD |= 0x3b;				//波特率设为19200
    UTX0IF = 0;
}

__near_func int putchar(int ch)
{
    U0DBUF = ch;
    while(UTX0IF == 0);
    UTX0IF = 0;
    return ch;
}
