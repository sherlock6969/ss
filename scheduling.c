#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

typedef struct process
{
    int pid, arrival, burst, wait, turn, bt_tracker, priority, processTypeBit;
    int temp;
}process;

int k=0;
int *pid;
int *time;
int prevIndex=-1;

void sort(process *p, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (p[min].arrival > p[j].arrival)
                min = j;
        }
        if (i != min)
        {
            process temp = p[i];
            p[i] = p[min];
            p[min] = temp;
        }
    }
}

void fcfs(process *p, int n)
{
    p[0].wait = 0;
    p[0].turn=p[0].burst;
    int sum=p[0].arrival;
    for (int i = 1; i < n; i++)
    {
        sum+=p[i-1].burst;
        p[i].wait = sum-p[i].arrival;
        if(p[i].wait<0)
            p[i].wait=0;
        p[i].turn = p[i].burst + p[i].wait;
    }
}

void gantt_chart_fcfs(process *p,int n)
{
    printf("\n\n");
    for (int i = 0; i < p[n-1].turn - 1; i++)
    {
        printf(" ");
    }
    printf("GANTT CHART\n\n ");

    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");
        printf("P%d", p[i].pid);
        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("--");
        printf(" ");
    }
    printf("\n%d",p[0].arrival);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("  ");
        if (p[i].turn+p[i].arrival > 9)
            printf("\b");
        printf("%d", p[i].turn+p[i].arrival);
    }
    printf("\n");
}

void sort_arrival_time(process *p, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (p[min].arrival > p[j].arrival)
            {
                min = j;
            }
        }
        if (i != min)
        {
            process temp = p[i];
            p[i] = p[min];
            p[min] = temp;
        }
    }
}

void sjfs(process *p, int n)
{
    int previous = p[0].arrival;
    for (int i = 0; i < n; i++)
    {
        
        
        p[i].wait = previous - p[i].arrival;
        if (p[i].wait < 0)
            p[i].wait = 0;
        p[i].turn = p[i].burst + p[i].wait;
        previous = p[i].arrival + p[i].turn;
    }
}

void gantt_chart_sjf(process *p, int n)
{
    printf("\n\n");
    for (int i = 0; i < p[n - 1].turn - 1; i++)
    {
        printf(" ");
    }
    printf("GANTT CHART\n\n ");

    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");
        printf("P%d", p[i].pid);
        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("--");
        printf(" ");
    }
    printf("\n%d", p[0].arrival);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("  ");
        if (p[i].turn + p[i].arrival > 9)
            printf("\b");
        printf("%d", p[i].turn + p[i].arrival);
    }
    printf("\n");
}

void round_robin(process *p, int n, int quantum)
{
    int rem[n];
    for (int i = 0; i < n; i++)
        rem[i] = p[i].burst;
    int previous = p[0].arrival;
    while (1)
    {
        int flag = 0;
        int i;
        int min = 0;
        for (i = 0; i < n; i++)
        {
            if (rem[i] > 0)
            {
                if (p[i].temp <= p[min].temp)
                    min = i;
            }
        }
        if (rem[min] > 0)
        {
            flag = 1;
            if (rem[min] > quantum)
            {
                previous += quantum;
                rem[min] -= quantum;
            }
            else
            {
                previous += rem[min];
                p[min].wait = previous - p[min].burst - p[min].arrival;
                rem[min] = 0;
                p[min].turn = p[min].burst + p[min].wait;
            }
            p[min].temp = previous;
            pid[k]=p[min].pid;
            time[k++]=p[min].temp;
        }
        if (!flag)
            break;
    }
}

void gantt_chart_rr(process *p, int n,int size)
{
    printf("\n\n");
    for(int i=0;i<(time[size-1]*2+size-11)/2;i++)
        printf(" ");
    printf("GANTT CHART\n\n ");
    int i,j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < time[i]-time[i-1] - 1; j++)
            printf(" ");
        printf("P%d", pid[i]);
        for (j = 0; j < time[i]-time[i-1] - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");
    printf("\n%d", p[0].arrival);
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < time[i]-time[i-1] ; j++)
            printf("  ");
        if (time[i] > 9)
            printf("\b");
        printf("%d", time[i]);
    }
    printf("\n");
}

int biggestPriority(process *Process,int count,int time)
{
    int index=-1;
    int biggestP = INT_MAX;
    for(int i=0;i<count;++i)
        if(Process[i].bt_tracker>0 && Process[i].arrival<=time && Process[i].priority<biggestP)
        {
            biggestP=Process[i].priority;
            index=i;
        }

    return index;
}

