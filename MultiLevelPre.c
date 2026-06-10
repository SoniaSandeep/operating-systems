#include <stdio.h>

struct Process
{
    int pid;
    int at;
    int bt;
    int rt;     // Remaining Time
    int ct;
    int tat;
    int wt;
    int type;   // 0 = System, 1 = User
};

int main()
{
    int n, time = 0, completed = 0;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i + 1);

        p[i].pid = i + 1;

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Enter Type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);

        p[i].rt = p[i].bt;
    }

    while(completed < n)
    {
        int idx = -1;

        // Check System processes first
        for(int i = 0; i < n; i++)
        {
            if(p[i].at <= time &&
               p[i].rt > 0 &&
               p[i].type == 0)
            {
                idx = i;
                break;
            }
        }

        // If no System process is ready, check User processes
        if(idx == -1)
        {
            for(int i = 0; i < n; i++)
            {
                if(p[i].at <= time &&
                   p[i].rt > 0 &&
                   p[i].type == 1)
                {
                    idx = i;
                    break;
                }
            }
        }

        if(idx == -1)
        {
            time++;
            continue;
        }

        // Execute for 1 unit (Preemptive)
        p[idx].rt--;
        time++;

        if(p[idx].rt == 0)
        {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            completed++;
        }
    }

    printf("\nProcess\tAT\tBT\tType\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
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

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
    printf("Average Waiting Time = %.2f\n", avg_wt / n);

    return 0;
}
