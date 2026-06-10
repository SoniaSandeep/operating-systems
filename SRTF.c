#include <stdio.h>

int main() {
    int n, at[10], bt[10], rm[10];
    int ct[10], tat[10], wt[10], rt[10], start[10];
    int time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("AT BT for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);

        rm[i] = bt[i];
        start[i] = -1;
    }

    while(completed < n) {
        int min = 999, p = -1;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && rm[i] > 0 && rm[i] < min) {
                min = rm[i];
                p = i;
            }
        }

        if(p == -1) {
            time++;
            continue;
        }

        if(start[p] == -1)
            start[p] = time;

        rm[p]--;
        time++;

        if(rm[p] == 0) {
            ct[p] = time;
            completed++;
        }
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = start[i] - at[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    return 0;
}
