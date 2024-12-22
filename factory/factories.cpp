#include "factories.h"


    DoubleDamageFactory::DoubleDamageFactory(){};

    IAbility* DoubleDamageFactory::createAbility(){
        auto ability = new DoubleDamage();
        return ability;
    }



    ScannerFactory::ScannerFactory(Map& map, CoordHolder& coordholder) : map(map), coordholder(coordholder){}

    IAbility* ScannerFactory::createAbility(){
        coordholder.RequestData();
        std::pair<int, int> coordinates  = coordholder.GetCoords();
        auto ability = new Scanner(map, coordinates.first,coordinates.second);
        return ability;
    }    



    BombardmentFactory::BombardmentFactory(Map& map) : map(map){}

    IAbility* BombardmentFactory::createAbility(){
        auto ability = new Bombardment(map);
        return ability;
    }