void gantt_chart_priority(int ganttVal[],int valIndex,int ganttTime[],int timeIndex)
{
    int i;
    printf("\nGantt Chart\n ");
    for(i=0;i<valIndex;++i)
        printf("--------");
    printf("\n|");
    for(i=0;i<valIndex;++i)
    {
        if(ganttVal[i]==-1)
            printf("     \t |");
        else
            printf("   P%d\t |",ganttVal[i]);
    }
    printf("\n ");
    for(i=0;i<valIndex;++i)
        printf("--------");
    printf("\n0\t");
    for(i=0;i<timeIndex;++i)
        printf(" %d\t",ganttTime[i]);
    printf("\n");
}

int findSystemProcess(process *Process,int count,int time)
{
    int startIndex=(prevIndex+1)%count;
    int systemIndex=-1;
    for(int i=startIndex;i<count;++i)
        if(Process[i].bt_tracker>0 && Process[i].arrival<=time && Process[i].processTypeBit==0)
        {
            systemIndex = prevIndex = i;
            break;
        }

    if(systemIndex==-1)
        for(int i=0;i<startIndex;++i)
            if(Process[i].bt_tracker>0 && Process[i].arrival<=time && Process[i].processTypeBit==0)
            {
                systemIndex = prevIndex = i;
                break;
            }

    return systemIndex;
}

void gantt_chart_multi(int ganttVal[],int valIndex,int ganttTime[],int timeIndex)
{
    int i;
    printf("\n\nGantt Chart\n ");
    for(i=0;i<valIndex;++i)
        printf("--------");
    printf("\n|");
    for(i=0;i<valIndex;++i)
    {
        if(ganttVal[i]==-1)
            printf("     \t |");
        else
            printf("   P%d\t |",ganttVal[i]);
    }
    printf("\n ");
    for(i=0;i<valIndex;++i)
        printf("--------");
    printf("\n0\t");
    for(i=0;i<timeIndex;++i)
        printf(" %d\t",ganttTime[i]);
    printf("\n");
}

void average(process *p,int n)
{
    float sumw = 0, sumt = 0;
    for (int i = 0; i < n; i++)
    {
        sumw += p[i].wait;
        sumt += p[i].turn;
    }
    printf("\n\nAverage Waiting Time = %0.3f", sumw / n);
    printf("\nAverage Turnaround Time = %0.3f\n", sumt / n);
}

