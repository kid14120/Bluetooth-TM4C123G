#ifndef		__BLE_H
#define		__BLE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"

#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/gpio.h"


//ʱ��
#define SYSCTL_PERIPH_BLE  						SYSCTL_PERIPH_UART2
#define SYSCTL_PERIPH_BLE_GPIO 			  SYSCTL_PERIPH_GPIOD

//���ں�
#define BLE_UART_BASE    							UART2_BASE
#define BLE_INT_UART									INT_UART2

//�ܽ�
#define BLE_GPIO_BASE									GPIO_PORTD_BASE
#define BLE_GPIO_RX										GPIO_PD6_U2RX
#define BLE_GPIO_TX										GPIO_PD7_U2TX
#define BLE_GPIO_PIN_RX               GPIO_PIN_6
#define BLE_GPIO_PIN_TX 							GPIO_PIN_7

//������
#define BLE_BAUD        							115200



void BLE_Init(void);
void BLE_sendware(char *wareaddr, uint32_t waresize);
void test(void);
#endif

