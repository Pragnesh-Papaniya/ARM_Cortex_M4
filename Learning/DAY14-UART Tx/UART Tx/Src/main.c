#include <stdint.h>

//AHB1ENR 0x40023830
//APB1ENR 0x40023840
//GPIOMODER 0x40020000
//GPIOAFRL 0x40020020
//USART2_SR 0x40004400
//USART2_DR 0x40004404
//USART2_BRR 0x40004408
//USART2_CR1 0x4000440c

uint32_t *pAHB1ENR    = (uint32_t*)0x40023830;
uint32_t *pAPB1ENR    = (uint32_t*)0x40023840;
uint32_t *pGPIOMODER  = (uint32_t*)0x40020000;
uint32_t *pGPIOAFRL    = (uint32_t*)0x40020020;
uint32_t *pUSART2_SR  = (uint32_t*)0x40004400;
uint32_t *pUSART2_DR  = (uint32_t*)0x40004404;
uint32_t *pUSART2_BRR = (uint32_t*)0x40004408;
uint32_t *pUSART2_CR1 = (uint32_t*)0x4000440c;

void Uart_Init(void);
void Uart_Write(int ch);

void Uart_Init(void)
{
	//1) Enable the Clock access for GPIOA
	*pAHB1ENR |=(1U<<0);
	//2) Enable the Clock access for USART2
	*pAPB1ENR |=(1U<<17);
	//3) Configure GPIOA TO ALT FUNCTION
	*pGPIOMODER &=~(1U<<4);
	*pGPIOMODER |=(1U<<5);
	//CONFIGURE PA2 TO USART2
	*pGPIOAFRL |=(1U<<8);
	*pGPIOAFRL |=(1U<<9);
	*pGPIOAFRL |=(1U<<10);
	*pGPIOAFRL &=~(1U<<11);
	//configure BRR too 9600
	*pUSART2_BRR =0x0683;
	//configure uart
	*pUSART2_CR1 |=0x0008;
	*pUSART2_CR1 |=0x2000;

}

void Uart_Write(int ch)
{
	while(!(*pUSART2_SR & 0x0080)){}
	*pUSART2_DR =(ch&0xff);


}

int __io_putchar(int ch)
{
	Uart_Write(ch);
	return ch;
}


int main(void)
{

	Uart_Init();
	//Uart_Write();
    /* Loop forever */
	while(1)
	{
		printf("Hello world \r \n");
	}
	for(;;);
}
