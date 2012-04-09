#ifndef PROLOGIN2012_API_HH_
# define PROLOGIN2012_API_HH_

/* defines */

# define VOLEUR_VISION          8
# define VOLEUR_DEPLACEMENT     8
# define VOLEUR_VIE             3
# define VOLEUR_ATTAQUE         3
# define VOLEUR_ATT_PORTEE      1
# define VOLEUR_ATT_ZONE        1

# define BARBARE_VISION         8
# define BARBARE_DEPLACEMENT    8
# define BARBARE_VIE            3
# define BARBARE_ATTAQUE        3
# define BARBARE_ATT_PORTEE     1
# define BARBARE_ATT_ZONE       1

# define ELFE_VISION            8
# define ELFE_DEPLACEMENT       8
# define ELFE_VIE               3
# define ELFE_ATTAQUE           3
# define ELFE_ATT_PORTEE        1
# define ELFE_ATT_ZONE          1

/* enums */

enum perso_classe
{
    PERSO_VOLEUR = 0,
    PERSO_BARBARE,
    PERSO_ELFE
};

enum case_type
{
    CASE_HERBE = 0,
    CASE_ROUTE,
    CASE_FORET,
    CASE_MARAIS,
    CASE_MUR,
    CASE_TOUR
};

enum attaque_type
{
    ATTAQUE_NORMALE = 0,
    ATTAQUE_PALANTIR,
    ATTAQUE_DANS_TON_DOS,
    ATTAQUE_BASTON,
    ATTAQUE_FUS_RO_DAH,
    ATTAQUE_I_SEE,
    ATTAQUE_LOTO
};

enum orientation
{
    ORIENTATION_NORD = 0,
    ORIENTATION_EST,
    ORIENTATION_SUD,
    ORIENTATION_OUEST
};

enum erreur
{
    OK = 0,
    POSITION_IMPOSSIBLE,
    PERSONNAGE_IMPOSSIBLE,
    CHEMIN_IMPOSSIBLE,
    ATTAQUE_IMPOSSIBLE
};

/* structs */

struct position
{
    position(int x_, int y_)
        : x(x_),
          y(y_)
    {}

    int x;
    int y;
};

struct perso_info
{
    int equipe;
    perso_classe classe;
    int vie;
    orientation orient;
};

#endif // PROLOGIN2012_API_HH_
