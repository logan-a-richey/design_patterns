// flyweight_animals.cpp

#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>

/*
--- Flyweight Pattern ---
Share common data (intrinsic state) between many objects to save memory, and only store unique data (extrinsic state) separately.

--- Animal Example ---
Many animals of the same species share the same species data
Intrinsic state (shared): Species info (e.g., "Dog", "Cat")
Extrinsic state (unique): Location, age, name — varies per animal instance
*/


// Step 1: Define the Flyweight (shared) — Species
class Species {
public:
    Species(std::string name, std::string sound)
        : name_(std::move(name)), sound_(std::move(sound)) {}

    void makeSound(int animalId) const {
        std::cout << "Animal #" << animalId << " (" << name_ << ") says: " << sound_ << "\n";
    }

private:
    std::string name_;  // intrinsic state
    std::string sound_; // intrinsic state
};


// Step 2: Flyweight Factory manages unique Species objects
class SpeciesFactory {
public:
    Species* getSpecies(const std::string& name) {
        auto it = species_.find(name);
        if (it == species_.end()) {
            // Create and store new Species if not found
            species_[name] = std::make_unique<Species>(name, getSoundForSpecies(name));
            return species_[name].get();
        }
        return it->second.get();
    }

private:
    std::string getSoundForSpecies(const std::string& name) {
        if (name == "Dog") return "Woof";
        if (name == "Cat") return "Meow";
        return "Unknown Sound";
    }

    std::unordered_map<std::string, std::unique_ptr<Species>> species_;
};


// Step 3: The Animal class holds extrinsic state + a pointer to shared Species
class Animal {
public:
    Animal(int id, Species* species, std::string location)
        : id_(id), species_(species), location_(std::move(location)) {}

    void speak() const {
        std::cout << "At " << location_ << ": ";
        species_->makeSound(id_);
    }

private:
    int id_;              // unique extrinsic state
    Species* species_;    // shared intrinsic state (flyweight)
    std::string location_; // unique extrinsic state
};

// Step 4: main!
int main() {
    SpeciesFactory factory;

    Animal a1(1, factory.getSpecies("Dog"), "Park");
    Animal a2(2, factory.getSpecies("Dog"), "Home");
    Animal a3(3, factory.getSpecies("Cat"), "Garden");
    Animal a4(4, factory.getSpecies("Dog"), "Vet");

    a1.speak();
    a2.speak();
    a3.speak();
    a4.speak();

    return 0;
}

