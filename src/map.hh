#ifndef MAP_HH_
# define MAP_HH_

# include <istream>
# include <utility>
# include <vector>
# include <cstdint>

# include "cell.hh"

class Map
{
public:
    Map() : map_()
    {};

    ~Map();

    int load(std::istream& s);
    Cell* newCell(uint32_t y, uint32_t x, CellType type);

    // utility
    std::vector<Unit*> getUnitsOn(Position cell) const;

private:
    std::vector< std::vector<Cell* >* > map_;
    uint32_t height_;
    uint32_t width_;
    uint8_t player_count_;
    uint32_t start_x_;
    uint32_t start_y_;
};

#endif // !MAP_HH_
