#ifndef MAP
#define MAP

#include <optional>
#include "ship.h"
#include "shipmanager.h"
#include "Cell.h"
#include "../exceptions/exceptions.h"
#include "../Ability/AbilityResponce.h"
class Map
{
public:
    enum class MapCells
    {
        ship, // занятое поле
        empty, // свободное поле
        unknown, // неизвестно
    };

private:

    int size_map_width;
    int size_map_height;
    std::vector<std::vector<Cell>> starting_map;
    ShipManager* manager;

public:

        Map(int size_map_height, int size_map_width, ShipManager* manager);
void ShipPlacement(int index, int coordinate_x, int coordinate_y, Ship::LocationShip location_ship) ;

   
    bool ShootingBattlefield(int x, int y, std::optional<AbilityResponce*> abilities_status);


    void print(bool myplace);


    // Конструктор копирования
    Map(const Map& other);

    Map& operator=(const Map& other);
        // move constructor and assignment operator
    Map(Map&& other) noexcept;
    
    Map& operator=(Map&& other) noexcept;

    int SizeHeight();
    int SizeWidht();
    Cell& GetCell(int x, int y);
    ShipManager& GetShipManager();

        // Метод для преобразования Cell::MapCells в Map::MapCells
    static MapCells ConvertCellStateToMapState(Cell::MapCells cellState);
    // Метод для преобразования Map::MapCells в Cell::MapCells
    static Cell::MapCells ConvertMapStateToCellState(MapCells mapState);
    // Метод для установки размеров карты
    void SetSize(int height, int width);
    // Метод для получения состояния ячейки
    MapCells GetCellState(int x, int y) const ;
    // Метод для установки состояния ячейки
    void SetCellState(int x, int y, MapCells state);
        // Метод для очистки карты
    void Clear();

};

#endif