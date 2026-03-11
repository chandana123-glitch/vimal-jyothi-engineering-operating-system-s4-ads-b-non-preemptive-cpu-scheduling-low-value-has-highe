#include <stdio.h>

#define MAX 100

typedef struct {
    char pid[10];
    int at;   // Arrival Time
    int bt;   // Burst Time
    int pr;   // Priority
    int wt;   // Waiting Time
    int tat;  // Turnaround Time
    int ct;   // Completion Time
    int done; // 0 = not completed
} Process;

int main() {
    int n;
    Process p[MAX];

    scanf("%d", &n);

    // Input
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
        p[i].done = 0;
        p[i].wt = p[i].tat = p[i].ct = 0;
    }

    int completed = 0;
    int time = 0;

    while (completed < n) {

        int idx = -1;

        for (int i = 0; i < n; i++) {

            if (p[i].at <= time && p[i].done == 0) {

                if (idx == -1 || 
                    p[i].pr < p[idx].pr || 
                    (p[i].pr == p[idx].pr && p[i].at < p[idx].at)) {
                    idx = i;
                }
            }
        }

        if (idx != -1) {

            time += p[idx].bt;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            p[idx].done = 1;
            completed++;
        }
        else {
            time++; // CPU idle
        }
    }

    float total_wt = 0, total_tat = 0;

    printf("\nWaiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].wt);
        total_wt += p[i].wt;
    }

    printf("\nTurnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].tat);
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
