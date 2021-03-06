#include <cstdint>
#include <istream>
#include <map>
#include <string>
#include <vector>

#include <utils/log.hh>

#include "cell.hh"
#include "constant.hh"
#include "map.hh"
#include "unit.hh"

Map::Map()
    : map_()
    , height_(0)
    , width_(0)
    , start_position_({0, 0})
    , placement_turns_(0)
    , max_turns_()
{}

Map::Map(const Map& copy_from)
    : map_()
    , paths_(copy_from.paths_)
    , distance_(copy_from.distance_)
    , height_(copy_from.height_)
    , width_(copy_from.width_)
    , start_position_(copy_from.start_position_)
    , placement_turns_(copy_from.placement_turns_)
    , max_turns_(copy_from.max_turns_)
{
    map_.resize(height_);

    for (int y = 0; y < height_; ++y)
    {
        std::vector<Cell*>& cell_line = map_[y];
        cell_line.resize(width_);

        for (int x = 0; x < width_; ++x)
            cell_line[x] = new Cell(*copy_from.map_[y][x]);
    }
}

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
// start_x start_y
// placement_turns
// max_turns
//  x ->
// y MAP DATA
// | MAP DATA
// v
int Map::load(std::istream& s)
{
    INFO("Loading map");
    std::string line;
    int start_x, start_y;

    s >> width_ >> height_;
    INFO("map: width=%d height=%d ", width_, height_);

    s >> start_x >> start_y;
    INFO("map: start: x=%d y=%d", start_x, start_y);
    start_position_ = position{start_x, start_y};

    s >> placement_turns_;
    INFO("map: placement_turns=%d", placement_turns_);

    s >> max_turns_;
    INFO("map: max_turns=%d", max_turns_);

    map_.resize(height_);

    for (int y = 0; y < height_; ++y)
    {
        s >> line;

        if (line.length() != (size_t)width_)
            FATAL("map: line %d is too short or too long (is %d long, should "
                  "be %d)",
                  y + 4, line.length(), width_);

        std::vector<Cell*>& cell_line = map_[y];
        cell_line.resize(width_);

        for (int x = 0; x < width_; ++x)
        {
            static std::map<char, zone_type> type_chars = {
                {'#', ZONE_MUR},    {'_', ZONE_ROUTE}, {'.', ZONE_HERBE},
                {'~', ZONE_MARAIS}, {'F', ZONE_FORET}, {'T', ZONE_TOUR},
            };

            if (type_chars.find(line[x]) == type_chars.end())
                FATAL("Invalid cell at y=%d x=%d", y, x);

            cell_line[x] = new Cell(type_chars[line[x]]);
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

int Map::getPlacementTurns() const
{
    return placement_turns_;
}

int Map::getMaxTurns() const
{
    return max_turns_;
}

position Map::getStartingPos() const
{
    return start_position_;
}

Cell* Map::getCell(position p) const
{
    return map_[p.y][p.x];
}

UnitVect Map::getUnitsOn(position cell) const
{
    return getCell(cell)->getUnits();
}

bool Map::isPositionValid(position p) const
{
    return p.x >= 0 && p.x < width_ && p.y >= 0 && p.y < height_;
}

// XXX: does not change unit.position_
void Map::moveUnit(unit_info unit, position from, position to)
{
    getCell(from)->removeUnit(unit);
    getCell(to)->addUnit(unit);
}

void Map::initializeDistance(position from, position to)
{
    int cost = getCell(from)->getCost();
    int fromId = from.y + from.x * height_;
    int toId = to.y + to.x * height_;

    if (cost < 255)
        (*paths_)[fromId][toId] = fromId;
    (*distance_)[fromId][toId] = cost;
}

// Calculate the all pairs shortest paths using Floyd-Warshall algorithm
// Results are stored in paths_, they represents the previous link table.
// To avoid useless and expensive copy, paths_ is actually a shared pointer
// (the table is (width_ * height_)^2).
// WARNING: the arbitrary value 255 is used as a max because wall currently
// have this weigth.
void Map::calculateShortestPaths()
{
    int size = height_ * width_;
    distance_.reset(
        new std::vector<std::vector<int>>(size, std::vector<int>(size, 255)));
    paths_.reset(
        new std::vector<std::vector<int>>(size, std::vector<int>(size, -1)));

    for (int i = 0; i < size; ++i)
    {
        std::vector<position> xy = {{-1, 0}, {1, 0}, {0, 0}, {0, -1}, {0, 1}};
        position pos{i / height_, i % height_};

        for (position dxdy : xy)
        {
            position p{pos.x + dxdy.x, pos.y + dxdy.y};

            if (!isPositionValid(p))
                continue;
            initializeDistance(pos, p);
        }
    }

    for (int k = 0; k < size; ++k)
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
            {
                int newDistance = (*distance_)[i][k] + (*distance_)[k][j];

                if (newDistance < (*distance_)[i][j])
                {
                    (*distance_)[i][j] = newDistance;
                    (*paths_)[i][j] = k;
                }
            }
}

bool Map::calculatePath(std::vector<position>& path, int fromId, int toId)
{
    int middleId = (*paths_)[toId][fromId];

    if (middleId == fromId || middleId == toId)
        return true;
    if (middleId == -1)
    {
        path.clear();
        return false;
    }
    if (!calculatePath(path, fromId, middleId))
    {
        path.clear();
        return false;
    }
    path.push_back(position{middleId / height_, middleId % height_});
    return calculatePath(path, middleId, toId);
}

// Get the path from 'from' to 'to' using the previous link table calculated by
// the function calculateShortestPaths.
// It would be useless to already store the vector in a table because we return
// it by copy.
std::vector<position> Map::getPath(position from, position to)
{
    std::vector<position> path;

    int fromId = from.y + from.x * height_;
    int toId = to.y + to.x * height_;

    if (fromId == toId)
        return path;

    if (calculatePath(path, fromId, toId))
        path.push_back(to);

    return path;
}

int Map::getDistance(position from, position to)
{
    return (*distance_)[from.y + from.x * height_][to.y + to.x * height_];
}

static inline bool near(int x, int y, position p)
{
    return abs(x - p.x) + abs(y - p.y) <= 1;
}

// North = 1 if North, -1 if South, 0 else.
// East = 1 if East, -1 if West, 0 else
// x and y inverts their role depending on the orientation.
// When isBlocked[j] is true, something prevents us to look in this column.
// When near is true, we are near our position and can see through the forest.
std::vector<position> Map::getVision(position pos, orientation direction,
                                     int range)
{
    if (getCell(pos)->getType() == ZONE_TOUR)
        return getSquareVision(pos, range);

    std::vector<position> visionCone;
    std::vector<bool> isBlocked(2 * range + 3, false);
    int North =
        (direction == ORIENTATION_SUD) - (direction == ORIENTATION_NORD);
    int East =
        (direction == ORIENTATION_EST) - (direction == ORIENTATION_OUEST);

    for (int i = 0; i <= range; ++i)
        for (int j = -(i + 1); j <= (i + 1); ++j)
        {
            int x = pos.x + i * East + j * North;
            int y = pos.y + i * North + j * East;

            if (!isPositionValid(position({x, y})) || isBlocked[j + range + 1])
                continue;

            zone_type zoneType = map_[y][x]->getType();
            if ((!near(x, y, pos) && zoneType == ZONE_FORET) ||
                ((!near(x, y, pos) || i == 1) && zoneType == ZONE_MUR))
                isBlocked[j + range + 1] = true;
            else if (zoneType != ZONE_MUR)
                visionCone.push_back(position({x, y}));
        }
    return visionCone;
}

std::vector<position> Map::getSquareVision(position pos, int range)
{
    std::vector<position> visionSquare;

    for (int i = -range; i <= range; ++i)
        for (int j = -range; j <= range; ++j)
        {
            int x = pos.x + i;
            int y = pos.y + j;

            if (!isPositionValid(position({x, y})))
                continue;
            zone_type zoneType = map_[y][x]->getType();

            if (zoneType != ZONE_MUR && zoneType != ZONE_FORET)
                visionSquare.push_back(position({x, y}));
        }

    return visionSquare;
}

/*
 * @return: a list of units visible from position ``pos``, orientation
 * ``direction`` and range ``range``
 */
std::vector<position> Map::getSurroundings(position pos, orientation direction,
                                           int range)
{
    if (getCell(pos)->getType() == ZONE_TOUR)
        return getSquareSurroundings(pos, range);

    std::vector<position> visionCone = getVision(pos, direction, range);
    std::vector<position> unitsPositions;

    for (auto visionPosition : visionCone)
        if (!getCell(visionPosition)->getUnits().empty())
            unitsPositions.push_back(visionPosition);

    return unitsPositions;
}

std::vector<position>
Map::getNormalSurroundings(position pos, orientation direction, int range)
{
    std::vector<position> visionCone;
    std::vector<bool> isBlocked(2 * range + 3, false);
    int North =
        (direction == ORIENTATION_SUD) - (direction == ORIENTATION_NORD);
    int East =
        (direction == ORIENTATION_EST) - (direction == ORIENTATION_OUEST);

    for (int i = 0; i <= range; ++i)
        for (int j = -(i + 1); j <= (i + 1); ++j)
        {
            int x = pos.x + i * East + j * North;
            int y = pos.y + i * North + j * East;

            if (!isPositionValid(position({x, y})) || isBlocked[j + range + 1])
                continue;

            zone_type zoneType = map_[y][x]->getType();
            if ((!near(x, y, pos) && zoneType == ZONE_FORET) ||
                ((!near(x, y, pos) || i == 1) && zoneType == ZONE_MUR))
                isBlocked[j + range + 1] = true;
            else if (zoneType != ZONE_MUR && !map_[y][x]->getUnits().empty())
                visionCone.push_back(position({x, y}));
        }
    return visionCone;
}

// Check the square of length (2 * range + 1) around pos
// Can see behind a wall or a forest (but not in a forest).
std::vector<position> Map::getSquareSurroundings(position pos, int range)
{
    std::vector<position> unitsPositions;

    for (int i = -range; i <= range; ++i)
        for (int j = -range; j <= range; ++j)
        {
            int x = pos.x + i;
            int y = pos.y + j;

            if (!isPositionValid(position({x, y})))
                continue;
            zone_type zoneType = map_[y][x]->getType();

            if (zoneType != ZONE_MUR && zoneType != ZONE_FORET &&
                !map_[y][x]->getUnits().empty())
                unitsPositions.push_back(position({x, y}));
        }

    return unitsPositions;
}

orientation Map::getOrientation(position p1, position p2)
{
    if (p2.x - p1.x > 0)
        return ORIENTATION_EST;
    if (p2.x - p1.x < 0)
        return ORIENTATION_OUEST;
    if (p2.y - p1.y > 0)
        return ORIENTATION_SUD;
    else
        return ORIENTATION_NORD;
}
