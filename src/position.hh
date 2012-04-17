#ifndef POSITION_HH_
# define POSITION_HH_

# include<cstdint>

class Position
{
public:
    Position(uint32_t y, uint32_t x)
        : y(y), x(x)
    {}

    uint32_t y;
    uint32_t x;
};

struct displacement
{
    int32_t dy;
    int32_t dx;
};

typedef struct displacement displacement;

#endif // !POSITION_HH_
