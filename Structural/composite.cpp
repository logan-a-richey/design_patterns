// composite.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

// Base component
class PageObject {
public:
    // comment out obj to surpress the compilation warning. Add and Remove get overriden.
    virtual void Add(std::shared_ptr<PageObject> /*obj*/) { /* Do nothing by default */ }
    virtual void Remove(std::shared_ptr<PageObject> /*obj*/) { /* Do nothing by default */ }
    // C++17: use:
    // virtual void Add([[maybe_unused]] std::shared_ptr<PageObject> obj) { }
    // virtual void Remove([[maybe_unused]] std::shared_ptr<PageObject> obj) { }
    virtual void Display(int indent = 0) const = 0;
    virtual ~PageObject() = default;
};

// Leaf
class Page : public PageObject {
public:
    void Display(int indent = 0) const override {
        std::cout << std::string(indent, '-') << "Page\n";
    }
};

// Composite
class Copy : public PageObject {
private:
    std::vector<std::shared_ptr<PageObject>> children;

public:
    void Add(std::shared_ptr<PageObject> obj) override {
        children.push_back(obj);
    }

    void Remove(std::shared_ptr<PageObject> obj) override {
        children.erase(std::remove(children.begin(), children.end(), obj), children.end());
    }

    void Display(int indent = 0) const override {
        std::cout << std::string(indent, '-') << "Copy\n";
        for (const auto& child : children) {
            child->Display(indent + 2);
        }
    }
};

// Demo
int main() {
    auto page1 = std::make_shared<Page>();
    auto page2 = std::make_shared<Page>();

    auto chapter = std::make_shared<Copy>();
    chapter->Add(page1);
    chapter->Add(page2);

    auto book = std::make_shared<Copy>();
    book->Add(chapter);

    book->Display();

    return 0;
}

