// Multi-Level Queue Scheduling (Non-Preemptive)
// System Queue (0) > User Queue (1)
// FCFS within each queue

#include <stdio.h>

struct Process
{
    int pid;
    int at;      // Arrival Time
    int bt;      // Burst Time
    int ct;      // Completion Time
    int wt;      // Waiting Time
    int tat;     // Turnaround Time
    int type;    // 0 = System, 1 = User
    int done;    // 0 = Not completed, 1 = Completed
};

int main()
{
    int n, i;
    int time = 0, completed = 0;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for(i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i + 1);

        p[i].pid = i + 1;

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Enter Type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);

        p[i].done = 0;
    }

    // Scheduling
    while(completed < n)
    {
        int idx = -1;

        // First check System processes
        for(i = 0; i < n; i++)
        {
            if(p[i].at <= time &&
               p[i].done == 0 &&
               p[i].type == 0)
            {
                idx = i;
                break;      // FCFS
            }
        }

        // If no System process is ready, check User processes
        if(idx == -1)
        {
            for(i = 0; i < n; i++)
            {
                if(p[i].at <= time &&
                   p[i].done == 0 &&
                   p[i].type == 1)
                {
                    idx = i;
                    break;   // FCFS
                }
            }
        }

        // No process available
        if(idx == -1)
        {
            time++;
            continue;
        }

        // Execute selected process
        time += p[idx].bt;

        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        p[idx].done = 1;
        completed++;
    }

    printf("\nProcess\tAT\tBT\tType\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%s\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               (p[i].type == 0) ? "SYS" : "USER",
               p[i].ct,
               p[i].tat,
               p[i].wt);

        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }

    printf("\nAverage Turnaround Time = %.2f",
           avg_tat / n);

    printf("\nAverage Waiting Time = %.2f\n",
           avg_wt / n);

    return 0;
}
