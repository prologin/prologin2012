==================================
Finale Prologin 2012 - Casus Belli
==================================

**TODO: Ajouter les tiles pour les types de terrain**

**TODO: Ajouter les tiles pour les unités**

**TODO: Enlever la partie stratégie**

-----
Intro
-----

Le sujet serveur Prologin 2012 est un RPG ou chaque joueur contrôle une équipe
de trois personnages ayant chacun des caractéristiques les différenciant. Le
but est de gagner le plus de point en tuant un maximum d'adversaire ou en
occupant des objectifs. **FIXME comment gagner des points**

------
Règles
------

Nombre de joueurs
=================

Une partie se compose de 2 à ``n`` joueurs. La valeur la plus fréquence sera 3,
mais rien ne nous empèche de faire un match à 100 avec tous les champions sur
une même carte.

Unités
======

Les unités sont au nombre de trois par joueur. Chaque unité possède des
caractéristiques complémentaires et le joueur doit les faire agir en
coopération pour les rendre efficaces. De plus chacune possède des abilités
spéciales.

Les unités peuvent voir dans un cône de vision situé devant elles. Elles ont
aussi une force d'attaque et un déplacement différent.

On peut utiliser une abilité spéciale ou une attaque de base par unité et par
tour dans la limite des cooldowns;

Voleur
------

Le Voleur peut se déplacer rapidement et voir à une longue distance.

Il a une arme de corps à corps et donc une portée de 1.

*Attaque de base*
  :description: Petit couteau
  :dégats: 5 points de vie

*Palantír*
  :description: Le Voleur peut poser un palantír qui lui donne une vision à
    distance. Elle reste sur le terrain jusqu'à ce que le Voleur pose un autre
    palantír.
  :cooldown: 5 tours

*Traîtrise*
  :description: Le Voleur peut tuer instantanément un personnage si il se
    trouve dans son dos, c'est à dire sur la même case que lui.
  :cooldown: 5 tours
  :dégats: >9000

Barbare
-------

Le Barbare peut se déplacer de manière moyenne et voir à une distance moyenne.

Il a une arme de dégât de zone (zone + portée à définir) qu'il peut utiliser
dans son cône de vision.

::

          +
  @      +++
          +

*Attaque de base*
  :description: Grosse masse
  :dégats: 3 points de vie sur toutes les cases touchées

*Bastoooon*
  :description: Si le Barbare est sur la même case qu'un autre joueur, il peut
    lui infliger des dégâts.
  :cooldown: 3 tours

*Fus ro dah!*
  :description: Le barbare repousse tous les personnages de son champs de
    vision. Voir `Résolution du tour`_.
  :cooldown: 10 tours

Elfe
----

L'Elfe peut se déplacer de manière lente et voir à une distance moyenne.

Il peut tirer sur toutes les cases visibles par le membres de son équipe. C'est
à dire qu'il peut tirer dans le champs de vision des autres personnage de son
équipe.

*Attaque de base*
  :description: Arc
  :dégats: 2 points de vie

*I see what you did there.*
  :description: Le tireur d'élite peut réveler une zone (géométrie à définir)
    de la carte. Elle sera visible au tour suivant uniquement.
  :cooldown: 5 tours

*Loto, à qui le tour*
  :description: Le tireur d'élite peut tirer sur n'importe quelle case de la
    carte, sauf dans son cône de vision.
  :cooldown: 5 tours

Champs de vision
================

Le champs de vision définit les cases visible par un personnage. C'est un cône
de la géométrie suivante :
Taille 1 : ::

  .....
   .@.

Taille 2 : ::

  .......
   .....
    .@.

Taille 3 : ::

  .........
   .......
    .....
     .@.

Taille 4 : ::

  ...........
   .........
    .......
     .....
      .@.

Taille 5 : ::

  .............
   ...........
    .........
     .......
      .....
       .@.


Sur une tour de guet : ::

  .......
  .......
  .......
  ...@...
  .......
  .......
  .......

Carte
=====

Une carte est un quadrillage de cases carrées représentant différents terrains.
La taille de cette carte n'est pas définie statiquement et sera donnée au
joueur au début de la partie.

Coordonnées
-----------

Les coordonnés sont en ``(x, y)`` les suivantes : ::

          NORD
    OUEST <-> EST
          SUD


+--------+--------+--------+-----+
| (0, 0) | (1, 0) | (2, 0) | ... |
+--------+--------+--------+-----+
| (0, 1) | (1, 1) | (2, 1) | ... |
+--------+--------+--------+-----+
| (0, 2) | (1, 2) | (2, 2) | ... |
+--------+--------+--------+-----+
|  ...   |  ...   |  ...   | ... |
+--------+--------+--------+-----+

Type de cases
-------------

Les différentes cases que l'on peut rencontrer sur une carte sont :

Herbe
-----

Zone normale.

Route
-----

*Plus rapide*

Les personnages sur une route peuvent se déplacer deux fois plus rapidement que
sur l'herbe, c'est à dire qu'ils consoment 1 point de déplacement au lieu de
2.

Marais
------

*Moins rapide*

