#include <iostream>
#include <thread>
#include <semaphore>

std::binary_semaphore sem{1};

int counter = 0; // 共享資源

void increment() {

    sem.acquire();
    // critical section
    for (int i = 0; i < 100000; ++i) {
        counter++; // 沒有加鎖，會產生競爭條件
    }
    sem.release();
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Final counter value: " << counter << std::endl;
    return 0;
}

