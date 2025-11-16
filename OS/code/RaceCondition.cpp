#include <iostream>
#include <thread>
#include <vector>

int counter = 0; // 共享資源

void increment() {
    for (int i = 0; i < 100000; ++i) {
        counter++; // 沒有加鎖，會產生競爭條件
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << std::endl;
    return 0;
}
