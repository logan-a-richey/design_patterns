// observer.cpp

/* 
--- Problem statement ---
Suppose you are developing a weather monitoring application, in which multiple
weather stations are responsible for collecting weather data, and you want to
create a system where multiple displays can show real-time weather updates.
When a weather station collects new data, all registered displays should be
updated automatically with the latest information. 
*/

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// Observer interface
class Observer : public std::enable_shared_from_this<Observer> {
public:
    virtual void update(float temperature, float humidity, float pressure) = 0;
    virtual ~Observer() = default;
};

// Subject (WeatherStation)
class WeatherStation {
private:
    float temperature{};
    float humidity{};
    float pressure{};

    std::vector<std::weak_ptr<Observer>> observers;

public:
    void registerObserver(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    void removeObserver(std::shared_ptr<Observer> observer) {
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                [&observer](const std::weak_ptr<Observer>& o) {
                    return !o.owner_before(observer) && !observer.owner_before(o);
                }),
            observers.end());
    }

    void notifyObservers() {
        // Clean expired observers and notify valid ones
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                [](const std::weak_ptr<Observer>& o) { return o.expired(); }),
            observers.end());

        for (auto& weakObs : observers) {
            if (auto obs = weakObs.lock()) {  // Promote weak_ptr to shared_ptr
                obs->update(temperature, humidity, pressure);
            }
        }
    }

    void setMeasurements(float temp, float hum, float press) {
        temperature = temp;
        humidity = hum;
        pressure = press;
        notifyObservers();
    }
};

// Concrete Observer
class Display : public Observer {
public:
    void update(float temperature, float humidity, float pressure) override {
        std::cout << "Display: Temperature = " << temperature
                  << "°C, Humidity = " << humidity
                  << "%, Pressure = " << pressure << " hPa"
                  << std::endl;
    }
};

int main() {
    WeatherStation weatherStation;

    auto display1 = std::make_shared<Display>();
    auto display2 = std::make_shared<Display>();

    weatherStation.registerObserver(display1);
    weatherStation.registerObserver(display2);

    weatherStation.setMeasurements(25.5, 60, 1013.2);
    weatherStation.setMeasurements(24.8, 58, 1014.5);

    // Optionally unregister display1
    weatherStation.removeObserver(display1);

    weatherStation.setMeasurements(23.3, 55, 1015.0);

    return 0;
}
