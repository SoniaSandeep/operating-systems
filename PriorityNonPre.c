#include <stdio.h>

int main()
{
    int n;
    int at[10], bt[10], prio[10];
    int ct[10], tat[10], wt[10];
    int done[10] = {0};

    int time = 0, completed = 0;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("Enter AT, BT and Priority for P%d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &prio[i]);
    }

    while(completed < n)
    {
        int high = -1;
        int p = -1;

        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time && done[i] == 0)
            {
                if(prio[i] > high)
                {
                    high = prio[i];
                    p = i;
                }
            }
        }

        if(p == -1)
        {
            time++;
            continue;
        }

        time += bt[p];
        ct[p] = time;
        done[p] = 1;
        completed++;
    }

    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_tat += tat[i];
        avg_wt += wt[i];

        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], prio[i],
               ct[i], tat[i], wt[i]);
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage Turnaround Time = %.2f", avg_tat);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt);

    return 0;
}
