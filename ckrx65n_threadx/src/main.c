/* This is a small demo of the high-performance ThreadX kernel.  It includes examples of eight
   threads of different priorities, using a message queue, semaphore, mutex, event flags group, 
   byte pool, and block pool.  */

#include "tx_api.h"
#include "ckrx65n_board.h"
#include "platform.h"
#include "hardware_setup.h"
#include "demo_printf.h"

extern void tx_application_define_user (void);

/* Define main entry point.  */
int main()
{
    /* Setup the hardware. */
    platform_setup();

    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
}

static void sample_periodic_timer_entry(ULONG context)
{
	static INT i = 0;
	i++;
//	if(LED4 == LED_OFF)
//	{
//		LED2_R = LED4= LED6 = LED_ON;
//	}
//	else
//	{
//		LED2_R = LED4= LED6 = LED_OFF;
//	}
}

/* Define what the initial system looks like.  */
void    tx_application_define(void *first_unused_memory)
{
	TX_TIMER sample_timer;

	/* Initialize terminal log output */
	LOG_TERMINAL_INIT();

	/* Initialize LED */
	LED_INIT
	/*TImer set one second*/
	tx_timer_create(&sample_timer,"sample timer", sample_periodic_timer_entry, 1, 100,100,TX_AUTO_ACTIVATE);

	tx_application_define_user();
}
