// strategy.cpp

#include <iostream>
#include <memory>

// Forward declaration of state interface
class AnimalState;

// Context class: Farm Animal
class Animal {
private:
    std::unique_ptr<AnimalState> state;

public:
    Animal(std::unique_ptr<AnimalState> initialState) 
        : state(std::move(initialState)) {}

    void setState(std::unique_ptr<AnimalState> newState);

    void performAction();  // Delegates to state
};

// State Interface
class AnimalState {
public:
    virtual ~AnimalState() = default;
    virtual void handle(Animal& animal) = 0;
};

// Concrete States
class SleepingState : public AnimalState {
public:
    void handle(Animal& animal) override;
};

class EatingState : public AnimalState {
public:
    void handle(Animal& animal) override;
};

class WalkingState : public AnimalState {
public:
    void handle(Animal& animal) override;
};

// Definitions

void Animal::setState(std::unique_ptr<AnimalState> newState) {
    state = std::move(newState);
}

void Animal::performAction() {
    state->handle(*this);
}

// State behaviors

void SleepingState::handle(Animal& animal) {
    std::cout << "Animal is sleeping... zzz" << std::endl;
    // After sleeping, animal wakes and starts eating
    animal.setState(std::make_unique<EatingState>());
}

void EatingState::handle(Animal& animal) {
    std::cout << "Animal is eating." << std::endl;
    // After eating, animal starts walking
    animal.setState(std::make_unique<WalkingState>());
}

void WalkingState::handle(Animal& animal) {
    std::cout << "Animal is walking around the farm." << std::endl;
    // After walking, animal goes to sleep again
    animal.setState(std::make_unique<SleepingState>());
}

// Main usage

int main() {
    Animal farmAnimal(std::make_unique<SleepingState>());

    // Simulate the animal's daily routine:
    for (int i = 0; i < 6; ++i) {
        farmAnimal.performAction();
    }

    return 0;
}

