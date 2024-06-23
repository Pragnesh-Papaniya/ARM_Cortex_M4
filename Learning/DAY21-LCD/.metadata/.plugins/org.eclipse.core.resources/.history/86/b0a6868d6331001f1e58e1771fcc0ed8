//PC0 -PC7  --D0-D7 IN LCD
//PB5 -RS
//PB6 -RW
//PB7 -EN

#include <stdint.h>
#include "stm32f4xx.h"

#define RS 0x20 //0010 0000
#define RW 0x40 //0100 0000
#define EN 0x80  //1000 0000

unsigned char Message[]=("PANTECH...");
void GPIO_Init(void);
void LCD_Command(unsigned char command);
void LCD_Data(unsigned char data);
void LCD_Init(void);
void delayMs(int delay);


int main(void)
{
	LCD_Init();
	/* Loop forever */

	for(;;);
}

void GPIO_Init(void)
{
	RCC->AHB1ENR |= 0X06;
	GPIOB->MODER |=0X5400;
	GPIOB->BSRR =0X00C; //SET EN AND RW LOW
	GPIOC->MODER |=0X00005555;



}
void LCD_Command(unsigned char command)
{
	// RS=0  RW=0
	GPIOB->BSRR=(RS|RW)<<16;
	GPIOC->ODR=command;
	GPIOB->BSRR=EN ; //ENABLE EN
	delayMs(0);
	GPIOB->BSRR=EN<<16 ; //clear EN
	//delayMs(30);

}

void LCD_Data(unsigned char data)
{
	//RS=1 ,RW=0
	GPIOB->BSRR=RS;
	GPIOB->BSRR=RW<<16;
	GPIOC->ODR=data;
	GPIOB->BSRR=EN ; //ENABLE EN
	delayMs(30);
	GPIOB->BSRR=EN<<16 ; //clear EN
	delayMs(30);



}

void LCD_Init(void)
{
	unsigned char i=0;

	GPIO_Init();
	LCD_Command(0x28); //select one line
	delayMs(15);
	LCD_Command(0x0c); //set b it data mode
	delayMs(15);
	LCD_Command(0x06); //move the cursor right
	delayMs(15);
	LCD_Command(0x01); //clear screen move cursor home
	delayMs(15);
	delayMs(5000);

	LCD_Command(0x80); //turn display
	delayMs(15);
	while (Message[i]!='\0')
		{
			LCD_Data(Message[i]);
			i++;
		}
		delayMs(50);
		LCD_Command(0xC0); //turn display
		delayMs(15);

}
void delayMs(int delay)
{
	int i;
	for (;delay>0;delay--)
	{
		for(i=0;i<3195;i++)
		{

		}
	}
}
