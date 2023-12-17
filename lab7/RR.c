#include <stdio.h>

// 定義行程的結構
struct Process
{
    int id;          // 行程 ID
    int arrivalTime; // 到達時間
    int burstTime;   // 執行時間
};

// 計算平均周轉時間和平均等待時間的函數
void calulateAvgTimes(struct Process processes[], int n, int timeQuantum)
{
    int waitingTime[n], turnaroundTime[n];

    // 初始化等待時間和周轉時間
    for (int i = 0; i < n; i++)
    {
        waitingTime[i] = 0;
        turnaroundTime[i] = 0;
    }

    int remainingBurstTime[n];
    for (int i = 0; i < n; i++)
    {
        remainingBurstTime[i] = processes[i].burstTime;
    }

    int currentTime = 0;
    int completed = 0;

    // 實現 Round Robin 排班
    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (remainingBurstTime[i] > 0)
            {
                if (remainingBurstTime[i] <= timeQuantum)
                {
                    currentTime += remainingBurstTime[i];
                    turnaroundTime[i] = currentTime - processes[i].arrivalTime;
                    waitingTime[i] = turnaroundTime[i] - processes[i].burstTime;
                    remainingBurstTime[i] = 0;
                    completed++;
                }
                else
                {
                    currentTime += timeQuantum;
                    remainingBurstTime[i] -= timeQuantum;
                }
            }
        }
    }

    // 計算平均周轉時間和平均等待時間
    float avgTurnaroundTime = 0, avgWaitingTime = 0;
    for (int i = 0; i < n; i++)
    {
        avgTurnaroundTime += turnaroundTime[i];
        avgWaitingTime += waitingTime[i];
    }

    avgTurnaroundTime /= n;
    avgWaitingTime /= n;

    // 列印各個行程的資訊
    printf("\nProcess Information:\n");
    printf("----------------------------------------\n");
    printf("| Process ID | Arrival Time | Burst Time |\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("| %-8d| %-13d| %-11d|\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime);
    }

    // 印出結果
    printf("\nAverage Turnaround Time = %.2f\n", avgTurnaroundTime);
    printf("Average Waiting Time = %.2f\n", avgWaitingTime);
}

void init(struct Process processes[], int id, int arrivalTime, int burstTime)
{
    processes[id].id = id;
    processes[id].arrivalTime = arrivalTime;
    processes[id].burstTime = burstTime;
}

int main()
{
    int n = 4;
    // printf("Enter the number of processes: ");
    // scanf("%d", &n);

    struct Process processes[n];

    // 手動輸入行程資訊
    // for (int i = 0; i < n; i++) {
    //     printf("Enter the arrival time for process %d: ", i + 1);
    //     scanf("%d", &processes[i].arrivalTime);

    //     printf("Enter the burst time of process %d: ", i + 1);
    //     scanf("%d", &processes[i].burstTime);

    //     processes[i].id = i + 1; // 自動分配行程 ID
    // }
    init(processes, 0, 12, 9);
    init(processes, 1, 0, 18);
    init(processes, 2, 5, 6);
    init(processes, 3, 7, 15);

    int timeQuantum;
    printf("Enter the time quantum for Round Robin scheduling: ");
    scanf("%d", &timeQuantum);

    calulateAvgTimes(processes, n, timeQuantum);

    return 0;
}