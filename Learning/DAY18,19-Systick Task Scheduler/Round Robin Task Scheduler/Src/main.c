#include<stdint.h>
#include<stdio.h>

#define MAX_TASKS   5

/* some stack memory calculations */
#define SIZE_TASK_STACK          1024U
#define SIZE_SCHED_STACK         1024U

#define SRAM_START               0x20000000U
#define SIZE_SRAM                ( (96) * (1024))
#define SRAM_END                 ((SRAM_START) + (SIZE_SRAM) )

#define T1_STACK_START           SRAM_END
#define T2_STACK_START           ( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define T3_STACK_START           ( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T4_STACK_START           ( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define IDLE_STACK_START         ( (SRAM_END) - (4 * SIZE_TASK_STACK) )
#define SCHED_STACK_START        ( (SRAM_END) - (5 * SIZE_TASK_STACK) )

#define TICK_HZ 1000U

#define HSI_CLOCK         		16000000U
#define SYSTICK_TIM_CLK   		HSI_CLOCK


#define DUMMY_XPSR  0x01000000U

#define TASK_READY_STATE  0x00
#define TASK_BLOCKED_STATE  0XFF

void Task1_Handler(void); //This is task1
void Task2_Handler(void); //this is task2
void Task3_Handler(void); //this is task3
void Task4_Handler(void); // this is task4 of the application


void init_systick_timer(uint32_t tick_hz);
__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack);
void init_tasks_stack(void);
void enable_processor_faults(void);
__attribute__((naked)) void switch_sp_to_psp(void);
uint32_t get_psp_value(void);

void task_delay(uint32_t tick_count);


/* This variable tracks the current_task being executed on the CPU */
uint8_t current_task = 1; //task1 is running



/* This is a task control block carries private information of each task */
typedef struct
{
	uint32_t psp_value;
	uint32_t block_count;
	uint8_t  current_state;
	void (*task_handler)(void);
}TCB_t;

/* Each task has its own TCB */
TCB_t user_tasks[MAX_TASKS];

int main(void)
{

	enable_processor_faults();
	init_scheduler_stack(SCHED_STACK_START);
	init_tasks_stack();
	init_systick_timer(TICK_HZ);
	switch_sp_to_psp();
	Task1_Handler();
	for(;;);
}


void idle_task(void)
{
	while(1);
}


void Task1_Handler(void)
{
	while(1)
	{

		printf(" Task1 \n");



	}

}

void Task2_Handler(void)
{
	while(1)
	{
		printf(" Task2 \n");


	}

}

void Task3_Handler(void)
{
	while(1)
	{
		printf(" Task3 \n");


	}

}

void Task4_Handler(void)

{
	while(1)
	{

		printf(" Task4 \n");

	}


}


void init_systick_timer(uint32_t tick_hz)
{
	uint32_t *pSRVR = (uint32_t*)0xE000E014;
	uint32_t *pSCSR = (uint32_t*)0xE000E010;

    /* calculation of reload value */
    uint32_t count_value = (SYSTICK_TIM_CLK/tick_hz)-1;

    //Clear the value of SVR
    *pSRVR &= ~(0x00FFFFFFFF);

    //load the value in to SVR
    *pSRVR |= count_value;

    //do some settings
    *pSCSR |= ( 1 << 1); //Enables SysTick exception request:
    *pSCSR |= ( 1 << 2);  //Indicates the clock source, processor clock source

    //enable the systick
    *pSCSR |= ( 1 << 0); //enables the counter

}


__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack)
{
     __asm volatile("MSR MSP,%0": :  "r" (sched_top_of_stack)  :   );
     __asm volatile("BX LR");

}



/* this function stores dummy stack contents for each task */

