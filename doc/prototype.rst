========================
Serveur 2012 - Prototype
========================

Nom du jeu : ProloWars (?)

-----
Intro
-----

Le sujet serveur Prologin 2012 est un RPG ou chaque joueur contrôle une équipe
de trois personnages ayant chacun des caractéristiques les différenciant. Le but
est de gagner le plus de point en tuant un maximum d'adversaire.

------
Règles
------

Carte
=====

Une carte est un quadrillage de cases carrées représentant différents terrains.
La taille de cette carte n'est pas définie statiquement et sera données au
joueur au début de la partie.

Les différentes cases que l'on peut rencontrer sur une carte sont :

- Herbe
    :Déplacement: 0
    :Vision: Normale
- Route
    :Déplacement: +1
    :Vision: Normale
- Forêt
    :Déplacement: -1
    :Vision: Les personnages ne peuvent voir que d'une case
- Marais
    :Déplacement: -2
    :Vision: Normale
- Mur
    :Déplacement: Obstacle
    :Vision: Aucune

Unités
======

Les unités sont au nombre de trois par joueur. Chaque unité possède des
caractéritiques complémentaire et le joueur doit les faire agir en coopération
pour les rendre efficaces.

Les unités peuvent voir dans un cône de vision situé devant elles. Elles ont
aussi une force d'attaque et un déplacement différent :

- Éclaireur
    :Vision: 10
    :Déplacement: 10
    :Vie: 3
    :Attaque: 

---
API
---

Constantes
==========

*À affiner empiriquement*

ECLAIREUR_VISION = 8
ECLAIREUR_DEPLACEMENT = 8
ECLAIREUR_VIE = 3
ECLAIREUR_ATTAQUE = 

vim:set tw=80:
