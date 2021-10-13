#include <ioCC2530.h>
#include <stdbool.h>
#define BMP280_S32_t long signed int

#define BMP280_Read   0x80
#define BMP280_Write  0x00
#define BMP280_ID_Number 0x58   // BMP ID 号

// 温度转换精度
#define BMP_TENP_SKIP  0x00
#define BMP_TENP_16     0x20   
#define BMP_TENP_17     0x40
#define BMP_TENP_18     0x60
#define BMP_TENP_19     0x80
#define BMP_TENP_20    0xA0
// 压强转换精度
#define BMP_PRESS_SKIP 0x00 
#define BMP_PRESS_16    0x04
#define BMP_PRESS_17    0x08
#define BMP_PRESS_18    0x0C
#define BMP_PRESS_19    0x10
#define BMP_PRESS_20   0x14
// 电源模式
#define BMP_SLEEP      0x00
#define BMP_FORCE      0x01
#define BMP_NORMAL     0x03
// IIR 滤波器系数
#define BMP_IIR_OFF    0x00
#define BMP_IIR_2      0x04
#define BMP_IIR_4      0x08
#define BMP_IIR_8      0x0A
#define BMP_IIR_16     0x10
// Tstandby 时间
#define BMP_Tstandby_0 0x00      // 000
#define BMP_Tstandby_1 0x20      // 001
#define BMP_Tstandby_2 0x40      // 010
#define BMP_Tstandby_3 0x60      // 011
#define BMP_Tstandby_4 0x80      // 100
#define BMP_Tstandby_5 0xA0      // 101 
#define BMP_Tstandby_6 0xC0      // 110
#define BMP_Tstandby_7 0xE       // 110

#define BMP_Temp_xlsb         0x7C  //  Bit 7654  温度计
#define BMP_Temp_lsb          0x7B  //  Bit 7654321
#define BMP_Temp_msb          0x7A  //  Bit 7654321

#define BMP_Press_xlsb        0x79  //  Bit 7654 气压力 
#define BMP_Press_lsb         0x78  //  BIT 7654321
#define BMP_Press_msb         0x77  //  BIT 7654321

#define BMP_Config            0x75  // Bit765 ；  
                                    // Bit432 配置IIR滤波器系数 ;
                                    // Bit0 使能 3线SPI
#define BMP_Ctrl_meas         0x74  // Bit765 配置温度转换精度： 000表示关闭温度转化;  
                                    // Bit432 配置气压计转换精度：000表示关闭气压计转换;
                                    // Bit10 配置 BMP 的电源模式：00 sleep; 01/10 Forced mode; 11 Normal mode; 
#define BMP_Status            0x73  // （只读）Bit0 表示不知道；
                                    //  Bit3 表示为数据转换标志位  0 为转换完成 1为转化没有完成
#define BMP_Reset             0x60  // （只写）软件复位寄存器 如果发送 0xB6 则BMP进行掉电复位
#define BMP_ID                0x50   // （只读）BMP280的 ID号寄存器 为0x58
#define BMP_Calib(x)          (0x88+x)   //  手册21页





void BMP_SPI_Init(void);


unsigned char bmp280_spi_read(unsigned char data);


void bmp280_spi_write(unsigned char data);


// 写BMP
void bmp280_write(unsigned char Address, unsigned char BMP_Data);

// 读BMP280
unsigned char bmp280_read(unsigned char Address);


//  读取温度计
BMP280_S32_t bmp280_read_Tdata(void);


// 读取气压计
BMP280_S32_t bmp280_read_Pdata(void);


//获取补偿系数
void bmp_compensation(void);


unsigned char bmp280_init(void);



// Returns temperature in DegC, double precision. Output value of “51.23” equals 51.23 DegC.
// t_fine carries fine temperature as global value

double bmp280_compensate_T_double(BMP280_S32_t adc_T);

// Returns pressure in Pa as double. Output value of “96386.2” equals 96386.2 Pa = 963.862 hPa
double bmp280_compensate_P_double(BMP280_S32_t adc_P);
