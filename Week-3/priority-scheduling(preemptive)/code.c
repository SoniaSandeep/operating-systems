#include <stdio.h>

struct Process {
    int pid, at, bt, pr, rt, ct, tat, wt;
};

int main() {
    int n, time = 0, completed = 0;
    struct Process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter AT BT Priority for P%d: ", i+1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].pid = i+1;
        p[i].rt = p[i].bt;
    }

    while(completed < n) {
        int idx = -1;
        int highest = 9999;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].rt > 0) {
                if(p[i].pr < highest) {
                    highest = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            p[idx].rt--;
            time++;

            if(p[idx].rt == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        }
        else {
            time++;
        }
    }

    float avgwt = 0, avgtat = 0;

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);

        avgwt += p[i].wt;
        avgtat += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", avgwt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avgtat/n);

    return 0;
}
