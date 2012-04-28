///
// This file has been generated, if you wish to
// modify it in a permanent way, please refer
// to the script file : gen/generator_python.rb
//

#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <Python.h>
# include <vector>
# include <string>

///
// Type de personnage
//
typedef enum perso_classe {
  PERSO_VOLEUR, /* <- Voleur */
  PERSO_BARBARE, /* <- Barbare */
  PERSO_ELFE, /* <- Elfe */
} perso_classe;


///
// Type de zone
//
typedef enum zone_type {
  ZONE_HERBE, /* <- Herbe */
  ZONE_ROUTE, /* <- Route */
  ZONE_FORET, /* <- Forêt */
  ZONE_MARAIS, /* <- Marais */
  ZONE_MUR, /* <- Mur */
  ZONE_TOUR, /* <- Tour de guet */
  ZONE_ERREUR, /* <- Erreur, case impossible */
} zone_type;


///
// Type d'attaque
//
typedef enum attaque_type {
  ATTAQUE_NORMALE, /* <- Attaque normale dont les dégats dépendent du personnage */
  ATTAQUE_PALANTIR, /* <- Attaque 'Palantir' du Voleur */
  ATTAQUE_TRAITRISE, /* <- Attaque 'Traîtrise' du Voleur */
  ATTAQUE_BASTOOOON, /* <- Attaque 'Bastoooon' de du Barbare */
  ATTAQUE_FUS_RO_DAH, /* <- Attaque 'Fus Ro Dah' du Barbare */
  ATTAQUE_I_SEE, /* <- Attaque 'I see what you did there.' de l'Elfe */
  ATTAQUE_LOTO, /* <- Attaque 'Loto, à qui le tour' de l'Elfe */
} attaque_type;


///
// Orientation du personnage
//
typedef enum orientation {
  ORIENTATION_NORD, /* <- Orienté au nord */
  ORIENTATION_EST, /* <- Orienté à l'est */
  ORIENTATION_SUD, /* <- Orienté au sud */
  ORIENTATION_OUEST, /* <- Orienté à l'ouest */
} orientation;


///
// Erreurs possibles
//
typedef enum erreur {
  POSITION_IMPOSSIBLE, /* <- La position n'existe pas */
  PERSONNAGE_IMPOSSIBLE, /* <- Le personnage n'existe pas ou ne vous appartient pas */
  CHEMIN_IMPOSSIBLE, /* <- Le chemin est impossible */
  ATTAQUE_INDISPONIBLE, /* <- L'attaque n'est pas utilisable pour le moment */
  OK, /* <- Pas d'erreur */
} erreur;


///
// Représente une position sur le terrain du jeu
//
typedef struct position {
  int x;  /* <- coordonnée en X */
  int y;  /* <- coordonnée en Y */
} position;


///
// Représente les informations sur un personnage
//
typedef struct perso_info {
  int equipe;  /* <- Équipe à laquelle appartient le personnage */
  perso_classe classe;  /* <- Classe du personnage */
  int vie;  /* <- Vie courante du personnage */
  orientation direction;  /* <- Orientation du personnage */
} perso_info;



extern "C" {

///
// Retourne la taille de la carte.
//
position api_carte_taille();

///
// Retourne la position de départ des personnages sur la map.
//
position api_carte_depart();

///
// Retourne la nature de la zone désignée par ``pos``.
//
zone_type api_carte_zone_type(position pos);

///
// Retourne la liste des personnages sur la zone.
//
std::vector<perso_info> api_carte_zone_perso(position pos);

///
// Renvoie la longueur du chemin le plus court entre deux points. Renvoie -1 en cas de positions invalides ou de chemin inexistant.
//
int api_distance(position p1, position p2);

///
// Renvoie le chemin le plus court entre deux points. Si le chemin n'existe pas, ou si les positions sont invalides, le chemin renvoyé est vide.
//
std::vector<position> api_chemin(position p1, position p2);

///
// Déplace le personnage ``perso`` en suivant un le chemin ``chemin`` donné sous forme d'une suite de ``position``, orientant le personnage sur la zone d'arrivée dans la direction ``orientation``.
//
erreur api_perso_deplace(perso_info perso, std::vector<position> chemin, orientation direction);

///
// Récupère la liste des zones sur lesquelles des personnages ont été aperçus dans la pénombre par ``perso``.
//
std::vector<position> api_perso_penombre(perso_info perso);

///
// Récupère la liste des zones dans le champs de vision de ``perso``.
//
std::vector<position> api_perso_vision(perso_info perso);

///
// Récupère la liste des zones dans le champs de vision de ``perso`` où sont situés un ou plusieurs personnages (amis ou ennemis).
//
std::vector<position> api_perso_vision_personnages(perso_info perso);

///
// Récupère la liste des positions sur lesquelles le palantír du voleur voit d'autre personnages.
//
std::vector<position> api_palantir_vision();

///
// Récupère la liste des zones sur lesquelles l'elfe peut voir via son attaque "I See What You Did There".
//
std::vector<position> api_elfe_vision();

///
// Effectue l'attaque ``attaque`` avec le personnage ``perso`` sur la zone ``pos``.
//
erreur api_perso_attaque(perso_info perso, attaque_type attaque, position pos);

///
// Retourne le temps de recharge restant pour l'attaque ``attaque`` du personnage ``perso``.
//
int api_perso_attaque_recharge(perso_info perso, attaque_type attaque);

///
// Retourne le numéro de votre équipe
//
int api_mon_equipe();

///
// Retourne les scores de chaque équipe
//
std::vector<int> api_scores();

///
// Retourne le nombre d'équipes sur le terrain
//
int api_nombre_equipes();

///
// Retourne le numéro du tour actuel
//
int api_tour_actuel();

///
// Affiche le contenu d'une valeur de type perso_classe
//
void api_afficher_perso_classe(perso_classe v);

///
// Affiche le contenu d'une valeur de type zone_type
//
void api_afficher_zone_type(zone_type v);

///
// Affiche le contenu d'une valeur de type attaque_type
//
void api_afficher_attaque_type(attaque_type v);

///
// Affiche le contenu d'une valeur de type orientation
//
void api_afficher_orientation(orientation v);

///
// Affiche le contenu d'une valeur de type erreur
//
void api_afficher_erreur(erreur v);

///
// Affiche le contenu d'une valeur de type position
//
void api_afficher_position(position v);

///
// Affiche le contenu d'une valeur de type perso_info
//
void api_afficher_perso_info(perso_info v);

const char* api_get_dump();

}

#endif // !INTERFACE_HH_
