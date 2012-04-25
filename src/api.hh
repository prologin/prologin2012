/*
** Stechec project is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** The complete GNU General Public Licence Notice can be found as the
** `NOTICE' file in the root directory.
**
** Copyright (C) 2012 Prologin
*/

#ifndef API_HH_
# define API_HH_

# include <vector>

# include <rules/game-state.hh>
# include <rules/actions.hh>
# include <rules/player.hh>

# include "constant.hh"
# include "game.hh"

class Game;

/*!
** Method of this call are called by the candidat, throught 'interface.cc'
*/
class Api
{
public:
    Api(GameState* game_state, rules::Player_sptr player);
    virtual ~Api() { }

    const rules::Player_sptr player() const
        { return player_; }
    void player_set(rules::Player_sptr player)
        { player_ = player; }

    rules::Actions* actions()
        { return &actions_; }

    const GameState* game_state() const
        { return game_state_; }
    GameState* game_state()
        { return game_state_; }
    void game_state_set(rules::GameState* gs)
        { game_state_ = dynamic_cast<GameState*>(gs); }

private:
    GameState* game_state_;
    rules::Player_sptr player_;
    rules::Actions actions_;

public:

///
// Retourne la taille de la carte sous la forme d'une position correspondant aux coordonnées du point extrême.
//
   position carte_taille();
///
// Retourne la nature de la zone désignée par ``pos``.
//
   zone_type carte_zone_type(position pos);
///
// Retourne la liste des personnages sur la zone.
//
   std::vector<perso_info> carte_zone_perso(position pos);
///
// Renvoie le chemin le plus court entre deux points (fonction lente)
//
   std::vector<position> chemin(position p1, position p2);
///
// Déplace le personnage ``perso`` en suivant un le chemin ``chemin`` donné sous forme d'une suite d'``orientation``, orientant le personnage sur la zone d'arrivée dans la direction ``orientation``.
//
   erreur perso_deplace(perso_info perso, std::vector<position> chemin, orientation direction);
///
// Récupère la liste des zones sur lesquelles des personnages ont été aperçus dans la pénombre par ``perso`` lors de son passage sur une ``zone`` de son déplacement.
//
   std::vector<position> perso_penombre(perso_info perso, position zone);
///
// Récupère la liste des zones sur lesquelles un personnage est passé au tour précédent.
//
   std::vector<position> perso_penombre_zone(perso_info perso);
///
// Récupère la liste des zones sur lesquelles ``perso`` voit d'autre personnages.
//
   std::vector<position> perso_vision(perso_info perso);
///
// Récupère la liste des zones sur lesquelles le palantír du voleur voit d'autre personnages.
//
   std::vector<position> palantir_vision();
///
// Effectue l'attaque ``attaque`` avec le personnage ``perso`` sur la zone ``pos``.
//
   erreur perso_attaque(perso_info perso, attaque_type attaque, position pos);
///
// Retourne le temps de recharge restant pour l'attaque ``attaque`` du personnage ``perso``.
//
   int perso_attaque_recharge(perso_info perso, attaque_type attaque);
///
// Annule l'action précédente. Renvoie ``true`` si une action a été annulée, ``false`` sinon.
//
   bool annuler();
///
// Retourne le numéro de votre équipe
//
   int mon_equipe();
///
// Retourne les scores de chaque équipe
//
   std::vector<int> scores();
///
// Retourne le nombre d'équipes sur le terrain
//
   int nombre_equipes();
///
// Retourne le numéro du tour actuel
//
   int tour_actuel();
///
// Affiche le contenu d'une valeur de type perso_classe
//

///
// Affiche le contenu d'une valeur de type zone_type
//

///
// Affiche le contenu d'une valeur de type attaque_type
//

///
// Affiche le contenu d'une valeur de type orientation
//

///
// Affiche le contenu d'une valeur de type erreur
//

///
// Affiche le contenu d'une valeur de type position
//

///
// Affiche le contenu d'une valeur de type perso_info
//

};


#endif /* !API_HH_ */