void main(){

    int repeat;
do{
    int n, quantum, size=0;

    printf("1.FCFS\t2.SJF\t3.Round Robin\n4.Priority\t5.Multi Level Job Scheduling\n");
    printf("Enter your choice: ");

    int ch;
    scanf("%d", &ch);

    switch(ch){

        case 1:{//FCFS
        printf("Enter the number of processes: ");
        scanf("%d",&n);
        process *p =(process*)malloc(sizeof(process)*n);
        printf("Enter the arrival time and burst time of Processes\n");
        for (int i = 0; i < n; i++)
        {
            printf("\nProcess [%d] : \nArrival time : ", i + 1);
            scanf("%d", &p[i].arrival);
            printf("Burst time : ");
            scanf("%d", &p[i].burst);
            p[i].pid = i + 1;
        }
        sort(p, n);
        fcfs(p, n);
        printf("\n\n              FIRST COME FIRST SERVED SCHEDULING");
        printf("\nProcesses   Arrival time   Burst time    Waiting time    Turnaround time\n");
        for (int i = 0; i < n; i++)
        {
            printf("    P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst, 
            p[i].wait, p[i].turn);
        }
        gantt_chart_fcfs(p,n);
        average(p, n);
        break;
        }

        case 2:{//SJFS
        printf("Enter the number of processes: ");
        scanf("%d", &n);
        process *p = (process *)malloc(sizeof(process) * n);
        printf("Enter the arrival time and burst time of Processes\n");
        for (int i = 0; i < n; i++)
        {
            printf("\nProcess [%d] : \nArrival time : ", i + 1);
            scanf("%d", &p[i].arrival);
            printf("Burst time : ");
            scanf("%d", &p[i].burst);
            p[i].pid = i + 1;
        }   
        sort_arrival_time(p, n);
        sjfs(p, n);
        printf("\n\n                   SHORTEST JOB FIRST SCHEDULING");
        printf("\nProcesses   Arrival time   Burst time    Waiting time    Turnaround time\n");
        for (int i = 0; i < n; i++)
        {
            printf("    P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst, 
            p[i].wait, p[i].turn);
        }
        gantt_chart_sjf(p, n);
        average(p, n);
        break;
        }

        case 3:{//Round Robin
        printf("Enter the number of processes: ");
        scanf("%d", &n);
        process *p = (process *)malloc(sizeof(process) * n);
        printf("Enter the time quantum : ");
        scanf("%d", &quantum);
        printf("Enter the arrival time and burst time of Processes\n");
        for (int i = 0; i < n; i++)
        {
            printf("\nProcess [%d] : \nArrival time : ", i + 1);
            scanf("%d", &p[i].arrival);
            printf("Burst time : ");
            scanf("%d", &p[i].burst);
            p[i].pid = i + 1;
            p[i].temp = p[i].arrival;
            float f=p[i].burst/(float)quantum;
            size+=ceil(f);
        }
        pid = (int *)malloc(sizeof(int)*size);
        time = (int *)malloc(sizeof(int)*size);
        sort_arrival_time(p, n);
        round_robin(p, n, quantum);
        printf("\n\n                       ROUND ROBIN SCHEDULING");
        printf("\nProcesses   Arrival time   Burst time    Waiting time    Turnaround time\n");
        for (int i = 0; i < n; i++)
        {
            printf("    P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
            p[i].wait, p[i].turn);
        }
        gantt_chart_rr(p, n, size);
        average(p, n);
        break;
        }

        case 4:{//Priority
        int i, j, next;
        int ganttVal[100],valIndex=0,timeIndex=0,ganttTime[100];
        printf("Enter the number of processes: ");  
        scanf("%d",&n);
        process *p = (process*)malloc(sizeof(process)*n);
        for(i=0;i<n;++i)  
        {  
            printf("\nProcess[%d]", i+1);  
            printf("\nArrival time: ");
            scanf("%d",&p[i].arrival); 
            printf("Burst time: ");
            scanf("%d", &p[i].burst);
            p[i].bt_tracker=p[i].burst;
            printf("Priority : ");
            scanf("%d",&p[i].priority);
        }  
        printf("\nProcesses\t Burst Time\t Turn around time\t\tWaiting Time");
        int sum=0,t_time,w_time,completed=0;
        while(completed!=n)     
        {
            i=biggestPriority(p,n,sum);
            if(i==-1)
                sum++;    
            else
            {
                if(sum!=ganttTime[timeIndex-1])
                {
                    ganttVal[valIndex++]=-1;
                    ganttTime[timeIndex++]=sum;
                }
                ganttVal[valIndex++]=i+1;
                p[i].bt_tracker=0;
                sum+=p[i].burst;
                t_time=sum-p[i].arrival;
                w_time=t_time-p[i].burst;
                p[i].turn+=t_time;
                p[i].wait+=w_time;
                completed++;
                ganttTime[timeIndex++]=sum;
                printf("\nP%d \t\t %d \t\t\t %d \t\t\t\t %d",i+1,p[i].burst,t_time,w_time);
            }
        }
        gantt_chart_priority(ganttVal,valIndex,ganttTime,timeIndex);
        average(p, n);
        break;
        }

        case 5:{//Multi level
        int i;
        int ganttVal[100],valIndex=0,timeIndex=0,ganttTime[100];
        printf("Enter the number of processes: ");  
        scanf("%d",&n);
        process *p = (process*)malloc(sizeof(process)*n);
        printf("\nEnter the time quantum: ");  
        scanf("%d", &quantum); 
        for(i=0;i<n;++i)  
        {  
            printf("\nProcess[%d]", i+1);  
            printf("\nArrival time: ");
            scanf("%d",&p[i].arrival); 
            printf("Burst time: ");
            scanf("%d", &p[i].burst);  
            printf("System/User process (0/1): ");
            scanf("%d",&p[i].processTypeBit);
            p[i].bt_tracker = p[i].burst;
        }   
        printf("\nProcesses\t System/User\t Burst Time\t Turn around time\t Waiting Time");
        i=0;
        int sum=0,completed=0,t_time,w_time,systemIndex;
        while(completed!=n) 
        {
            systemIndex = findSystemProcess(p,n,sum);
            if(systemIndex!=-1)
                i=systemIndex;        
            if(p[i].bt_tracker>0 && p[i].arrival<=sum)
            {
                if(p[i].arrival>sum)
                {
                    ganttVal[valIndex++]=-1;
                    ganttTime[timeIndex++]=p[i].arrival;
                    sum=p[i].arrival;
                }
                if(p[i].bt_tracker<=quantum)
                {
                    sum+=p[i].bt_tracker;
                    p[i].bt_tracker=0;
                    completed++;
                    t_time=sum-p[i].arrival;
                    w_time=t_time-p[i].burst;
                    p[i].turn+=t_time;
                    p[i].wait+=w_time;
                    char type[10];
                    if(p[i].processTypeBit==0)
                        strcpy(type,"System");
                    else
                        strcpy(type,"User  ");
                    printf("\nP%d\t\t   %s\t    %d\t\t     %d\t\t\t     %d",i+1,type,p[i].burst,t_time,w_time);
                }
                else
                {   
                    p[i].bt_tracker-=quantum;
                    sum+=quantum;
                }
                ganttVal[valIndex++]=i+1;
                ganttTime[timeIndex++]=sum;
            }
            if(i==n-1)
                i=0;
            else
                ++i;
        }
        gantt_chart_multi(ganttVal,valIndex,ganttTime,timeIndex);
        average(p, n);
        break;
        }
    }
    printf("\n\nPress 1 - Continue\t0 - Exit: ");
    scanf("%d", &repeat);
}while(repeat==1);
}