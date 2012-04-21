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
    Cell(int y, int x, int cost,
            int range_bonus, zone_type type)
        : x_(x), y_(y), type_(type), units_(), cost_(cost),
        range_bonus_(range_bonus), corpse_(false)
    {};

    int getCost() const;
    int getRangeBonus() const;
    zone_type getType() const;
    int getPopulation() const;

    void addUnit(Unit_sptr unit);
    int removeUnit(Unit_sptr unit);
    UnitList getUnits() const;

    std::vector<position>* getVision(int vision) const;

    bool isUnitOnCell(Unit_sptr unit) const;

    void setCorpse();
    void resetCorpse();
    bool isCorpse() const;

    DISALLOW_COPY_AND_ASSIGN(Cell);

private:
    int x_;
    int y_;

    zone_type type_;

    UnitList units_;

    int cost_;
    int range_bonus_;

    bool corpse_;
};


class Wall : public Cell
{
public:
    Wall(int y, int x)
        : Cell(y, x, 255, 0, ZONE_MUR)
    {}
};

class Road : public Cell
{
public:
    Road(int y, int x)
        : Cell(y, x, 1, 0, ZONE_ROUTE)
    {}
};

class Grass : public Cell
{
public:
    Grass(int y, int x)
        : Cell(y, x, 2, 0, ZONE_HERBE)
    {}
};

class Swamp : public Cell
{
public:
    Swamp(int y, int x)
        : Cell(y, x, 4, 0, ZONE_MARAIS)
    {}
};

class Forest : public Cell
{
public:
    Forest(int y, int x)
        : Cell(y, x, 2, 0, ZONE_FORET)
    {}
};

class Tower : public Cell
{
public:
    Tower(int y, int x)
        : Cell(y, x, 2, 0, ZONE_TOUR)
    {}
};

#endif // !CELL_HH_
