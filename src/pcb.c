#include "pcb.h"

PcbPtr createnullPcb(){
    PcbPtr new_process_Ptr = (PcbPtr) malloc(sizeof(Pcb));
    if(!new_process_Ptr){
        fprintf(stderr, "ERROR: Could not create new process control block");
        return NULL;
    }
    new_process_Ptr->pid = 0;
    new_process_Ptr->args[0] = "./process";
    new_process_Ptr->args[1] = NULL;
    new_process_Ptr->arrival_time = 0;
    new_process_Ptr->service_time = 0;
    new_process_Ptr->remaining_cpu_time = 0;
    new_process_Ptr->status = PCB_UNINITIALIZED;
    new_process_Ptr->next = NULL;
    return new_process_Ptr;
}

PcbPtr enqPcb(PcbPtr q, PcbPtr p){
    if(!q) return p;

    PcbPtr h = q;
    while(q->next) q = q->next;
    q->next = p;
    p->next = NULL;
    return h;
}

PcbPtr deqPcb(PcbPtr* hPtr){
    if(!hPtr) return NULL;
    PcbPtr p = *hPtr;
    *hPtr = p->next;
    return p;
}

PcbPtr startPcb(PcbPtr p){
    if(p->pid == 0){
        switch (p->pid == fork()){
            case -1:
                fprintf(stderr, "FATAL: Could not fork process!\n");
                exit(EXIT_FAILURE);
            case 0:
                p->pid = getpid();
                p->status = PCB_RUNNING;
                printPcbHdr();
                printPcb(p);
                fflush(stdout);
                execv(p->args[0], p->args);
                fprintf(stderr, "ALERT: You should never see me!\n");
                exit(EXIT_FAILURE);
        }
    }
    else{
        kill(p->pid, SIGCONT);
    }
    p->status = PCB_RUNNING;
    return p;
}

PcbPtr terminatePcb(PcbPtr p){
    int status;
    if(!p){
        fprintf(stderr, "ERRORL: Can not terminate a NULL process\n");
        return NULL;
    }
    else{
        kill(p->pid, SIGINT);
        waitpid(p->pid, &status, WUNTRACED);
        p->status = PCB_TERMINATED;
        return p;
    }
}

PcbPtr printPcb(PcbPtr p){
    printf("%7d%7d%9d%7d  ", (int) p->pid, p->arrival_time, p->service_time, p->remaining_cpu_time);
    
    switch (p->status) {
        case PCB_UNINITIALIZED:
            printf("UNINITIALIZED");
            break;
        case PCB_INITIALIZED:
            printf("INITIALIZED");
            break;
        case PCB_READY:
            printf("READY");
            break;
        case PCB_RUNNING:
            printf("RUNNING");
            break;
        case PCB_SUSPENDED:
            printf("SUSPENDED");
            break;
        case PCB_TERMINATED:
            printf("PCB_TERMINATED");
            break;
        default:
            printf("UNKNOWN");
    }
    printf("\n");
    
    return p;
}
void printPcbHdr(){
    printf("    pid arrive  service    cpu  status\n");
}