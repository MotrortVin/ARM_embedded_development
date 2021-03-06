#include <stdint.h>
#include <stdbool.h>
#include "hw_memmap.h"
#include "debug.h"
#include "gpio.h"
#include "hw_types.h"
#include "pin_map.h"
#include "sysctl.h"


#define   FASTFLASHTIME			(uint32_t) 300000
#define   SLOWFLASHTIME			(uint32_t) FASTFLASHTIME*20


void 		Delay(uint32_t value);
void 		S800_GPIO_Init(void);
//void		PF0_Flash(uint32_t key_value);
//void		PF0_Flash_1(uint32_t key_value);
//void		PF1_Flash_1(uint32_t key_value);

uint32_t debug1;            //Debug HERE!
uint8_t btn_cnt = 0; 
bool press_sw1 = false;

int main(void)
{
//	uint32_t read_key_value;
//	uint32_t read_key_value1;
	S800_GPIO_Init();
//	debug1=SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |SYSCTL_OSC_MAIN |SYSCTL_USE_PLL |SYSCTL_CFG_VCO_480), 120000000);        //debug HERE!
/************************************************text1-1******************************************/
//  SysCtlClockFreqSet((SYSCTL_OSC_INT |SYSCTL_USE_OSC), 16000000);
//  SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |SYSCTL_OSC_MAIN |SYSCTL_USE_OSC), 25000000);
	SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |SYSCTL_OSC_MAIN |SYSCTL_USE_PLL |SYSCTL_CFG_VCO_480), 20000000);
/************************************************text1-3******************************************/	
	while(1)
	{
	    if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0) == 0)
	  	{
	  	  press_sw1 = true;
	  	}
	  	else
	  	{
	  	  if(press_sw1)
	  		{
	  			btn_cnt++;
					if(btn_cnt>=4) btn_cnt = 0;
	  		}
	  		press_sw1 = false;
	  	}	
  	
	  
  	  switch(btn_cnt)
  	  {
				case 1:
	    	{
	    	  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);			// Turn on the LED.
		    	Delay(FASTFLASHTIME);
    			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);							// Turn off the LED.
		    	Delay(FASTFLASHTIME);
		    	break;
    		}
		    case 2:
        {
		      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);							// Turn off the LED.
		    	break;
		    }
        case 3:	
		    {
		      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);			// Turn on the LED.
		    	Delay(FASTFLASHTIME);
		    	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);							// Turn off the LED.
			    Delay(FASTFLASHTIME);
			    break;
		    }
				case 0:
        {
				  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);							// Turn off the LED.
				}					
		    default:
			    break;
	    }
  }
/***********************************************text1-2*********************************************/	
//	while(1)
//  {
//		read_key_value = GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0)	;				//read the PJ0 key value
//		read_key_value1 = GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_1)	;				//read the PJ1 key value
//		PF0_Flash(read_key_value);
//		PF0_Flash_1(read_key_value);
//		PF1_Flash_1(read_key_value1);
//   } 	
}

//void PF0_Flash_1(uint32_t key_value)
//{
//  if (key_value	== 0)						//USR_SW1-PJ0 pressed
//			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);			// Turn on the LED.
//		else													//USR_SW1-PJ0 released
//			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);							// Turn off the LED.
//}
//void PF1_Flash_1(uint32_t key_value)
//{
// if(key_value == 0)
//		  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);			// Turn on the LED.
//	else
//		  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);							// Turn off the LED.
//}

/*****************************************the origin text********************************************/
//void PF0_Flash(uint32_t key_value)
//{
//	uint32_t delay_time;
//		if (key_value	== 0)						//USR_SW1-PJ0 pressed
//			delay_time							= FASTFLASHTIME;
//		else													//USR_SW1-PJ0 released
//			delay_time							= SLOWFLASHTIME;
//		
//		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);			// Turn on the LED.
//		Delay(delay_time);
//		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);							// Turn off the LED.
//		Delay(delay_time);
//}

void Delay(uint32_t value)
{

		uint32_t ui32Loop;
	for(ui32Loop = 0; ui32Loop < value; ui32Loop++){};
}


void S800_GPIO_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);						//Enable PortF
	//函数原型：void SysCtlPeripheralEnable(uint32_t ui32Peripheral)
	
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));			//Wait for the GPIO moduleF ready
	//函数原型：bool SysCtlPeripheralReady(uint32_t ui32Peripheral)
	//如果指定的外设被使能成功，返回true，否则返回false
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);						//Enable PortJ	
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ));			//Wait for the GPIO moduleJ ready	
	
	/*********************************Here,Change the output!************************************************/
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_1);			//Set PF0 as Output pin
	//函数原型：void GPIOPinTypeGPIOOutput(uint32_t ui32Port, uint8_t ui8Pins)
	//配置GPIO端口引脚为输出引脚，如果字符型（uint8_t）参数ui8Pins某位为1，则GPIO端口对应位配置为输出引脚
	
	GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE,GPIO_PIN_0 | GPIO_PIN_1);//Set the PJ0,PJ1 as input pin
	//配置GPIO端口引脚为输入引脚，与GPIOPinTypeGPIOOutput()类似。GPIO_PIN_0 | GPIO_PIN_1 = 00000011b
	
	GPIOPadConfigSet(GPIO_PORTJ_BASE,GPIO_PIN_0 | GPIO_PIN_1,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
	//函数原型：void GPIOPadConfigSet(uint32_t ui32Port, uint8_t ui8Pins, uint32_t ui32Strength, uint32_t ui32PinType)
	//GPIO端口配置。uint32_t ui32Port：GPIO端口基地址
	//ui8Pins：端口引脚位组合表示，如10000001b表示配置端口的D7、D0位
	//ui32Strength：端口的输出驱动能力，对输入设置无效，可选项包括GPIO_STRENGTH_2MA/4MA/8MA/8MA_SC/6MA/10MA/12MA
	//ui32PinType：引脚类型，可选项包括GPIO_PIN_TYPE_STD（推挽）、GPIO_PIN_TYPE_STD_WPU（推挽上拉）、GPIO_PIN_TYPE_STD_WPD（推挽下拉）、
	//GPIO_PIN_TYPE_OD（开漏）、GPIO_PIN_TYPE_ANALOG（模拟）、GPIO_PIN_TYPE_WAKE_HIGH（高电平从冬眠唤醒）、GPIO_PIN_TYPE_WAKE_LOW（低）
}


