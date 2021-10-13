#ifndef __HAL_BOARD_H__

#define __HAL_BOARD_H__

#define LED1    0
#define LED2    1
#define LED3    2
#define LED4    4

void hal_led_init(void);

void hal_led_off(int leds);
void hal_led_on(int leds);


void hal_uart_init(void);

#endif
