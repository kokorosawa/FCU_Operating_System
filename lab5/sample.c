#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int process_id;
    int burst_time;
} Process;

void sortProcesses(Process processes[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].burst_time > processes[j + 1].burst_time)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void calculateTurnaroundTime(Process processes[], int n, int turnaround_time[])
{
    int waiting_time[n];
    waiting_time[0] = 0;

    for (int i = 1; i < n; i++)
    {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
    }

    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }
}

void calculateAverageTime(Process processes[], int n)
{
    int turnaround_time[n];
    calculateTurnaroundTime(processes, n, turnaround_time);

    float total_turnaround_time = 0;

    for (int i = 0; i < n; i++)
    {
        total_turnaround_time += turnaround_time[i];
    }

    float avg_turnaround_time = total_turnaround_time / n;
    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);
}

int main()
{
    int n;
    printf("Enter the number of processes(max 5): ");
    scanf("%d", &n);
    if (n < 1 || n > 5)
    {
        printf("Invalid number of processes\n");
        return 1;
    }

    Process processes[n];

    for (int i = 0; i < n; i++)
    {
        processes[i].process_id = i + 1;
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    printf("Process ID\tBurst Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\n", processes[i].process_id, processes[i].burst_time);
    }

    sortProcesses(processes, n);

    calculateAverageTime(processes, n);

    return 0;
}