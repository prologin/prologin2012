// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (c) 2012-2020 Association Prologin <association@prologin.org>

// This file contains all the API functions for the C++ language, and all the
// constants, enumerations and structures.
// This file was generated by stechec2-generator. DO NOT EDIT.

#pragma once

#include <string>
#include <vector>

/// Vision du Voleur
#define VOLEUR_VISION_PORTEE 5

/// Déplacement du Voleur
#define VOLEUR_DEPLACEMENT 10

/// Vie du Voleur
#define VOLEUR_VIE 10

/// Attaque du voleur
#define VOLEUR_ATTAQUE 5

/// Cooldown de l'attaque "Palantir" du Voleur
#define VOLEUR_PALANTIR_CD 3

/// Cooldown de l'attaque "Traîtrise" du Voleur
#define VOLEUR_TRAITRISE_CD 5

/// Vision du Barbare
#define BARBARE_VISION_PORTEE 4

/// Déplacement du Barbare
#define BARBARE_DEPLACEMENT 8

/// Vie du Barbare
#define BARBARE_VIE 10

/// Attaque du Barbare
#define BARBARE_ATTAQUE 3

/// Cooldown de l'attaque "Bastoooon" du Barbare
#define BARBARE_BASTOOOON_CD 3

/// Portée de l'attaque "Bastoooon" du Barbare
#define BARBARE_BASTOOOON_PORTEE 3

/// Cooldown de l'attaque "Fus Ro Dah" du Barbare
#define BARBARE_FUS_RO_DAH_CD 5

/// Vision de l'Elfe
#define ELFE_VISION_PORTEE 4

/// Déplacement de l'Elfe
#define ELFE_DEPLACEMENT 6

/// Vie de l'Elfe
#define ELFE_VIE 10

/// Attaque de l'Elfe
#define ELFE_ATTAQUE 2

/// Cooldown de l'attaque "Loto, à qui le tour ?" de l'Elfe
#define ELFE_LOTO_CD 5

/// Cooldown de l'attaque "I See What You Did There" de l'Elfe
#define ELFE_I_SEE_CD 5

/// Type de personnage
typedef enum perso_classe
{
    PERSO_VOLEUR, ///< Voleur
    PERSO_BARBARE, ///< Barbare
    PERSO_ELFE, ///< Elfe
} perso_classe;

/// Type de zone
typedef enum zone_type
{
    ZONE_HERBE, ///< Herbe
    ZONE_ROUTE, ///< Route
    ZONE_FORET, ///< Forêt
    ZONE_MARAIS, ///< Marais
    ZONE_MUR, ///< Mur
    ZONE_TOUR, ///< Tour de guet
    ZONE_ERREUR, ///< Erreur, case impossible
} zone_type;

/// Type d'attaque
typedef enum attaque_type
{
    ATTAQUE_NORMALE, ///< Attaque normale dont les dégats dépendent du personnage
    ATTAQUE_PALANTIR, ///< Attaque 'Palantir' du Voleur
    ATTAQUE_TRAITRISE, ///< Attaque 'Traîtrise' du Voleur
    ATTAQUE_BASTOOOON, ///< Attaque 'Bastoooon' de du Barbare
    ATTAQUE_FUS_RO_DAH, ///< Attaque 'Fus Ro Dah' du Barbare
    ATTAQUE_I_SEE, ///< Attaque 'I see what you did there.' de l'Elfe
    ATTAQUE_LOTO, ///< Attaque 'Loto, à qui le tour' de l'Elfe
} attaque_type;

/// Orientation du personnage
typedef enum orientation
{
    ORIENTATION_NORD, ///< Orienté au nord
    ORIENTATION_EST, ///< Orienté à l'est
    ORIENTATION_SUD, ///< Orienté au sud
    ORIENTATION_OUEST, ///< Orienté à l'ouest
} orientation;

