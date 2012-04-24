#ifndef MAP_HH_
# define MAP_HH_

# include <istream>
# include <utility>
# include <vector>
# include <cstdint>
# include <memory>

# include <utils/log.hh>

# include "cell.hh"
# include "constant.hh"

inline bool operator==(const position& a, const position& b)
{
    return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const position& a, const position& b)
{
    return !(a == b);
}

typedef std::vector<position> path_t;

class Map
{
public:
    Map()
        : map_(), start_position_({0, 0})
    {}

    Map(const Map& copy_from);

    ~Map();

    int load(std::istream& s);

    int getWidth() const;
    int getHeight() const;

    /*
     * @return where all unit starts on turn 0
     */
    position getStartingPos() const;

    Cell* getCell(position p) const;
    UnitVect getUnitsOn(position cell) const;

    // checks
    /*
     * @return if the path is valid
     *  - unit on first cell of the path,
     *  - path is contiguous,
     *  - unit have enought movePoints
     */
    erreur checkMove(unit_info unit, path_t path) const;
    bool isPositionValid(position p) const;

    void moveUnit(unit_info unit, position from, position to);

    /*
     * Calculate all pairs shortest path and store it.
     * MUST be called before any call to the getPath function.
     */
    void calculateShortestPaths();
    /*
     * @return the path from 'from' to 'to'
     */
    std::vector<position> getPath(position from, position to);

    /*
     * @return the positions where units could be seen
     */
    std::vector<position> getSurroundings(position pos, orientation direction, int range);

private:
    std::vector<std::vector<Cell*>> map_;
    std::shared_ptr<std::vector<std::vector<int>>> paths_;

    std::vector<position> getSurroundingsOnTower(position pos, int range);
    int initializeDistance(int from, int to);

    int height_;
    int width_;
    position start_position_;
};

#endif // !MAP_HH_
