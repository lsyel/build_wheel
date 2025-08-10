#include "dog.h"
#include <iostream>
Dog::Dog(const std::string& n):Mammal(n){
    std::cout <<name_<<" (Dog) is construct"<<std::endl;
}

void Dog::eat(const std::string& food){
    std::cout<<name_<<"ken  "<<food<<std::endl;
}

void Dog::speak() const {
    std::cout<<"WANG!"<<std::endl;
}

void Dog::giveBirth(){
    std::cout<<name_<<"give birth to a Dog"<<std::endl;
}

Dog::~Dog(){
    std::cout<<name_<<"(Dog) is delete"<<std::endl;
}