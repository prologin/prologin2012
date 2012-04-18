#ifndef MAP_HH_
# define MAP_HH_

# include <istream>
# include <utility>
# include <vector>
# include <cstdint>

# include <utils/log.hh>

# include "cell.hh"
# include "position.hh"
# include "erreur.hh"

typedef std::vector<Position> path_t;

class Map
{
public:
    Map()
        : map_(), start_position_(0, 0)
    {};

    ~Map();

    int load(std::istream& s);

    uint32_t getWidth() const;
    uint32_t getHeight() const;

    /*
     * @return where all unit starts
     */
    Position getStartingPos() const;

    Cell* getCell(Position p) const;
    std::vector<Unit*> getUnitsOn(Position cell) const;

    bool isPositionValid(Position p) const;

    void moveUnit(Unit* unit, Position from, Position to);

    // checks
    /*
     * @return if the path is valid
     *  - unit on first cell of the path,
     *  - path is contiguous,
     *  - unit have enought movePoints
     */
    erreur checkMove(Unit* unit, path_t path) const;

protected:
    static Cell* newCell(uint32_t y, uint32_t x, CellType type)
    {
        Cell* cell;

        switch (type)
        {
        case WALL:
            cell = new Wall(y, x);
            break;
        case ROAD:
            cell = new Road(y, x);
            break;
        case GRASS:
            cell = new Grass(y, x);
            break;
        case SWAMP:
            cell = new Swamp(y, x);
            break;
        case FOREST:
            cell = new Forest(y, x);
            break;
        case TOWER:
            cell = new Tower(y, x);
            break;
        default:
            FATAL("not in enum");
            break;
        }

        return cell;
    }

private:
    std::vector< std::vector<Cell* >* > map_;

    uint32_t height_;
    uint32_t width_;
    uint8_t player_count_;
    Position start_position_;
};

#endif // !MAP_HH_
