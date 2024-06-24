
#include <stdint.h>

void delay(void)
{
	for (volatile uint32_t i=0;i<300000;i++);
}

int main(void)
{
	uint32_t *portcAHB1ENR =(uint32_t*)0x40023830;
	uint32_t *portcMODER=(uint32_t*)0x40020800;
	uint32_t *portcODR=(uint32_t*)0x40020814;
	uint32_t *portcIDR=(uint32_t*)0x40020810;

	uint32_t *portPUPDR=(uint32_t*)0x4002080C;


	// Enable the peripheral clock of GPIOC Register
	//*portcAHB1ENR  |=0X04;
	*portcAHB1ENR  |=(1<<2);
	//configure ROW GPIO IN OUTPUT MODE  PC0-PC3

	//configure COLUMN GPIO IN INPUT MODE PC4-PC7



	*portPUPDR &= 0XFFFF0000;
	*portPUPDR |= 0X00005500;

/////////////////

	*portcMODER &= 0XFFFF0000;
		*portcMODER |= 0X00000055;
	/////
	*portcODR|=0x0f;

	//MAKE R1 LOW
	while(1)
	{

		*portcODR|=0x0f;
	*portcODR &= ~(1<<0);

	if(!(*portcIDR & (1 <<4 )))
	{
		//key is pressed
		delay();
		printf("1 \n");
	}
	if(!(*portcIDR & (1 <<5 )))
		{
			//key is pressed
		delay();
			printf("2 \n");
		}
	if(!(*portcIDR & (1 <<6 )))
			{
				//key is pressed
		delay();
				printf("3 \n");
			}
	if(!(*portcIDR & (1 <<7 )))
			{
				//key is pressed
		delay();
				printf("4 \n");
			}
//MAKE R2 LOW
	*portcODR|=0x0f;
	*portcODR &= ~(1<<1);
	if(!(*portcIDR & (1 <<4 )))
		{
			//key is pressed
			delay();
			printf("5 \n");
		}
		if(!(*portcIDR & (1 <<5 )))
			{
				//key is pressed
			delay();
				printf("6 \n");
			}
		if(!(*portcIDR & (1 <<6 )))
				{
					//key is pressed
			delay();
					printf("7 \n");
				}
		if(!(*portcIDR & (1 <<7 )))
				{
					//key is pressed
			delay();
					printf("8 \n");
				}
		//MAKE R3 LOW
		*portcODR|=0x0f;
			*portcODR &= ~(1<<2);
			if(!(*portcIDR & (1 <<4 )))
					{
						//key is pressed
						delay();
						printf("9 \n");
					}
					if(!(*portcIDR & (1 <<5 )))
						{
							//key is pressed
						delay();
							printf("10 \n");
						}
					if(!(*portcIDR & (1 <<6 )))
							{
								//key is pressed
						delay();
								printf("11 \n");
							}
					if(!(*portcIDR & (1 <<7 )))
							{
								//key is pressed
						delay();
								printf("12 \n");
							}
					//MAKE R4 LOW
					*portcODR|=0x0f;
					*portcODR &= ~(1<<3);
								if(!(*portcIDR & (1 <<4 )))
										{
											//key is pressed
											delay();
											printf("13 \n");
										}
										if(!(*portcIDR & (1 <<5 )))
											{
												//key is pressed
											delay();
												printf("14 \n");
											}
										if(!(*portcIDR & (1 <<6 )))
												{
													//key is pressed
											delay();
													printf("15 \n");
												}
										if(!(*portcIDR & (1 <<7 )))
												{
													//key is pressed
											delay();
													printf("16 \n");
												}

//	delay();


}
}
