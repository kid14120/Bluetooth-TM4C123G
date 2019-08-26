#ifndef  __BLE_H
#define  __BLE_H
//时钟
#define SYSCTL_PERIPH_BLE           SYSCTL_PERIPH_UART2
#define SYSCTL_PERIPH_BLE_GPIO      SYSCTL_PERIPH_GPIOD
//串口号
#define BLE_UART_BASE               UART2_BASE
#define BLE_INT_UART                INT_UART2
//管脚
#define BLE_GPIO_BASE               GPIO_PORTD_BASE
#define BLE_GPIO_RX                 GPIO_PD6_U2RX
#define BLE_GPIO_TX                 GPIO_PD7_U2TX
#define BLE_GPIO_PIN_RX             GPIO_PIN_6
#define BLE_GPIO_PIN_TX             GPIO_PIN_7
//波特率
#define BLE_BAUD                    115200

void BLE_Init(void);
void BLE_sendware(char *wareaddr, uint32_t waresize);
void test(void);
#endif


