#include "mammal.h"
#include <string>
#include <iostream>
Mammal::Mammal(const std::string &n):Animal(n){
    std::cout <<name_<<" (Mammal) is construct"<<std::endl;

}

void Mammal::speak() const {
    std::cout<<name_<<"speak like mammal"<<std::endl;
}

void Mammal::giveBirth(){
    std::cout<<name_<<"give birth to a new baby "<<std::endl;
}

Mammal::~Mammal(){
    std::cout<<name_<<"(Mammal) is delete"<<std::endl;
}