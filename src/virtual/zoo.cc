#include "zoo.h"
#include <iostream>
void Zoo::addAnimal(Animal *a){
    animals.push_back(a);
}
void Zoo::showAll(){
    for(auto a:animals){
        a->speak();
        a->eat("meat");
        a->eat(3);
        a->sleep();
        std::cout<<"-----"<<std::endl;
    }
}

Zoo::~Zoo(){
    for(auto a:animals){
        delete a;
    }
}