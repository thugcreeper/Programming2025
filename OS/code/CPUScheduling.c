#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define MAX_PROCESSES 20
#define MAX_NAME_LEN 20

// 進程結構
typedef struct {
    int pid;                    // 進程 ID
    char name[MAX_NAME_LEN];   // 進程名稱
    int arrival_time;          // 到達時間
    int burst_time;            // 執行時間
    int remaining_time;        // 剩餘執行時間
    int completion_time;       // 完成時間
    int turnaround_time;       // 周轉時間
    int waiting_time;          // 等待時間
    int response_time;         // 回應時間
    int first_response;        // 首次回應標記
} Process;

// 調度結果結構
typedef struct {
    char algorithm[20];        // 算法名稱
    double avg_waiting_time;   // 平均等待時間
    double avg_turnaround_time;// 平均周轉時間
    double avg_response_time;  // 平均回應時間
    double throughput;         // 吞吐量
    int total_time;           // 總執行時間
} ScheduleResult;

// 全域變數
Process processes[MAX_PROCESSES];
Process temp_processes[MAX_PROCESSES];
int n = 0;  // 進程數量

// 函數宣告
void input_processes();
void generate_random_processes();
void copy_processes();
void reset_process_times();
void print_processes();
void print_gantt_chart(int *sequence, int *times, int count);
void calculate_metrics(ScheduleResult *result, const char *algorithm_name);
void print_result(ScheduleResult *result);
void compare_algorithms(ScheduleResult results[], int count);

// FCFS 調度算法
ScheduleResult fcfs_scheduling() {
    printf("\n=== First-Come, First-Served (FCFS) Scheduling ===\n");
    
    copy_processes();
    reset_process_times();
    
    // 按到達時間排序
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (temp_processes[j].arrival_time > temp_processes[j + 1].arrival_time) {
                Process temp = temp_processes[j];
                temp_processes[j] = temp_processes[j + 1];
                temp_processes[j + 1] = temp;
            }
        }
    }
    
    int current_time = 0;
    int sequence[MAX_PROCESSES];
    int times[MAX_PROCESSES + 1];
    int seq_count = 0;
    
    times[0] = 0;
    
    for (int i = 0; i < n; i++) {
        // 如果 CPU 空閒，跳到下一個進程的到達時間
        if (current_time < temp_processes[i].arrival_time) {
            current_time = temp_processes[i].arrival_time;
        }
        
        sequence[seq_count] = temp_processes[i].pid;
        temp_processes[i].response_time = current_time - temp_processes[i].arrival_time;
        
        current_time += temp_processes[i].burst_time;
        temp_processes[i].completion_time = current_time;
        temp_processes[i].turnaround_time = temp_processes[i].completion_time - temp_processes[i].arrival_time;
        temp_processes[i].waiting_time = temp_processes[i].turnaround_time - temp_processes[i].burst_time;
        
        times[++seq_count] = current_time;
    }
    
    print_gantt_chart(sequence, times, seq_count);
    print_processes();
    
    ScheduleResult result;
    calculate_metrics(&result, "FCFS");
    print_result(&result);
    
    return result;
}