/// Erreurs possibles
typedef enum erreur
{
    POSITION_IMPOSSIBLE, ///< La position n'existe pas
    PERSONNAGE_IMPOSSIBLE, ///< Le personnage n'existe pas ou ne vous appartient pas
    CHEMIN_IMPOSSIBLE, ///< Le chemin est impossible
    ATTAQUE_INDISPONIBLE, ///< L'attaque n'est pas utilisable pour le moment
    OK, ///< Pas d'erreur
} erreur;

/// Représente une position sur le terrain du jeu
typedef struct position
{
    int x; ///< coordonnée en X
    int y; ///< coordonnée en Y
} position;

/// Représente les informations sur un personnage
typedef struct perso_info
{
    int equipe; ///< Équipe à laquelle appartient le personnage
    perso_classe classe; ///< Classe du personnage
    int vie; ///< Vie courante du personnage
    orientation direction; ///< Orientation du personnage
} perso_info;

/// Retourne la taille de la carte.
position carte_taille();

/// Retourne la position de départ des personnages sur la map.
position carte_depart();

/// Retourne la nature de la zone désignée par ``pos``.
zone_type carte_zone_type(position pos);

/// Retourne la liste des personnages sur la zone.
std::vector<perso_info> carte_zone_perso(position pos);

/// Renvoie le nombre de points nécessaires pour parcourir le chemin le plus
/// court entre deux points. Renvoie -1 en cas de positions invalides ou de
/// chemin inexistant.
int distance(position p1, position p2);

/// Renvoie le chemin le plus court entre deux points. Si le chemin n'existe
/// pas, ou si les positions sont invalides, le chemin renvoyé est vide.
std::vector<position> chemin(position p1, position p2);

/// Déplace le personnage ``perso`` en suivant un le chemin ``chemin`` donné
/// sous forme d'une suite de ``position``, orientant le personnage sur la zone
/// d'arrivée dans la direction ``orientation``.
erreur perso_deplace(perso_info perso, std::vector<position> chemin, orientation direction);

/// Récupère la liste des zones sur lesquelles des personnages ont été aperçus
/// dans la pénombre par ``perso``.
std::vector<position> perso_penombre(perso_info perso);

/// Récupère la liste des zones dans le champs de vision de ``perso``.
std::vector<position> perso_vision(perso_info perso);

/// Récupère la liste des zones dans le champs de vision de ``perso`` où sont
/// situés un ou plusieurs personnages (amis ou ennemis).
std::vector<position> perso_vision_personnages(perso_info perso);

/// Récupère la liste des positions sur lesquelles le palantír du voleur voit
/// d'autre personnages.
std::vector<position> palantir_vision();

/// Récupère la liste des positions sur lesquelles l'elfe voit d'autres
/// personnages *via* son attaque spéciale.
std::vector<position> elfe_vision();

/// Effectue l'attaque ``attaque`` avec le personnage ``perso`` sur la zone
/// ``pos``.
erreur perso_attaque(perso_info perso, attaque_type attaque, position pos);

/// Retourne le temps de recharge restant pour l'attaque ``attaque`` du
/// personnage ``perso``.
int perso_attaque_recharge(perso_info perso, attaque_type attaque);

/// Retourne la position du personnage ``perso``.
position perso_position(perso_info perso);

/// Retourne le personnage de type ``classe`` de sa propre équipe.
perso_info perso_classe_info(perso_classe classe);

/// Retourne le numéro de votre équipe
int mon_equipe();

/// Retourne les scores de chaque équipe
std::vector<int> scores();

/// Retourne le nombre d'équipes sur le terrain
int nombre_equipes();

/// Retourne le numéro du tour actuel
int tour_actuel();

/// Retourne le nombre de tours de placements
int nombre_tours_placement();

/// Retourne le nombre total de tours
int nombre_tours();

/// Affiche le contenu d'une valeur de type perso_classe
void afficher_perso_classe(perso_classe v);

/// Affiche le contenu d'une valeur de type zone_type
void afficher_zone_type(zone_type v);

/// Affiche le contenu d'une valeur de type attaque_type
void afficher_attaque_type(attaque_type v);

/// Affiche le contenu d'une valeur de type orientation
void afficher_orientation(orientation v);

