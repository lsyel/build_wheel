#include "cat.h"
#include <iostream>
Cat::Cat(const std::string &n):Mammal(n){
    std::cout <<name_<<" (Cat) is construct"<<std::endl;

}

void Cat::speak()const{
    std::cout<<name_<< ":Miao~"<<std::endl;
}

void Cat::eat(const std::string &food){
    std::cout<<name_<<"tian:"<<food<<std::endl;
}

void Cat::giveBirth(){
    std::cout<<name_<<"give birth to a new Cat"<<std::endl;
}

Cat::~Cat(){
    std::cout<<name_<<"(cat)is delete"<<std::endl;
}