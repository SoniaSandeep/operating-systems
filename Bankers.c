#include <stdio.h>

int main()
{
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int allocation[n][m], max[n][m], need[n][m];
    int available[m], work[m];
    int finish[n], safe[n];

    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("\nEnter Max Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources:\n");
    for(int j = 0; j < m; j++)
        scanf("%d", &available[j]);

    // Calculate Need Matrix
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Initialize
    for(int j = 0; j < m; j++)
        work[j] = available[j];

    for(int i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;

    while(count < n)
    {
        int found = 0;

        for(int i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int possible = 1;

                for(int j = 0; j < m; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if(possible)
                {
                    for(int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    if(count == n)
    {
        printf("\nSystem is in SAFE state\n");
        printf("Safe Sequence: ");

        for(int i = 0; i < n; i++)
            printf("P%d ", safe[i]);

        printf("\n");
    }
    else
    {
        printf("\nSystem is NOT in SAFE state\n");
    }

    return 0;
}
