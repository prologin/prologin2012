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

#ifndef CONSTANT_HH_
# define CONSTANT_HH_

///
// Vision du Voleur
//
# define VOLEUR_VISION             8

///
// Déplacement du Voleur
//
# define VOLEUR_DEPLACEMENT        8

///
// Vie du Voleur
//
# define VOLEUR_VIE                3

///
// Attaque du voleur
//
# define VOLEUR_ATTAQUE            3

///
// Portée de l'arme du Voleur
//
# define VOLEUR_ATT_PORTEE         1

///
// Zone de dégats de l'arme du Voleur
//
# define VOLEUR_ATT_ZONE           1

///
// Vision du Barbare
//
# define BARBARE_VISION            8

///
// Déplacement du Barbare
//
# define BARBARE_DEPLACEMENT       8

///
// Vie du Barbare
//
# define BARBARE_VIE               3

///
// Attaque du Barbare
//
# define BARBARE_ATTAQUE           5

///
// Portée de l'arme du Barbare
//
# define BARBARE_ATT_PORTEE        5

///
// Zone de dégats de l'arme du Barbare
//
# define BARBARE_ATT_ZONE          2

///
// Vision de l'Elfe
//
# define ELFE_VISION               8

///
// Déplacement de l'Elfe
//
# define ELFE_DEPLACEMENT          8

///
// Vie de l'Elfe
//
# define ELFE_VIE                  3

///
// Attaque de l'Elfe
//
# define ELFE_ATTAQUE              2

///
// Portée de l'arme de l'Elfe
//
# define ELFE_ATT_PORTEE           8

///
// Zone de dégats de l'arme de l'Elfe
//
# define ELFE_ATT_ZONE             1

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
  ZONE_ERREUR /* <- Erreur, mauvaise position */
} zone_type;


///
// Type d'attaque
//
typedef enum attaque_type {
  ATTAQUE_NORMALE, /* <- Attaque normale */
  ATTAQUE_PALANTIR, /* <- Attaque 'Palantir' de l'Elfe */
  ATTAQUE_DANS_TO_DOS, /* <- Attaque 'Dans ton dos' de l'Elfe */
  ATTAQUE_BASTOOOON, /* <- Attaque 'Bastoooon' de du Barbare */
  ATTAQUE_FUS_RO_DAH, /* <- Attaque 'Fus Ro Dah' du Barbare */
  ATTAQUE_I_SEE, /* <- Attaque 'I see what you did there.' du Voleur */
  ATTAQUE_LOTO, /* <- Attaque 'Loto, à qui le tour' du Voleur */
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



#endif // !CONSTANT_HH_
