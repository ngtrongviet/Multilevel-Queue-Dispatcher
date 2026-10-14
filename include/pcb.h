#ifndef PCB_H
#define PCB_H
 
#include <stdio.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define PCB_UNINITIALIZED 0
#define PCB_INITIALIZED 1
#define PCB_READY 2
#define PCB_RUNNING 3
#define PCB_SUSPENDED 4
#define PCB_TERMINATED 5 

typedef struct Pcb{
    pid_t pid;
    char *args[3];
    int arrival_time;
    int service_time;
    int remaining_cpu_time;
    int status;
    struct Pcb *next;
} Pcb;

typedef Pcb* PcbPtr;

PcbPtr startPcb(PcbPtr);
PcbPtr terminatePcb(PcbPtr);
PcbPtr printPcb(PcbPtr);
void printPcbHdr(void);
PcbPtr createnullPcb();
PcbPtr enqPcb(PcbPtr, PcbPtr);
PcbPtr deqPcb(PcbPtr*);

#endif