// SJF 調度算法 (非搶佔式)
ScheduleResult sjf_scheduling() {
    printf("\n=== Shortest Job First (SJF) Scheduling ===\n");
    
    copy_processes();
    reset_process_times();
    
    int current_time = 0;
    int completed = 0;
    int sequence[MAX_PROCESSES];
    int times[MAX_PROCESSES + 1];
    int seq_count = 0;
    int is_completed[MAX_PROCESSES] = {0};
    
    times[0] = 0;
    
    while (completed != n) {
        int idx = -1;
        int min_burst = INT_MAX;
        
        // 找到已到達且執行時間最短的進程
        for (int i = 0; i < n; i++) {
            if (temp_processes[i].arrival_time <= current_time && 
                !is_completed[i] && 
                temp_processes[i].burst_time < min_burst) {
                min_burst = temp_processes[i].burst_time;
                idx = i;
            }
        }
        
        if (idx != -1) {
            sequence[seq_count] = temp_processes[idx].pid;
            temp_processes[idx].response_time = current_time - temp_processes[idx].arrival_time;
            
            current_time += temp_processes[idx].burst_time;
            temp_processes[idx].completion_time = current_time;
            temp_processes[idx].turnaround_time = temp_processes[idx].completion_time - temp_processes[idx].arrival_time;
            temp_processes[idx].waiting_time = temp_processes[idx].turnaround_time - temp_processes[idx].burst_time;
            
            times[++seq_count] = current_time;
            is_completed[idx] = 1;
            completed++;
        } else {
            current_time++;
        }
    }
    
    print_gantt_chart(sequence, times, seq_count);
    print_processes();
    
    ScheduleResult result;
    calculate_metrics(&result, "SJF");
    print_result(&result);
    
    return result;
}

// Round Robin 調度算法
ScheduleResult round_robin_scheduling() {
    int time_quantum;
    printf("\n=== Round Robin (RR) Scheduling ===\n");
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);
    
    copy_processes();
    reset_process_times();
    
    // 初始化剩餘時間
    for (int i = 0; i < n; i++) {
        temp_processes[i].remaining_time = temp_processes[i].burst_time;
        temp_processes[i].first_response = 0;
    }
    
    int current_time = 0;
    int completed = 0;
    int sequence[MAX_PROCESSES * 10];  // 可能有很多小片段
    int times[MAX_PROCESSES * 10 + 1];
    int seq_count = 0;
    int queue[MAX_PROCESSES];
    int front = 0, rear = 0;
    int in_queue[MAX_PROCESSES] = {0};
    
    times[0] = 0;
    
    // 將時間 0 時已到達的進程加入佇列
    for (int i = 0; i < n; i++) {
        if (temp_processes[i].arrival_time <= current_time) {
            queue[rear++] = i;
            in_queue[i] = 1;
        }
    }
    
    while (completed != n) {
        if (front == rear) {
            // 佇列為空，找到下一個到達的進程
            int next_arrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (temp_processes[i].remaining_time > 0 && 
                    temp_processes[i].arrival_time > current_time &&
                    temp_processes[i].arrival_time < next_arrival) {
                    next_arrival = temp_processes[i].arrival_time;
                }
            }
            if (next_arrival != INT_MAX) {
                current_time = next_arrival;
                for (int i = 0; i < n; i++) {
                    if (temp_processes[i].arrival_time <= current_time && 
                        temp_processes[i].remaining_time > 0 && !in_queue[i]) {
                        queue[rear++] = i;
                        in_queue[i] = 1;
                    }
                }
            }
            continue;
        }
        
        int idx = queue[front++];
        in_queue[idx] = 0;
        
        if (temp_processes[idx].remaining_time <= 0) continue;
        
        // 記錄首次回應時間
        if (!temp_processes[idx].first_response) {
            temp_processes[idx].response_time = current_time - temp_processes[idx].arrival_time;
            temp_processes[idx].first_response = 1;
        }
        
        sequence[seq_count] = temp_processes[idx].pid;
        
        int execute_time = (temp_processes[idx].remaining_time < time_quantum) ? 
                          temp_processes[idx].remaining_time : time_quantum;
        
        current_time += execute_time;
        temp_processes[idx].remaining_time -= execute_time;
        times[++seq_count] = current_time;
        
        // 檢查新到達的進程
        for (int i = 0; i < n; i++) {
            if (temp_processes[i].arrival_time <= current_time && 
                temp_processes[i].remaining_time > 0 && !in_queue[i] && i != idx) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }
        
        if (temp_processes[idx].remaining_time <= 0) {
            temp_processes[idx].completion_time = current_time;
            temp_processes[idx].turnaround_time = temp_processes[idx].completion_time - temp_processes[idx].arrival_time;
            temp_processes[idx].waiting_time = temp_processes[idx].turnaround_time - temp_processes[idx].burst_time;
            completed++;
        } else {
            queue[rear++] = idx;
            in_queue[idx] = 1;
        }
    }
    
    print_gantt_chart(sequence, times, seq_count);
    print_processes();
    
    ScheduleResult result;
    calculate_metrics(&result, "Round Robin");
    print_result(&result);
    
    return result;
}

