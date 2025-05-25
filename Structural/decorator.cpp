// decorator.cpp

#include <iostream>
#include <string>
#include <memory>

/*
Concept: we can create a chain of decorators, adding functionality to an existing class.

If we were to do this manually, we would have:
iceCream = std::make_unique<CaramelDecorator>(
              std::make_unique<ChocolateDecorator>(
                  std::make_unique<VanillaIceCream>()));

We can use OOP to make this process more modular.
*/

// Component Interface
class IceCream {
public:
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~IceCream() = default;
};

// Concrete Component
class VanillaIceCream : public IceCream {
public:
    std::string getDescription() const override {
        return "Vanilla Ice Cream";
    }

    double cost() const override {
        return 160.0;
    }
};

// Decorator (abstract)
class IceCreamDecorator : public IceCream {
protected:
    std::unique_ptr<IceCream> iceCream;

public:
    IceCreamDecorator(std::unique_ptr<IceCream> ic)
        : iceCream(std::move(ic)) {}

    std::string getDescription() const override {
        return iceCream->getDescription();
    }

    double cost() const override {
        return iceCream->cost();
    }
};

// Concrete Decorator - Chocolate
class ChocolateDecorator : public IceCreamDecorator {
public:
    ChocolateDecorator(std::unique_ptr<IceCream> ic)
        : IceCreamDecorator(std::move(ic)) {}

    std::string getDescription() const override {
        return iceCream->getDescription() + " with Chocolate";
    }

    double cost() const override {
        return iceCream->cost() + 100.0;
    }
};

// Concrete Decorator - Caramel
class CaramelDecorator : public IceCreamDecorator {
public:
    CaramelDecorator(std::unique_ptr<IceCream> ic)
        : IceCreamDecorator(std::move(ic)) {}

    std::string getDescription() const override {
        return iceCream->getDescription() + " with Caramel";
    }

    double cost() const override {
        return iceCream->cost() + 150.0;
    }
};

// Smart Pointer Version
void with_smart_pointers() {
    std::unique_ptr<IceCream> iceCream = std::make_unique<VanillaIceCream>();
    std::cout << "Order: " << iceCream->getDescription()
              << ", Cost: $" << iceCream->cost() << std::endl;

    iceCream = std::make_unique<ChocolateDecorator>(std::move(iceCream));
    std::cout << "Order: " << iceCream->getDescription()
              << ", Cost: $" << iceCream->cost() << std::endl;

    iceCream = std::make_unique<CaramelDecorator>(std::move(iceCream));
    std::cout << "Order: " << iceCream->getDescription()
              << ", Cost: $" << iceCream->cost() << std::endl;
}

int main() {
    std::cout << "--- With Smart Pointers ---" << std::endl;
    with_smart_pointers();
    return 0;
}

