

#include <iocc2530.h>
#include <stdio.h>
#define LED1  P0_4
#define LED2  P0_5

void hal_led_init(void)
{
    P0SEL &= ~0x30;          //P0.4 P0.5Ϊ��ͨ I/O ��
    P0DIR |= 0x30;           //���
    LED1   = 0;       //Ĭ�Ͻ��ƹر�
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
*�������� ����ʼ������1										
*��ڲ��� ����												
*�� �� ֵ ����							
*˵    �� ��19200-8-n-1						
****************************************************************/
void hal_uart_init(void)
{
    PERCFG = 0x00;				//λ��1 P0��
    P0SEL |= 0x0C;				//P0��������
    P2DIR &= ~0XC0;                             //P0������Ϊ����0

    U0CSR |= 0x80;				//UART��ʽ
    U0CSR |= 0X40;				//�������
    
    U0GCR = 0x09;				//baud_e
    U0BAUD |= 0x3b;				//��������Ϊ19200
    UTX0IF = 0;
}

__near_func int putchar(int ch)
{
    U0DBUF = ch;
    while(UTX0IF == 0);
    UTX0IF = 0;
    return ch;
}