void init_tasks_stack(void)
{

	user_tasks[0].current_state = TASK_READY_STATE;
	user_tasks[1].current_state = TASK_READY_STATE;
	user_tasks[2].current_state = TASK_READY_STATE;
	user_tasks[3].current_state = TASK_READY_STATE;
	user_tasks[4].current_state = TASK_READY_STATE;

	user_tasks[0].psp_value = IDLE_STACK_START;
	user_tasks[1].psp_value = T1_STACK_START;
	user_tasks[2].psp_value = T2_STACK_START;
	user_tasks[3].psp_value = T3_STACK_START;
	user_tasks[4].psp_value = T4_STACK_START;

	user_tasks[0].task_handler = idle_task;
	user_tasks[1].task_handler = Task1_Handler;
	user_tasks[2].task_handler = Task2_Handler;
	user_tasks[3].task_handler = Task3_Handler;
	user_tasks[4].task_handler = Task4_Handler;


	uint32_t *pPSP;

	for(int i = 0 ; i < MAX_TASKS ;i++)
	{
		pPSP = (uint32_t*) user_tasks[i].psp_value;

		pPSP--;
		*pPSP = DUMMY_XPSR;//0x01000000

		pPSP--; //PC
		*pPSP = (uint32_t) user_tasks[i].task_handler;

		pPSP--; //LR
		*pPSP = 0xFFFFFFFD;

		for(int j = 0 ; j < 13 ; j++)
		{
			pPSP--;
		    *pPSP = 0;

		}

		user_tasks[i].psp_value = (uint32_t)pPSP;


	}

}

void enable_processor_faults(void)
{
	uint32_t *pSHCSR = (uint32_t*)0xE000ED24;

	*pSHCSR |= ( 1 << 16); //mem manage
	*pSHCSR |= ( 1 << 17); //bus fault
	*pSHCSR |= ( 1 << 18); //usage fault
}


uint32_t get_psp_value(void)
{

	return user_tasks[current_task].psp_value;
}


void save_psp_value(uint32_t current_psp_value)
{
	user_tasks[current_task].psp_value = current_psp_value;
}


void update_next_task(void)
{
	current_task++;
		current_task %=MAX_TASKS;//SET ROUND ROBIN

}




__attribute__((naked)) void switch_sp_to_psp(void)
{

	 //1. initialize the PSP with TASK1 stack start address
		//get the value of psp of current_task
		//Preserve LR which connects back to main() using PUSH
		__asm volatile ("PUSH {LR}");
		//Get the PSP Value of the Current Task
		__asm volatile ("BL get_psp_value");
		//Initialize PSP
		__asm volatile ("MSR PSP,R0");
		//Retrieve LR Value using POP
		__asm volatile ("POP {LR}");
		//Change SP to PSP using CONTROL register
		__asm volatile ("MOV R0,#0X02");
		__asm volatile ("MSR CONTROL,R0");
		//Return to Main Function
		__asm volatile ("BX LR");
}













__attribute__((naked))  SysTick_Handler(void)
{

	//1. Get current running task's PSP value
		__asm volatile("MRS R0,PSP");
		//2. Using that PSP value store SF2( R4 to R11)
		__asm volatile("STMDB R0!,{R4-R11}");
	    //3.Save the LINK Register Using PUSH Operations
		__asm volatile("PUSH {LR}");
		//4. Save the current value of PSP
	    __asm volatile("BL save_psp_value");
	    //5. Decide next task to run
	    __asm volatile("BL update_next_task");
		//6. get its past PSP value
		__asm volatile ("BL get_psp_value");
		//7. Using that PSP value retrieve SF2(R4 to R11)
		__asm volatile ("LDMIA R0!,{R4-R11}");
		//8. update PSP
		__asm volatile("MSR PSP,R0");
	     //9.Retrieve the LINK Register Using POP Operations
		__asm volatile("POP {LR}");
	     //Update PSP and exit
		__asm volatile("BX LR");

}

//2. implement the fault handlers
void HardFault_Handler(void)
{
	printf("Exception : Hardfault\n");
	while(1);
}


void MemManage_Handler(void)
{
	printf("Exception : MemManage\n");
	while(1);
}

void BusFault_Handler(void)
{
	printf("Exception : BusFault\n");
	while(1);
}
