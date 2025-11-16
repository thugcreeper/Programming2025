#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

class DeadlockExample {
private:
    std::mutex first_mutex;
    std::mutex second_mutex;

public:
    void do_work_one() {
        first_mutex.lock();
        std::cout << "do_work_one: first_mutex.lock()" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 增加發生 deadlock 的機率

        second_mutex.lock();
        std::cout << "do_work_one" << std::endl;

        second_mutex.unlock();
        first_mutex.unlock();
    }

    void do_work_two() {
        second_mutex.lock();
        std::cout << "do_work_two: second_mutex.lock()" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 增加發生 deadlock 的機率

        first_mutex.lock();
        std::cout << "do_work_two" << std::endl;

        first_mutex.unlock();
        second_mutex.unlock();
    }

    void exec() {
        std::thread t1(&DeadlockExample::do_work_one, this);
        std::thread t2(&DeadlockExample::do_work_two, this);

        t1.join();
        t2.join();
    }
};

int main() {
    DeadlockExample example;
    example.exec();
    return 0;
}