#include "zoo.h"
#include "dog.h"
#include "cat.h"

int main(){
    Zoo my_zoo;
    my_zoo.addAnimal(new Dog("WangCai"));
    my_zoo.addAnimal(new Cat("MIMI"));
    my_zoo.showAll();
}