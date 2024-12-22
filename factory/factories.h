#ifndef FACTORIES_H 
#define FACTORIES_H

#include "IFactory.h"
#include "../Ability/Abilities.h"
#include "../holders/holders.h"

class DoubleDamageFactory : public IFactory {
public:
    DoubleDamageFactory();

    IAbility* createAbility();
};

class ScannerFactory : public IFactory{
private:
    Map& map;
    CoordHolder& coordholder;
public:
    ScannerFactory(Map& map, CoordHolder& coordholder);

    IAbility* createAbility();
};

class BombardmentFactory : public IFactory {
private:
    Map& map;
public:
    BombardmentFactory(Map& map);

    IAbility* createAbility();
};  
#endif