// 輔助函數實現
void input_processes() {
    printf("Enter number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);
    
    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes!\n");
        n = 0;
        return;
    }
    
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nProcess %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", processes[i].name);
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst time: ");
        scanf("%d", &processes[i].burst_time);
    }
}

void generate_random_processes() {
    srand(time(NULL));
    n = 5 + rand() % 6; // 5-10 個進程
    
    printf("Generating %d random processes...\n", n);
    
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        sprintf(processes[i].name, "P%d", i + 1);
        processes[i].arrival_time = rand() % 10;
        processes[i].burst_time = 1 + rand() % 15;
    }
    
    printf("\nGenerated processes:\n");
    printf("PID\tName\tArrival\tBurst\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\n", 
               processes[i].pid, processes[i].name, 
               processes[i].arrival_time, processes[i].burst_time);
    }
}

void copy_processes() {
    for (int i = 0; i < n; i++) {
        temp_processes[i] = processes[i];
    }
}

void reset_process_times() {
    for (int i = 0; i < n; i++) {
        temp_processes[i].completion_time = 0;
        temp_processes[i].turnaround_time = 0;
        temp_processes[i].waiting_time = 0;
        temp_processes[i].response_time = 0;
        temp_processes[i].first_response = 0;
    }
}

void print_processes() {
    printf("\nProcess Details:\n");
    printf("PID\tName\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               temp_processes[i].pid, temp_processes[i].name,
               temp_processes[i].arrival_time, temp_processes[i].burst_time,
               temp_processes[i].completion_time, temp_processes[i].turnaround_time,
               temp_processes[i].waiting_time, temp_processes[i].response_time);
    }
    printf("------------------------------------------------------------\n");
    printf("AT=Arrival Time, BT=Burst Time, CT=Completion Time\n");
    printf("TAT=Turnaround Time, WT=Waiting Time, RT=Response Time\n");
}

void print_gantt_chart(int *sequence, int *times, int count) {
    printf("\nGantt Chart:\n");
    
    // 上邊框
    printf("|");
    for (int i = 0; i < count; i++) {
        printf("  P%-2d  |", sequence[i]);
    }
    printf("\n");
    
    // 時間軸
    printf("%-2d", times[0]);
    for (int i = 1; i <= count; i++) {
        printf("      %-2d", times[i]);
    }
    printf("\n");
}

void calculate_metrics(ScheduleResult *result, const char *algorithm_name) {
    strcpy(result->algorithm, algorithm_name);
    
    double total_waiting = 0, total_turnaround = 0, total_response = 0;
    int max_completion = 0;
    
    for (int i = 0; i < n; i++) {
        total_waiting += temp_processes[i].waiting_time;
        total_turnaround += temp_processes[i].turnaround_time;
        total_response += temp_processes[i].response_time;
        if (temp_processes[i].completion_time > max_completion) {
            max_completion = temp_processes[i].completion_time;
        }
    }
    
    result->avg_waiting_time = total_waiting / n;
    result->avg_turnaround_time = total_turnaround / n;
    result->avg_response_time = total_response / n;
    result->total_time = max_completion;
    result->throughput = (double)n / max_completion;
}

