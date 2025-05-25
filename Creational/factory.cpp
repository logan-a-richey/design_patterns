// factory.cpp
#include <iostream>
#include <memory>

class Animal {
public:
    virtual void make_sound() = 0; // make pure virtual function to override
    virtual ~Animal() {} // virtual destructor for polymorphism
};
class Dog : public Animal {
    void make_sound() override {
        std::cout << "Dog says bark!" << std::endl;
    }
};
class Cat : public Animal {
    void make_sound() override {
        std::cout << "Cat says meow!" << std::endl;
    }
};

class AnimalFactory {
public:
    virtual Animal* make_animal() = 0; // make pure virtual function to override
    virtual ~AnimalFactory() {} // virtual destructor for polymorphism
};
class DogFactory : public AnimalFactory {
public:
    Animal* make_animal() override {
       return new Dog(); 
    }
};
class CatFactory : public AnimalFactory {
public:
    Animal* make_animal() override {
       return new Cat(); 
    }
};

void tutorial_01(){
    CatFactory* my_cat_factory = new CatFactory();
    DogFactory* my_dog_factory = new DogFactory();

    Animal* my_cat = my_cat_factory->make_animal();
    Animal* my_dog = my_dog_factory->make_animal();

    my_cat->make_sound();
    my_dog->make_sound();

    delete my_cat; 
    delete my_dog;
    delete my_cat_factory;
    delete my_dog_factory;
}

void tutorial_02(){
    // create animal factories
    auto my_dog_factory = std::unique_ptr<DogFactory>(new DogFactory());
    auto my_cat_factory = std::unique_ptr<CatFactory>(new CatFactory());

    // create animals
    auto my_dog = std::unique_ptr<Animal>(my_dog_factory->make_animal());
    auto my_cat = std::unique_ptr<Animal>(my_cat_factory->make_animal());

    // test animal functions
    my_dog->make_sound();
    my_cat->make_sound();

}

int main(){
    std::cout << "--- With new and delete ---" << std::endl;
    tutorial_01();
    std::cout << std::endl;

    std::cout << "--- With new and delete ---" << std::endl;
    tutorial_02();
}
