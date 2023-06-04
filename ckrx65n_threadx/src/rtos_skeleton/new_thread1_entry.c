/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : thread_x_entry.c
 * Version      : 1.0
 * Description  : declare Thread entry function  
 **********************************************************************************************************************/
/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "azurertos_object_init.h"
#include "tx_api.h"
#include "ckrx65n_board.h"
#define DEMO_QUEUE_SIZE         10
#define DEMO_BYTE_POOL_SIZE 100

/* Queue setting */
UCHAR                   memory_area[DEMO_BYTE_POOL_SIZE];
TX_QUEUE                queue_0;

/* Event Flag */
TX_EVENT_FLAGS_GROUP sample_event_flag;

extern TX_MUTEX sample_mutex;
extern TX_SEMAPHORE sample_semaphore;

/* New Thread entry function */
void new_thread1_entry(ULONG entry_input)
{

	TX_BYTE_POOL            byte_pool_0;
	CHAR    *pointer = TX_NULL;
	UINT    status;
	ULONG i[5] = {0,1,2,3,4};


    /* Create a byte memory pool from which to allocate the thread stacks.  */
    tx_byte_pool_create(&byte_pool_0, "byte pool 0", memory_area, DEMO_BYTE_POOL_SIZE);
    /* Allocate the message queue.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_QUEUE_SIZE*sizeof(ULONG), TX_NO_WAIT);
    /* Create the message queue shared by threads 1 and 2.  */
    tx_queue_create(&queue_0, "queue 0", (sizeof(i)/sizeof(ULONG)), pointer, DEMO_QUEUE_SIZE*sizeof(ULONG));

    /*Create event flags*/
    tx_event_flags_create(&sample_event_flag,"sample flag");

    /* TODO: add your own code here */
    while (1)
    {
        /* Send message to queue 0.  */
        status =  tx_queue_send(&queue_0, i, TX_WAIT_FOREVER);

        /*flag set */
        status =  tx_event_flags_set(&sample_event_flag,(0x1 || 0x10),TX_OR);

    	status = tx_mutex_get(&sample_mutex,TX_WAIT_FOREVER);
    	LED3 = LED_ON;
        tx_thread_sleep (100);
    	printf("new_thread1_entry hello\n");
    	status = tx_mutex_put(&sample_mutex);

    	status = tx_semaphore_get(&sample_semaphore,TX_WAIT_FOREVER);
    	printf("semaphore : new_thread1_entry hello\n");
    	printf("semaphore : new_thread1_entry hello 2\n");
        LED3 = LED_OFF;
        tx_thread_sleep (100);
    	status = tx_semaphore_put(&sample_semaphore);

    }
}

