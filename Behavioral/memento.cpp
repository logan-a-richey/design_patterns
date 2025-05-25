// memento.cpp

/*
--- Problem Statement ---
Suppose we have to represent two states by the use of memento patterns then 
we can use three classes to represent this Originator class to store the 
data then memento patterns for storing the state of originator then 
caretaker will hold the memento to solve the problem.
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// Originator: The object whose state needs to be saved and restored.
class Originator {
private:
    std::string state;

public:
    void SetState(const std::string& newState) {
        state = newState;
    }

    std::string GetState() const {
        return state;
    }

    // Memento: Represents a snapshot of the Originator's state.
    class Memento {
    private:
        std::string savedState;

    public:
        explicit Memento(const std::string& originatorState)
            : savedState(originatorState) {}

        std::string GetSavedState() const {
            return savedState;
        }
    };

    // Save the current state in a Memento
    Memento CreateMemento() const {
        return Memento(state);
    }

    // Restore state from a Memento
    void RestoreState(const Memento& memento) {
        state = memento.GetSavedState();
    }
};

// Caretaker: Stores and manages Mementos
class Caretaker {
private:
    std::vector<Originator::Memento> mementos;

public:
    void AddMemento(Originator::Memento memento) {
        mementos.push_back(std::move(memento));
    }

    const Originator::Memento& GetMemento(std::size_t index) const {
        if (index < mementos.size()) {
            return mementos[index];
        }
        throw std::out_of_range("Invalid Memento index");
    }
};

int main() {
    Originator originator;
    Caretaker caretaker;

    originator.SetState("State 1");
    caretaker.AddMemento(originator.CreateMemento());

    originator.SetState("State 2");
    caretaker.AddMemento(originator.CreateMemento());

    originator.RestoreState(caretaker.GetMemento(0));
    std::cout << "Restored to: " << originator.GetState() << std::endl;

    originator.RestoreState(caretaker.GetMemento(1));
    std::cout << "Restored to: " << originator.GetState() << std::endl;

    return 0;
}

