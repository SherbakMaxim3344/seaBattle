#ifndef ABILITIES_H 
#define ABILITIES_H

#include "Iability.h"


class DoubleDamage : public IAbility {

public:
    DoubleDamage();

    void use(AbilityResponce& responce) override;
};

class Scanner : public IAbility {
private:
    int x;
    int y;
    Map& map;
public:
    Scanner(Map& map, int x, int y);
    void use(AbilityResponce& responce)override;
};


class Bombardment : public IAbility {
private:
    Map& map;
public:
    Bombardment(Map& map);

    void use(AbilityResponce& responce) final;
};
#endif