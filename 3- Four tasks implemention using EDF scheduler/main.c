/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/* 
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used.
*/


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 * 
 * Main.c also creates a task called "Check".  This only executes every three 
 * seconds but has the highest priority so is guaranteed to get processor time.  
 * Its main function is to check that all the other tasks are still operational.
 * Each task (other than the "flash" tasks) maintains a unique count that is 
 * incremented each time the task successfully completes its function.  Should 
 * any error occur within such a task the count is permanently halted.  The 
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have 
 * changed all the tasks are still executing error free, and the check task
 * toggles the onboard LED.  Should any task contain an error at any time 
 * the LED toggle rate will change from 3 seconds to 500ms.
 *
 */

/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"
#include "queue.h"

/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"

#include "semphr.h"


TaskHandle_t Button_1_Monitor_Handler = NULL;
TaskHandle_t Button_2_Monitor_Handler = NULL;
TaskHandle_t Periodic_Tx_Handler = NULL;
TaskHandle_t Uart_Rx_Handler = NULL;
TaskHandle_t Load_1_Simulation_Handler = NULL;
TaskHandle_t Load_2_Simulation_Handler = NULL;


/*RunTime stats buffer*/
char RunTimeBuffer[200];

/*Queue Handlers*/
QueueHandle_t Q1 = NULL;
QueueHandle_t Q2 = NULL;
QueueHandle_t Q3 = NULL;

/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )


/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );


/* Task to be created. */
void Button_1_Monitor( void * pvParameters )
{
	pinState_t Button_1_State;
	pinState_t prevstate = GPIO_read(PORT_1  , PIN0);

	/* Read button 1*/
	Button_1_State = GPIO_read( Port_1 , PIN0);


    for( ;; )
    {
        /* Task code goes here. */
			/* Button is pressed s*/
		if ()
		{

		}
    }
}
/* Task to be created. */
void Button_2_Monitor( void * pvParameters )
{

    for( ;; )
    {
        /* Task code goes here. */

    }
}
/* Task to be created. */
void Periodic_Transmitter( void * pvParameters )
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. 
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );*/

    for( ;; )
    {
        /* Task code goes here. */
    }
}
/* Task to be created. */
void Uart_Receiver( void * pvParameters )
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. 
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );*/

    for( ;; )
    {
        /* Task code goes here. */
    }
}
/* Task to be created. */
void Load_1_Simulation( void * pvParameters )
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. 
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );*/

    for( ;; )
    {
        /* Task code goes here. */
    }
}
/* Task to be created. */
void Load_2_Simulation( void * pvParameters )
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. 
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );*/

    for( ;; )
    {
        /* Task code goes here. */
    }
}

/* Implement tick hook */
void vApplicationTickHook( void )	
{
	/*write your code here*/
	GPIO_write(PORT_0, PIN4, PIN_IS_HIGH);
	GPIO_write(PORT_0, PIN4, PIN_IS_LOW);
	/*
	GPIO_write(PORT_0, PIN4, PIN_IS_LOW);
	GPIO_write(PORT_0, PIN2, PIN_IS_LOW);*/
}

/*Implement hook tick
void vApplicationIdleHook( void )	
{
	//write your code here
	GPIO_write(PORT_0, PIN3, PIN_IS_HIGH);
	
	GPIO_write(PORT_0, PIN2, PIN_IS_LOW);
	
	GPIO_write(PORT_0, PIN4, PIN_IS_LOW);
}
*/
/*-----------------------------------------------------------*/


/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */

int main( void )
{
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();
															
/* Create the task, storing the handle. */
 xTaskCreate(
                    Button_1_Monitor,       /* Function that implements the task. */
                    "Button One Monitor",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Button_1_Monitor_Handler );      /* Used to pass out the created task's handle. */
										
 xTaskCreate(
                    Button_2_Monitor,       /* Function that implements the task. */
                    "Button Two Monitor",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    2,/* Priority at which the task is created. */
                   &Button_2_Monitor_Handler );      /* Used to pass out the created task's handle. */

xTaskCreate(
                    Periodic_Transmitter,       /* Function that implements the task. */
                    "Periodic Transmitter",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    3,/* Priority at which the task is created. */
                    &Periodic_Tx_Handler );      /* Used to pass out the created task's handle. */
								
xTaskCreate(
                    Uart_Receiver,       /* Function that implements the task. */
                    "Uart Receiver",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    4,/* Priority at which the task is created. */
                    &Uart_Rx_Handler );      /* Used to pass out the created task's handle. */
	/* Now all the tasks have been started - start the scheduler.

/* Create the task, storing the handle. */
 xTaskCreate(
                    Load_1_Simulation,       /* Function that implements the task. */
                    "Load One Simulation",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    5,/* Priority at which the task is created. */
                    &Load_1_Simulation_Handler );      /* Used to pass out the created task's handle. */

/* Create the task, storing the handle. */
 xTaskCreate(
                    Load_2_Simulation,       /* Function that implements the task. */
                    "Load Two Simulation",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    6,/* Priority at which the task is created. */
                    &Load_2_Simulation_Handler );      /* Used to pass out the created task's handle. */
	
	/*NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/




/* Function to reset timer 1 */
void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}  

/* Function to initialize and start timer 1 */
static void configTimer1(void)
{
	T1PR = 1000;     //speed 20 kHz
	T1TCR |= 0x1;
}

void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);

	/* Configure GPIO */
	GPIO_init();
	
	/* Config trace timer 1 and read T1TC to get current tick */
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}
/*-----------------------------------------------------------*/


