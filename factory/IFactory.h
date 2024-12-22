#ifndef IFACTORY_H 
#define IFACTORY_H

#include "../Ability/Iability.h"
#include "../holders/holders.h"

class IFactory {
public:
  virtual IAbility* createAbility() = 0;
  virtual ~IFactory() = default;
};
#endif