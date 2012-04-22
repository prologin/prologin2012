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
    UnitList getUnitsOn(position cell) const;

    // checks
    /*
     * @return if the path is valid
     *  - unit on first cell of the path,
     *  - path is contiguous,
     *  - unit have enought movePoints
     */
    erreur checkMove(Unit_sptr unit, path_t path) const;
    bool isPositionValid(position p) const;

    void moveUnit(Unit_sptr unit, position from, position to);

    /*
     * Calculate all pairs shortest path and store it.
     * MUST be called before any call to the getPath function.
     */
    void calculateShortestPaths();
    /*
     * @return the path from 'from' to 'to'
     */
    std::vector<position> getPath(position from, position to);

protected:
    static Cell* newCell(int y, int x, zone_type type)
    {
        Cell* cell;

        switch (type)
        {
        case ZONE_MUR:
            cell = new Wall(y, x);
            break;
        case ZONE_ROUTE:
            cell = new Road(y, x);
            break;
        case ZONE_HERBE:
            cell = new Grass(y, x);
            break;
        case ZONE_MARAIS:
            cell = new Swamp(y, x);
            break;
        case ZONE_FORET:
            cell = new Forest(y, x);
            break;
        case ZONE_TOUR:
            cell = new Tower(y, x);
            break;
        default:
            FATAL("not in enum");
            break;
        }

        return cell;
    }

private:
    std::vector<std::vector<Cell*>> map_;
    std::shared_ptr<std::vector<std::vector<int>>> paths_;

    int initializeDistance(int from, int to);

    int height_;
    int width_;
    position start_position_;
};

#endif // !MAP_HH_