Un personnage qui veut se déplacer dans un marais doit dépenser quatre points
par case traversée.

Forêt
-----

*Vision réduite à 1, camouflage*

Un personnage qui regarde vers la foret ne peut voir qu'une seule case en face
de lui et un personnage hors de la foret ne peut pas voir l'intérieur de
celle-ci.

Exemples (``?`` foret, ``@`` personnage, ``.`` case visible) : ::

  Étant donne la foret suivante :
    ?????
   ???????
  ?????????
   ????????
   ?????

  Dans la foret :
    ?????
   ??.????
  ???@.????
   ??.?????
   ??????

  À la lisière :
  .........
   .......
    .....
    ?.@.?
   ???????
  ?????????
   ????????
   ??????

  À la lisière (2) :
         .....
    ?????....
   ??????...
  ??????.@.
   ????????
   ??????

  Hors de la foret :
    ?????
   ???????
  ?????????
   ????????
   ?????..
    .....
     .@.

Mur
---

*Infranchissable*

Un mur est une case opaque et infranchissable.

Tour de guet
------------

*Vision agrandie*

::

  .......
  .......
  .......
  ...@...
  .......
  .......
  .......

Un personnage sur une tour de guet gagne une vision circulaire de même taille
que sa vision naturelle.

Attaques
========

Les attaques sont données en position absolue sur la carte.

On peut attaquer ses propres personnages.

Mort
====

Un personnage meurt quand la valeur de ses points de vie est négative ou nulle.

Les points sont attribués selon ces trois règles (données par ordre de
précédence) :

1. Si un personnage meurt et alors qu'il s'est fait toucher par un allier et un
   un adversaire, aucun point n'est accordé.

2. Le personnage qui a tué fait gagner un point à son équipe.

2. Si un personnage tue un personage de sa propre équipe (y compris lui-même)
   l'équipe perd un point.

Un personnage mort réapparait à son point de départ (défini à la `Phase de
placement`_)

Cadavres
--------

Lorsque qu'un personange meurt on laisse sur sa case un "cadavre" afin de
signaler aux autres personnages sa mort. Cela permet de distinguer si un
personnage est juste sorti du champs de vision ou si il est mort. Le cadavre
reste en place un tour (ou plus, à définir).

Les cadavres ne sont pas visibles dans la pénombre (à définir).

HotSpot
=======

*À débattre.*

On peut définir un endroit spécial de la carte comme étant un "hotspot". C'est
une zone qui, si une équipe parvient à y rester seule pendant un certain nombre
de tours, donne un point.

Déroulement d'une partie
========================

Un partie dure un nombre déterminé de tours, donné aux joueurs en début de
partie. Le vainqueur est celui qui a le plus de points.

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

La phase de jeu se découpe en deux étapes consécutives : attaque et
déplacement. Le champion donne ses ordres pour les deux tours ensembles, il ne
connait donc pas l'état intermédiaire.

Attaque
```````

Au début de cette phase le joueur obtient les informations du tours précédent
(pénombre). On peut attaquer toute case visible et dans la portée du
personnage. Il peut utiliser ses abilites spéciales lors de cette phase.

Déplacement
```````````

Une case peut accueillir un nombre quelconque de personnages. Tout le monde se
déplace en même temps

Pour déplacer un personnage le champion doit donner la liste des déplacements
relatifs qui composent le chemin.

*Pénombre*

Le déplacement s'effectue d'une case à une autre. Lorsque le personnage se
déplace il regarde systématiquement dans la direction du déplacement. On
consididère que le personnage se retourne instantanément.

Pour chaque case du déplacement on regarde si il y a un personnage ennemi dans
le champs de vision et on note son emplacement. Si un personnage se déplace en
même temps qu'un autre, on peut imaginer qu'ils se croisent alors il laissera
plusieurs traces consécutives. Lors de la phase suivante on donne au joueur la
liste des positions des personnages croisés en chemin. On ne donnera ni le
propriétaire du personnage ni sa classe.

Pour que la simulation soit correcte on fera se déplacer tous les personnages
en même temps. Le nombre de tours simulés pour chaque déplacement correspondra
au nombre de cases qui compose le chemin.  Ainsi si un personnage a un parcours
plus court de les autres il s'arrêtera plus tôt alors que les autres
personnages continueront de se déplacer.

Résolution du tour
------------------

Toutes attaques sont effecutées en même temps avec une priorité pour *FUS RO
DAH*. Les attaques sont données en position relative ainsi les personnages
peuvent toujours attaquer après *FUS RO DAH*.

Puis les personnages encore vivants se déplacement.

Implication des règles
======================

*FUS RO DAH* permet de :

- Fucker les attaques des autres personnages
- Accélérer le déplacement de ses personnages (avec une possibilité d'attaquer
  plus loin, car *FUS RO DAH* est résolu avant les autres attaques)

Se mettre à côté d'un "point de départ", tirer dès que quelqu'un ressuscite, et
le tuer en boucle.

Stratégie/alliance : si deux joueurs ont un point de départ proche, ils peuvent
se tuer en boucle et amasser beaucoup de points rapidement.