/// Affiche le contenu d'une valeur de type erreur
void afficher_erreur(erreur v);

/// Affiche le contenu d'une valeur de type position
void afficher_position(position v);

/// Affiche le contenu d'une valeur de type perso_info
void afficher_perso_info(perso_info v);

// -----
// API ends here, you can stop reading now.
// The rest of the file is generated operators for the structs defined above.
// -----

namespace std
{
template <typename T>
struct hash<std::vector<T>>
{
    std::size_t operator()(const std::vector<T>& v) const
    {
        std::size_t res = v.size();
        for (const auto& e : v)
            res ^= std::hash<T>()(e) + 0x9e3779b9 + (res << 6) + (res >> 2);
        return res;
    }
};
} // namespace std

inline bool operator==(const position& a, const position& b)
{
    if (a.x != b.x)
        return false;
    if (a.y != b.y)
        return false;
    return true;
}

inline bool operator!=(const position& a, const position& b)
{
    return !(a == b);
}

inline bool operator<(const position& a, const position& b)
{
    if (a.x < b.x)
        return true;
    if (a.x > b.x)
        return false;
    if (a.y < b.y)
        return true;
    if (a.y > b.y)
        return false;
    return false;
}

inline bool operator>(const position& a, const position& b)
{
    if (a.x > b.x)
        return true;
    if (a.x < b.x)
        return false;
    if (a.y > b.y)
        return true;
    if (a.y < b.y)
        return false;
    return false;
}

namespace std
{
template <>
struct hash<position>
{
    std::size_t operator()(const position& s) const
    {
        std::size_t res = 0;
        res ^= 0x9e3779b9 + (res << 6) + (res >> 2) + std::hash<int>()(s.x);
        res ^= 0x9e3779b9 + (res << 6) + (res >> 2) + std::hash<int>()(s.y);
        return res;
    }
};
} // namespace std
inline bool operator==(const perso_info& a, const perso_info& b)
{
    if (a.equipe != b.equipe)
        return false;
    if (a.classe != b.classe)
        return false;
    if (a.vie != b.vie)
        return false;
    if (a.direction != b.direction)
        return false;
    return true;
}

inline bool operator!=(const perso_info& a, const perso_info& b)
{
    return !(a == b);
}

inline bool operator<(const perso_info& a, const perso_info& b)
{
    if (a.equipe < b.equipe)
        return true;
    if (a.equipe > b.equipe)
        return false;
    if (a.classe < b.classe)
        return true;
    if (a.classe > b.classe)
        return false;
    if (a.vie < b.vie)
        return true;
    if (a.vie > b.vie)
        return false;
    if (a.direction < b.direction)
        return true;
    if (a.direction > b.direction)
        return false;
    return false;
}

inline bool operator>(const perso_info& a, const perso_info& b)
{
    if (a.equipe > b.equipe)
        return true;
    if (a.equipe < b.equipe)
        return false;
    if (a.classe > b.classe)
        return true;
    if (a.classe < b.classe)
        return false;
    if (a.vie > b.vie)
        return true;
    if (a.vie < b.vie)
        return false;
    if (a.direction > b.direction)
        return true;
    if (a.direction < b.direction)
        return false;
    return false;
}

namespace std
{
template <>
struct hash<perso_info>
{
    std::size_t operator()(const perso_info& s) const
    {
        std::size_t res = 0;
        res ^= 0x9e3779b9 + (res << 6) + (res >> 2) + std::hash<int>()(s.equipe);
        res ^= 0x9e3779b9 + (res << 6) + (res >> 2) + std::hash<perso_classe>()(s.classe);
        res ^= 0x9e3779b9 + (res << 6) + (res >> 2) + std::hash<int>()(s.vie);
        res ^= 0x9e3779b9 + (res << 6) + (res >> 2) + std::hash<orientation>()(s.direction);
        return res;
    }
};
} // namespace std

extern "C"
{
    void partie_init();
    void jouer_placement();
    void jouer_deplacement();
    void jouer_attaque();
    void partie_fin();
}