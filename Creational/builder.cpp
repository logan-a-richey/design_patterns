// builder.cpp
#include <iostream>
#include <string>

/*
Key components of the Builder Pattern in C++

Director:
* The Director is the main component of the builder pattern it basically responsible for the construction process of the program.
* It works with a Builder to build an object. 
* The Director knows the actual steps required to build an object, but it does not know the details of how each step is implemented.
    
Builder: 
* The Builder is the main interface or an abstract class that defines the construction steps required to create an object.

Concrete Builder:
*  Basically, these are the classes that implement the Builder interface. 
* Each Concrete Builder is responsible for constructing a particular variant of the object.
    
Product:
* The Product is the complex object that we want to create. 
* The Product class may have methods to access or manipulate these components. 
* It often has multiple parts or components that are built by the Builder.
*/

// Product class
class Computer {
public:
    void setCPU(const std::string& cpu) {
        cpu_ = cpu;
    }

    void setMemory(const std::string& memory) {
        memory_ = memory;
    }

    void setStorage(const std::string& storage) {
        storage_ = storage;
    }

    void display() {
        std::cout << "CPU: " << cpu_ << std::endl;
        std::cout << "Memory: " << memory_ << std::endl;
        std::cout << "Storage: " << storage_ << std::endl;
    }

private:
    std::string cpu_;
    std::string memory_;
    std::string storage_;
};

// Builder interface
class ComputerBuilder {
public:
    virtual void buildCPU(const std::string& cpu) = 0;
    virtual void buildMemory(const std::string& memory) = 0;
    virtual void buildStorage(const std::string& storage) = 0;
    virtual Computer getResult() = 0;
};

// Concrete Builder
class DesktopComputerBuilder : public ComputerBuilder {
public:
    DesktopComputerBuilder() {
        computer_ = Computer();
    }

    void buildCPU(const std::string& cpu) override {
        computer_.setCPU(cpu);
    }

    void buildMemory(const std::string& memory) override {
        computer_.setMemory(memory);
    }

    void buildStorage(const std::string& storage) override {
        computer_.setStorage(storage);
    }

    Computer getResult() override {
        return computer_;
    }

private:
    Computer computer_;
};

// Director
class ComputerAssembler {
public:
    Computer assembleComputer(ComputerBuilder& builder) {
        builder.buildCPU("Intel i7");
        builder.buildMemory("16GB");
        builder.buildStorage("512GB SSD");
        return builder.getResult();
    }
};

int main() {
    DesktopComputerBuilder desktopBuilder;
    ComputerAssembler assembler;
    Computer desktop = assembler.assembleComputer(desktopBuilder);

    std::cout << "Desktop Computer Configuration:" << std::endl;
    desktop.display();

    return 0;
}
