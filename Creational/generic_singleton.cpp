// generic_singleton.cpp

/*
Use the CRTP (Curiously Recurring Template Pattern) to make a generic Singleton
Goal: 
* derive a class <Farmer> from <Singleton>
* create 2 instances of <Farmer>
* show they share the same memory location
*/ 

#include <iostream>

template<typename T>
class Singleton {
public:
    static T& getInstance()
    {
        static T instance;
        return instance;
    }

    // Delete copy & move
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() {
        std::cout << "Singleton<" << typeid(T).name() << "> instance created." << std::endl;
    }
    ~Singleton() {}
};

class Farmer : public Singleton<Farmer> {
    friend class Singleton<Farmer>; // allow base to access Farmer's private constructor

public:
    void speak() {
        std::cout << "I am a singleton Farmer." << std::endl;
    }

private:
    Farmer() {
        std::cout << "Farmer constructor." << std::endl;
    }
};

int main() {
    Farmer& farmer1 = Farmer::getInstance();
    Farmer& farmer2 = Farmer::getInstance();

    farmer1.speak();

    // Show they are the same instance
    std::cout << &farmer1 << " == " << &farmer2 << std::endl;

    return 0;
}

