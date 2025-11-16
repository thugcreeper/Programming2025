#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

constexpr int NUM_PHILOSOPHERS = 5;

std::mutex forks[NUM_PHILOSOPHERS];

void philosopher(int id) {
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    while (true) {
        // Thinking
        std::cout << "Philosopher " << id << " is thinking.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Avoid deadlock: last philosopher picks up right fork first
        if (id == NUM_PHILOSOPHERS - 1) {
            std::lock(forks[right], forks[left]);  // lock in fixed order
        } else {
            std::lock(forks[left], forks[right]);
        }

        // Lock guard (adopt_lock avoids re-locking)
        std::lock_guard<std::mutex> lock_left(forks[left], std::adopt_lock);
        std::lock_guard<std::mutex> lock_right(forks[right], std::adopt_lock);

        // Eating
        std::cout << "Philosopher " << id << " is eating.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::vector<std::thread> philosophers;
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.emplace_back(philosopher, i);
    }

    for (auto& p : philosophers) {
        p.join();
    }

    return 0;
}