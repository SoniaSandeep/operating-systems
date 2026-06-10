#include <stdio.h>

int main() {
    int n, at[10], bt[10], ct[10], tat[10], wt[10];
    int done[10] = {0}, completed = 0, time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("AT BT for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    while(completed < n) {
        int min = 999, p = -1;

        for(int i = 0; i < n; i++) {
            if(!done[i] && at[i] <= time && bt[i] < min) {
                min = bt[i];
                p = i;
            }
        }

        if(p == -1) {
            time++;
            continue;
        }

        time += bt[p];
        ct[p] = time;
        done[p] = 1;
        completed++;
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    return 0;
}
