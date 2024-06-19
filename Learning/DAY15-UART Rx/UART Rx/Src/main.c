
#include <stdint.h>

uint32_t *pAHB1ENR  =(uint32_t*)0x40023830;
uint32_t *pAPB1ENR  =(uint32_t*)0x40023840;
uint32_t *pGPIOAMODER  =(uint32_t*)0x40020000;
uint32_t *pGPIOAODR  =(uint32_t*)0x40020014;
uint32_t *pGPIOAAFRL  =(uint32_t*)0x40020020;
uint32_t *pUSART2_SR  =(uint32_t*)0x40004400;
uint32_t *pUSART2_DR  =(uint32_t*)0x40004404;
uint32_t *pUSART2_BRR  =(uint32_t*)0x40004408;
uint32_t *pUSART2_CR1  =(uint32_t*)0x4000440c;

void Uart_Init(void);
void Uart_Write(int ch);
char Uart_Read(void);


void Uart_Init(void)
{
	//1) Enable the clock access for GPIOA

	  *pAHB1ENR   |=(1U<<0);

	//2) Enable the clock access for usart2
	  *pAPB1ENR  |=(1U<<17);
	//3)Configure the gpio MODE REGISTERS to alt function
	  //SET PA2 AS ALT FUNC
	  *pGPIOAMODER  &=~(1U<<4);
	  *pGPIOAMODER   |=(1U<<5);
	  //SET PA3 AS ALT FUNC
	  *pGPIOAMODER  &=~(1U<<6);
	  *pGPIOAMODER   |=(1U<<7);


	//4)Configure the gpio to o/p function
	  //SET PA5 AS 0/P
	   *pGPIOAMODER   |=(1U<<10);
	  *pGPIOAMODER  &=~(1U<<11);

	//5) configure the ALT FUNCTION to AFRL FOR PA2 and PA3
	  *pGPIOAAFRL |=(1U<<8);
	  *pGPIOAAFRL |=(1U<<9);
	  *pGPIOAAFRL |=(1U<<10);
	  *pGPIOAAFRL &=~(1U<<11);

	  *pGPIOAAFRL |=(1U<<12);
	  *pGPIOAAFRL |=(1U<<13);
	  *pGPIOAAFRL |=(1U<<14);
	  *pGPIOAAFRL &=~(1U<<15);

	//6)Configure the BRR TO 9600

	  *pUSART2_BRR =0X0683;

	//7)Configure the UART FOR TX AND RX

	  *pUSART2_CR1 |=0X0008;
	  *pUSART2_CR1 |=0X0004;

	  *pUSART2_CR1 |=0X2000;


}

void Uart_Write(int ch)
{
	//Make sure the transmit data register is empty

	while(!(*pUSART2_SR &0x0080)){}
	*pUSART2_DR =(ch&0xff);

}
char Uart_Read(void)
{

	while(!(*pUSART2_SR &0x0020)){}
	return	*pUSART2_DR;

}

int __io_putchar(int ch)
{
	Uart_Write(ch);
	return ch;
}

int main(void)
{

	char ch;
	Uart_Init();
	printf("Enter the loop \n");

	while(1)
	{
		ch=Uart_Read();
		if (ch=='a')
		{
			 *pGPIOAODR |=(1<<5);
		}else
		{
			 *pGPIOAODR &=~(1<<5);

		}
		printf("Data is  %c \n", ch);
	}


}
