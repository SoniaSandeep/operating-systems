#include <stdio.h>

#define MAX 10

int main()
{
    int n, i, time, hyperperiod = 1;
    int period[MAX], burst[MAX], remaining[MAX];
    int gcd, lcm;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    printf("Enter burst time and period for each task:\n");

    for(i = 0; i < n; i++)
    {
        printf("Task %d:\n", i + 1);

        printf("Burst Time: ");
        scanf("%d", &burst[i]);

        printf("Period: ");
        scanf("%d", &period[i]);

        remaining[i] = burst[i];
    }

    /* Calculate Hyperperiod (LCM of all periods) */
    lcm = period[0];

    for(i = 1; i < n; i++)
    {
        int a = lcm, b = period[i];

        while(b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }

        gcd = a;
        lcm = (lcm * period[i]) / gcd;
    }

    hyperperiod = lcm;

    printf("\nHyperperiod: %d\n", hyperperiod);
    printf("\nCPU Execution Intervals:\n");

    int current_task = -1;
    int start_time = 0;

    for(time = 0; time < hyperperiod; time++)
    {
        int highest = -1;

        /* Release tasks at their periods */
        for(i = 0; i < n; i++)
        {
            if(time % period[i] == 0)
            {
                remaining[i] = burst[i];
            }
        }

        /* Select highest-priority task
           (smallest period = highest priority) */
        for(i = 0; i < n; i++)
        {
            if(remaining[i] > 0)
            {
                if(highest == -1 ||
                   period[i] < period[highest])
                {
                    highest = i;
                }
            }
        }

        /* Context switch */
        if(highest != current_task)
        {
            if(current_task != -1)
            {
                printf("Task %d: [%d - %d]\n",
                       current_task + 1,
                       start_time,
                       time);
            }
            else if(time > start_time)
            {
                printf("Idle: [%d - %d]\n",
                       start_time,
                       time);
            }

            start_time = time;
            current_task = highest;
        }

        /* Execute selected task */
        if(highest != -1)
        {
            remaining[highest]--;
        }
    }

    /* Print final interval */
    if(current_task != -1)
    {
        printf("Task %d: [%d - %d)\n",
               current_task + 1,
               start_time,
               hyperperiod);
    }
    else
    {
        printf("Idle: [%d - %d]\n",
               start_time,
               hyperperiod);
    }

    return 0;
}
