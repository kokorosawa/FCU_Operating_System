#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定義序列的大小
#define SIZE 20
#define NUMBER_OF_THREADS 6

void *sorter(void *params); // 排序
void *merger(void *params); // 合併

int list[SIZE];
int result[SIZE];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
    int from_index;
    int to_index;
    int pthread_id;
} parameters;

int main(int argc, const char *argv[])
{
    int i;
    int h;
    int length;
    int arr[length];

    // 輸入 sort 大小，並隨機產生 sort 大小的亂數
    printf("請輸入排序大小: ");
    scanf("%d", &length);
    for (h = 0; h < length; h++)
    {
        list[h] = rand() % 100;
        printf("%d ", list[h]);
    }
    printf("\n");
    pthread_t workers[NUMBER_OF_THREADS];

    // 使用 clock() #clock_t clock(void);
    // startime, endtime 用來計算合併排序的時間
    clock_t startime, endtime;
    startime = clock();

    // 建立第一個排序執行緒
    parameters *data = (parameters *)malloc(sizeof(parameters));
    data->from_index = 0;
    data->to_index = 3;
    data->pthread_id = 0;
    pthread_create(&workers[0], 0, sorter, data);

    // 建立第二個排序執行緒
    data = (parameters *)malloc(sizeof(parameters));
    data->from_index = 4;
    data->to_index = 7;
    data->pthread_id = 1;
    pthread_create(&workers[1], 0, sorter, data);

    // 建立第3個排序執行緒
    data = (parameters *)malloc(sizeof(parameters));
    data->from_index = 8;
    data->to_index = 11;
    data->pthread_id = 2;
    pthread_create(&workers[2], 0, sorter, data);

    // 建立第4個排序執行緒
    data = (parameters *)malloc(sizeof(parameters));
    data->from_index = 12;
    data->to_index = 15;
    data->pthread_id = 3;
    pthread_create(&workers[3], 0, sorter, data);

    // 建立第5個排序執行緒
    data = (parameters *)malloc(sizeof(parameters));
    data->from_index = 16;
    data->to_index = 19;
    data->pthread_id = 4;
    pthread_create(&workers[4], 0, sorter, data);

    // 等待兩個排序執行緒完成
    for (i = 0; i < NUMBER_OF_THREADS - 1; i++)
    {
        pthread_join(workers[i], NULL);
    }

    // 建立合併執行緒
    data = (parameters *)malloc(sizeof(parameters));
    data->from_index = 0;
    data->to_index = SIZE - 1;
    data->pthread_id = 5;
    pthread_create(&workers[5], 0, merger, data);

    // 等待合併執行緒完成
    pthread_join(workers[5], NULL);

    endtime = clock();

    // CLOCKS_PER_SEC 單位微秒
    printf("\n");
    printf("Time taken: %f\n", (endtime - startime) / (double)CLOCKS_PER_SEC);

    return 0;
}

void *sorter(void *params)
{
    // 包含 from_index, to_index
    parameters *p = (parameters *)params;

    // 執行第一個 thread 排序
    int begin = p->from_index;
    int end = p->to_index + 1;
    int pthread_id = p->pthread_id;
    int z;
    printf("The unsorted array: ");
    for (z = begin; z < end; z++)
    {
        printf("%d ", list[z]);
    }

    printf("\n");

    int i, j, t, k;

    // lock
    if (pthread_mutex_trylock(&lock) != 0)
    {
        // lock failed
        printf("No.%d Thread sort Lock Fail!\n", pthread_id);
    }
    else
    {
        // lock success
        printf("No.%d Thread sort Lock!\n", pthread_id);
        // 泡沫排序法，排序從小到大
        for (i = begin; i < end; i++)
        {
            for (j = begin; j < end - 1; j++)
            {
                if (list[j] > list[j + 1])
                {
                    t = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = t;
                }
            }
        }

        printf("The sorted array:   ");
        for (k = begin; k < end; k++)
        {
            printf("%d ", list[k]);
        }

        int x;
        for (x = begin; x < end; x++)
        {
            result[x] = list[x];
        }
        printf("\n");

        // unlock
        pthread_mutex_unlock(&lock);
        printf("No.%d Thread sort UnLock!\n", pthread_id);
        printf("\n");
    }

    pthread_exit(NULL);
}

void *merger(void *params)
{
    // 包含 from_index, to_index
    parameters *p = (parameters *)params;

    // 執行第二個 thread 合併
    int begin = p->from_index;
    int end = p->to_index + 1;
    int pthread_id = p->pthread_id;
    int i, j, t;

    if (pthread_mutex_trylock(&lock) != 0)
    {
        // lock failed
        printf("No.%d Thread sort Lock Fail!\n", pthread_id);
    }
    else
    {
        // lock success
        printf("No.%d Thread merge Lock!\n", p->pthread_id);
        // 泡沫排序法，排序從小到大
        for (i = begin; i < end; i++)
        {
            for (j = begin; j < end - 1; j++)
            {
                if (result[j] > result[j + 1])
                {
                    t = result[j];
                    result[j] = result[j + 1];
                    result[j + 1] = t;
                }
            }
        }

        int d;
        printf("The merged array: ");
        for (d = 0; d < SIZE; d++)
        {
            printf("%d ", result[d]);
        }
        printf("\n");
        pthread_mutex_unlock(&lock);
        printf("No.%d Thread merge unLock!\n", p->pthread_id);
    }

    printf("\n");
    pthread_exit(NULL);
}