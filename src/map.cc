#include <istream>
#include <vector>
#include <string>
#include <cstdint>

#include <utils/log.hh>

#include "map.hh"
#include "cell.hh"
#include "unit.hh"
#include "constant.hh"

// TODO
// copy constructor

Map::~Map()
{
    for (int y = 0; y < height_; ++y)
    {
        for (int x = 0; x < width_; ++x)
        {
            // delete cell
            delete map_[y][x];
        }
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
    uint32_t start_x, start_y;

    s >> width_ >> height_;
    INFO("map: width=%d height=%d ", width_, height_);
    s >> start_x >> start_y;
    start_position_ = position {start_x, start_y};
    INFO("map start: x=%d y=%d", start_x, start_y);

    map_.resize(height_);

    for (int y = 0; y < height_; ++y)
    {
        s >> line;

        if (line.length() != (size_t)width_)
            FATAL("map: line %d is too short or too long (is %d long, should be %d)",
                    y + 4, line.length(), width_);

        std::vector<Cell*>& cell_line = map_[y];
        cell_line.resize(width_);

        for (int x = 0; x < width_; ++x)
        {
            Cell* cell;

            switch (line[x])
            {
            case '#':
                cell = newCell(y, x, ZONE_MUR);
                break;
            case '_':
                cell = newCell(y, x, ZONE_ROUTE);
                break;
            case '.':
                cell = newCell(y, x, ZONE_HERBE);
                break;
            case '~':
                cell = newCell(y, x, ZONE_MARAIS);
                break;
            case 'F':
                cell = newCell(y, x, ZONE_FORET);
                break;
            case 'T':
                cell = newCell(y, x, ZONE_TOUR);
                break;
            default:
                FATAL("Invalid cell");
                break;
            }

            cell_line[x] = cell;
        }
    }

    return 0;
}

int Map::getWidth() const
{
    return width_;
}

int Map::getHeight() const
{
    return height_;
}

position Map::getStartingPos() const
{
    return start_position_;
}

Cell* Map::getCell(position p) const
{
    return map_[p.y][p.x];
}

std::vector<Unit*> Map::getUnitsOn(position cell) const
{
    return getCell(cell)->getUnits();
}

bool Map::isPositionValid(position p) const
{
    return p.x < width_ && p.y < height_;
}

void Map::moveUnit(Unit* unit, position from, position to)
{
     getCell(from)->removeUnit(unit);
     getCell(to)->addUnit(unit);
}

erreur Map::checkMove(Unit* unit, path_t path) const
{
    position from = path.front();
    position to = path.back();

    if (!isPositionValid(from) || !isPositionValid(to))
        return POSITION_IMPOSSIBLE;

    if (!getCell(from)->isUnitOnCell(unit))
        return PERSONNAGE_IMPOSSIBLE;

    return OK;
}
