
#include <stdint.h>
#include <stdbool.h>
#include "hw_memmap.h"
#include "debug.h"
#include "gpio.h"
#include "hw_i2c.h"
#include "hw_types.h"
#include "i2c.h"
#include "pin_map.h"
#include "sysctl.h"
#include "systick.h"     //for text 4
#include "interrupt.h"     //for text 4

#define SYSTICK_FREQUENCY	1000  //1000HZ
#define I2C_FLASHTIME 500  //500HZ
#define GPIO_FLASHTIME  300  //300HZ
//*****************************************************************************
//
//I2C GPIO chip address and resigster define
//
//*****************************************************************************
#define TCA6424_I2CADDR 					0x22
#define PCA9557_I2CADDR						0x18

#define PCA9557_INPUT							0x00
#define	PCA9557_OUTPUT						0x01
#define PCA9557_POLINVERT					0x02
#define PCA9557_CONFIG						0x03

#define TCA6424_CONFIG_PORT0			0x0c
#define TCA6424_CONFIG_PORT1			0x0d
#define TCA6424_CONFIG_PORT2			0x0e

#define TCA6424_INPUT_PORT0				0x00
#define TCA6424_INPUT_PORT1				0x01
#define TCA6424_INPUT_PORT2				0x02

#define TCA6424_OUTPUT_PORT0			0x04
#define TCA6424_OUTPUT_PORT1			0x05
#define TCA6424_OUTPUT_PORT2			0x06




void 		Delay(uint32_t value);
void 		S800_GPIO_Init(void);
uint8_t 	I2C0_WriteByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t WriteData);
uint8_t 	I2C0_ReadByte(uint8_t DevAddr, uint8_t RegAddr);
void		S800_I2C0_Init(void);
volatile uint8_t result;
uint32_t ui32SysClock;
uint8_t seg7[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x58,0x5e,0x079,0x71,0x5c};
uint8_t count_add=1;     //for text 1
uint8_t count_sub=1;     //for text 1

volatile uint8_t systick_10ms_status,systick_100ms_status,gpio_status;   //for text 4
volatile uint8_t systick_10ms_counter,systick_100ms_counter;    //for text 4

