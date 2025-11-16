#include <iostream>
#include <thread>
#include <vector>
#include <semaphore>
#include <chrono>

std::binary_semaphore mutex(1);     // 保護 read_count
std::binary_semaphore rw_mutex(1);  // 控制寫入與讀取互斥
int read_count = 0;

void reader(int id) {
    while (true) {
        mutex.acquire();
        read_count++;
        if (read_count == 1)
            rw_mutex.acquire();  // 第一個讀者鎖住寫者
        mutex.release();

        // ---- Reading section ----
        std::cout << "Reader " << id << " is reading.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        mutex.acquire();
        read_count--;
        if (read_count == 0)
            rw_mutex.release();  // 最後一個讀者釋放寫者
        mutex.release();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void writer(int id) {
    while (true) {
        rw_mutex.acquire();  // 確保無讀者或寫者
        // ---- Writing section ----
        std::cout << "Writer " << id << " is writing.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        rw_mutex.release();

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

int main() {
    std::vector<std::thread> threads;

    // 建立讀者和寫者 threads
    for (int i = 0; i < 3; ++i)
        threads.emplace_back(reader, i + 1);
    for (int i = 0; i < 2; ++i)
        threads.emplace_back(writer, i + 1);

    for (auto& t : threads)
        t.join();

    return 0;
}