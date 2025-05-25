// CRPT_pattern.cpp
// Curiously Recurring Template Pattern

#include <cstdio>

template <class Derived>
struct Base {
public:
    void name() {
        static_cast<Derived*>(this)->impl();
    }

protected:
    Base() = default;
};

struct D1 : public Base<D1> {
    void impl() { std::puts("D1::impl()"); }
};

struct D2 : public Base<D2> {
    void impl() { std::puts("D2::impl()"); }
};

int main() {
    D1 d1; d1.name();
    D2 d2; d2.name();
}

