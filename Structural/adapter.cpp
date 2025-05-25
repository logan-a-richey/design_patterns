// adapter.cpp
#include <iostream>
#include <string>
#include <memory>

/*
Problem Statement:
Suppose you have a legacy printer class that only understands commands in 
uppercase, and a modern computer class that sends commands in lowercase. 
You need to make the modern computer work with the legacy printer without 
modifying the existing printer class.
*/

/*
Implementation of the Adapter Pattern in C++ Design Patterns:
It defines three classes:
1.) LegacyPrinter is the legacy component (Adaptee). It has a method printInUppercase that can print text in uppercase.
2.) ModernComputer is the modern client class. It has a method sendCommand to send commands, but it sends them in lowercase.
3.) PrinterAdapter is the adapter class. It encapsulates the LegacyPrinter and adapts it to work with the ModernComputer.
*/

// Legacy Printer (Adaptee)
class LegacyPrinter {
public:
    void printInUppercase(const std::string& text){
        std::cout << "Printing: " << text << std::endl;
    }
};

// Modern Computer (Client)
class ModernComputer{
public:
    void sendCommand(const std::string& command){
        std::cout << "Sending commend: " << command << std::endl;
    }    
};

// Adapter class to make the LegacyPrinter compatible with ModernComputer
class PrinterAdapter {
private:
    LegacyPrinter legacyPrinter;

public:
    void sendCommand(const std::string& command) {
        // Convert the command to uppercase and pass it to the LegacyPrinter
        std::string uppercaseCommand = command;
        for (char& c : uppercaseCommand) {
            c = std::toupper(c);
        }
        legacyPrinter.printInUppercase(uppercaseCommand);
    }
};

int main() {
    ModernComputer computer;
    PrinterAdapter adapter;

    computer.sendCommand("Print this in lowercase");
    adapter.sendCommand("Print this in lowercase (adapted)");

    return 0;
}
