#ifndef PROLOGIN2012_SQUARE_HH_
# define PROLOGIN2012_SQUARE_HH_

# include <list>

# include "api.hh"

struct Square
{
public:
    Square(case_type type);

    case_type type() const
    { return type_; }

    int corpses()
    { return corpses_; }

private:
    case_type type_;
    int corpses_;
    std::list<perso_info> players_;
};

#endif // PROLOGIN2012_SQUARE_HH_
