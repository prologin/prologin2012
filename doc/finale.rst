==================================
Finale Prologin 2012 - Casus Belli
==================================

-----
Intro
-----

Le sujet serveur Prologin 2012 est un RPG ou chaque joueur contrôle une équipe
de trois personnages ayant chacun des caractéristiques les différenciant. Le
but est de gagner le plus de point en tuant un maximum d'adversaire en
minimisant ses pertes.

------
Règles
------

Nombre de joueurs
=================

Une partie se compose de 2 à ``n`` joueurs. La valeur la plus fréquence sera 3,
mais rien ne nous empêche de faire un match à 100 avec tous les champions sur
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
tour dans la limite des cooldowns.

Voleur
------

Le Voleur peut se déplacer rapidement et voir à une longue distance.

Il a une arme de corps à corps et donc une portée de 1.

*Attaque de base*
  :description: Petit couteau
  :dégats: 5 points de vie
  :portée: 1
  :teamkill: Oui

*Palantír*
  :description: Le Voleur peut poser un palantír qui lui donne une vision à
    distance. Elle reste sur le terrain jusqu'à ce que le Voleur pose un autre
    palantír. Le champs de vision est le même que celui qu'aurait un Voleur sur
    un tour.
    Il peut le poser sur n'importe quelle case de son champ de vision.
  :cooldown: 3 tours

*Traîtrise*
  :description: Le Voleur peut tuer instantanément les personnage se trouvant
    sur la même case que lui.
  :cooldown: 5 tours
  :dégats: >9000
  :teamkill: Non

Barbare
-------

Le Barbare peut se déplacer de manière moyenne et voir à une distance moyenne.

Il a une arme de dégât de zone qu'il peut utiliser dans son cône de vision.

::

          +
  @      +++
          +

*Attaque de base*
  :description: Gros marteau
  :dégats: 3 points de vie sur toutes les cases touchées
  :teamkill: Oui

*Bastoooon*
  :description: Le Barbare s'énerve puis effectue son attaque normale.
  :dégats: 11 - *vie restante du Barbare*
  :cooldown: 3 tours
  :portée: 3
  :teamkill: Oui

*Fus ro dah!*
  :description: Le barbare repousse tous les personnages de son champs de
    vision en ligne droite jusqu'à ce qu'ils soient bloqués ou hors de son
    champs de vision. Voir `Résolution de la phase d'attaque`_ pour plus
    d'informations.
  :cooldown: 5 tours

Elfe
----

L'Elfe peut se déplacer de manière lente et voir à une distance moyenne.

Il peut tirer sur toutes les cases visibles par le membres de son équipe. C'est
à dire qu'il peut tirer dans le champs de vision des autres personnage de son
équipe.

*Attaque de base*
  :description: Arc long
  :dégats: 2 points de vie
  :teamkill: Oui

*Loto, à qui le tour*
  :description: Arc très long. L'Elfe peut tirer sur n'importe quelle case de
    la carte.
  :dégats: 4 points de vie
  :cooldown: 5 tours
  :teamkill: Oui

*I see what you did there.*
  :description: L'Elfe peut réveler une zone carrée (comme si il
    était sur une tour) de la carte. Elle sera visible jusqu'à la prochaine
    phase d'attaque.
    Il peut révéler n'importe quelle case de la carte, même hors de son
    champ de vision.
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


Sur une tour de guet (taille 3) : ::

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

Les mouvements en diagonale ne sont pas autorisés.

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

Zone normale. Un déplacement depuis cette case coûte **deux** points de
déplacement.

Route
-----

*Plus rapide*

Les personnages sur une route peuvent se déplacer deux fois plus rapidement que
sur l'herbe, c'est à dire qu'ils consoment **un** point de déplacement au lieu
de deux.

Marais
------

*Moins rapide*

Un personnage qui veut se déplacer dans un marais doit dépenser **quatre**
points par case traversée.

Forêt
-----

*Vision réduite à 1, camouflage*

Un personnage qui regarde vers la foret ne peut voir qu'une seule case en face
de lui et un personnage hors de la foret ne peut pas voir l'intérieur de
celle-ci.

Un déplacement coûte **deux** points de déplacement.


