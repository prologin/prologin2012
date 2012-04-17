#include <sstream>

#include <gtest/gtest.h>

#include "../unit.hh"
#include "../map.hh"

TEST(Map, MapCreateFromFile) {
    std::stringstream f;
    f << "10 10\n";
    f << "4 4\n";
    f << "##########\n";
    f << "#FFF_....#\n";
    f << "#FFF_..T.#\n";
    f << "#FFF_....#\n";
    f << "#________#\n";
    f << "#..._....#\n";
    f << "#~~~_....#\n";
    f << "#~T~_....#\n";
    f << "#~~~_....#\n";
    f << "##########\n";

    Map map;
    map.load(f);
}
