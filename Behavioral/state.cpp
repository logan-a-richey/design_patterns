// state.cpp

/*
--- Problem Statement ---
We have to design a simple traffic light system. The traffic light system 
consists of different states: Red, Yellow, and Green and the behavior of the 
traffic light is determined by its current state.
*/

#include <iostream>
#include <memory>  // for std::unique_ptr

// State Interface
class TrafficLightState {
public:
    virtual void handle() = 0;
    virtual ~TrafficLightState() = default;  // virtual destructor for safety
};

// Concrete States
class RedState : public TrafficLightState {
public:
    void handle() override {
        std::cout << "Traffic Light is Red\n";
    }
};

class YellowState : public TrafficLightState {
public:
    void handle() override {
        std::cout << "Traffic Light is Yellow\n";
    }
};

class GreenState : public TrafficLightState {
public:
    void handle() override {
        std::cout << "Traffic Light is Green\n";
    }
};

// Context
class TrafficLight {
private:
    std::unique_ptr<TrafficLightState> state;

public:
    TrafficLight() : state(std::make_unique<RedState>()) {}

    void setState(std::unique_ptr<TrafficLightState> newState) {
        state = std::move(newState);
    }

    void change() { state->handle(); }
};

int main() {
    TrafficLight trafficLight;

    trafficLight.change(); // Initial state: Red

    trafficLight.setState(std::make_unique<GreenState>());
    trafficLight.change(); // State changed to Green

    trafficLight.setState(std::make_unique<YellowState>());
    trafficLight.change(); // State changed to Yellow

    return 0;
}
