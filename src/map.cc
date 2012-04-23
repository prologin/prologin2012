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
    int start_x, start_y;

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

UnitVect Map::getUnitsOn(position cell) const
{
    return getCell(cell)->getUnits();
}

bool Map::isPositionValid(position p) const
{
    return p.x >= 0 && p.x < width_ && p.y >= 0 && p.y < height_;
}

void Map::moveUnit(unit_info unit, position from, position to)
{
     getCell(from)->removeUnit(unit);
     getCell(to)->addUnit(unit);
}

erreur Map::checkMove(unit_info unit, path_t path) const
{
    position from = path.front();
    position to = path.back();

    if (!isPositionValid(from) || !isPositionValid(to))
        return POSITION_IMPOSSIBLE;

    if (!getCell(from)->isUnitOnCell(unit))
        return PERSONNAGE_IMPOSSIBLE;

    return OK;
}

int Map::initializeDistance(int from, int to)
{
  (*paths_)[from][to] = from;
  return map_[from % height_][from / height_]->getCost();
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
  std::vector<std::vector<int>> distance(size, std::vector<int>(size, 255));
  paths_.reset(new std::vector<std::vector<int>>(size, std::vector<int>(size, -1)));

  for (int i = 0; i < size; ++i)
  {
    distance[i][i] = 0;
    if (i / height_ > 0)
      distance[i][i - height_] = initializeDistance(i, i - height_);
    if (i / height_ < width_ - 1)
      distance[i][i + height_] = initializeDistance(i, i + height_);
    if (i % height_ > 0)
      distance[i][i - 1] = initializeDistance(i, i - 1);
    if (i % height_ < height_ - 1)
      distance[i][i + 1] = initializeDistance(i, i + 1);
  }

  for (int k = 0; k < size; ++k)
    for (int i = 0; i < size; ++i)
      for (int j = 0; j < size; ++j)
      {
        int newDistance = distance[i][k] + distance[k][j];

        if (newDistance < distance[i][j])
        {
          distance[i][j] = newDistance;
          (*paths_)[i][j] = k;
        }
      }
}

// Get the path from 'from' to 'to' using the previous link table calculated by
// the function calculateShortestPaths.
// It would be useless to already store the vector in a table because we return
// it by copy.
std::vector<position> Map::getPath(position from, position to)
{
  std::vector<position> path;

  if (!isPositionValid(from) || !isPositionValid(to))
    return path;

  int fromID = from.y + from.x * height_;
  int toID = to.y + to.x * height_;

  while ((*paths_)[toID][fromID] != toID && (*paths_)[toID][fromID] != -1)
  {
    fromID = (*paths_)[toID][fromID];
    path.push_back(position({ fromID / height_, fromID % height_ }));
  }
  path.push_back(to);

  if ((*paths_)[fromID][toID] == -1)
    path.clear();

  return path;
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
std::vector<position> Map::getSurroundings(position pos, orientation direction, int range)
{
  if (getCell(pos)->getType() == ZONE_TOUR)
    return getSurroundingsOnTower(pos, range);

  std::vector<position> unitsPositions;
  std::vector<bool> isBlocked(2 * range + 3, false);
  int North = (direction == ORIENTATION_NORD) - (direction == ORIENTATION_SUD);
  int East = (direction == ORIENTATION_EST) - (direction == ORIENTATION_OUEST);

  for (int i = 0; i <= range; ++i)
    for (int j = -(i + 1); j <= (i + 1); ++j)
    {
      int x = pos.x + i * East + j * North;
      int y = pos.y + i * North + j * East;

      if (!isPositionValid(position({x,y})) || isBlocked[j + i + 1]) continue;

      zone_type zoneType = map_[y][x]->getType();
      if ((!near(x, y, pos) && zoneType == ZONE_FORET) ||
          ((!near(x, y, pos) || i == 1) && zoneType == ZONE_MUR))
        isBlocked[j + i + 1] = true;
      else if (!map_[y][x]->getUnits().empty())
        unitsPositions.push_back(position({x, y}));
    }

  return unitsPositions;
}

// Check the square of length (2 * range + 1) around pos (but not pos).
// Can see behind a wall or a forest (but not in a forest).
std::vector<position> Map::getSurroundingsOnTower(position pos, int range)
{
  std::vector<position> unitsPositions;

  for (int i = -range; i <= range; ++i)
    for (int j = -range; j <= range; ++j)
    {
      int x = pos.x + i;
      int y = pos.y + j;

      if (!isPositionValid(position({x, y}))) continue;
      zone_type zoneType = map_[y][x]->getType();

      if (zoneType != ZONE_MUR && zoneType != ZONE_FORET
          && !map_[y][x]->getUnits().empty())
        unitsPositions.push_back(position({x, y}));
    }

  return unitsPositions;
}
