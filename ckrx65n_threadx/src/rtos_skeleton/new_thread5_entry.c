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
#include <stdio.h>
#include <string.h>
#include "tx_api.h"

TX_SEMAPHORE sample_semaphore;

/* New Thread entry function */
void new_thread5_entry(ULONG entry_input)
{
	UINT status;
	static UINT i;
	CHAR sample_output[40];

	status = tx_semaphore_create(&sample_semaphore,"sample semaphore",2);

    while (1)
    {
    	status = tx_semaphore_get(&sample_semaphore,TX_WAIT_FOREVER);
    	//sample_output = "new_thread4_entry hello";
    	strcpy(sample_output,"semaphore : new_thread5_entry hello");
    	sprintf(sample_output,"%s : %d",sample_output,i++);
    	printf("%s\n",sample_output);
    	strcpy(sample_output,"semaphore : new_thread5_entry hello");
    	sprintf(sample_output,"%s2 : %d",sample_output,i++);
    	printf("%s\n",sample_output);
        tx_thread_sleep (70);
    	status = tx_semaphore_put(&sample_semaphore);

    }
}

