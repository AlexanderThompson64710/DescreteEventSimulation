#include <stdio.h>
#include <limits.h>
#include <malloc.h>
#include <string.h>

int isEmpty();
int isFull();
void push();
struct job pop();
void processCPU ();
void processDisk ();
void processNetwork ();

struct job createJob();

#define Job_Arrival 1
#define CPU_Begin 2
#define CPU_Finish 3
#define Disk_Begin 4
#define Disk1_Finish 5
#define Disk2_Finish 7
#define Network_Begin 8
#define Network_Finish 9
#define Finish_Simulation 10

#define QUIT_PROB = 0.2
#define NETWORK_PROB = 0.3
#define DISK_PROB = 0.7

int current_time = 0;
int total_jobs = 0;
int job_number;


struct job
{
    int time;
    int job_number;
    int event_type;
    int time_arrival;
};

struct queue
{
    int maxCap;
    int top;
    int front;
    int busy;
    int rear;
    int size;
    struct job *array;
};

struct queue* priority (int cap)
{
    struct queue *pq;
    pq->array = (struct stack*)malloc(sizeof(struct queue));

    pq->maxCap = cap;
    pq->top = -1;
    struct job *array;
}

int main()
{
    struct queue priority;
    priority.array = (struct job*) malloc(1000*sizeof(struct job));



    int curr_time = 0;
    int fin_time = 0;

    void srand(unsigned seed);

    while (!isEmpty(&priority) && (curr_time <= fin_time))
    {
        struct job curr_job = pop(&priority);
        curr_time = curr_job.time;
        switch (curr_job.event_type)
        {
            case CPU_Begin: processCPU(&priority, curr_job);
            case CPU_Finish: processCPU(&priority, curr_job);
            case Disk_Begin: processDisk(&priority, curr_job);
            case Disk1_Finish: processDisk(&priority, curr_job);
            case Disk2_Finish: processDisk(&priority, curr_job);
            case Network_Begin: processNetwork(&priority, curr_job);
            case Network_Finish: processNetwork(&priority, curr_job);
            case Finish_Simulation: break;

        }
    }
}

struct job createJob(int job_number, int time, int event_type)
{
    struct job next_Job;

    job_number += job_number +1;
    time = (rand() % 50);


    return next_Job;
}

void processCPU (struct queue priority, struct job curr_job)
{
    struct queue cpuFIFO;

    int quitProb = rand() % 100;
    int diskProb = rand() % 100;

    if (curr_job.event_type == CPU_Begin)
    {
        struct job next_Job = createJob(5, total_jobs+1, CPU_Begin);
        push(priority, next_Job);
    }
    else
    {
        priority.busy = 0;
        if (quitProb > 20)
        {
            if (diskProb >= 70)
            {
                struct job disk_job = {5, total_jobs+1, Disk_Begin};
                push(priority, disk_job);
            }
            else
            {
                struct job network_job = {5, total_jobs+1, Network_Begin};
                push(priority, network_job);
            }
        }
        else
        {
            return;
        }
        if(!isEmpty(&cpuFIFO) && cpuFIFO.busy == 0)
        {
            struct job curr_Job = pop(&cpuFIFO);
            struct job fin_job = {5, job_number, CPU_Finish};
            push(priority, fin_job);
            cpuFIFO.busy = 1;
        }
    }
}

void processDisk (struct queue priority, struct job curr_job)
{
    struct queue disk1FIFO;
    struct queue disk2FIFO;

    int disk_prob = rand() % 50;
    if (curr_job.event_type == Disk_Begin)
    {
        if(disk_prob < 25)
        {
            struct job next_Job = createJob(job_number, (rand()%100), Disk_Begin);
            push(disk1FIFO, next_Job);
        }
        else
        {
            struct job next_Job = createJob(job_number, (rand()%100), Disk_Begin);
            push(disk2FIFO, next_Job);
        }
    }
    if(!isEmpty(&disk1FIFO) && disk1FIFO.busy == 0)
    {
        struct job curr_Job = pop(&disk1FIFO);
        struct job fin_job = {5, job_number, Disk1_Finish};
        push(disk1FIFO, fin_job);
        disk1FIFO.busy = 1;
    }
    if(!isEmpty(&disk2FIFO) && disk2FIFO.busy == 0)
    {
        struct job curr_Job = pop(&disk2FIFO);
        struct job fin_job = {5, job_number, Disk2_Finish};
        push(disk2FIFO, fin_job);
        disk2FIFO.busy = 1;
    }
}

void processNetwork (struct queue networkFIFO, struct job curr_job)
{

    if (curr_job.event_type == Network_Begin)
    {
        struct job next_Job = createJob(job_number, 5, Network_Begin);
        push(networkFIFO, next_Job);
    }
    if(!isEmpty(&networkFIFO) && networkFIFO.busy == 0)
    {
        struct job curr_Job = pop(&networkFIFO);
        struct job fin_job = {5, job_number, Network_Finish};
        push(networkFIFO, fin_job);
        networkFIFO.busy = 1;
    }
}

int isEmpty(struct queue *pq)
{
    return pq->top == 0;
}

int isFull(struct queue *pq)
{
    return pq->top == pq->maxCap-1;
}

void push (struct queue *pq)
{
    if(isFull(pq))
    {
        exit(0);
    }
    struct job new_Job;
    new_Job.time = current_time ;
    new_Job.job_number = total_jobs+1;
    pq->array[0] = new_Job;
    pq->array++;
}

struct job pop (struct queue *pq)
{
    if(isEmpty(pq))
    {
        exit(0);
    }
    pq->array[--pq->top];
}