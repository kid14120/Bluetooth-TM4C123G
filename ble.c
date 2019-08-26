#include "ble.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
int num = 0;
uint8_t  startBit_ble = 0;
uint8_t startBit_Ble = 0;
uint16_t intpurBleString[80] = {0};
uint16_t BleBit = 0;


extern uint8_t mode;
extern void mode_change(uint8_t modee);
extern void mode7_change(float mode7_centerr);
extern void mode2_change(uint8_t mode_2_counttt);
extern float angel_up ;
extern float angel_down ;


void BleIntHandler(void)
{
		uint32_t flag = UARTIntStatus(BLE_UART_BASE,1);
		//清除中断标志
		UARTIntClear(BLE_UART_BASE,flag);
	
		BleBit =UARTCharGet(BLE_UART_BASE);	//读取接收到的数据
//		UARTCharPut(UART0_BASE,BleBit);	
		if(BleBit == '$')
	    {
	      	startBit_ble = 1;
					num = 0;
	    }
	    if(startBit_ble == 1)
	    {
	       	intpurBleString[num] = BleBit;     
	    }  
	    if (startBit_ble == 1 && BleBit == '#') 
	    {		
				startBit_Ble = 1; 
				startBit_ble = 0;
	    }
			num++;
			if(num >= 80)
				{
					num = 0;
					startBit_ble = 0;
					startBit_Ble	= 0;
				}	 	
}


void BLE_Init(void)
{
	//使能UART外设
	SysCtlPeripheralEnable(SYSCTL_PERIPH_BLE);
	//使能GPIO外设
	SysCtlPeripheralEnable(SYSCTL_PERIPH_BLE_GPIO);
//	//GPIO复用模式配置
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0xFF;
	
	GPIOPinConfigure(BLE_GPIO_RX);
	GPIOPinConfigure(BLE_GPIO_TX);
	GPIOPinTypeUART(BLE_GPIO_BASE, BLE_GPIO_PIN_RX |BLE_GPIO_PIN_TX);
	//uart配置 波特率：115200 8位 1位停止位 无校验
	UARTConfigSetExpClk(BLE_UART_BASE, SysCtlClockGet(),
                    BLE_BAUD, (UART_CONFIG_WLEN_8 |UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
	
	//UART禁用FIFO 默认FIFO Level为4/8 寄存器满8字节后产生中断
	//禁用后接收1位就产生中断
	UARTFIFODisable(BLE_GPIO_BASE);
	//使能UART0中断
	IntEnable(BLE_INT_UART);
	//使能UART0接收中断
	UARTIntEnable(BLE_UART_BASE,UART_INT_RX |UART_INT_RT);
	//UART中断地址注册
	UARTIntRegister(BLE_UART_BASE,BleIntHandler);
	
	IntPrioritySet(BLE_INT_UART, 3);
	
	
}





void usart_ble_putbuff(char *buff, uint32_t len)
{

	UARTCharPut(UART2_BASE,'$');
	while(len--)
	{
		UARTCharPut(UART2_BASE,*buff);
		buff++;
	}
	UARTCharPut(UART2_BASE,'#');
//	LED_GREEN_DUBUG(OFF);
}

void BLE_sendware(char *wareaddr, uint32_t waresize)
{
	usart_ble_putbuff(wareaddr, waresize);
}





