#ifndef CELL_HH_
# define CELL_HH_

# include <vector>
# include <cstdint>

# include "constant.hh"
# include "safety.hh"
# include "unit.hh"

class Cell
{
public:
    Cell(int y, int x, int cost, zone_type type)
        : x_(x), y_(y), type_(type), units_(), cost_(cost), corpse_(false)
    {};

    // return the cost in movement points to walk on this cell
    int getCost() const;
    zone_type getType() const;
    int getPopulation() const;

    void addUnit(unit_info unit);
    int removeUnit(unit_info unit);
    UnitVect getUnits() const;

    std::vector<position> getVision(int vision) const;

    bool isUnitOnCell(unit_info unit) const;

    // corpse stuff, must be reset after each turn, before
    // GameState::attackResolve
    void setCorpse();
    void resetCorpse();
    bool isCorpse() const;

    DISALLOW_COPY_AND_ASSIGN(Cell);

private:
    int x_;
    int y_;

    zone_type type_;

    UnitVect units_;

    int cost_;

    bool corpse_;
};


class Wall : public Cell
{
public:
    Wall(int y, int x)
        : Cell(y, x, 255, ZONE_MUR)
    {}
};

class Road : public Cell
{
public:
    Road(int y, int x)
        : Cell(y, x, 1, ZONE_ROUTE)
    {}
};

class Grass : public Cell
{
public:
    Grass(int y, int x)
        : Cell(y, x, 2, ZONE_HERBE)
    {}
};

class Swamp : public Cell
{
public:
    Swamp(int y, int x)
        : Cell(y, x, 4, ZONE_MARAIS)
    {}
};

class Forest : public Cell
{
public:
    Forest(int y, int x)
        : Cell(y, x, 2, ZONE_FORET)
    {}
};

class Tower : public Cell
{
public:
    Tower(int y, int x)
        : Cell(y, x, 2, ZONE_TOUR)
    {}
};

#endif // !CELL_HH_
