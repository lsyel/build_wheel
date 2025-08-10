#include "animal.h"
#include <iostream>
Animal::Animal(std::string n):name_(n){
    std::cout <<name_<<" (Animal) is construct"<<std::endl;

};

void Animal::eat(const std::string & food){
    std::cout<<name_<<"is eating"<<food<<std::endl;
}

void Animal::eat(const int food_count){
    std::cout<<name_<<"eat "<<food_count<<" times"<<std::endl;
}

void Animal::sleep(){
    std::cout<<name_<<"is sleeping ..."<<std::endl;
}

Animal::~Animal(){
    std::cout<<name_<<"(animal)is delete"<<std::endl;
}