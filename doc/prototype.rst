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
- Route
- Forêt
- Marais
- Mur

Unités
======

Les unités sont au nombre de trois par joueur. Chaque unité possède des
caractéritiques complémentaire et le joueur doit les faire agir en coopération
pour les rendre efficaces.

Les unités peuvent voir dans un cône de vision situé devant elles. Elles ont
aussi une force d'attaque et un déplacement différent :

- Éclaireur
- Barbare
- Tireur d'élite

Déplacement
===========

Pénombre
--------

Le déplacement s'effectue d'une case à une autre. Le champion doit donner la
liste des cases adjacentes qui composent le chemin qu'il souhaite que le
personnage empreinte. Lorsque le personnage se déplace il regarde
systématiquement dans la direction du déplacement. On consididère que le
personnage se retourne instantanément.

Pour chaque case du déplacement on regarde si il y a un personnage énemi dans
le champs de vision et son emplacement. Si un personnage se déplace en même
temps qu'un autre, on peut imaginer qu'ils se croisent, il laissera plusieurs
traces consécutives. Lors de la phase suivante on donne au joueur la liste des
positions des personnages croisés en chemin. On ne donnera ni le propriétaire
du personnage ni sa classe.

Pour que la simulation soit correcte on fera se déplacer tous les personnages
en même temps. Le nombre de tours simulé pour chaque déplacement correspondra
au nombre de cases qui compose le chemin.  Ainsi si un personnage a parcours
plus court de les autres il s'arrêtera plus tôt alors les autres personnages
continuerons de se déplacer.

Attaques
========

Les types d'attaques/abilités spéciales sont à définir.

Cadavres
========

Lorsque qu'un personange meurt on lasse sur sa case un "cadavre" afin de
signaler aux autres personnage sa mort. Cela permet de distinguer si un
personnage est juste sorti du champs de vision ou si il est mort. Le cadavre
reste en place un tour (ou plus, à définir).

Les cadavres ne sont pas visibles dans la pénombre (à définir)

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
