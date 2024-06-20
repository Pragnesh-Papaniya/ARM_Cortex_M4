
#include <stdint.h>

#define SYSTICK_LOAD_VALUE 16000

#define CTRL_ENABLE (1U<<0)
#define CTRL_CLKSRC (1U<<2)
#define CTRL_COUNTFLAG (1U<<16)

#define GPIOAEN (1U<<0)
#define PIN5 (1U<<5)

#define LED (1U<<5)

void systickdelayms(int delay);


uint32_t *pSTCSR =(uint32_t*)0xe000e010;
uint32_t *pSTRVR =(uint32_t*)0xe000e014;
uint32_t *pSTCVR =(uint32_t*)0xe000e018;
uint32_t *pSTCR  =(uint32_t*)0xe000e01c;

uint32_t *pAHB1ENR  =(uint32_t*)0x40023830;
uint32_t *pGPIOAMODER  =(uint32_t*)0x40020000;
uint32_t *pGPIOAMODR  =(uint32_t*)0x40020014;

void systickdelayms(int delay)
{
	*pSTRVR  |=SYSTICK_LOAD_VALUE;

	*pSTCVR |=0;
	*pSTCSR |=CTRL_ENABLE;
	*pSTCSR |=CTRL_CLKSRC;
	for (int i=0;i<delay;i++)
	{
		while((*pSTCSR & CTRL_COUNTFLAG)==0){}
	}
	*pSTCSR |=0;
}


int main(void)
{

	*pAHB1ENR |=GPIOAEN;
	*pGPIOAMODER |= (1U<<10);
	*pGPIOAMODER  &= ~(1U<<11);
while(1)
{
	*pGPIOAMODR ^=LED;
	systickdelayms(500);
}
}
