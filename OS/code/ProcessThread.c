#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

// 宣告全域變數
int global_var = 0;

// Thread 函數
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    
    printf("Thread %d: 初始 global_var = %d\n", thread_id, global_var);
    
    // 修改全域變數
    global_var += 10;
    printf("Thread %d: 修改後 global_var = %d\n", thread_id, global_var);
    
    // 等待一秒讓其他 thread 也有機會執行
    sleep(1);
    
    printf("Thread %d: 最終 global_var = %d\n", thread_id, global_var);
    
    return NULL;
}

// Process 函數
void process_function(int process_id) {
    printf("Process %d: 初始 global_var = %d\n", process_id, global_var);
    
    // 修改全域變數
    global_var += 10;
    printf("Process %d: 修改後 global_var = %d\n", process_id, global_var);
    
    // 等待一秒
    sleep(1);
    
    printf("Process %d: 最終 global_var = %d\n", process_id, global_var);
}

int main() {
    
    printf("=== Process vs Thread 全域變數測試 ===\n");
    printf("初始全域變數值: %d\n\n", global_var);
    
    // === Thread 測試 ===
    printf("--- Thread 測試 (共用記憶體空間) ---\n");
    
    pthread_t threads[3];
    int thread_ids[3] = {1, 2, 3};
    
    // 建立 3 個 threads
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }
    
    // 等待所有 threads 完成
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("主程序中的 global_var (thread 測試後): %d\n\n", global_var);
    
    // 重置全域變數
    global_var = 0;
    
    // === Process 測試 ===
    printf("--- Process 測試 (獨立記憶體空間) ---\n");
    
    pid_t pids[3];
    
    // 建立 3 個 child processes
    for (int i = 0; i < 3; i++) {
        pids[i] = fork();
        
        if (pids[i] == 0) {
            // 子程序
            process_function(i + 1);
            exit(0);
        } else if (pids[i] < 0) {
            perror("fork");
            exit(1);
        }
    }
    
    // 父程序等待所有子程序完成
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }
    
    printf("主程序中的 global_var (process 測試後): %d\n\n", global_var);
    
    // === 結果說明 ===
    printf("=== 結果分析 ===\n");
    printf("Thread 特性:\n");
    printf("- 所有 threads 共用同一個記憶體空間\n");
    printf("- 對全域變數的修改會影響到其他 threads\n");
    printf("- 可能出現競爭條件 (race condition)\n\n");
    
    printf("Process 特性:\n");
    printf("- 每個 process 有獨立的記憶體空間\n");
    printf("- 對全域變數的修改不會影響到其他 processes\n");
    printf("- 父程序的全域變數值保持不變\n");
    
    return 0;
}