
#include <stdint.h>



int main(void)
{
	//Enable the Fault
	uint32_t *pSHCSR = (uint32_t*)0xe000ed24;

	//Enable the fault
//	*pSHCSR |= (1<<18); //usage fault
	*pSHCSR |= (1<<17); //Bus fault
	*pSHCSR |= (1<<16); //Mem fault

// Lets force the processor to execute an undefined instruction

	void(*random_address)(void);
	random_address=(void*)0xe0000008;
	random_address();


	for(;;);
}


void HardFault_Handler(void)
{
	printf("Exception:Hard fault \n");
	while(1);
}
void MemManage_Handler(void)
{
	printf("Exception:Memmanage fault \n");
	while(1);
}
void BusFault_Handler(void)
{
	printf("Exception:Bus fault \n");
	while(1);
}
void UsageFault_Handler(void)
{
	printf("Exception:UsageFault \n");
while(1);
}
