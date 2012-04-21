#ifndef CELL_HH_
# define CELL_HH_

#include <vector>
#include <cstdint>

#include "constant.hh"
#include "unit.hh"
#include "safety.hh"

class Cell
{
public:
    Cell(uint32_t y, uint32_t x, uint8_t cost,
            uint8_t range_bonus, zone_type type)
        : x_(x), y_(y), type_(type), units_(), cost_(cost),
        range_bonus_(range_bonus)
    {};

    uint8_t getCost() const;
    uint8_t getRangeBonus() const;
    zone_type getType() const;
    uint16_t getPopulation() const;

    void addUnit(Unit* unit);
    int removeUnit(Unit* unit);
    std::vector<Unit*> getUnits() const;

    std::vector<position>* getVision(uint8_t vision) const;

    bool isUnitOnCell(Unit* unit) const;

    DISALLOW_COPY_AND_ASSIGN(Cell);

private:
    uint32_t x_;
    uint32_t y_;

    zone_type type_;

    std::vector<Unit* > units_;

    uint8_t cost_;
    uint8_t range_bonus_;
};


class Wall : public Cell
{
public:
    Wall(uint32_t y, uint32_t x)
        : Cell(y, x, 255, 0, ZONE_MUR)
    {}
};

class Road : public Cell
{
public:
    Road(uint32_t y, uint32_t x)
        : Cell(y, x, 1, 0, ZONE_ROUTE)
    {}
};

class Grass : public Cell
{
public:
    Grass(uint32_t y, uint32_t x)
        : Cell(y, x, 2, 0, ZONE_HERBE)
    {}
};

class Swamp : public Cell
{
public:
    Swamp(uint32_t y, uint32_t x)
        : Cell(y, x, 4, 0, ZONE_MARAIS)
    {}
};

class Forest : public Cell
{
public:
    Forest(uint32_t y, uint32_t x)
        : Cell(y, x, 2, 0, ZONE_FORET)
    {}
};

class Tower : public Cell
{
public:
    Tower(uint32_t y, uint32_t x)
        : Cell(y, x, 2, 0, ZONE_TOUR)
    {}
};

#endif // !CELL_HH_
