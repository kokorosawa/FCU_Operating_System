#include <stdio.h>
#include <string.h>

// 定義行程的結構
struct Process
{
    int id;          // 行程 ID
    int arrivalTime; // 到達時間
    int burstTime;   // 執行時間
    int finishTime;  // 結束時間
};

// 計算平均周轉時間和平均等待時間的函數
float calulateAvgTimes(struct Process processes[], int n, int timeQuantum)
{
    int waitingTime[n], turnaroundTime[n],schedule[n];
    int queue[n];
    memset(queue, -1, n * sizeof(queue[0]));
    // 初始化等待時間和周轉時間
    for (int i = 0; i < n; i++)
    {
        waitingTime[i] = 0;
        turnaroundTime[i] = 0;
        schedule[i] = 0;
    }

    int remainingBurstTime[n];
    for (int i = 0; i < n; i++)
    {
        remainingBurstTime[i] = processes[i].burstTime;
    }

    int currentTime = 0;
    int completed = 0;
    int queueindex = 0;

    // while (queueindex == 0)
    // {
    //     for (int i = 0; i < queueindex; i++)
    //     {
    //         remainingBurstTime[queue[i]] = processes[queue[i]].burstTime;
    //         if (remainingBurstTime[queue[i]] <= timeQuantum)
    //         {
    //             printf("currentTime = %d\n", currentTime);
    //             currentTime += remainingBurstTime[queue[i]];
    //             printf("currentTime = %d\n", currentTime);
    //             turnaroundTime[queue[i]] = currentTime - processes[queue[i]].arrivalTime;
    //             waitingTime[queue[i]] = turnaroundTime[queue[i]] - processes[queue[i]].burstTime;
    //             remainingBurstTime[queue[i]] = 0;
    //             completed++;
    //         }
    //         else
    //         {
    //             printf("currentTime = %d\n", currentTime);
    //             currentTime += timeQuantum;
    //             remainingBurstTime[queue[i]] -= timeQuantum;
    //         }
    //     }
    // }

    //實現 Round Robin 排班
    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            printf("%d %d %d %d\n", queue[0], queue[1], queue[2], queue[3]);
            if (processes[i].arrivalTime <= currentTime && schedule[i] == 0) 
            {
                schedule[i] = 1;
                printf("processes[i].arrivalTime = %d   %d\n", processes[i].arrivalTime, processes[i].id);
                queue[queueindex] = processes[i].id;
                queueindex++;
            }
            if (queue[i] >= 0)
            {
                if (remainingBurstTime[queue[i]] <= timeQuantum)
                {
                    printf("currentTime = %d\n", currentTime);
                    currentTime += remainingBurstTime[queue[i]];
                    printf("currentTime = %d\n", currentTime);
                    turnaroundTime[queue[i]] = currentTime - processes[queue[i]].arrivalTime;
                    waitingTime[queue[i]] = turnaroundTime[queue[i]] - processes[queue[i]].burstTime;
                    remainingBurstTime[queue[i]] = 0;
                    queue[i] = -1;
                    completed++;
                }
                else
                {
                    printf("currentTime = %d\n", currentTime);
                    currentTime += timeQuantum;
                    remainingBurstTime[queue[i]] -= timeQuantum;
                }
            }
        }
    }

        // 實現 Round Robin 排班
    // while (completed < n)
    // {
    //     for (int i = 0; i < n; i++)
    //     {
    //         if (remainingBurstTime[i] > 0)
    //         {
    //             if (remainingBurstTime[i] <= timeQuantum)
    //             {
    //                 currentTime += remainingBurstTime[i];
    //                 turnaroundTime[i] = currentTime - processes[i].arrivalTime;
    //                 waitingTime[i] = turnaroundTime[i] - processes[i].burstTime;
    //                 processes[i].finishTime = currentTime;
    //                 remainingBurstTime[i] = 0;
    //                 completed++;
    //             }
    //             else
    //             {
    //                 currentTime += timeQuantum;
    //                 remainingBurstTime[i] -= timeQuantum;
    //             }
    //         }
    //     }
    // }
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

    return avgWaitingTime;
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

    // 自動產生行程資訊
    init(processes, 0, 12, 9);
    init(processes, 1, 0, 18);
    init(processes, 2, 5, 6);
    init(processes, 3, 7, 15);

    // 手動輸入行程資訊
    // for (int i = 0; i < n; i++) {
    //     printf("Enter the arrival time for process %d: ", i + 1);
    //     scanf("%d", &processes[i].arrivalTime);

    //     printf("Enter the burst time of process %d: ", i + 1);
    //     scanf("%d", &processes[i].burstTime);

    //     processes[i].id = i + 1; // 自動分配行程 ID
    // }

    // int timeQuantum;
    // printf("Enter the time quantum for Round Robin scheduling: ");
    // scanf("%d", &timeQuantum);

    // float minwaitingTime = 100;
    // int timeQuantum = 0;
    // for(int i = 1; i < 50; i++) {
    //     printf("timeQuantum = %d\n", i);
    //     float res = calulateAvgTimes(processes, n, i);
    //     if(res < minwaitingTime){
    //         minwaitingTime = res;
    //         timeQuantum = i;
    //     }
    // }
    // printf("----------------------------------------\n");
    // printf("minwaitingTime = %f\n", minwaitingTime);
    // printf("timeQuantum = %d\n", timeQuantum);d
    //calulateAvgTimes(processes, n, 8);
    calulateAvgTimes(processes, n, 8);
    return 0;
}