// mediator.cpp

#include <iostream>
#include <string>
#include <memory>

/*
--- Problem Statement ---
The Mediator Design Pattern in C++ is a behavioral pattern that defines an 
object, the mediator, to centralize communication between various components 
or objects in a system. This promotes loose coupling by preventing direct 
interactions between components, instead of having them communicate through 
the mediator, facilitating better maintainability and flexibility in the 
system architecture. 
*/

// Forward declaration
class Airplane;

// Mediator Interface
class AirTrafficControlTower {
public:
    virtual void requestTakeoff(Airplane* airplane) = 0;
    virtual void requestLanding(Airplane* airplane) = 0;

    virtual ~AirTrafficControlTower() = default;
};

// Colleague Interface
class Airplane {
public:
    virtual void requestTakeoff() = 0;
    virtual void requestLanding() = 0;
    virtual void notifyAirTrafficControl(const std::string& message) = 0;

    virtual ~Airplane() = default;
};

// Concrete Mediator
class AirportControlTower : public AirTrafficControlTower {
public:
    void requestTakeoff(Airplane* airplane) override {
        airplane->notifyAirTrafficControl("Requesting takeoff clearance.");
    }

    void requestLanding(Airplane* airplane) override {
        airplane->notifyAirTrafficControl("Requesting landing clearance.");
    }
};

// Concrete Colleague
class CommercialAirplane : public Airplane {
private:
    AirTrafficControlTower* mediator;

public:
    CommercialAirplane(AirTrafficControlTower* mediator)
        : mediator(mediator) {}

    void requestTakeoff() override {
        mediator->requestTakeoff(this);
    }

    void requestLanding() override {
        mediator->requestLanding(this);
    }

    void notifyAirTrafficControl(const std::string& message) override {
        std::cout << "Commercial Airplane: " << message << std::endl;
    }
};

int main() {
    auto tower = std::make_unique<AirportControlTower>();
    auto airplane1 = std::make_unique<CommercialAirplane>(tower.get());
    auto airplane2 = std::make_unique<CommercialAirplane>(tower.get());

    airplane1->requestTakeoff();
    airplane2->requestLanding();

    return 0;
}
