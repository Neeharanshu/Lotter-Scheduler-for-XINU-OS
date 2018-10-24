#include <xinu.h>
#include <stdio.h>
#include <math.h>

int prA, prB, prC, prD;
int proc_a(), proc_b(), proc_c(), proc_d();
volatile int a_cnt = 0;
volatile int b_cnt = 0;
volatile int c_cnt = 0;
volatile int d_cnt = 0;

int main() {
    double total_cnt, a_percent, b_percent, c_percent, d_percent;
    
    kprintf("\n\n########## Test Case 1, lottery scheduling (2 processes):\n");
    total_cnt=0;
    a_percent=0;
    b_percent=0;
    prA = create_user_proc(proc_a, 1024, 500, "proc A", 1, 'A');
    prB = create_user_proc(proc_b, 1024, 500, "proc B", 1, 'B');
    set_tickets(prA, 1000);
    set_tickets(prB, 1000);
    resume(prA);
    resume(prB);
    sleepms(1000);
    kill(prA);
    kill(prB);
    total_cnt = a_cnt + b_cnt ;
    a_percent = (double) a_cnt / total_cnt * 100;
    b_percent = (double) b_cnt / total_cnt * 100;
    kprintf("Test RESULT: A : B (%d : %d)\n", (int) a_percent, (int) b_percent);
    return OK;
}


proc_a(c)
char c; {
    int i;
    while (1) {
        for (i = 0; i < 1000; i++)
            ;
        a_cnt++;
    }
}

proc_b(c)
char c; {
    int i;
    while (1) {
        for (i = 0; i < 1000; i++)
            ;
        b_cnt++;
    }
}

proc_c(c)
char c; {
    int i;
    
    while (1) {
        for (i = 0; i < 1000; i++)
            ;
        c_cnt++;
    }
}

proc_d(c)
char c; {
    int i;
    
    while (1) {
        for (i = 0; i < 1000; i++)
           ;
        d_cnt++;
    }
}
