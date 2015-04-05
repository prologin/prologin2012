#ifndef CELL_HH_
# define CELL_HH_

# include <vector>
# include <cstdint>

# include "constant.hh"
# include "unit.hh"

class Cell
{
public:
    Cell(zone_type type);

    // return the cost in movement points to walk on this cell
    int getCost() const;
    zone_type getType() const;
    int getPopulation() const;

    void addUnit(unit_info unit);
    int removeUnit(unit_info unit);
    UnitVect getUnits() const;

    bool isUnitOnCell(unit_info unit) const;

private:
    zone_type type_;

    UnitVect units_;

    int cost_;
};

#endif // !CELL_HH_
