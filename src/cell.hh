#ifndef CELL_HH_
# define CELL_HH_

#include <vector>
#include <cstdint>

#include "unit.hh"

enum CellType {
    WALL,
    SWAMP,
    ROAD,
    GRASS,
    FOREST,
    TOWER
};

class Cell
{
public:
    Cell(uint32_t y, uint32_t x, uint8_t cost,
            uint8_t range_bonus)
        : x_(x), y_(y), units_(), cost_(cost), range_bonus_(range_bonus)
    {};

    uint8_t getCost() const;
    uint8_t getRangeBonus() const;
    std::vector<Unit*> getUnits() const;

    void addUnit(Unit* unit);
    int removeUnit(Unit* unit);

    uint16_t getPopulation() const;

    std::vector<displacement>* getVision(uint8_t vision) const;

private:
    uint32_t x_;
    uint32_t y_;

    std::vector<Unit* > units_;

    uint8_t cost_;
    uint8_t range_bonus_;
};

class Wall : public Cell
{
public:
    Wall(uint32_t y, uint32_t x)
        : Cell(y, x, 255, 0)
    {}
};

class Road : public Cell
{
public:
    Road(uint32_t y, uint32_t x)
        : Cell(y, x, 1, 0)
    {}
};

class Grass : public Cell
{
public:
    Grass(uint32_t y, uint32_t x)
        : Cell(y, x, 2, 0)
    {}
};

class Swamp : public Cell
{
public:
    Swamp(uint32_t y, uint32_t x)
        : Cell(y, x, 4, 0)
    {}
};

class Forest : public Cell
{
public:
    Forest(uint32_t y, uint32_t x)
        : Cell(y, x, 2, 0)
    {}
};

class Tower : public Cell
{
public:
    Tower(uint32_t y, uint32_t x)
        : Cell(y, x, 2, 0)
    {}
};

#endif // !CELL_HH_
