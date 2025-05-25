// proxy.cpp

#include <iostream>
#include <memory>

/*
--- Animal Sound Proxy Example ---
The proxy will delay loading the actual animal data (which is "expensive") until needed.
*/

// Step 1: Animal Interface
class Animal {
public:
    virtual ~Animal() = default;
    virtual void makeSound() = 0;
};

// Step 2: RealAnimal: Heavy object (e.g. loads data, expensive)
class RealAnimal : public Animal {
private:
    std::string species_;

public:
    explicit RealAnimal(const std::string& species) : species_(species) {
        // Simulate expensive loading (e.g., loading big data from disk)
        std::cout << "Loading data for species: " << species_ << std::endl;
    }

    void makeSound() override {
        if (species_ == "Dog") {
            std::cout << "Woof!" << std::endl;
        } else if (species_ == "Cat") {
            std::cout << "Meow!" << std::endl;
        } else {
            std::cout << species_ << " makes a sound!" << std::endl;
        }
    }
};

// Step 3: ProxyAnimal: Controls access to RealAnimal, lazy loads
class ProxyAnimal : public Animal {
private:
    std::string species_;
    std::unique_ptr<RealAnimal> realAnimal_;

public:
    explicit ProxyAnimal(const std::string& species) : species_(species), realAnimal_(nullptr) {}

    void makeSound() override {
        if (!realAnimal_) {
            // Lazy initialization: create RealAnimal only when needed
            realAnimal_ = std::make_unique<RealAnimal>(species_);
        }
        realAnimal_->makeSound();
    }
};

// Step 4: Main!
int main() {
    std::unique_ptr<Animal> dog = std::make_unique<ProxyAnimal>("Dog");

    // No loading yet, just proxy created

    std::cout << "Calling makeSound first time:" << std::endl;
    dog->makeSound();  // Loads and then makes sound

    std::cout << "Calling makeSound second time:" << std::endl;
    dog->makeSound();  // Uses cached RealAnimal, no loading

    return 0;
}

