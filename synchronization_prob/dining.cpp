#include <iostream> // DINNING 
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

#define N 5             // Number of philosophers
#define THINKING 2      // State when a philosopher is thinking
#define HUNGRY 1        // State when a philosopher wants to eat
#define EATING 0        // State when a philosopher is eating
#define LEFT (phnum + 4) % N   // Index of left philosopher
#define RIGHT (phnum + 1) % N  // Index of right philosopher

int state[N];
int phil[N] = {0, 1, 2, 3, 4}; // Philosopher identifiers

std::mutex mutex;               // Mutex to protect shared state
std::condition_variable S[N];   // Condition variables for each philosopher

// Function to check if philosopher can start eating
void test(int phnum) {
    if (state[phnum] == HUNGRY &&
        state[LEFT] != EATING &&
        state[RIGHT] != EATING) {
        
        state[phnum] = EATING;
        std::cout << "Philosopher " << phnum + 1 << " takes forks " 
                  << LEFT + 1 << " and " << phnum + 1 << std::endl;
        std::cout << "Philosopher " << phnum + 1 << " is Eating" << std::endl;
        S[phnum].notify_one();
    }
}

void take_fork(int phnum) {
    std::unique_lock<std::mutex> lock(mutex);
    state[phnum] = HUNGRY;
    std::cout << "Philosopher " << phnum + 1 << " is Hungry" << std::endl;
    
    test(phnum);

    if (state[phnum] != EATING)
        S[phnum].wait(lock);
}

void put_fork(int phnum) {
    std::unique_lock<std::mutex> lock(mutex);
    state[phnum] = THINKING;
    
    std::cout << "Philosopher " << phnum + 1 << " puts down forks " 
              << LEFT + 1 << " and " << phnum + 1 << std::endl;
    std::cout << "Philosopher " << phnum + 1 << " is Thinking" << std::endl;

    test(LEFT);
    test(RIGHT);
}

void philosopher(int num) {
    for (int i = 0; i < 3; i++) {  // Loop to allow only 3 attempts
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Thinking
        take_fork(num);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Eating
        put_fork(num);
    }
}

int main() {
    std::thread threads[N];

    for (int i = 0; i < N; i++) {
        threads[i] = std::thread(philosopher, i);
        std::cout << "Philosopher " << i + 1 << " is Thinking" << std::endl;
    }

    for (int i = 0; i < N; i++) {
        threads[i].join();
    }

    return 0;
}
