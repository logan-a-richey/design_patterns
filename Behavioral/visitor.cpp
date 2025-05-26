// visitor.cpp

/*
--- Problem Statement ---
A visitor design patterns or visitor method is basically defined as a 
behavioral design pattern that allows us to define a new operation without 
changing the classes of the elements on which it operates. 
*/

#include <iostream>
#include <vector>
#include <memory>

// Forward declarations
class Circle;
class Square;

// Visitor interface
class ShapeVisitor {
public:
    virtual ~ShapeVisitor() = default;
    virtual void visit(Circle& circle) = 0;
    virtual void visit(Square& square) = 0;
};

// Element interface
class Shape {
public:
    virtual ~Shape() = default;
    virtual void accept(ShapeVisitor& visitor) = 0;
};

// Concrete Element: Circle
class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double getRadius() const { return radius; }

    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }

    void draw() {
        std::cout << "Drawing Circle\n";
    }
};

// Concrete Element: Square
class Square : public Shape {
    double side;
public:
    Square(double s) : side(s) {}
    double getSide() const { return side; }

    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }

    void draw() {
        std::cout << "Drawing Square\n";
    }
};

// Concrete Visitor: DrawingVisitor
class DrawingVisitor : public ShapeVisitor {
public:
    void visit(Circle& circle) override {
        std::cout << "Drawing a Circle\n";
        circle.draw();
    }

    void visit(Square& square) override {
        std::cout << "Drawing a Square\n";
        square.draw();
    }
};

// Concrete Visitor: AreaVisitor
class AreaVisitor : public ShapeVisitor {
public:
    void visit(Circle& circle) override {
        double area = 3.14159 * circle.getRadius() * circle.getRadius();
        std::cout << "Area of Circle: " << area << std::endl;
    }

    void visit(Square& square) override {
        double area = square.getSide() * square.getSide();
        std::cout << "Area of Square: " << area << std::endl;
    }
};

// Object Structure
class ShapeContainer {
    std::vector<std::shared_ptr<Shape>> shapes;
public:
    void addShape(std::shared_ptr<Shape> shape) {
        shapes.push_back(shape);
    }

    void performOperations(ShapeVisitor& visitor) {
        for (auto& shape : shapes) {
            shape->accept(visitor);
        }
    }
};

int main() {
    ShapeContainer container;
    container.addShape(std::make_shared<Circle>(2.0));
    container.addShape(std::make_shared<Square>(3.0));

    DrawingVisitor drawingVisitor;
    AreaVisitor areaVisitor;

    container.performOperations(drawingVisitor);
    container.performOperations(areaVisitor);

    return 0;
}
