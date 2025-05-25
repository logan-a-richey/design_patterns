// decorator_singleton.cpp

#include <iostream>
#include <memory>
#include <mutex>

template <typename T>
class Singleton {
public:
    // Delete copy and assignment constructors
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T& getInstance() {
        static T instance; // thread-safe since C++11
        return instance;
    }

protected:
    Singleton() = default;
    virtual ~Singleton() = default;
};


// Manager class as Singleton
class Manager : public Singleton<Manager> {
    // Allow Singleton to construct Manager
    friend class Singleton<Manager>;

private:
    Manager() {
        std::cout << "Manager created\n";
    }

public:
    void doWork() {
        std::cout << "Working...\n";
    }
};

int main() {
    Manager& m1 = Manager::getInstance();
    Manager& m2 = Manager::getInstance();

    m1.doWork();

    std::cout << std::boolalpha << (&m1 == &m2) << std::endl;  // true
}

