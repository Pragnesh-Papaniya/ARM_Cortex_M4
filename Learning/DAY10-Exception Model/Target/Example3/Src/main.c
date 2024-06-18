
#include <stdint.h>

void delay()
{
	for(uint32_t i=0;i<300000;i++);
}

int main(void)
{

	uint32_t *pAHB1ENR  = (uint32_t*)0X40023830;
	uint32_t *pMODER    = (uint32_t*)0X40020000;
	uint32_t *pODR      = (uint32_t*)0X40020014;

	*pAHB1ENR  |= (1<<0);
	*pMODER    |= (1<<10);

	while(1)
	{
		 *pODR    |= (1<<5);
		 delay();
		 *pODR   &=~(1<<5);
		 delay();
	}


	return 0;
}
