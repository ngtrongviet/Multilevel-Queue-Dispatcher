#include "fcfs.h"

int main(int argc, char *argv[]){
    FILE *input_list_stream = NULL;
    PcbPtr fcfs_queue = NULL;
    PcbPtr current_process = NULL;
    PcbPtr process = NULL;
    int timer = 0;

    if (argc <= 0){
        fprintf(stderr, "FATAL: Bad arguments array\n");
        exit(EXIT_FAILURE);
    }

    else if (argc != 2){
        fprintf(stderr, "Usage: %s <TESTFILE>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (!(input_list_stream = fopen(argv[1], "r"))){
        fprintf(stderr, "ERROR: Could not open \"%s\"\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (!feof(input_list_stream)) {
        process = createnullPcb();
        if (fscanf(input_list_stream, "%d, %d", &(process->arrival_time), &(process->service_time)) != 2){
            free(process);
            continue;
        }
        process->remaining_cpu_time = process->service_time;
        process->status = PCB_INITIALIZED;
        fcfs_queue = enqPcb(fcfs_queue, process);
    }

    while(current_process || fcfs_queue){
        if (current_process){
            current_process->remaining_cpu_time--;
            if (current_process->remaining_cpu_time <= 0){
                terminatePcb(current_process);

                free(current_process);
                current_process = NULL;
            }
        }
        
        if(!current_process && fcfs_queue && fcfs_queue->arrival_time <= timer){
            current_process = deqPcb(&fcfs_queue);
            startPcb(current_process);
        }

        sleep(1);
        timer++;
    }
    exit(EXIT_SUCCESS);
}