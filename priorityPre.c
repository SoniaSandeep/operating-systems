#include <stdio.h>

int main()
{
    int n;
    int at[10], bt[10], prio[10];
    int ct[10], tat[10], wt[10];
    int rt[10], start[10], rm[10];

    int time = 0, completed = 0;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("Enter AT, BT and Priority for P%d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &prio[i]);

        rm[i] = bt[i];      // Remaining Time
        start[i] = -1;      // First CPU allocation time
    }

    while(completed < n)
    {
        int high = -1;
        int p = -1;

        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time &&
               rm[i] > 0 &&
               prio[i] > high)
            {
                high = prio[i];
                p = i;
            }
        }

        if(p == -1)
        {
            time++;
            continue;
        }

        if(start[p] == -1)
            start[p] = time;

        rm[p]--;      // Execute for 1 unit
        time++;

        if(rm[p] == 0)
        {
            ct[p] = time;
            completed++;
        }
    }

    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = start[i] - at[i];

        avg_tat += tat[i];
        avg_wt += wt[i];

        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               i + 1,
               at[i],
               bt[i],
               prio[i],
               ct[i],
               tat[i],
               wt[i],
               rt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
    printf("Average Waiting Time = %.2f\n", avg_wt / n);

    return 0;
}
