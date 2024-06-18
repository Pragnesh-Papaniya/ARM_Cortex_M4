#include <stdint.h>
#include <stdio.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE (128*1024)
#define SRAM_END ((SRAM_START)+(SRAM_SIZE))
#define STACK_START SRAM_END
#define STACK_MSP_START STACK_START
#define STACK_MSP_END (STACK_MSP_START -512)
#define STACK_PSP_START STACK_MSP_END




int function_add(int a,int b,int c,int d);

int function_add(int a,int b,int c,int d)
{
	int sum;
	sum=a+b+c+d;
	return sum;
}

__attribute__((naked))void change_sp_to_psp(void)
{
	__asm volatile(".equ SRAM_END,(0X20000000 +(128*1024))");
	__asm volatile(".equ PSP_START,(SRAM_END-512)");

	__asm volatile("LDR R0,=PSP_START");
	__asm volatile("MSR PSP,R0");
	__asm volatile("MOV R0,0X02");
	__asm volatile("MSR CONTROL,R0");
	__asm volatile("BX LR");

}

void generate_exception(void)
{
	__asm volatile("SVC #0x2");
}


int main(void)
{
 change_sp_to_psp();
	int sum;
	sum=function_add(1,2,3,4);
    printf("Sum of two numbers %d \n",sum);
    fflush(stdout);
    generate_exception();
	return 0;
}


void SVC_Handler(void)
{
    printf("in SVC_Handler \n");

}

/* This is caller*/
void function_Math(void)
{
	int sum;
	sum=function_add(1,2,3,4);
}


/* This is callee*/
int function_add(int a,int b,int c,int d)
{
	int sum;
	sum=a+b+c+d;
	return sum;
}

