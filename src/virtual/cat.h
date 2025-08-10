#ifndef BUILD_WHEEL_VIRTUAL_CAT_H
#define BUILD_WHEEL_VIRTUAL_CAT_H

#include "mammal.h"
class Cat:public Mammal{
public:
    Cat(const std::string &);
    void eat(const std::string &);
    void speak()const override;
    void giveBirth() override;
    ~Cat();
};
#endif