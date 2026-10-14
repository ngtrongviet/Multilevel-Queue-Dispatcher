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

PcbPtr enqPcb(PcbPtr, PcbPtr){
    
}

PcbPtr startPcb(PcbPtr);
PcbPtr terminatePcb(PcbPtr);
PcbPtr printPcb(PcbPtr);
void printPcbHdr(void);
PcbPtr deqPcb(PcbPtr*);

