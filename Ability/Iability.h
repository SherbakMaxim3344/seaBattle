#ifndef IABILITY_H 
#define IABILITY_H

#include <iostream>
#include <memory>
#include <optional>
#include "AbilityResponce.h"
class Map;

class IAbility {
public:
    virtual void use(AbilityResponce& responce) = 0;
    virtual~IAbility() = default;
};

#endif