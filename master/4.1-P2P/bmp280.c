#include <stdbool.h>
#include "bmp280.h"
#include "sys_init.h"

unsigned short  dig_T1=0x00;
signed short  dig_T2=0x00;
signed short  dig_T3=0x00;
unsigned short  dig_P1=0x00;
signed short  dig_P2=0x00;
signed short  dig_P3=0x00;
signed short  dig_P4=0x00;
signed short  dig_P5=0x00;
signed short  dig_P6=0x00;
signed short  dig_P7=0x00;
signed short  dig_P8=0x00;
signed short  dig_P9=0x00;

BMP280_S32_t t_fine;
#if 0
#define CSB_IO             P0_5
#define BMP280_CSB_IO_L()  (CSB_IO=0)
#define BMP280_CSB_IO_H()  (CSB_IO=1)

#define MOSI_IO             P0_6
#define BMP280_MOSI_IO_L()  (MOSI_IO=0)
#define BMP280_MOSI_IO_H()  (MOSI_IO=1)

#define MISO_IO             P0_7


#define SCK_IO             P0_0
#define BMP280_SCK_IO_L()  (SCK_IO=0)
#define BMP280_SCK_IO_H()  (SCK_IO=1)
#else

#define CSB_IO             P1_4
#define BMP280_CSB_IO_L()  (CSB_IO=0)
#define BMP280_CSB_IO_H()  (CSB_IO=1)

#define MOSI_IO             P1_6
#define BMP280_MOSI_IO_L()  (MOSI_IO=0)
#define BMP280_MOSI_IO_H()  (MOSI_IO=1)

#define MISO_IO             P1_7


#define SCK_IO             P1_5
#define BMP280_SCK_IO_L()  (SCK_IO=0)
#define BMP280_SCK_IO_H()  (SCK_IO=1)
#endif
//void Delay_us(void)              
//{ 
//  volatile unsigned short i;
//  for(i=0;i<1;i++)
//  asm("NOP");
//}
void BMP_SPI_Init(void)
{
     unsigned short i;
  for(i=0;i<500;i++)
    asm("NOP");
#if 0
    P0SEL &= ~0x61;          
    P0DIR |= 0x61;           //���
    
    P0SEL &=~ (0x80);
    P0DIR &=~ (0x80);
    P0INP &= ~(0x80);        //0:������1:����
#else
    P1SEL &= ~0x70;          //P1.4 -P1.6Ϊ��ͨ I/O ��
    P1DIR |= 0x70;           //���
    
    P1SEL &=~ (0x80);
    P1DIR &=~ (0x80);
    P1INP &= ~(0x80);        //0:������1:����
    
#endif
    Delay_us();
    BMP280_CSB_IO_L();  //  ���� CSB �� BMP280 ����ΪSPI�ӿ�
    Delay_us();
    BMP280_SCK_IO_L() ;
    BMP280_MOSI_IO_L();
    
    Delay_us();
    BMP280_CSB_IO_H();
}

unsigned char bmp280_spi_read(unsigned char data)
{
     unsigned char i;
     unsigned char ucResult=0;

     BMP280_SCK_IO_L();
     Delay_us();
     for(i=8;i>0;i--)
     {
        Delay_us();
         BMP280_SCK_IO_H();
         ucResult <<= 1;
         ucResult|=(bool)(MISO_IO);
         Delay_us();
         BMP280_SCK_IO_L();
     }
 
     BMP280_SCK_IO_L();
     return ucResult;
}

void bmp280_spi_write(unsigned char data)
{  
    unsigned char i;



     BMP280_SCK_IO_L();



    for(i=8;i>0;i--)
    {
        MOSI_IO = ((data&0x80)==0x80);
        Delay_us();
        BMP280_SCK_IO_H();
        data <<= 1;
        Delay_us();
        BMP280_SCK_IO_L();
    }

     BMP280_SCK_IO_L();
}

