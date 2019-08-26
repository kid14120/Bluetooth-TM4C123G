#include "ble.h"

int num = 0;                        //用来记数组位数的
uint8_t  startBit_ble = 0;          //开始接受数据标志位
uint16_t intpurBleString[80] = {0}; //用来存储蓝牙接受的数据的
uint16_t BleBit = 0;                //接受蓝牙发送的数据

//中断服务函数
void BleIntHandler(void)
{
  uint32_t flag = UARTIntStatus(BLE_UART_BASE,1);
  UARTIntClear(BLE_UART_BASE,flag);  //清除中断标志
  BleBit =UARTCharGet(BLE_UART_BASE); //读取接收到的数据
 
  if(BleBit == '$')  //读取开始位
     {
        startBit_ble = 1;
        num = 0;
     }
  if(startBit_ble == 1)
     {
         intpurBleString[num] = BleBit;     
     }  
  if (startBit_ble == 1 && BleBit == '#') //读到了停止位
     {  
    	 startBit_ble = 0;
     }
     
  num++;
  
  if(num >= 80)      //阈值
    {
	   num = 0;
	   startBit_ble = 0;
    }   
}

//蓝牙串口初始化
void BLE_Init(void)
{
 //使能UART外设
 SysCtlPeripheralEnable(SYSCTL_PERIPH_BLE);
 //使能GPIO外设
 SysCtlPeripheralEnable(SYSCTL_PERIPH_BLE_GPIO);
 //GPIO复用模式配置，解锁引脚
 HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
 HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0xFF;
 
 GPIOPinConfigure(BLE_GPIO_RX);
 GPIOPinConfigure(BLE_GPIO_TX);
 GPIOPinTypeUART(BLE_GPIO_BASE, BLE_GPIO_PIN_RX |BLE_GPIO_PIN_TX);
 //uart配置 波特率：115200 8位 1位停止位 无校验，一般蓝牙模块默认的波特率为9600记得修改
 UARTConfigSetExpClk(BLE_UART_BASE, SysCtlClockGet(),
                    BLE_BAUD, (UART_CONFIG_WLEN_8 |UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
 
 //UART禁用FIFO 默认FIFO Level为4/8 寄存器满8字节后产生中断
 //禁用后接收1位就产生中断
 UARTFIFODisable(BLE_GPIO_BASE);
 //使能UART2中断
 IntEnable(BLE_INT_UART);
 //使能UART2接收中断
 UARTIntEnable(BLE_UART_BASE,UART_INT_RX |UART_INT_RT);
 //UART中断地址注册
 UARTIntRegister(BLE_UART_BASE,BleIntHandler);
 //优先级
 IntPrioritySet(BLE_INT_UART, 3);
}
//发送数据
void BLE_sendware(char *wareaddr, uint32_t waresize)
{
   usart_ble_putbuff(wareaddr, waresize);
}
//打包
void usart_ble_putbuff(char *buff, uint32_t len)
{
   UARTCharPut(UART2_BASE,'$')；
   while(len--)
      {
	  UARTCharPut(UART2_BASE,*buff);
	  buff++;
      }
   UARTCharPut(UART2_BASE,'#');
 }


