#include <LPC17xx.h>
#include "stdio.h"
#include "uart.h"
#include <cmsis_os2.h>

unsigned int prvBtnPress = 1;
unsigned int pressed = 0;
unsigned int counter = 0;
osMutexId_t myMutexID;

const osMutexAttr_t Thread_Mutex_attr = {
	"myButtonMutex", // human readable mutex name
	0, // attr_bits
	NULL, // memory for control block
	0U // size for control block
};

void printSimpleMutex(void* args)
{
	while(1){
		osMutexAcquire(myMutexID,osWaitForever);
		//critical section
		osMutexRelease(myMutexID);
	}
}

void toggleLED(void* args)
{
	while(1)
	{
		unsigned int btn = (LPC_GPIO2->FIOPIN) & (1<<10);
		
		if(!btn && prvBtnPress)
		{
			pressed = !pressed;
		}
		
	}
}

int main (void) 
{
	SystemInit();
	osKernelInitialize();
	myMutexID = osMutexNew(&Thread_Mutex_attr);
	
	//osThreadNew(function, NULL, NULL);
	
	osKernelStart();
	while(1);
}