// дBMP
void bmp280_write(unsigned char Address, unsigned char BMP_Data)
{
    BMP280_CSB_IO_L();
    bmp280_spi_write(Address);
    bmp280_spi_write(BMP_Data);
    BMP280_CSB_IO_H();
}
// ��BMP280
unsigned char bmp280_read(unsigned char Address)
{
    unsigned char sta=0x00;
    BMP280_CSB_IO_L();
    Delay_us();
    bmp280_spi_write(Address);
    sta=bmp280_spi_read(0xFF);
    Delay_us();
    BMP280_CSB_IO_H();
    
    return sta;
}

//  ��ȡ�¶ȼ�
BMP280_S32_t bmp280_read_Tdata(void)
{
    unsigned char Temp_Data[3]={0};
    BMP280_S32_t Temp_Result=0;

    BMP280_CSB_IO_L();
    bmp280_spi_write(BMP280_Read|BMP_Temp_msb);
    Temp_Data[2]=bmp280_spi_read(0xFF);
    Temp_Data[1]=bmp280_spi_read(0xFF);
    Temp_Data[0]=bmp280_spi_read(0xFF);
    BMP280_CSB_IO_H();
    
    //Temp_Result=Temp_Data[0]>>4;
    //Temp_Result|=Temp_Data[1]<<4;
    //Temp_Result|=Temp_Data[2]<<12;
    Temp_Result = (BMP280_S32_t)(((BMP280_S32_t)Temp_Data[2] << 12)|((BMP280_S32_t)Temp_Data[1] << 4)|((BMP280_S32_t)Temp_Data[0] >> 4));
    return Temp_Result;
}

// ��ȡ��ѹ��
BMP280_S32_t bmp280_read_Pdata(void)
{
    unsigned char  Press_Data[3]={0};
    BMP280_S32_t Press_Result=0;
    
    BMP280_CSB_IO_L();
    
    bmp280_spi_write(BMP280_Read|BMP_Press_msb);
    Press_Data[2]=bmp280_spi_read(0xFF);
    Press_Data[1]=bmp280_spi_read(0xFF);
    Press_Data[0]=bmp280_spi_read(0xFF);
    
    BMP280_CSB_IO_H();
    
    //Press_Result=Press_Data[0]>>4;
    //Press_Result|=Press_Data[1]<<4;
    //Press_Result|=Press_Data[2]<<12;
    Press_Result = (BMP280_S32_t)(((BMP280_S32_t)Press_Data[2] << 12)|((BMP280_S32_t)Press_Data[1] << 4)|((BMP280_S32_t)Press_Data[0] >> 4));
    return Press_Result;
}

//��ȡ����ϵ��
void bmp_compensation(void)
{
      BMP280_CSB_IO_L();
      bmp280_spi_write(BMP280_Read|BMP_Calib(0));
      
      dig_T1=bmp280_spi_read(0xFF);  // ��ȡ�¶Ȳ���ϵ��
      dig_T1|=(bmp280_spi_read(0xFF)<<8);
      
      dig_T2=bmp280_spi_read(0xFF);
      dig_T2|=(bmp280_spi_read(0xFF)<<8);
      
      dig_T3=bmp280_spi_read(0xFF);
      dig_T3|=(bmp280_spi_read(0xFF)<<8);
      
      dig_P1=bmp280_spi_read(0xFF);  // ��ȡѹǿ����ϵ�� 
      dig_P1|=(bmp280_spi_read(0xFF)<<8);
      
      dig_P2=bmp280_spi_read(0xFF);
      dig_P2|=(bmp280_spi_read(0xFF)<<8);
      
      dig_P3=bmp280_spi_read(0xFF);
      dig_P3|=(bmp280_spi_read(0xFF)<<8);
      
      dig_P4=bmp280_spi_read(0xFF);
      dig_P4|=(bmp280_spi_read(0xFF)<<8);
      
      dig_P5=bmp280_spi_read(0xFF);
      dig_P5|=(bmp280_spi_read(0xFF)<<8);
      
      dig_P6=bmp280_spi_read(0xFF);
      dig_P6|=(bmp280_spi_read(0xFF)<<8);
      
      dig_P7=bmp280_spi_read(0xFF);
      dig_P7|=(bmp280_spi_read(0xFF)<<8);
      
      dig_P8=bmp280_spi_read(0xFF);
      dig_P8|=(bmp280_spi_read(0xFF)<<8);
      
      dig_P9=bmp280_spi_read(0xFF);
      dig_P9|=(bmp280_spi_read(0xFF)<<8);
      
      BMP280_CSB_IO_H();

}

