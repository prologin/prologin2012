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
#include <algorithm>

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

Api::Api(GameState* game_state, rules::Player_sptr player,int equipe)
    : game_state_(game_state),
      player_(player),
      equipe_(equipe)
{
  api = this;
}

///
// Retourne la taille de la carte.
//
position Api::carte_taille()
{
    Map* map = game_state_->getMap();
    return position {map->getWidth(), map->getHeight()};
}

///
// Retourne la position de départ des personnages sur la map.
//
position Api::carte_depart()
{
    return game_state_->getMap()->getStartingPos();
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
    bool ok = false;

    // invalid position, return something considered null
    if (!map->isPositionValid(pos))
        return std::vector<perso_info>();
    for (Unit_sptr unit : game_state_->getUnits())
        if (unit->getPlayer() == equipe_ &&
                unit->isPositionInVision(map, pos))
            ok = true;

    if (game_state_->isPalantirActivated(equipe_))
    {
        position palantir = game_state_->getPalantir(equipe_);

        auto square = map->getSquareVision(palantir, VOLEUR_VISION);
        if (std::find(square.begin(), square.end(), pos) != square.end())
            ok = true;
    }

    if (game_state_->isElfeVisionActivated(equipe_))
    {
        position elfe_vision = game_state_->getElfeVision(equipe_);

        auto square = map->getSquareVision(elfe_vision, ELFE_VISION);
        if (std::find(square.begin(), square.end(), pos) != square.end())
            ok = true;
    }

    if (!ok)
        return std::vector<perso_info>();

    UnitVect units = map->getUnitsOn(pos);

    std::vector<perso_info> persos;
    for (auto unitInfo : units)
    {
        Unit_sptr unit = game_state_->getUnit(unitInfo);

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
// Renvoie la longueur du chemin le plus court entre deux points
//
int Api::distance(position p1, position p2)
{
    Map* map = game_state_->getMap();

    if (!map->isPositionValid(p1) || !map->isPositionValid(p2))
        return -1;

    int distance = map->getDistance(p1, p2);

    return (distance < 255) ? distance : -1;
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
// Déplace le personnage ``perso`` en suivant un le chemin ``chemin`` donné sous forme d'une suite de ``position``, orientant le personnage sur la zone d'arrivée dans la direction ``orientation``.
//
erreur Api::perso_deplace(perso_info perso, std::vector<position> chemin, orientation direction)
{
    if (game_state_->getPhase() == PHASE_ATTAQUE)
      return CHEMIN_IMPOSSIBLE;

    if (perso.equipe != mon_equipe() || perso.classe < 0 || perso.classe > 2)
      return PERSONNAGE_IMPOSSIBLE;

    for (auto action : actions_.actions())
    {
        perso_info persoInfo = dynamic_cast<const ActionMove*>(action.get())->getPersoInfo();
        if (persoInfo.equipe == perso.equipe && persoInfo.classe == perso.classe)
            return PERSONNAGE_IMPOSSIBLE;
    }

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
std::vector<position> Api::perso_penombre(perso_info perso)
{
    if (perso.equipe != mon_equipe() || perso.classe < 0 || perso.classe > 2)
        return std::vector<position>();

    return game_state_->getUnit(perso)->getPenombre();
}

///
// Récupère la liste des zones dans le champs de vision de ``perso``.
//
std::vector<position> Api::perso_vision(perso_info perso)
{
    // Error, you cannot see what the other team sees
    if (perso.equipe != mon_equipe() || perso.classe < 0 || perso.classe > 2)
        return std::vector<position>();

    Unit_sptr unit = game_state_->getUnit(perso);
    position unit_pos = unit->getPosition();

    return game_state_->getMap()->getVision(unit_pos,
            unit->getOrientation(), unit->getVision());
}

///
// Récupère la liste des zones sur lesquelles ``perso`` voit d'autre personnages.
//
std::vector<position> Api::perso_vision_personnages(perso_info perso)
{
    // Error, you cannot see what the other team sees
    if (perso.equipe != mon_equipe() || perso.classe < 0 || perso.classe > 2)
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
    if (!game_state_->isPalantirActivated(mon_equipe()))
        return std::vector<position>();

    return game_state_->getMap()->getSquareSurroundings(game_state_->getPalantir(mon_equipe()), VOLEUR_VISION);
}

///
// Récupère la liste des zones sur lesquelles l'elfe peut voir via son attaque "I See What You Did There".
//
std::vector<position> Api::elfe_vision()
{
    if (!game_state_->isElfeVisionActivated(mon_equipe()))
        return std::vector<position>();

    return game_state_->getMap()->getSquareSurroundings(game_state_->getElfeVision(mon_equipe()), ELFE_VISION);
}

///
// Effectue l'attaque ``attaque`` avec le personnage ``perso`` sur la zone ``pos``.
//
erreur Api::perso_attaque(perso_info perso, attaque_type attaque, position pos)
{
    if (game_state_->getPhase() != PHASE_ATTAQUE)
      return ATTAQUE_INDISPONIBLE;

    if (perso.equipe != mon_equipe() || perso.classe < 0 || perso.classe > 2)
      return PERSONNAGE_IMPOSSIBLE;

    for (auto action : actions_.actions())
    {
        perso_info persoInfo = dynamic_cast<const ActionAttack*>(action.get())->getPersoInfo();
        if (persoInfo.equipe == perso.equipe && persoInfo.classe == perso.classe)
            return PERSONNAGE_IMPOSSIBLE;
    }


    rules::IAction_sptr action(new ActionAttack(perso, attaque, pos, player_->id));

    erreur err;

    if ((err = static_cast<erreur>(action->check(game_state_))) != OK)
        return err;

    game_state_ = dynamic_cast<GameState*>(action->apply(game_state_));
    actions_.add(action);

    return OK;
}

///
// Retourne le temps de recharge restant pour l'attaque ``attaque`` du personnage ``perso``.
//
int Api::perso_attaque_recharge(perso_info perso, attaque_type attaque)
{
    if (perso.equipe != mon_equipe() || perso.classe < 0 || perso.classe > 2)
      return -1;

    return game_state_->getUnit(perso)->getAbilityCooldown(attaque);
}

///
// Retourne la position du personnage ``perso``.
//
position Api::perso_position(perso_info perso)
{
    if (perso.equipe != mon_equipe() || perso.classe < 0 || perso.classe > 2)
      return {-1, -1};

    return game_state_->getUnit(perso)->getPosition();
}

///
// Retourne le personnage de type ``classe`` de sa propre équipe.
//
perso_info Api::perso_classe_info(perso_classe classe)
{
    if (classe < 0 || classe > 2)
        return { -1, PERSO_VOLEUR, -1, ORIENTATION_NORD};

    auto unit = game_state_->getUnit(unit_info {equipe_, classe});

    return { equipe_, classe, unit->getCurrentLife(), unit->getOrientation()};
}

///
// Retourne le numéro de votre équipe
//
int Api::mon_equipe()
{
    return equipe_;
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

///
// Retourne le nombre de tours de placements
//
int Api::nombre_tours_placement()
{
    return game_state_->getMap()->getPlacementTurns();
}

///
// Retourne le nombre total de tours
//
int Api::nombre_tours()
{
    return game_state_->getMap()->getMaxTurns();
}

///
// Return un dump JSON de l'état complet du jeu.
//
const char* Api::get_dump()
{
    if (player_->type == rules::SPECTATOR)
        return dump_game_state(*game_state_, actions_);
    else
        return nullptr;
}
