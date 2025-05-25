// composite_animals.cpp

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class AnimalComponent {
public:
    // virtual void Add(std::shared_ptr<AnimalComponent> animal) { /* default: do nothing */ }
    // virtual void Remove(std::shared_ptr<AnimalComponent> animal) { /* default: do nothing */ }
    virtual void Add(std::shared_ptr<AnimalComponent> /*animal*/) { /* default: do nothing */ }
    virtual void Remove(std::shared_ptr<AnimalComponent> /*animal*/) { /* default: do nothing */ }
    
    virtual void Speak() const = 0;  // Polymorphic behavior
    virtual ~AnimalComponent() = default;
};

class Animal : public AnimalComponent {
private:
    std::string name;

public:
    Animal(const std::string& name) : name(name) {}

    void Speak() const override {
        std::cout << name << " says: ";
        if (name == "Dog") std::cout << "Woof!\n";
        else if (name == "Cat") std::cout << "Meow!\n";
        else std::cout << "Some animal sound\n";
    }
};

class AnimalGroup : public AnimalComponent {
private:
    std::vector<std::shared_ptr<AnimalComponent>> members;

public:
    void Add(std::shared_ptr<AnimalComponent> animal) override {
        members.push_back(animal);
    }

    void Remove(std::shared_ptr<AnimalComponent> animal) override {
        members.erase(std::remove(members.begin(), members.end(), animal), members.end());
    }

    void Speak() const override {
        std::cout << "Animal Group:\n";
        for (const auto& member : members) {
            member->Speak();
        }
    }
};

int main() {
    // Leaf nodes
    auto dog = std::make_shared<Animal>("Dog");
    auto cat = std::make_shared<Animal>("Cat");

    // Composite nodes
    auto pack = std::make_shared<AnimalGroup>();
    pack->Add(dog);
    pack->Add(cat);

    auto zoo = std::make_shared<AnimalGroup>();
    zoo->Add(pack);
    zoo->Add(std::make_shared<Animal>("Elephant"));

    zoo->Speak();

    return 0;
}

