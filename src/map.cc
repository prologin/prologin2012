#include <istream>
#include <vector>
#include <string>
#include <cstdint>

#include <utils/log.hh>

#include "map.hh"
#include "cell.hh"
#include "position.hh"
#include "unit.hh"
#include "erreur.hh"

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
    uint32_t start_x, start_y;

    s >> width_ >> height_;
    INFO("map: width=%d height=%d ", width_, height_);
    s >> player_count_;
    INFO("map: player_count=%d", player_count_);
    s >> start_x >> start_y;
    start_position_ = Position(start_x, start_y);
    INFO("map start: x=%d y=%d", start_x, start_y);

    for (uint32_t y = 0; y < height_; ++y)
    {
        s >> line;

        if (line.length() != width_)
            FATAL("map: line %d is too short (is %d long, should be %d)",
                    y + 4, line.length(), width_);

        std::vector<Cell*>* cell_line = new std::vector<Cell*>();

        for (uint32_t x = 0; x < width_; ++x)
        {
            Cell* cell = NULL;

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

            cell_line->push_back(cell);
        }

        map_.push_back(cell_line);
    }

    return 0;
}

uint32_t Map::getWidth() const
{
    return width_;
}

uint32_t Map::getHeight() const
{
    return height_;
}

Position Map::getStartingPos() const
{
    return start_position_;
}

Cell* Map::getCell(Position p) const
{
    return (*map_[p.y])[p.x];
}

std::vector<Unit*> Map::getUnitsOn(Position cell) const
{
    return getCell(cell)->getUnits();
}

bool Map::isPositionValid(Position p) const
{
    return p.x < width_ && p.y < height_;
}

void Map::moveUnit(Unit* unit, Position from, Position to)
{
     getCell(from)->removeUnit(unit);
     getCell(to)->addUnit(unit);
}

erreur Map::checkMove(Unit* unit, path_t path) const
{
    Position from = path.front();
    Position to = path.back();

    if (!isPositionValid(from) || !isPositionValid(to))
        return POSITION_IMPOSSIBLE;

    if (!getCell(from)->isUnitOnCell(unit))
        return PERSONNAGE_IMPOSSIBLE;

    return OK;
}
