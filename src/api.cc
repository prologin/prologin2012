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

#include "Api.hh"

// global used in interface.cc
Api* api;

Api::Api(GameState* game_state, Player* player)
    : game_state_(game_state),
      player_(player)
{
  api = this;
}

///
// Retourne la taille de la carte sous la forme d'une position correspondant aux coordonnées du point extrême.
//
position Api::carte_taille()
{
  // TODO
  abort();
}

///
// Retourne la nature de la zone désignée par ``pos``.
//
zone_type Api::carte_zone_type(position pos)
{
  // TODO
  abort();
}

///
// Retourne ``true`` si un cadavre se trouve sur la zone ``pos``.
//
bool Api::carte_zone_cadavre(position pos)
{
  // TODO
  abort();
}

///
// Retourne la liste des personnages sur la zone.
//
std::vector<perso_info> Api::carte_zone_perso(position pos)
{
  // TODO
  abort();
}

///
// Renvoie le chemin le plus court entre deux points (fonction lente)
//
std::vector<position> Api::chemin(position p1, position p2)
{
  // TODO
  abort();
}

///
// Déplace le personnage ``perso`` en suivant un le chemin ``chemin`` donné sous forme d'une suite d'``orientation``, orientant le personnage sur la zone d'arrivée dans la direction ``orientation``.
//
erreur Api::perso_deplace(perso_info perso, std::vector<orientation> chemin, orientation direction)
{
  // TODO
  abort();
}

///
// Récupère la liste des zones sur lesquelles des personnages ont été aperçus dans la pénombre par ``perso`` lors de son passage sur une ``zone`` de son déplacement.
//
std::vector<position> Api::perso_penombre(perso_info perso, position zone)
{
  // TODO
  abort();
}

///
// Récupère la liste des zones sur lesquelles un personnage est passé au tour précédent.
//
std::vector<position> Api::perso_penombre_zone(perso_info perso)
{
  // TODO
  abort();
}

///
// Récupère la liste des zones sur lesquelles ``perso`` voit d'autre personnages.
//
std::vector<position> Api::perso_vision(perso_info perso)
{
  // TODO
  abort();
}

///
// Effectue l'attaque ``attaque`` avec le personnage ``perso`` sur la zone ``pos``.
//
erreur Api::perso_attaque(perso_info perso, attaque_type attaque, position pos)
{
  // TODO
  abort();
}

///
// Retourne le temps de recharge restant pour l'attaque ``attaque`` du personnage ``perso``.
//
int Api::perso_attaque_recharge(perso_info perso, attaque_type attaque)
{
  // TODO
  abort();
}

///
// Annule l'action précédente. Renvoie ``true`` si une action a été annulée, ``false`` sinon.
//
bool Api::annuler()
{
  // TODO
  abort();
}

///
// Retourne le numéro de votre équipe
//
int Api::mon_equipe()
{
  // TODO
  abort();
}

///
// Retourne les scores de chaque équipe
//
std::vector<int> Api::scores()
{
  // TODO
  abort();
}

///
// Retourne le nombre d'équipes sur le terrain
//
int Api::nombre_equipes()
{
  // TODO
  abort();
}

///
// Retourne le numéro du tour actuel
//
int Api::tour_actuel()
{
  // TODO
  abort();
}

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

