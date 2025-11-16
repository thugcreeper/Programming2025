#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#define TOTAL_NUMBERS 100
#define NUM_PROCESSES 2

// 共享記憶體結構
struct shared_data {
    int partial_sums[NUM_PROCESSES];  // 儲存每個 process 的部分結果
    int process_status[NUM_PROCESSES]; // 0: 未完成, 1: 已完成
};

// 計算指定範圍的總和
int calculate_range_sum(int start, int end, int process_id) {
    printf("Process %d 開始計算範圍 %d 到 %d\n", process_id, start, end);
    
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += i;
        // 模擬一些計算時間
        usleep(1000);  // 1 毫秒
    }
    
    printf("Process %d 完成計算，部分結果: %d\n", process_id, sum);
    return sum;
}

// 展示序列版本計算
int sequential_sum() {
    printf("\n=== 序列版本計算 ===\n");
    clock_t start = clock();
    
    int sum = 0;
    for (int i = 1; i <= TOTAL_NUMBERS; i++) {
        sum += i;
        usleep(1000);  // 相同的模擬時間
    }
    
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("序列版本結果: %d\n", sum);
    printf("序列版本時間: %.3f 秒\n", time_taken);
    
    return sum;
}

int main() {
    printf("=== Data Parallelism 範例：使用兩個 Process 計算 1+2+...+100 ===\n\n");
    
    // 先執行序列版本作為對比
    int sequential_result = sequential_sum();
    
    printf("\n=== 並行版本計算（使用兩個 Process）===\n");
    
    // 建立共享記憶體
    key_t key = ftok(".", 'M');
    int shmid = shmget(key, sizeof(struct shared_data), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget 失敗");
        exit(1);
    }
    
    // 附加共享記憶體
    struct shared_data *shared = (struct shared_data*)shmat(shmid, NULL, 0);
    if (shared == (void*)-1) {
        perror("shmat 失敗");
        exit(1);
    }
    
    // 初始化共享記憶體
    for (int i = 0; i < NUM_PROCESSES; i++) {
        shared->partial_sums[i] = 0;
        shared->process_status[i] = 0;
    }
    
    clock_t parallel_start = clock();
    
    // 建立兩個子 process
    pid_t pids[NUM_PROCESSES];
    
    for (int i = 0; i < NUM_PROCESSES; i++) {
        pids[i] = fork();
        
        if (pids[i] == 0) {
            // 子 process 程式碼
            int process_id = i;
            int start, end;
            
            if (process_id == 0) {
                // Process 0: 計算 1 到 50
                start = 1;
                end = 50;
            } else {
                // Process 1: 計算 51 到 100
                start = 51;
                end = 100;
            }
            
            // 執行相同的操作（加法），但處理不同的資料範圍
            int partial_sum = calculate_range_sum(start, end, process_id);
            
            // 將結果儲存到共享記憶體
            shared->partial_sums[process_id] = partial_sum;
            shared->process_status[process_id] = 1;  // 標記完成
            
            printf("Process %d 結束，結果已儲存\n", process_id);
            
            // 分離共享記憶體並結束子 process
            shmdt(shared);
            exit(0);
        } else if (pids[i] == -1) {
            perror("fork 失敗");
            exit(1);
        }
    }
    
    // 父 process 等待所有子 process 完成
    printf("\n父 process 等待子 process 完成...\n");
    
    // 等待所有子 process
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int status;
        waitpid(pids[i], &status, 0);
        printf("Process %d 已結束\n", i);
    }
    
    clock_t parallel_end = clock();
    double parallel_time = ((double)(parallel_end - parallel_start)) / CLOCKS_PER_SEC;
    
    // 收集並計算最終結果
    printf("\n=== 收集結果 ===\n");
    int total_sum = 0;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Process %d 的部分結果: %d\n", i, shared->partial_sums[i]);
        total_sum += shared->partial_sums[i];
    }
    
    printf("\n=== 最終結果 ===\n");
    printf("並行版本總和: %d\n", total_sum);
    printf("並行版本時間: %.3f 秒\n", parallel_time);
    
    // 驗證結果
    printf("\n=== 結果驗證 ===\n");
    printf("序列版本結果: %d\n", sequential_result);
    printf("並行版本結果: %d\n", total_sum);
    printf("結果正確性: %s\n", (sequential_result == total_sum) ? "正確" : "錯誤");
    
    // 數學公式驗證
    int formula_result = TOTAL_NUMBERS * (TOTAL_NUMBERS + 1) / 2;
    printf("數學公式結果: %d\n", formula_result);
    printf("公式驗證: %s\n", (formula_result == total_sum) ? "正確" : "錯誤");
    
    
    printf("\n=== Data Parallelism 特徵展示 ===\n");
    printf("1. 相同操作: 兩個 process 都執行加法運算\n");
    printf("2. 不同資料: Process 0 處理 1-50，Process 1 處理 51-100\n");
    printf("3. 獨立計算: 每個 process 獨立計算自己負責的範圍\n");
    printf("4. 結果合併: 父 process 收集並合併所有部分結果\n");
    printf("5. 負載平衡: 兩個範圍的工作量相同（都是 50 個數字）\n");
    
    // 清理共享記憶體
    shmdt(shared);
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}