#ifndef BUILD_WHEEL_VIRTUAL_MAMMAL_H
#define BUILD_WHEEL_VIRTUAL_MAMMAL_H
#include "animal.h"
#include <string>
class Mammal:public Animal{
public:
    Mammal(const std::string &);
    void speak() const override;
    virtual void giveBirth();
    virtual ~Mammal();
};

#endif