#ifndef BUILD_WHEEL_VIRTUAL_DOG_H
#define BUILD_WHEEL_VIRTUAL_DOG_H
#include "mammal.h"

class Dog : public Mammal{
public:
    Dog(const std::string&);

    void eat(const std::string&);
    void speak()const override;
    void giveBirth() override;

    ~Dog();
};
#endif