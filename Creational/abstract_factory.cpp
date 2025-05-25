// abstract_factory.cpp
#include <iostream>
#include <memory>

// === Abstract Product Interface ===
class Pizza {
public:
    virtual void bake() = 0;
    virtual void cut() = 0;
    virtual void box() = 0;
    virtual ~Pizza() = default;
};

// === Concrete Products ===
class NewYorkCheesePizza final : public Pizza {
public:
    void bake() override {
        std::cout << "Baking New York-style cheese pizza.\n";
    }
    void cut() override {
        std::cout << "Cutting New York-style cheese pizza.\n";
    }
    void box() override {
        std::cout << "Boxing New York-style cheese pizza.\n";
    }
};

class NewYorkPepperoniPizza final : public Pizza {
public:
    void bake() override {
        std::cout << "Baking New York-style pepperoni pizza.\n";
    }
    void cut() override {
        std::cout << "Cutting New York-style pepperoni pizza.\n";
    }
    void box() override {
        std::cout << "Boxing New York-style pepperoni pizza.\n";
    }
};

class ChicagoCheesePizza final : public Pizza {
public:
    void bake() override {
        std::cout << "Baking Chicago-style cheese pizza.\n";
    }
    void cut() override {
        std::cout << "Cutting Chicago-style cheese pizza.\n";
    }
    void box() override {
        std::cout << "Boxing Chicago-style cheese pizza.\n";
    }
};

class ChicagoPepperoniPizza final : public Pizza {
public:
    void bake() override {
        std::cout << "Baking Chicago-style pepperoni pizza.\n";
    }
    void cut() override {
        std::cout << "Cutting Chicago-style pepperoni pizza.\n";
    }
    void box() override {
        std::cout << "Boxing Chicago-style pepperoni pizza.\n";
    }
};

// === Abstract Factory Interface ===
class PizzaFactory {
public:
    virtual std::unique_ptr<Pizza> createCheesePizza() = 0;
    virtual std::unique_ptr<Pizza> createPepperoniPizza() = 0;
    virtual ~PizzaFactory() = default;
};

// === Concrete Factories ===
class NewYorkPizzaFactory final : public PizzaFactory {
public:
    std::unique_ptr<Pizza> createCheesePizza() override {
        return std::make_unique<NewYorkCheesePizza>();
    }

    std::unique_ptr<Pizza> createPepperoniPizza() override {
        return std::make_unique<NewYorkPepperoniPizza>();
    }
};

class ChicagoPizzaFactory final : public PizzaFactory {
public:
    std::unique_ptr<Pizza> createCheesePizza() override {
        return std::make_unique<ChicagoCheesePizza>();
    }

    std::unique_ptr<Pizza> createPepperoniPizza() override {
        return std::make_unique<ChicagoPepperoniPizza>();
    }
};

// === Client Code ===
void orderPizza(PizzaFactory& factory) {
    auto cheesePizza = factory.createCheesePizza();
    cheesePizza->bake();
    cheesePizza->cut();
    cheesePizza->box();

    auto pepperoniPizza = factory.createPepperoniPizza();
    pepperoniPizza->bake();
    pepperoniPizza->cut();
    pepperoniPizza->box();
}

int main() {
    NewYorkPizzaFactory nyFactory;
    ChicagoPizzaFactory chicagoFactory;

    std::cout << "--- Ordering from New York Factory ---\n";
    orderPizza(nyFactory);

    std::cout << "\n--- Ordering from Chicago Factory ---\n";
    orderPizza(chicagoFactory);

    return 0;
}

