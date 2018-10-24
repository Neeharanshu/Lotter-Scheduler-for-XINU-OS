#include<xinu.h>
qid16 readylist;

syscall print_ready_list(void){
int pid = firstid(readylist);
while(1){
	kprintf("----printing currpid %d----\n", pid);
	pid = queuetab[pid].qnext;
	if(isbadpid(pid))
		break;
}
return OK;
}
