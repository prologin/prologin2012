========================
Serveur 2012 - Prototype
========================

Nom du jeu : ProloWars (?)

-----
Intro
-----

Le sujet serveur Prologin 2012 est un RPG ou chaque joueur contrôle une équipe
de trois personnages ayant chacun des caractéristiques les différenciant. Le but
est de gagner le plus de point en tuant un maximum d'adversaire ou en occupant
des objectifs.

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
    :Attaque: Diminue en fonction de la distance, fort \ courte distance

- Barbare
    :Vision: 5
    :Déplacement: 5
    :Vie: 10
    :Attaque: Arme de zone (lance grenade)

- Tireur d'élite
    :Vision: 4
    :Déplacement: 6
    :Vie: 6
    :Attaque: Fusil de précision

Déroulement d'une partie
========================

Le jeu se découpe en deux phases : la phase de placement et la phase de jeu.

Phase de placement
------------------

Tous les personnages des joueurs partent de la même position (généralement au
milieu de la carte mais pas forcément). Ils disposent alors d'un nombre fixé de
tour pour déplacer leurs personnages jusqu'à des endroits de leur choix qui
seront leurs points de réapparition en cas de mort durant toute la partie.

Lors de cette phase de jeu, les personnages ne peuvent que bouger (ils ne
peuvent pas se tirer dessus par exemple durant toute la partie).

Phase de jeu
------------

La phase de jeu se découpe en tours. Un partie dure un nombre déterminé de
tours, donné aux joueurs en début de partie.


Une case peut accueillir un nombre quelconque de personnages. Tout le monde se
déplace en même temps

---
API
---

Constantes
==========

*À affiner empiriquement*

ECLAIREUR_VISION = 8

ECLAIREUR_DEPLACEMENT = 8

ECLAIREUR_VIE = 3

ECLAIREUR_ATTAQUE = ?

BARBARE_VISION = 8

BARBARE_DEPLACEMENT = 8

BARBARE_VIE = 3

BARBARE_ATTAQUE = ?

ELITE_VISION = 8

ELITE_DEPLACEMENT = 8

ELITE_VIE = 3

ELITE_ATTAQUE = ?
