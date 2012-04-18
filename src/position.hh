#ifndef POSITION_HH_
# define POSITION_HH_

# include<cstdint>

class Position
{
public:
    Position(uint32_t x, uint32_t y)
        : x(x), y(y)
    {}

    uint32_t x;
    uint32_t y;
};

struct displacement
{
    int32_t dx;
    int32_t dy;
};

typedef struct displacement displacement;

enum orientation {
    NORTH,
    SOUTH,
    EAST,
    WEST,
};

#endif // !POSITION_HH_