unsigned char bmp280_init(void)
{

    unsigned char sta=0x00;
    //bmp280_write(BMP280_Write|BMP_Reset,0xb6); //״̬ȫ������ 
    sta=bmp280_read(BMP280_Read|BMP_ID);  // ��ȡ BMP280 ID��
    if(sta!=BMP280_ID_Number)  // ��� BMP ID��Ϊ 0x58 ��ʾBMP������
       return 0x01;
    
    while(sta&0x01)  // �ȴ� NVM �����ɹ�
      sta=bmp280_read(BMP_Status|BMP280_Read);
    
    //bmp_compensation();
    /*
    #define BMP_Ctrl_meas         0x74  // Bit765 �����¶�ת�����ȣ� 000��ʾ�ر��¶�ת��;  
                                    // Bit432 ������ѹ��ת�����ȣ�000��ʾ�ر���ѹ��ת��;
                                    // Bit10 ���� BMP �ĵ�Դģʽ��00 sleep; 01/10 Forced mode; 11 Normal mode; 
    */
    bmp280_write(BMP280_Write|BMP_Ctrl_meas,BMP_TENP_20|BMP_PRESS_20|BMP_NORMAL);  // ���� �¶ȡ�ѹǿת�����ȡ���Դģʽ
    /*
    #define BMP_Config            0x75  // Bit765 ��  
                                    // Bit432 ����IIR�˲���ϵ�� ;
                                    // Bit0 ʹ�� 3��SPI
    */
    bmp280_write(BMP280_Write|BMP_Config,BMP_Tstandby_0|BMP_IIR_16);  // ����Tstandy ��BMP �˲�ϵ���� SPI ģʽ
    
    bmp_compensation();

    return 0x00;
}


// Returns temperature in DegC, double precision. Output value of ��51.23�� equals 51.23 DegC.
// t_fine carries fine temperature as global value

double bmp280_compensate_T_double(BMP280_S32_t adc_T)
{
  double var1, var2, T;
  var1 = (((double)adc_T)/16384.0-((double)dig_T1)/1024.0)*((double)dig_T2);
  var2 = ((((double)adc_T)/131072.0-((double)dig_T1)/8192.0)*(((double)adc_T)/131072.0-((double)dig_T1)/8192.0))*((double)dig_T3);

  t_fine = (unsigned long)(var1+var2);

  T = (var1+var2)/5120.0;

  return T;
}
// Returns pressure in Pa as double. Output value of ��96386.2�� equals 96386.2 Pa = 963.862 hPa
double bmp280_compensate_P_double(BMP280_S32_t adc_P)
{
  double var1, var2, p;
  var1 = ((double)t_fine/2.0)-64000.0;
  var2 = var1*var1*((double)dig_P6)/32768.0;
  var2 = var2 +var1*((double)dig_P5)*2.0;
  var2 = (var2/4.0)+(((double)dig_P4)*65536.0);
  var1 = (((double)dig_P3)*var1*var1/524288.0+((double)dig_P2)*var1)/524288.0;
  var1 = (1.0+var1/32768.0)*((double)dig_P1);
  p = 1048576.0-(double)adc_P;
  p = (p-(var2/4096.0))*6250.0/var1;
  var1 = ((double)dig_P9)*p*p/2147483648.0;
  var2 = p*((double)dig_P8)/32768.0;
  p = p+(var1+var2+((double)dig_P7))/16.0;

  return p;
}






