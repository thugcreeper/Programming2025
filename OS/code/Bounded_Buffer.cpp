#include <iostream>
#include <thread>
#include <vector>
#include <semaphore>
#include <queue>
#include <chrono>

const int BUFFER_SIZE = 5;  // Buffer大小
std::queue<int> buffer;     // Bounded buffer
std::counting_semaphore<BUFFER_SIZE> empty_slots(BUFFER_SIZE); // 控制空位數量
std::counting_semaphore<BUFFER_SIZE> full_slots(0); // 控制滿位數量
std::binary_semaphore mutex(1); // 保證互斥訪問緩衝區

void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        empty_slots.acquire();   // 等待空位
        mutex.acquire();         // 確保互斥訪問緩衝區

        // 將產品放入緩衝區
        buffer.push(i);
        std::cout << "Producer " << id << " produced: " << i << std::endl;

        mutex.release();         // 釋放互斥
        full_slots.release();    // 增加滿位數量

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 模擬生產時間
    }
}

void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        full_slots.acquire();    // 等待有產品
        mutex.acquire();         // 確保互斥訪問緩衝區

        // 從緩衝區消費產品
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed: " << item << std::endl;

        mutex.release();         // 釋放互斥
        empty_slots.release();   // 增加空位數量

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 模擬消費時間
    }
}

int main() {
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // 創建生產者和消費者
    for (int i = 0; i < 2; ++i) {
        producers.push_back(std::thread(producer, i+1));
        consumers.push_back(std::thread(consumer, i+1));
    }

    // 等待所有線程結束
    for (auto& p : producers) {
        p.join();
    }
    for (auto& c : consumers) {
        c.join();
    }

    return 0;
}
