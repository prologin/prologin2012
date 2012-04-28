#include <cstring>
#include <cstdlib>
#include <sstream>

#include <rules/action.hh>
#include <rules/actions.hh>
#include <utils/buffer.hh>

#include "map.hh"
#include "cell.hh"
#include "dumper.hh"

static std::ostream& dump_scores(
    std::ostream& ss, const std::vector<int>& scores
)
{
    ss << "[";
    for (unsigned i = 0; i < scores.size(); ++i)
    {
        ss << scores[i];
        if (i != scores.size() - 1)
            ss << ", ";
    }
    ss << "]";
    return ss;
}

static std::ostream& dump_map(std::ostream& ss, Map& map)
{
    int width = map.getWidth();
    int height = map.getHeight();
    position p;

    ss << "{";
    ss << "\"width\": " << width << ", ";
    ss << "\"height\": " << height << ", ";

    ss << "\"cells\": [";
    for (int y = 0; y < height; ++y)
    {
        p.y = y;
        ss << "[";
        for (int x = 0; x < width; ++x)
        {
            p.x = x;
            Cell& cell = *map.getCell(p);
            ss << cell.getType();
            if (x != width - 1)
                ss << ", ";
        }
        ss << "]";
        if (y != height - 1)
            ss << ", ";
    }
    ss << "]}";
    return ss;
}

static std::ostream& dump_units(std::ostream& ss, const Units &units)
{
    ss << "[";
    for (unsigned i = 0; i < units.size(); ++i)
    {
        const Unit& unit = *units[i];
        ss << "{";
        ss << "\"player\": " << unit.getPlayer() << ", ";
        ss << "\"class\": " << unit.getClasse() << ", ";
        ss << "\"life\": " << unit.getCurrentLife() << ", ";
        ss << "\"life_max\": " << unit.getMaxLife() << ", ";
        ss << "\"x\": " << unit.getPosition().x << ", ";
        ss << "\"y\": " << unit.getPosition().y << ", ";
        ss << "\"direction\": " << unit.getOrientation();
        ss << "}";
        if (i != units.size() - 1)
            ss << ", ";
    }
    ss << "]";
    return ss;
}

static std::ostream& dump_actions(std::ostream& ss, rules::Actions& acts)
{
    utils::Buffer buf;
    acts.handle_buffer(buf);
    ss << "\"";
    for (unsigned i = 0; i < buf.size(); ++i)
        ss << "\\x" << std::hex << buf.data()[i] << std::dec;
    ss << "\"";
    return ss;
}

const char* dump_game_state(const GameState& st, rules::Actions& acts)
{
    std::stringstream ss;

    ss << "{";
    ss << "\"turn\": " << st.getCurrentTurn() << ", ";
    ss << "\"turn_max\": " << st.getMap()->getMaxTurns() << ", ";
    ss << "\"scores\": ";
         dump_scores(ss, st.getScores());
        ss << ", ";
    ss << "\"map\": ";
        dump_map(ss, *st.getMap());
        ss << ", ";
    ss << "\"units\": ";
        dump_units(ss, st.getUnits());
        ss << ", ";
    ss << "\"actions\": ";
        dump_actions(ss, acts);
    ss << "}";

    char* result = new char[ss.str().size() + 1];
    strcpy(result, ss.str().c_str());
    return result;
}
