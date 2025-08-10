#ifndef BUILD_WHEEL_VIRTUAL_ANIMAL_H
#define BUILD_WHEEL_VIRTUAL_ANIMAL_H
#include <string>
class Animal{
protected:
    std::string name_;
public:
    Animal(std::string n);
    virtual void speak() const =0;
    virtual void eat(const std::string& food);
    virtual void eat(const int food_count);
    void sleep();
    virtual ~Animal();
};
#endif