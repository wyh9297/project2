
#include <iocc2530.h>
#include "hal_mcu.h"
#include "hal_assert.h"
#include "hal_board.h"
#include <string.h>
#include <stdio.h>
#include "hal_rf.h"
#include "basic_rf.h"
#include <stdio.h>

typedef unsigned char uchar;
typedef unsigned int  uint;
#define RF_CHANNEL            25      // 2.4 GHz RF channel

#include "DHT11.h"
#include "bmp280.h"
#define PAN_ID                0x2007
#define SEND_ADDR             0x2530
#define RECV_ADDR             0x2520

#define NODE_TYPE             1         //0:���սڵ㣬1�����ͽڵ�
#define A1 P0_6 //���岽��������Ӷ˿� N1
#define B1 P0_7 //                     N2
const int oneTime =240;//һȦ
const int oneTimeFFW = 180;//˳ʱ��ת
const int oneTimeREV = 171;//��ʱ��

static basicRfCfg_t basicRfConfig;

//ms��ʱ����

void Delay_ms_1(uint x)
{
  uint i,j;
  for(i=0;i<x;i++)
    for(j=0;j<535;j++);
}
void MotorFFW(uint speed)
{
  A1=0;
  B1=1;
}
void MotorREV(unsigned int speed)
{
  A1=1;
  B1=0;

}
void MotorStop()
{
  A1=0;
  B1=0;
  
}

void InitIO(void)
{
//  P0SEL &= 0x0F;  //P04 05 06 07����Ϊ��ͨIO
  P0DIR |= 0xF0;  //P04 05 06 07����Ϊ���
//  P0SEL &= ~0xFF;          //P0.4 P0.5Ϊ��ͨ I/O ��
//  P0DIR |= 0x0C;  // 02 03����Ϊ���
}
void openAndClose()
{
  MotorFFW(1);
  Delay_ms_1(oneTimeFFW);
  MotorStop();
  Delay_ms_1(2000);
  MotorREV(1);
  Delay_ms_1(oneTimeREV);
  MotorStop();
  Delay_ms_1(3000);  
}
//��ʱ��ת�� speedԽ���ٶ�Խ��

void rfSendData(void)
{
    char temp[3];
    char Txtemp[3];
    uint8 pTxData[] = {'H', 'e', 'l', 'l', 'o', ' ', 'c', 'c', '2', '5', '3', '0', '\r', '\n'};
    uint8 ret;
    
    printf("send node start up...\r\n");
    // Keep Receiver off when not needed to save power
    basicRfReceiveOff();
    
    // Main loop
    while (TRUE) {
       memset(temp, 0, 4);
       DHT11();
       temp[0]=wendu_shi+0x30;
       temp[1]=wendu_ge+0x30;
       temp[2]='1';
       printf(temp);
       printf("\r\n");
       ret = basicRfSendPacket(RECV_ADDR, temp, sizeof pTxData);       
       if (ret == SUCCESS) {
          hal_led_on(1);
          halMcuWaitMs(100);
          hal_led_off(1);
          halMcuWaitMs(2900); 
       } else {
          hal_led_on(1);
          halMcuWaitMs(1000);
          hal_led_off(1);
          halMcuWaitMs(1000);
       }
       
    }
}

void rfRecvData(void)
{
    uint8 pRxData[128];
    int rlen;
  
  
    printf("recv node start up...\r\n");
  
    basicRfReceiveOn();

    // Main loop
    while (TRUE) {
        while(!basicRfPacketIsReady());
        rlen = basicRfReceive(pRxData, sizeof pRxData, NULL);
        if(rlen > 0) {
          pRxData[rlen] = '/0';
            
          printf((char *)pRxData);
          if(pRxData[0] == '3' || pRxData[0] == '4'){
            MotorFFW(1);
            Delay_ms_1(2000);
          }
            
        }
    }
}

void main(void)
{
    
    InitIO();
    Delay_ms_1(2000);
    halMcuInit();
    hal_led_init();
  
    hal_uart_init();
    openAndClose();
    Delay_ms_1(5000);
    if (FAILED == halRfInit()) {
        HAL_ASSERT(FALSE);
    }
    
    // Config basicRF
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
#ifdef SECURITY_CCM
    basicRfConfig.securityKey = key;
#endif

    
    // Initialize BasicRF
#if NODE_TYPE
    basicRfConfig.myAddr = SEND_ADDR;
#else
    basicRfConfig.myAddr = RECV_ADDR; 
#endif
    
    if(basicRfInit(&basicRfConfig)==FAILED) {
      HAL_ASSERT(FALSE);
    }
#if NODE_TYPE
  rfSendData();
#else
  rfRecvData();   
#endif
}
