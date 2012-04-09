#ifndef PROLOGIN2012_MAP_HH_
# define PROLOGIN2012_MAP_HH_

# include <string>

# include "square.hh"

class Map
{
public:
    Map(int height, int width);
    Map(const std::string& name);

private:
    int height_;
    int width_;
};

#endif // PROLOGIN2012_MAP_HH_
