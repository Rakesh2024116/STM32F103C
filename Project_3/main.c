#include "stm32f10x.h"
#include "gpio_driver.h"
#include "systick_time.h"

void SysTick_Handler(void);

int main(void)
{
	init_GPIO(POA,0, IN, IN_PP);
	init_GPIO(POA, 12, OUT50, OP_GP_PP);
	init_GPIO(POC, 13, OUT50, OP_GP_PP);

	
	while(1)
	{
		Write_GP(POA, 12, Read_GP(POA,0));
	}
	
}

void SysTick_Handler(void)
{
	toggle_GP(POC, 13);
}
