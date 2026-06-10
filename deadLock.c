#include <stdio.h>

int main()
{
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int available[m], allocation[n][m], request[n][m];
    int work[m], finish[n];

    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(int j = 0; j < m; j++)
    {
        scanf("%d", &available[j]);
        work[j] = available[j];
    }

    // Initialize Finish[]
    for(int i = 0; i < n; i++)
    {
        int sum = 0;

        for(int j = 0; j < m; j++)
        {
            sum += allocation[i][j];
        }

        if(sum == 0)
            finish[i] = 1;
        else
            finish[i] = 0;
    }

    int found, possible;

    do
    {
        found = 0;

        for(int i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                possible = 1;

                // Check Request <= Work
                for(int j = 0; j < m; j++)
                {
                    if(request[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if(possible)
                {
                    // Release allocated resources
                    for(int j = 0; j < m; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

    } while(found);

    int deadlock = 0;

    printf("\nDeadlocked Processes: ");

    for(int i = 0; i < n; i++)
    {
        if(finish[i] == 0)
        {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0)
    {
        printf("None");
    }

    printf("\n");

    return 0;
}
