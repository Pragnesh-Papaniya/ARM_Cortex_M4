
#include <stdint.h>

void delay()
{
	for(uint32_t i=0;i<300000;i++);
}

int main(void)
{

	uint32_t *pAHB1ENR  = (uint32_t*)0X40023830;
	uint32_t *pGPIOAMODER    = (uint32_t*)0X40020000;
	uint32_t *pGPIOAODR      = (uint32_t*)0X40020014;
	uint32_t *pGPIOCMODER    = (uint32_t*)0X40020800;
	uint32_t *pGPIOCIDR      = (uint32_t*)0X40020810;

	*pAHB1ENR  |= (1<<0); //ENABLE GPIOA
	*pAHB1ENR  |= (1<<2); //ENABLE GPIOC

	*pGPIOAMODER    |= (1<<10);

	while(1)
	{
		uint8_t value;
		value= (uint8_t)((*pGPIOCIDR >>13)&(0x01));
		if (value ==0)
		{
         delay();
		 *pGPIOAODR   ^=(1<<5);
		}
	}
	return 0;
}