int main(void)
{
	volatile uint16_t i2c_flash_cnt,gpio_flash_cnt;//TEXT4
	//use internal 16M oscillator, HSI
  ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_16MHZ |SYSCTL_OSC_INT |SYSCTL_USE_PLL |SYSCTL_CFG_VCO_480), 20000000);		
	
	SysTickPeriodSet(ui32SysClock/SYSTICK_FREQUENCY);//TEXT4
	SysTickEnable();//TEXT4
	SysTickIntEnable();//TEXT4
	IntMasterEnable();//TEXT4
	
	S800_GPIO_Init();
	S800_I2C0_Init();
	
	while (1)
	{

/*******************************************************************************************************/		
/*                             1.The running light that is very simple                                 */		
/*******************************************************************************************************/
/*		
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT1,seg7[1]);						//write port 1 				
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT2,(uint8_t)(1));					//write port 2		
		result = I2C0_WriteByte(PCA9557_I2CADDR,PCA9557_OUTPUT,0xfe);	
    Delay(4000000);
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT1,seg7[2]);						//write port 1 				
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT2,(uint8_t)(2));					//write port 2		
		result = I2C0_WriteByte(PCA9557_I2CADDR,PCA9557_OUTPUT,0xfd);	
    Delay(4000000);
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT1,seg7[3]);						//write port 1 				
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT2,(uint8_t)(4));					//write port 2		
		result = I2C0_WriteByte(PCA9557_I2CADDR,PCA9557_OUTPUT,0xfb);	
    Delay(4000000);
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT1,seg7[4]);						//write port 1 				
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT2,(uint8_t)(8));					//write port 2		
		result = I2C0_WriteByte(PCA9557_I2CADDR,PCA9557_OUTPUT,0xf7);	
    Delay(4000000);
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT1,seg7[5]);						//write port 1 				
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT2,(uint8_t)(16));					//write port 2		
		result = I2C0_WriteByte(PCA9557_I2CADDR,PCA9557_OUTPUT,0xef);	
    Delay(4000000);
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT1,seg7[6]);						//write port 1 				
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT2,(uint8_t)(32));					//write port 2		
		result = I2C0_WriteByte(PCA9557_I2CADDR,PCA9557_OUTPUT,0xdf);	
    Delay(4000000);
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT1,seg7[7]);						//write port 1 				
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT2,(uint8_t)(64));					//write port 2		
		result = I2C0_WriteByte(PCA9557_I2CADDR,PCA9557_OUTPUT,0xbf);	
    Delay(4000000);
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT1,seg7[8]);						//write port 1 				
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT2,(uint8_t)(128));					//write port 2		
		result = I2C0_WriteByte(PCA9557_I2CADDR,PCA9557_OUTPUT,0x7f);	
    Delay(4000000);
		//You need to notice that the number "0xff" means the BCD code. you can thansfer to number.
*/

/*******************************************************************************************************/
/*                      2.we will ues a loop way to achieve the running light                          */
/*******************************************************************************************************/
/*
    result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT1,seg7[count_add]);						//write num of seg 				
		result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT2,(uint8_t)(count_sub));					//write No of seg		
		result = I2C0_WriteByte(PCA9557_I2CADDR,PCA9557_OUTPUT,~count_sub);        //write No of led, you can use ~
    Delay(1000000);
		if(count_add>=8)  count_add = 1;
		else count_add++;
		if(count_sub>=128) count_sub = 1;
		else count_sub = count_sub * 2; 
*/
/*******************************************************************************************************/
/*                          3.we will ues a PJ1 to stop the running light                              */
/*******************************************************************************************************/
/*		
		while(!GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0))  //If you press the switch, it will be 0!
		{
		    Delay(100);
			  if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0))  break;  //until you give up press the switch
		}
*/

/*
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);												// Turn on the PF0 
		Delay(8000000);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);																// Turn off the PF0.
		Delay(8000000);	
*/
/*******************************************************************************************************/
/*                        4.we will ues an interrupt to make the running light                         */
/*******************************************************************************************************/
     
    if(systick_10ms_status)
		{
		    systick_10ms_status = 0;
			  if(++gpio_flash_cnt >= GPIO_FLASHTIME/10)
				{
				    gpio_flash_cnt = 0;
					  if(gpio_status)
							GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);												// Turn on the PF0 
						else
							GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);																// Turn off the PF0.
						gpio_status = !gpio_status;
				}
		}
		if(systick_100ms_status)
		{
		    systick_100ms_status = 0;
			  if((++i2c_flash_cnt >= I2C_FLASHTIME/100)&&GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_1))
				{
				    i2c_flash_cnt = 0;
					  result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT1,seg7[count_add]);						//write num of seg 				
		        result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT2,(uint8_t)(count_sub));					//write No of seg		
		        result = I2C0_WriteByte(PCA9557_I2CADDR,PCA9557_OUTPUT,~count_sub);        //write No of led, you can use ~
				    if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_1))
						{
						    if(count_add>=8)  count_add = 1;
		            else count_add++;
		            if(count_sub>=128) count_sub = 1;
		            else count_sub = count_sub * 2;
						}
				}
		}
	}
}

void Delay(uint32_t value)
{
	uint32_t ui32Loop;
	for(ui32Loop = 0; ui32Loop < value; ui32Loop++){};
}

void S800_GPIO_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);						//Enable PortF
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));			//Wait for the GPIO moduleF ready
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);						//Enable PortJ	
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ));			//Wait for the GPIO moduleJ ready
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);						//Enable PortN
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));			//Wait for the GPIO moduleN ready	
	
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);			//Set PF0 as Output pin
	GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);			//Set PN0 as Output pin
	GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE,GPIO_PIN_0 | GPIO_PIN_1);//Set the PJ0,PJ1 as input pin
	GPIOPadConfigSet(GPIO_PORTJ_BASE,GPIO_PIN_0 | GPIO_PIN_1,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
}


