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
    Cell(int y, int x, zone_type type);

    // return the cost in movement points to walk on this cell
    int getCost() const;
    zone_type getType() const;
    int getPopulation() const;

    void addUnit(unit_info unit);
    int removeUnit(unit_info unit);
    UnitVect getUnits() const;

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

#endif // !CELL_HH_
