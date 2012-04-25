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

#include <stdlib.h>

#include <rules/game-state.hh>
#include <rules/player.hh>

#include "api.hh"
#include "constant.hh"

#include "game.hh"
#include "map.hh"
#include "cell.hh"

#include "action-move.hh"
#include "action-attack.hh"

// global used in interface.cc
Api* api;

Api::Api(GameState* game_state, rules::Player_sptr player)
    : game_state_(game_state),
      player_(player)
{
  api = this;
}

// FIXME: Y U NO DTOR?

///
// Retourne la taille de la carte sous la forme d'une position correspondant aux coordonnées du point extrême.
// XXX: ÇA NE CORRESPOND PAS VRAIMENT À LA DÉFINITION D'UNE TAILLE
//
position Api::carte_taille()
{
    Map* map = game_state_->getMap();
    return position {map->getWidth(), map->getHeight()};
}

///
// Retourne la nature de la zone désignée par ``pos``.
//
zone_type Api::carte_zone_type(position pos)
{
    Map* map = game_state_->getMap();
    if (!map->isPositionValid(pos))
        return ZONE_ERREUR;

    return map->getCell(pos)->getType();
}

// Retourne la liste des personnages sur la zone.
//
std::vector<perso_info> Api::carte_zone_perso(position pos)
{
    Map* map = game_state_->getMap();

    // invalid position, return something considered null
    if (!map->isPositionValid(pos))
        return std::vector<perso_info>();

    UnitVect units = map->getUnitsOn(pos);

    std::vector<perso_info> persos;
    for (auto it  = units.begin(); it != units.end(); ++it)
    {
        Unit_sptr unit = game_state_->getUnit(*it);

        persos.push_back(perso_info {
                .equipe = unit->getPlayer(),
                .classe = unit->getClasse(),
                .vie = unit->getCurrentLife(),
                .direction = unit->getOrientation(),
                });
    }

    return persos;
}

///
// Renvoie le chemin le plus court entre deux points (fonction pas lente)
//
std::vector<position> Api::chemin(position p1, position p2)
{
    Map* map = game_state_->getMap();

    if (!map->isPositionValid(p1) || !map->isPositionValid(p2))
        return std::vector<position>();

    return map->getPath(p1, p2);
}

///
// Déplace le personnage ``perso`` en suivant un le chemin ``chemin`` donné sous forme d'une suite d'``orientation``, orientant le personnage sur la zone d'arrivée dans la direction ``orientation``.
//
erreur Api::perso_deplace(perso_info perso, std::vector<position> chemin, orientation direction)
{
    if (game_state_->getPhase() == PHASE_ATTAQUE)
      return CHEMIN_IMPOSSIBLE;

    if ((unsigned int)perso.equipe != player_->id || perso.classe < 0 || perso.classe > 2)
      return PERSONNAGE_IMPOSSIBLE;

    rules::IAction_sptr move(new ActionMove(perso, chemin, direction,
                player_->id));

    erreur err;

    if ((err = static_cast<erreur>(move->check(game_state_))) != OK)
        return err;

    game_state_ = dynamic_cast<GameState*>(move->apply(game_state_));
    actions_.add(move);

    return OK;
}

///
// Récupère la liste des zones sur lesquelles un personnage est passé au tour précédent.
//
std::vector<position> Api::perso_penombre_zone(perso_info perso)
{
    if ((unsigned int)perso.equipe != player_->id || perso.classe < 0 || perso.classe > 2)
        return std::vector<position>();

    return game_state_->getUnit(perso)->getPenombre();
}

///
// Récupère la liste des zones sur lesquelles ``perso`` voit d'autre personnages.
//
std::vector<position> Api::perso_vision(perso_info perso)
{
    // Error, you cannot see what the other team sees
    if ((unsigned int)perso.equipe != player_->id || perso.classe < 0 || perso.classe > 2)
        return std::vector<position>();

    Unit_sptr unit = game_state_->getUnit(perso);
    position unit_pos = unit->getPosition();

    return game_state_->getMap()->getSurroundings(unit_pos,
            unit->getOrientation(), unit->getVision());
}

///
// Récupère la liste des zones sur lesquelles le palantír du voleur voit d'autre personnages.
//
std::vector<position> Api::palantir_vision()
{
    // TODO test
    palantir_t palantir = game_state_->getPalantir(player_->id);

    if (!palantir.activated)
        return std::vector<position>();

    return game_state_->getMap()->getSquareSurroundings(palantir.location, VOLEUR_VISION);
}

///
// Effectue l'attaque ``attaque`` avec le personnage ``perso`` sur la zone ``pos``.
//
erreur Api::perso_attaque(perso_info perso, attaque_type attaque, position pos)
{
    if (game_state_->getPhase() != PHASE_ATTAQUE)
      return ATTAQUE_INDISPONIBLE;

    if ((unsigned int)perso.equipe != player_->id || perso.classe < 0 || perso.classe > 2)
      return PERSONNAGE_IMPOSSIBLE;

    rules::IAction_sptr action(new ActionAttack(perso, attaque, pos,
                player_->id));

    erreur err;

    if ((err = static_cast<erreur>(action->check(game_state_))) != OK)
        return err;

    game_state_ = dynamic_cast<GameState*>(action->apply(game_state_));
    actions_.add(action);

    // TODO More tests
    return OK;
}

///
// Retourne le temps de recharge restant pour l'attaque ``attaque`` du personnage ``perso``.
//
int Api::perso_attaque_recharge(perso_info perso, attaque_type attaque)
{
    if ((unsigned int)perso.equipe != player_->id || perso.classe < 0 || perso.classe > 2)
      return -1;

    // TODO test + getAbilityCooldown for ELFE and BARBARE
    return game_state_->getUnit(perso)->getAbilityCooldown(attaque);
}

///
// Retourne le numéro de votre équipe
//
int Api::mon_equipe()
{
    return player_->id;
}

///
// Retourne les scores de chaque équipe
//
std::vector<int> Api::scores()
{
    return game_state_->getScores();
}

///
// Retourne le nombre d'équipes sur le terrain
//
int Api::nombre_equipes()
{
    return game_state_->getPlayerCount();
}

///
// Retourne le numéro du tour actuel
//
int Api::tour_actuel()
{
    return game_state_->getCurrentTurn();
}

