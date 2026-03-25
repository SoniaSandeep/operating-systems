#include <stdio.h>

// Structure to store process details
struct Process {
    int pid;
    int at;   // Arrival Time
    int bt;   // Burst Time
    int type; // 0 = System, 1 = User
    int ct;   // Completion Time
    int tat;  // Turnaround Time
    int wt;   // Waiting Time
    int start; // Start Time
};

// Function to sort processes by arrival time (FCFS)
void sortByArrival(struct Process p[], int n) {
    int i, j;
    struct Process temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n], systemQ[n], userQ[n];
    int sysCount = 0, userCount = 0;

    // Input
    for (i = 0; i < n; i++) {
        printf("\nEnter details for Process %d\n", i + 1);
        printf("PID: ");
        scanf("%d", &p[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);
    }

    // Step 1: Separate into System and User queues
    for (i = 0; i < n; i++) {
        if (p[i].type == 0) {
            systemQ[sysCount++] = p[i];
        } else {
            userQ[userCount++] = p[i];
        }
    }

    // Step 2: Sort both queues by Arrival Time
    sortByArrival(systemQ, sysCount);
    sortByArrival(userQ, userCount);

    int time = 0;

    // Step 3: Execute System Processes first
    for (i = 0; i < sysCount; i++) {
        if (time < systemQ[i].at)
            time = systemQ[i].at;

        systemQ[i].start = time;
        time += systemQ[i].bt;
        systemQ[i].ct = time;

        systemQ[i].tat = systemQ[i].ct - systemQ[i].at;
        systemQ[i].wt = systemQ[i].tat - systemQ[i].bt;
    }

    // Step 4: Execute User Processes after System queue
    for (i = 0; i < userCount; i++) {
        if (time < userQ[i].at)
            time = userQ[i].at;

        userQ[i].start = time;
        time += userQ[i].bt;
        userQ[i].ct = time;

        userQ[i].tat = userQ[i].ct - userQ[i].at;
        userQ[i].wt = userQ[i].tat - userQ[i].bt;
    }

    // Step 5: Display results
    printf("\n\n--- System Processes ---\n");
    printf("PID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");
    for (i = 0; i < sysCount; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               systemQ[i].pid,
               systemQ[i].at,
               systemQ[i].bt,
               systemQ[i].type,
               systemQ[i].ct,
               systemQ[i].tat,
               systemQ[i].wt);
    }

    printf("\n--- User Processes ---\n");
    printf("PID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");
    for (i = 0; i < userCount; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               userQ[i].pid,
               userQ[i].at,
               userQ[i].bt,
               userQ[i].type,
               userQ[i].ct,
               userQ[i].tat,
               userQ[i].wt);
    }

    return 0;
}
