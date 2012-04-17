#include <istream>
#include <vector>
#include <string>
#include <cstdint>

#include <utils/log.hh>

#include "map.hh"
#include "cell.hh"
#include "position.hh"
#include "unit.hh"

Map::~Map()
{
    for (uint32_t y = 0; y < height_; ++y)
    {
        for (uint32_t x = 0; x < width_; ++x)
        {
            // delete cell
            delete (*map_[y])[x];
        }

        // delete row vector
        delete map_[y];
    }
}

// Create a map from an istream
// Format:
// height width
// player_count
// start_x start_y
//  x ->
// y MAP DATA
// | MAP DATA
// v
int Map::load(std::istream& s)
{
    std::string line;

    s >> height_ >> width_;
    s >> player_count_;
    s >> start_x_ >> start_y_;

    for (uint32_t y = 0; y < height_; ++y)
    {
        s >> line;
        CHECK(line.length() == width_);

        for (uint32_t x = 0; x < width_; ++x)
        {
            Cell* cell;

            switch (line[x])
            {
            case '#':
                cell = newCell(y, x, WALL);
                break;
            case '_':
                cell = newCell(y, x, ROAD);
                break;
            case '.':
                cell = newCell(y, x, GRASS);
                break;
            case '~':
                cell = newCell(y, x, SWAMP);
                break;
            case 'F':
                cell = newCell(y, x, FOREST);
                break;
            case 'T':
                cell = newCell(y, x, TOWER);
                break;
            default:
                FATAL("Invalid cell");
                break;
            }

            (*map_[y])[x] = cell;
        }
    }

    return 0;
}

// factory for new cells
// set walking cost, vision and range bonus
Cell* Map::newCell(uint32_t y, uint32_t x, CellType type)
{
    Cell* cell;

    switch (type)
    {
    case WALL:
        cell = new Wall(y, x);
        break;
    case ROAD:
        cell = new Road(y, x);
        break;
    case GRASS:
        cell = new Grass(y, x);
        break;
    case SWAMP:
        cell = new Swamp(y, x);
        break;
    case FOREST:
        cell = new Forest(y, x);
        break;
    case TOWER:
        cell = new Tower(y, x);
        break;
    default:
        FATAL("not in enum");
        break;
    }

    return cell;
}

std::vector<Unit*> Map::getUnitsOn(Position cell) const
{
    return (*map_[cell.y])[cell.x]->getUnits();
}
