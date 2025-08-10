#ifndef BUILD_WHELL_VIRTUAL_ZOO_H
#define BUILD_WHELL_VIRTUAL_ZOO_H
#include <vector>
#include "animal.h"
class Zoo{
private:
    std::vector<Animal*> animals;
public:
    void addAnimal(Animal*);
    void showAll();
    ~Zoo();
};
#endif