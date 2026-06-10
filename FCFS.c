#include <stdio.h>

int main()
{
    int n, i, j;
    int pid[20];
    int at[20], bt[20], ct[20], tat[20], wt[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for(i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        printf("\nProcess P%d\n", pid[i]);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    // Sort by Arrival Time
    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(at[i] > at[j])
            {
                int temp;

                // Swap PID
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;

                // Swap AT
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // Swap BT
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }

    // Calculate CT, TAT, WT
    for(i = 0; i < n; i++)
    {
        if(i == 0)
        {
            ct[i] = at[i] + bt[i];
        }
        else
        {
            if(ct[i - 1] < at[i]) // CPU Idle
                ct[i] = at[i] + bt[i];
            else
                ct[i] = ct[i - 1] + bt[i];
        }

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    // Output Table
    printf("\n-------------------------------------------------\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("-------------------------------------------------\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i],
               at[i],
               bt[i],
               ct[i],
               tat[i],
               wt[i]);
    }

    printf("-------------------------------------------------\n");

    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);

    return 0;
}
