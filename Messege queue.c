/*
 * Messege queue.c
 *
 * Created: 7/21/2023 4:08:23 AM
 * Author : kamar
 */ 

#include <avr/io.h>
#include "LCD driver.h"
#include "Keybad driver.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

void keypad (void *pv);
void LCD (void *pv);

QueueHandle_t  my_queue;

int main(void)
{
	
	/* intialization*/
	Keybad_vinit ();
	LCD_vinit ();
	
	/* create tasks*/
	xTaskCreate (keypad ,"k",100,NULL, 2,NULL);
    xTaskCreate (LCD ,"L",100,NULL, 1,NULL);
	
	/*create message queue*/
	my_queue= xQueueCreate(5, sizeof(char));
	
	/*start OS*/
	vTaskStartScheduler();
}

void keypad (void *pv)
{
	char x;
	while(1)
	{
		x=Keybad_u8check_press ();
		if (x!=NOTBRESSED)                                                              // if the user enter data 
		{
			xQueueSend(my_queue, &x,  1000);                                            // post data to the messege queue
			vTaskDelay(300);                                                            // go to waiting state for 300 tick
		}
	}
}

void LCD (void *pv)
{
	char y;
	while(1)
	{
		xQueueReceive(my_queue, &y, 1000);                                          //pend data from the messege queue
		LCD_vsend_char (y); 
	}
}