void print_result(ScheduleResult *result) {
    printf("\nPerformance Metrics:\n");
    printf("Average Waiting Time: %.2f\n", result->avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", result->avg_turnaround_time);
    printf("Average Response Time: %.2f\n", result->avg_response_time);
    printf("Total Execution Time: %d\n", result->total_time);
    printf("Throughput: %.3f processes/unit time\n", result->throughput);
}

void compare_algorithms(ScheduleResult results[], int count) {
    printf("\n================================================================================\n");
    printf("ALGORITHM COMPARISON\n");
    printf("================================================================================\n");
    
    printf("%-15s %-10s %-10s %-10s %-10s %-10s\n", 
           "Algorithm", "Avg WT", "Avg TAT", "Avg RT", "Total Time", "Throughput");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-15s %-10.2f %-10.2f %-10.2f %-10d %-10.3f\n",
               results[i].algorithm,
               results[i].avg_waiting_time,
               results[i].avg_turnaround_time,
               results[i].avg_response_time,
               results[i].total_time,
               results[i].throughput);
    }
    
    // 找出最佳性能
    printf("\n================================================================================\n");
    printf("BEST PERFORMANCE:\n");
    printf("================================================================================\n");
    
    int best_wt = 0, best_tat = 0, best_rt = 0, best_throughput = 0;
    for (int i = 1; i < count; i++) {
        if (results[i].avg_waiting_time < results[best_wt].avg_waiting_time)
            best_wt = i;
        if (results[i].avg_turnaround_time < results[best_tat].avg_turnaround_time)
            best_tat = i;
        if (results[i].avg_response_time < results[best_rt].avg_response_time)
            best_rt = i;
        if (results[i].throughput > results[best_throughput].throughput)
            best_throughput = i;
    }
    
    printf("Lowest Average Waiting Time: %s (%.2f)\n", 
           results[best_wt].algorithm, results[best_wt].avg_waiting_time);
    printf("Lowest Average Turnaround Time: %s (%.2f)\n", 
           results[best_tat].algorithm, results[best_tat].avg_turnaround_time);
    printf("Lowest Average Response Time: %s (%.2f)\n", 
           results[best_rt].algorithm, results[best_rt].avg_response_time);
    printf("Highest Throughput: %s (%.3f)\n", 
           results[best_throughput].algorithm, results[best_throughput].throughput);
}

int main() {
    int choice;
    ScheduleResult results[3];
    int result_count = 0;
    
    printf("============================================================\n");
    printf("CPU SCHEDULING ALGORITHMS SIMULATOR\n");
    printf("============================================================\n");
    
    printf("\nProcess Input Method:\n");
    printf("1. Manual input\n");
    printf("2. Generate random processes\n");
    printf("Enter choice (1-2): ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            input_processes();
            break;
        case 2:
            generate_random_processes();
            break;
        default:
            printf("Invalid choice! Using random processes.\n");
            generate_random_processes();
    }
    
    if (n == 0) {
        printf("No processes to schedule!\n");
        return 1;
    }
    
    while (1) {
        printf("\n============================================================\n");
        printf("CPU SCHEDULING ALGORITHMS\n");
        printf("============================================================\n");
        printf("1. First-Come, First-Served (FCFS)\n");
        printf("2. Shortest Job First (SJF)\n");
        printf("3. Round Robin (RR)\n");
        printf("4. Compare All Algorithms\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                results[0] = fcfs_scheduling();
                if (result_count == 0) result_count = 1;
                break;
            case 2:
                results[1] = sjf_scheduling();
                if (result_count <= 1) result_count = 2;
                break;
            case 3:
                results[2] = round_robin_scheduling();
                result_count = 3;
                break;
            case 4:
                if (result_count > 0) {
                    printf("\nRunning all algorithms for comparison...\n");
                    results[0] = fcfs_scheduling();
                    results[1] = sjf_scheduling();
                    results[2] = round_robin_scheduling();
                    compare_algorithms(results, 3);
                } else {
                    printf("Please run at least one algorithm first!\n");
                }
                break;
            case 5:
                printf("Exiting simulator. Thank you!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}