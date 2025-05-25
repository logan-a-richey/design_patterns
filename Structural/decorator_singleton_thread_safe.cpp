// decorator_singleton_thread_safe.cpp

#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

// Thread-safe Singleton template
template <typename T>
class Singleton {
public:
    // Deleted copy constructor and assignment
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T& getInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_ = new T();
        }
        return *instance_;
    }

protected:
    Singleton() = default;
    virtual ~Singleton() = default;

private:
    static T* instance_;
    static std::mutex mutex_;
};

// Static member initialization
template <typename T>
T* Singleton<T>::instance_ = nullptr;

template <typename T>
std::mutex Singleton<T>::mutex_;

// Manager class
class Manager : public Singleton<Manager> {
    friend class Singleton<Manager>;

private:
    Manager() {
        std::cout << "Manager created (thread-safe)\n";
    }

public:
    void doWork() {
        std::cout << "Doing important work...\n";
    }
};

// Global variables to capture instances
Manager* global_m1 = nullptr;
Manager* global_m2 = nullptr;

void thread1() {
    global_m1 = &Manager::getInstance();
}

void thread2() {
    global_m2 = &Manager::getInstance();
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    global_m1->doWork();

    std::cout << "Address of m1: " << global_m1 << std::endl;
    std::cout << "Address of m2: " << global_m2 << std::endl;
    std::cout << "Same instance? " << std::boolalpha << (global_m1 == global_m2) << std::endl;

    return 0;
}
