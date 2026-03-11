#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char pid[10];
    int at;   // Arrival Time
    int bt;   // Burst Time
    int pr;   // Priority
    int wt;   // Waiting Time
    int tat;  // Turnaround Time
    int ct;   // Completion Time
    int done; // 0 = not finished, 1 = finished
} Process;

int main() {
    int n;
    Process p[MAX];

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
        p[i].done = 0;
    }

    int completed = 0;
    int time = 0;

    while (completed < n) {

        int idx = -1;

        for (int i = 0; i < n; i++) {

            if (p[i].at <= time && p[i].done == 0) {

                if (idx == -1)
                    idx = i;

                else if (p[i].pr < p[idx].pr)
                    idx = i;

                else if (p[i].pr == p[idx].pr && p[i].at < p[idx].at)
                    idx = i;
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
            time++;
        }
    }

    float total_wt = 0, total_tat = 0;

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].wt);
        total_wt += p[i].wt;
    }

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].tat);
        total_tat += p[i].tat;
    }

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
