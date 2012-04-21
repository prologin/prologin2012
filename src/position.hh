#ifndef POSITION_HH_
# define POSITION_HH_

# include<cstdint>

class Position
{
public:
    Position(int x, int y)
        : x(x), y(y)
    {}

    int x;
    int y;
};

typedef struct displacement
{
    int dx;
    int dy;
} displacement;

typedef std::vector<Position> path_t;

#endif // !POSITION_HH_