Exemples (``?`` foret, ``@`` personnage, ``.`` case visible) : ::

  Étant donne la foret suivante :
    ?????
   ???????
  ?????????
   ????????
   ?????

  Dans la foret (le personnage regarde vers l'Est) :
    ?????
   ??.????
  ???@.????
   ??.?????
   ??????

  À la lisière (le personnage regarde vers le Nord) :
  .........
   .......
    .....
    ?.@.?
   ???????
  ?????????
   ????????
   ??????

  À la lisière (2) (le personnage regarde vers le Nord) :
         .....
    ?????....
   ??????...
  ??????.@.
   ????????
   ??????

  Hors de la foret (le personnage regarde vers le Nord) :
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

*Vision élargie*

::

  .......
  .......
  .......
  ...@...
  .......
  .......
  .......

Un personnage qui passe sur une tour de guet gagne une vision circulaire de
même taille que sa vision naturelle.


Format ASCII
------------

Les cartes sont représentées sous forme de fichiers de texte utilisant la norme
suivante :

+-------+--------+
| ``.`` | Herbe  |
+-------+--------+
| ``_`` | Route  |
+-------+--------+
| ``~`` | Marais |
+-------+--------+
| ``#`` | Mur    |
+-------+--------+
| ``F`` | Forêt  |
+-------+--------+
| ``T`` | Tour   |
+-------+--------+

Le fichier doit suivre le format suivant : ::

  height width
  starting_position.x starting_position.y
  number_of_placement_turns
  maximum_number_of_turns
  ASCII map representation

Voici un exemple: ::

  10 9
  5 4
  3
  20
  ##########
  #FFF_....#
  #FFF_..T.#
  #FFF_....#
  #..._....#
  #~~~_....#
  #~T~_....#
  #~~~_....#
  ##########


Attaques
========

Les attaques sont données en position absolue sur la carte.

Certaines attaques permettent d'attaquer ses propres personnages.

Mort
====

Un personnage meurt quand la valeur de ses points de vie est négative ou nulle.

Les points sont attribués selon ces trois règles (données par ordre de
précédence) :

1. Si un personnage meurt et alors qu'il s'est fait toucher par un allié et un
   un adversaire, aucun point n'est accordé.

2. Le personnage qui a tué fait gagner un point à son équipe. Le personnage qui
   est tué fait perde un point à son équipe.

3. Si un personnage tue un personage de sa propre équipe (y compris lui-même)
   l'équipe perd un point.

Un personnage mort réapparait à son point de départ (défini à la `Phase de
placement`_)

Déroulement d'une partie
========================

Un partie dure un nombre déterminé de tours, donné aux joueurs en début de
partie. Le vainqueur est celui qui a le plus de points.

Phase de placement
------------------

Tous les personnages des joueurs partent de la même position (généralement au
milieu de la carte mais pas forcément). Ils disposent alors d'un nombre fixé de
tour pour déplacer leurs personnages jusqu'à des endroits de leur choix qui
seront leurs points de réapparition en cas de mort durant toute la partie (voir
la fonction ``jouer_placement``).

Lors de cette phase de jeu, les personnages ne peuvent que bouger (ils ne
peuvent pas donc encore s'attaquer dessus).

Phase de jeu
------------

La phase de jeu se découpe en deux étapes consécutives : attaque et
déplacement. Le champion donne ses ordres étape par étape (voir les fonctions
``jouer_deplacement`` et ``jouer_attaque``).

Attaque
```````

Au début de cette phase le joueur obtient les informations du tours précédent
(pénombre). On peut attaquer toute case visible et dans la portée du
personnage. Il peut utiliser ses abilités spéciales lors de cette phase.

Déplacement
```````````

Une case peut accueillir un nombre quelconque de personnages. Tout le monde se
déplace en même temps.

Pour déplacer un personnage le champion doit donner la liste des cases qui
composent le chemin.

Chaque déplacement **depuis** une case de type T dépense le nombre de points
de déplacement correspondant au type T.

*Pénombre*

Le déplacement s'effectue d'une case à une autre. Lorsque le personnage se
déplace il regarde systématiquement dans la direction du déplacement. On
considère que le personnage se retourne instantanément.

Pour chaque case du déplacement on regarde si il y a un personnage ennemi dans
le champs de vision et on note son emplacement. Si un personnage se déplace en
même temps qu'un autre et qu'ils se croisent alors il laissera plusieurs traces
consécutives. Lors de la phase suivante on donne au joueur la liste des
positions des personnages croisés en chemin. On ne donnera ni le propriétaire
du personnage ni sa classe (même si il s'agit d'un de vos personnages).


Pour que la simulation soit correcte on fera se déplacer tous les personnages
en même temps. Le nombre de tours simulés pour chaque déplacement correspondra
au nombre de cases qui compose le chemin.  Ainsi si un personnage a un parcours
plus court de les autres il s'arrêtera plus tôt alors que les autres
personnages continueront de se déplacer.

Résolution de la phase d'attaque
--------------------------------

L'attaque *Fus Ro Dah* est toujours résolue en premier.

L'attaque *Bastoooon* est toujours résolue en dernier.

Si un personnage est déplacé par l'attaque *Fus Ro Dah*, son attaque sera
décalée et appliquée (si cela est toujours possible).

L'attaque *Bastoooon* se base sur les points de vie du Barbare l'invoquant
après la résolution de toutes les attaques d'un autere type.
