

#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
int hard(int a,int b);

int hard(int a,int b)
{

	  void (*jump_address)(void);
	  jump_address =(void*)0x20000008;
	      jump_address();
	      return a+b;
}

int main(void)
{
	//1. Enable all the configurabel exceptions like usage fault,memmnagae and bus fault
      uint32_t *pSHCSR =(uint32_t *)0xe000ed24;

	//2.Implement Fault Handlers
  *pSHCSR |=(1<<16);//Mem Manage
  *pSHCSR |=(1<<17);//Bus fault
  *pSHCSR |=(1<<18); //usage fault

      //void(*jump_addr)(void)
      hard(1,2);
	//3.Lets force the processor to execute undefined instruction
      uint32_t *pSRAM =(uint32_t *)0x40001000;
      *pSRAM = 0XFFFFFFFF;
      void (*random_address)(void);
      random_address =(void*)0x20000008;
      random_address();
    /* Loop forever */
	for(;;);
}
void HardFault_Handler(void)
{
	printf("Exception: Hard fault \n");
	while (1);

}
void MemManage_Handler(void)
{
	printf("Exception: Memmanage \n");
		while (1);
}
void BusFault_Handler(void)
{
	printf("Exception: BusFault \n");
while (1);

}
void UsageFault_Handler(void)
{
    uint32_t *pCFSR =(uint32_t *)0xE000ED28;


	printf("Exception: UsageFault \n");
	printf("CFSR= %x\n: ",(*pCFSR)&0xffff);

		while (1);
}
