/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/
	struct procent *pt = &proctab[currpid];

	/* Decrement the ms counter, and see if a second has passed */
		if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */
		//pt->time_elapsed--;
		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
		//	kprintf("the delay for %d is %d\n", firstid(sleepq), queuetab[firstid(sleepq)].qkey);
			wakeup();
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = QUANTUM;
		//kprintf("I called resched when currpid is %d\n", currpid);
		resched();
	}
	if(pt->sys_call == 0)
	{
		pt->time_elapsed--;
		if(pt->time_elapsed <= 0){
			kprintf("I came here for %d", currpid);
			kill(currpid);
		}
		//kprintf("For currpid %d the time remaining for execution is %d\n", currpid, pt->time_elapsed);
	}

}
