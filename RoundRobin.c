#include <stdio.h>

int main()
{
    int n, tq;

    int at[10], bt[10], rt[10];
    int ct[10], tat[10], wt[10], start[10];
    int visited[10] = {0};

    int queue[100];
    int front = 0, rear = 0;

    int time = 0, completed = 0;

    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);

        rt[i] = bt[i];
        start[i] = -1;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    /* Add processes arriving at time 0 */
    for(int i = 0; i < n; i++)
    {
        if(at[i] == 0)
        {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while(completed < n)
    {
        if(front == rear)
        {
            time++;

            for(int i = 0; i < n; i++)
            {
                if(at[i] <= time && !visited[i])
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int p = queue[front++];

        if(start[p] == -1)
            start[p] = time;

        if(rt[p] > tq)
        {
            rt[p] -= tq;
            time += tq;
        }
        else
        {
            time += rt[p];
            rt[p] = 0;

            ct[p] = time;
            completed++;
        }

        /* Add newly arrived processes */
        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time && !visited[i])
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        /* Put unfinished process back into queue */
        if(rt[p] > 0)
        {
            queue[rear++] = p;
        }
    }

    for(int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1,
               at[i],
               bt[i],
               ct[i],
               tat[i],
               wt[i]);
    }

    printf("\nAverage TAT = %.2f", avg_tat / n);
    printf("\nAverage WT = %.2f\n", avg_wt / n);

    return 0;
}
