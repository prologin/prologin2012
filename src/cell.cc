#include <vector>

#include <utils/log.hh>

#include "position.hh"
#include "cell.hh"

// Return the cost of walking on this cell
uint8_t  Cell::getCost() const
{
    return cost_;
}

// Return the range bonus given to the units on this cell
uint8_t Cell::getRangeBonus() const
{
    return range_bonus_;
}

std::vector<Unit*> Cell::getUnits() const
{
    return units_;
}

// Add unit in this cell
void Cell::addUnit(Unit* unit)
{
    units_.push_back(unit);
}

// Remove unit from this cell
// return: 1 if not found
int Cell::removeUnit(Unit* unit)
{
    auto it = units_.begin();

    // find it or get to the end of the vector
    while (it != units_.end() && unit != *it)
        ++it;

    // not found
    if (it == units_.end())
    {
        ERR("No such unit in this cell");
        return 1;
    }

    units_.erase(it);
    return 0;
}

uint16_t Cell::getPopulation() const
{
    return units_.size();
}

std::vector<displacement>* Cell::getVision(uint8_t vision) const
{
    // TODO
    return new std::vector<displacement> {{1, 0}, {-1, 0}};
}
