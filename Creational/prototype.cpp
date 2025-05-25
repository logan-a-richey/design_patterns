// prototype.cpp
#include <iostream>
#include <memory>

// create new objects by copying an existing object, then adding onto it

// abstract base class
class Shape {
    public:
    virtual Shape* clone() const = 0; // clone method for creating copies
    virtual void draw() const = 0; // drw method for rendering the shape.
    virtual ~Shape() {} // virtual destructor for proper cleanup
};

// concrete classes
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}
    Shape* clone() const override {
        return new Circle(*this);
    }

    void draw() const override {
        std::cout << "Drawing a circle with radius" << radius << std::endl;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    Shape* clone() const override {
        return new Rectangle(*this);
    }

    void draw() const override {
        std::cout << "Drawing a Rectangle with width " << width << " and height " << height << std::endl;
    }
};

int main(){
    Circle circlePrototype(5.0);
    Rectangle rectanglePrototype(4.0, 6.0);

    // Shape* shape1 = circlePrototype.clone();
    // Shape* shape2 = rectanglePrototype.clone();
    
    auto shape1 = std::unique_ptr<Shape>(circlePrototype.clone());
    auto shape2 = std::unique_ptr<Shape>(rectanglePrototype.clone());

    shape1->draw();
    shape2->draw();

    // delete shape1;
    // delete shape2;

    return 0;
}