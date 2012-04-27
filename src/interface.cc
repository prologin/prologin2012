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

#include "api.hh"

#include <iostream>
#include <sstream>
#include <vector>

// from api.cc
extern Api* api;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& arr)
{
  os << "[";
  typename std::vector<T>::const_iterator it;
  for (it = arr.begin(); it != arr.end(); ++it)
  {
    if (it != arr.begin())
      os << ", ";
    os << *it;
  }
  os << "]";
  return os;
}


// todo avoir un ostringstream a la place de std::string

std::string convert_to_string(int i){
  std::ostringstream s;
  s << i;
  std::string result = s.str();
  return result;
}
std::string convert_to_string(std::string i){
  return i;
}
std::string convert_to_string(bool i){
  return i?"true":"false";
}
std::string convert_to_string(std::vector<int> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(perso_classe in){
  switch (in)
  {
    case PERSO_VOLEUR: return "\"perso_voleur\"";
    case PERSO_BARBARE: return "\"perso_barbare\"";
    case PERSO_ELFE: return "\"perso_elfe\"";
  }
  return "bad value";
}
std::string convert_to_string(std::vector<perso_classe> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(zone_type in){
  switch (in)
  {
    case ZONE_HERBE: return "\"zone_herbe\"";
    case ZONE_ROUTE: return "\"zone_route\"";
    case ZONE_FORET: return "\"zone_foret\"";
    case ZONE_MARAIS: return "\"zone_marais\"";
    case ZONE_MUR: return "\"zone_mur\"";
    case ZONE_TOUR: return "\"zone_tour\"";
    case ZONE_ERREUR: return "\"zone_erreur\"";
  }
  return "bad value";
}
std::string convert_to_string(std::vector<zone_type> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(attaque_type in){
  switch (in)
  {
    case ATTAQUE_NORMALE: return "\"attaque_normale\"";
    case ATTAQUE_PALANTIR: return "\"attaque_palantir\"";
    case ATTAQUE_TRAITRISE: return "\"attaque_traitrise\"";
    case ATTAQUE_BASTOOOON: return "\"attaque_bastoooon\"";
    case ATTAQUE_FUS_RO_DAH: return "\"attaque_fus_ro_dah\"";
    case ATTAQUE_I_SEE: return "\"attaque_i_see\"";
    case ATTAQUE_LOTO: return "\"attaque_loto\"";
  }
  return "bad value";
}
std::string convert_to_string(std::vector<attaque_type> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(orientation in){
  switch (in)
  {
    case ORIENTATION_NORD: return "\"orientation_nord\"";
    case ORIENTATION_EST: return "\"orientation_est\"";
    case ORIENTATION_SUD: return "\"orientation_sud\"";
    case ORIENTATION_OUEST: return "\"orientation_ouest\"";
  }
  return "bad value";
}
std::string convert_to_string(std::vector<orientation> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(erreur in){
  switch (in)
  {
    case POSITION_IMPOSSIBLE: return "\"position_impossible\"";
    case PERSONNAGE_IMPOSSIBLE: return "\"personnage_impossible\"";
    case CHEMIN_IMPOSSIBLE: return "\"chemin_impossible\"";
    case ATTAQUE_INDISPONIBLE: return "\"attaque_indisponible\"";
    case OK: return "\"ok\"";
  }
  return "bad value";
}
std::string convert_to_string(std::vector<erreur> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(position in){
  std::string x = convert_to_string(in.x);
  std::string y = convert_to_string(in.y);
  std::string out = "{";
  out += "x:" + x;
  out += ", ";
  out += "y:" + y;
  return out + "}";
}

std::string convert_to_string(std::vector<position> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(perso_info in){
  std::string equipe = convert_to_string(in.equipe);
  std::string classe = convert_to_string(in.classe);
  std::string vie = convert_to_string(in.vie);
  std::string direction = convert_to_string(in.direction);
  std::string out = "{";
  out += "equipe:" + equipe;
  out += ", ";
  out += "classe:" + classe;
  out += ", ";
  out += "vie:" + vie;
  out += ", ";
  out += "direction:" + direction;
  return out + "}";
}

std::string convert_to_string(std::vector<perso_info> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
///
// Retourne la taille de la carte.
//
extern "C" position api_carte_taille()
{
  return api->carte_taille();
}

///
// Retourne la nature de la zone désignée par ``pos``.
//
extern "C" zone_type api_carte_zone_type(position pos)
{
  return api->carte_zone_type(pos);
}

///
// Retourne la liste des personnages sur la zone.
//
extern "C" std::vector<perso_info> api_carte_zone_perso(position pos)
{
  return api->carte_zone_perso(pos);
}

///
// Renvoie la longueur du chemin le plus court entre deux points. Renvoie -1 en cas de positions invalides ou de chemin inexistant.
//
extern "C" int api_distance(position p1, position p2)
{
  return api->distance(p1, p2);
}

///
// Renvoie le chemin le plus court entre deux points. Si le chemin n'existe pas, ou si les positions sont invalides, le chemin renvoyé est vide.
//
extern "C" std::vector<position> api_chemin(position p1, position p2)
{
  return api->chemin(p1, p2);
}

///
// Déplace le personnage ``perso`` en suivant un le chemin ``chemin`` donné sous forme d'une suite de ``position``, orientant le personnage sur la zone d'arrivée dans la direction ``orientation``.
//
extern "C" erreur api_perso_deplace(perso_info perso, std::vector<position> chemin, orientation direction)
{
  return api->perso_deplace(perso, chemin, direction);
}

///
// Récupère la liste des zones sur lesquelles des personnages ont été aperçus dans la pénombre par ``perso``.
//
extern "C" std::vector<position> api_perso_penombre(perso_info perso)
{
  return api->perso_penombre(perso);
}

///
// Récupère la liste des zones dans le champs de vision de ``perso``.
//
extern "C" std::vector<position> api_perso_vision(perso_info perso)
{
  return api->perso_vision(perso);
}

///
// Récupère la liste des zones dans le champs de vision de ``perso`` où sont situés un ou plusieurs personnages (amis ou ennemis).
//
extern "C" std::vector<position> api_perso_vision_ennemis(perso_info perso)
{
  return api->perso_vision_ennemis(perso);
}

///
// Récupère la liste des positions sur lesquelles le palantír du voleur voit d'autre personnages.
//
extern "C" std::vector<position> api_palantir_vision()
{
  return api->palantir_vision();
}

///
// Récupère la liste des zones sur lesquelles l'elfe peut voir via son attaque "I See What You Did There".
//
extern "C" std::vector<position> api_elfe_vision()
{
  return api->elfe_vision();
}

///
// Effectue l'attaque ``attaque`` avec le personnage ``perso`` sur la zone ``pos``.
//
extern "C" erreur api_perso_attaque(perso_info perso, attaque_type attaque, position pos)
{
  return api->perso_attaque(perso, attaque, pos);
}

///
// Retourne le temps de recharge restant pour l'attaque ``attaque`` du personnage ``perso``.
//
extern "C" int api_perso_attaque_recharge(perso_info perso, attaque_type attaque)
{
  return api->perso_attaque_recharge(perso, attaque);
}

///
// Retourne le numéro de votre équipe
//
extern "C" int api_mon_equipe()
{
  return api->mon_equipe();
}

///
// Retourne les scores de chaque équipe
//
extern "C" std::vector<int> api_scores()
{
  return api->scores();
}

///
// Retourne le nombre d'équipes sur le terrain
//
extern "C" int api_nombre_equipes()
{
  return api->nombre_equipes();
}

///
// Retourne le numéro du tour actuel
//
extern "C" int api_tour_actuel()
{
  return api->tour_actuel();
}

///
// Affiche le contenu d'une valeur de type perso_classe
//
std::ostream& operator<<(std::ostream& os, perso_classe v)
{
  switch (v) {
  case PERSO_VOLEUR: os << "PERSO_VOLEUR"; break;
  case PERSO_BARBARE: os << "PERSO_BARBARE"; break;
  case PERSO_ELFE: os << "PERSO_ELFE"; break;
  }
  return os;
}
extern "C" void api_afficher_perso_classe(perso_classe v)
{
  std::cerr << v << std::endl;
}

///
// Affiche le contenu d'une valeur de type zone_type
//
std::ostream& operator<<(std::ostream& os, zone_type v)
{
  switch (v) {
  case ZONE_HERBE: os << "ZONE_HERBE"; break;
  case ZONE_ROUTE: os << "ZONE_ROUTE"; break;
  case ZONE_FORET: os << "ZONE_FORET"; break;
  case ZONE_MARAIS: os << "ZONE_MARAIS"; break;
  case ZONE_MUR: os << "ZONE_MUR"; break;
  case ZONE_TOUR: os << "ZONE_TOUR"; break;
  case ZONE_ERREUR: os << "ZONE_ERREUR"; break;
  }
  return os;
}
extern "C" void api_afficher_zone_type(zone_type v)
{
  std::cerr << v << std::endl;
}

///
// Affiche le contenu d'une valeur de type attaque_type
//
std::ostream& operator<<(std::ostream& os, attaque_type v)
{
  switch (v) {
  case ATTAQUE_NORMALE: os << "ATTAQUE_NORMALE"; break;
  case ATTAQUE_PALANTIR: os << "ATTAQUE_PALANTIR"; break;
  case ATTAQUE_TRAITRISE: os << "ATTAQUE_TRAITRISE"; break;
  case ATTAQUE_BASTOOOON: os << "ATTAQUE_BASTOOOON"; break;
  case ATTAQUE_FUS_RO_DAH: os << "ATTAQUE_FUS_RO_DAH"; break;
  case ATTAQUE_I_SEE: os << "ATTAQUE_I_SEE"; break;
  case ATTAQUE_LOTO: os << "ATTAQUE_LOTO"; break;
  }
  return os;
}
extern "C" void api_afficher_attaque_type(attaque_type v)
{
  std::cerr << v << std::endl;
}

///
// Affiche le contenu d'une valeur de type orientation
//
std::ostream& operator<<(std::ostream& os, orientation v)
{
  switch (v) {
  case ORIENTATION_NORD: os << "ORIENTATION_NORD"; break;
  case ORIENTATION_EST: os << "ORIENTATION_EST"; break;
  case ORIENTATION_SUD: os << "ORIENTATION_SUD"; break;
  case ORIENTATION_OUEST: os << "ORIENTATION_OUEST"; break;
  }
  return os;
}
extern "C" void api_afficher_orientation(orientation v)
{
  std::cerr << v << std::endl;
}

///
// Affiche le contenu d'une valeur de type erreur
//
std::ostream& operator<<(std::ostream& os, erreur v)
{
  switch (v) {
  case POSITION_IMPOSSIBLE: os << "POSITION_IMPOSSIBLE"; break;
  case PERSONNAGE_IMPOSSIBLE: os << "PERSONNAGE_IMPOSSIBLE"; break;
  case CHEMIN_IMPOSSIBLE: os << "CHEMIN_IMPOSSIBLE"; break;
  case ATTAQUE_INDISPONIBLE: os << "ATTAQUE_INDISPONIBLE"; break;
  case OK: os << "OK"; break;
  }
  return os;
}
extern "C" void api_afficher_erreur(erreur v)
{
  std::cerr << v << std::endl;
}

///
// Affiche le contenu d'une valeur de type position
//
std::ostream& operator<<(std::ostream& os, position v)
{
  os << "{ ";
  os << "x" << "=" << v.x;
  os << ", ";
  os << "y" << "=" << v.y;
  os << " }";
  return os;
}
extern "C" void api_afficher_position(position v)
{
  std::cerr << v << std::endl;
}

///
// Affiche le contenu d'une valeur de type perso_info
//
std::ostream& operator<<(std::ostream& os, perso_info v)
{
  os << "{ ";
  os << "equipe" << "=" << v.equipe;
  os << ", ";
  os << "classe" << "=" << v.classe;
  os << ", ";
  os << "vie" << "=" << v.vie;
  os << ", ";
  os << "direction" << "=" << v.direction;
  os << " }";
  return os;
}
extern "C" void api_afficher_perso_info(perso_info v)
{
  std::cerr << v << std::endl;
}

