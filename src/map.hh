#ifndef MAP_HH_
# define MAP_HH_

# include <istream>
# include <utility>
# include <vector>
# include <cstdint>
# include <memory>

# include <utils/log.hh>

# include "constant.hh"
# include "unit.hh"

class Cell;

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
    Map();

    //Map(const Map& copy_from);

    ~Map();

    int load(std::istream& s);

    int getWidth() const;
    int getHeight() const;

    int getPlacementTurns() const;
    int getMaxTurns() const;

    /*
     * @return Where all unit starts on turn 0
     */
    position getStartingPos() const;

    /*
     * @return Cell from ``position``
     */
    Cell* getCell(position p) const;

    /*
     * @return Units on cell position
     */
    UnitVect getUnitsOn(position cell) const;

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
     * @return the cost to go from 'from' to 'to'
     */
    int getDistance(position from, position to);

    /*
     * @return the positions visible from pos
     */
    std::vector<position> getVision(position pos, orientation direction, int range);
    std::vector<position> getSquareVision(position pos, int range);
    /*
     * @return the positions where units could be seen
     */
    std::vector<position> getSurroundings(position pos, orientation direction, int range);
    std::vector<position> getNormalSurroundings(position pos, orientation direction, int range);
    std::vector<position> getSquareSurroundings(position pos, int range);

    static orientation getOrientation(position p1, position p2);

private:
    void initializeDistance(int from, int to);

private:
    std::vector<std::vector<Cell*>> map_;
    std::shared_ptr<std::vector<std::vector<int>>> paths_;
    std::shared_ptr<std::vector<std::vector<int>>> distance_;

    int height_;
    int width_;
    position start_position_;
    int placement_turns_;
    int max_turns_;
};

#endif // !MAP_HH_
