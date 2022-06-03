#include "api.hh"

#include <algorithm>
#include <array>

position target;

/// Fonction appellée au début de la partie
void partie_init()
{
    int team = mon_equipe();
    auto mapSize = carte_taille();
    if (team == 0)
        target = {.x = 1, .y = mapSize.y - 2};
    else
        target = {.x = mapSize.x - 2, .y = 1};
}

/// Fonction appellée pendant la phase de placement
void jouer_placement()
{
    // TODO
}

/// Fonction appellée pendant la phase de déplacement
void jouer_deplacement()
{
    for (auto classe : {PERSO_VOLEUR, PERSO_BARBARE, PERSO_ELFE})
    {
        auto info = perso_classe_info(classe);
        auto pos = perso_position(info);
        auto positions = chemin(pos, target);
        std::vector<position> go;
        if (!positions.empty())
            go.emplace_back(positions[0]);
        perso_deplace(info, go, ORIENTATION_NORD);
    }
}

/// Fonction appellée pendant la phase d'attaque
void jouer_attaque()
{
    // TODO
}

/// Fonction appellée à la fin de la partie
void partie_fin()
{
    // TODO
}
