#include "map.hh"

Map::Map(int height, int width)
    : height_(height),
      width_(width)
{
}

Map::Map(const std::string& name)
{
    (void) name;
}