void S800_I2C0_Init(void)
{
	uint8_t result;
  SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);//��ʼ��i2cģ��
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);//ʹ��I2Cģ��0����������ΪI2C0SCL--PB2��I2C0SDA--PB3
	GPIOPinConfigure(GPIO_PB2_I2C0SCL);//����PB2ΪI2C0SCL
  GPIOPinConfigure(GPIO_PB3_I2C0SDA);//����PB3ΪI2C0SDA
  GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);//I2C��GPIO_PIN_2����SCL
  GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);//I2C��GPIO_PIN_3����SDA

	I2CMasterInitExpClk(I2C0_BASE,ui32SysClock, true);										//config I2C0 400k
	I2CMasterEnable(I2C0_BASE);	

	result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_CONFIG_PORT0,0x0ff);		//config port 0 as input
	result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_CONFIG_PORT1,0x0);			//config port 1 as output
	result = I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_CONFIG_PORT2,0x0);			//config port 2 as output 

	result = I2C0_WriteByte(PCA9557_I2CADDR,PCA9557_CONFIG,0x00);					//config port as output
	result = I2C0_WriteByte(PCA9557_I2CADDR,PCA9557_OUTPUT,0x0ff);				//turn off the LED1-8
	
}


uint8_t I2C0_WriteByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t WriteData)
{
	uint8_t rop;
	while(I2CMasterBusy(I2C0_BASE)){};//���I2C0ģ��æ���ȴ�
		//
	I2CMasterSlaveAddrSet(I2C0_BASE, DevAddr, false);
		//��������Ҫ�ŵ������ϵĴӻ���ַ��false��ʾ����д�ӻ���true��ʾ�������ӻ�
		
	I2CMasterDataPut(I2C0_BASE, RegAddr);//����д�豸�Ĵ�����ַ
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);//ִ���ظ�д�����
	while(I2CMasterBusy(I2C0_BASE)){};
		
	rop = (uint8_t)I2CMasterErr(I2C0_BASE);//������

	I2CMasterDataPut(I2C0_BASE, WriteData);
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);//ִ���ظ�д�����������
	while(I2CMasterBusy(I2C0_BASE)){};

	rop = (uint8_t)I2CMasterErr(I2C0_BASE);//������

	return rop;//���ش������ͣ��޴�����0
}

uint8_t I2C0_ReadByte(uint8_t DevAddr, uint8_t RegAddr)
{
	uint8_t value,rop;
	while(I2CMasterBusy(I2C0_BASE)){};	
	I2CMasterSlaveAddrSet(I2C0_BASE, DevAddr, false);
	I2CMasterDataPut(I2C0_BASE, RegAddr);
//	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);		
	I2CMasterControl(I2C0_BASE,I2C_MASTER_CMD_SINGLE_SEND);//ִ�е���д�����
	while(I2CMasterBusBusy(I2C0_BASE));
	rop = (uint8_t)I2CMasterErr(I2C0_BASE);
	Delay(1);
	//receive data
	I2CMasterSlaveAddrSet(I2C0_BASE, DevAddr, true);//���ôӻ���ַ
	I2CMasterControl(I2C0_BASE,I2C_MASTER_CMD_SINGLE_RECEIVE);//ִ�е��ζ�����
	while(I2CMasterBusBusy(I2C0_BASE));
	value=I2CMasterDataGet(I2C0_BASE);//��ȡ��ȡ������
		Delay(1);
	return value;
}
//for text 4
void SysTick_Handler(void)
{
  if(systick_100ms_counter != 0)
		systick_100ms_counter--;
	else
	{
	  systick_100ms_counter = SYSTICK_FREQUENCY/10;
		systick_100ms_status = 1;
	}
  if(systick_10ms_counter != 0)
		systick_10ms_counter--;
	else
	{
	  systick_10ms_counter = SYSTICK_FREQUENCY/100;
		systick_10ms_status = 1;
	}
/*******************************************************************************************************/
/*                       5.we will ues an interrupt to make LED PN0                                    */
/*******************************************************************************************************/	
	if(!GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0))
	{
	  systick_10ms_status = systick_100ms_status = 0;
   	GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);												// Turn on the PF0 			
	}	
	else 
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);																// Turn off the PF0.
}
