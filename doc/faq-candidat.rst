===============
FAQ Casus Belli
===============

**Deux trois conseils avant de poser une question**

1. Lire le sujet
2. Relire le sujet
3. Lire votre code
4. Relire votre code
5. Contacter un orga

Vision
======

Les murs bloquent-ils la vision en diagonale ?
----------------------------------------------

Non, un mur (ou une forêt) ne bloque la vision que de la colonne orienté par la
direction du personnage.

Sur une tour, je vois tout autour de moi, comment ça marche avec les murs ?
---------------------------------------------------------------------------

Une tour est bien plus haute que le reste, elle permet donc de voir au-delà des
murs qui ne bloquent alors plus la vision.

Si mon personnage est sur une tour, peut-il voir dans une forêt ?
-----------------------------------------------------------------

Non, par contre vous pourrez voir au-delà de la forêt si c'est toujours dans la
vision de la tour.

Que voit un Palantír/un I See What You Did There dans la forêt ?
----------------------------------------------------------------

Rien. Le cas est en fait exactement le même que la question précédente.

La fonction ``perso_vision`` renvoit-elle le contenu de la case où est situé le personnage ?
--------------------------------------------------------------------------------------------

Oui, votre personnage voit les personnages sur la même case que lui.

Déplacement
===========

Pourquoi mes points de déplacement ne sont pas correctement dépensés ?
----------------------------------------------------------------------

Les coûts des déplacements d'une case sont ceux dépensés lors du déplacement **depuis** cette case.

Pénombre
========

Si un personnage ne bouge pas alors que je passe à coté de lui, apparaitra-t-il plusieurs fois dans la liste des pénombres ?
----------------------------------------------------------------------------------------------------------------------------

Oui, ``perso_penombre`` peut donc renvoyer plusieurs fois la même case, si un
personnage a été vu sur plusieurs cases de déplacement.

Ai-je accès à la pénombre du tour n-1 lors de la phase de déplacement n ?
-------------------------------------------------------------------------

Oui !

Fus Ro Dah génère-t-il de la pénombre ?
---------------------------------------

Non. :)

Mon personnage est-il inclus dans sa propre pénombre ?
------------------------------------------------------

Oui, il fait nuit et il est difficile de dicerner la différence entre son ombre
et celle des autres.

Quel est l'algorithme de la fonction vision ?
---------------------------------------------

::

    position liste getVision(position pos, orientation direction, entier vision)
    {
        si type_case(pos) = ZONE_TOUR
        {
            retourne getSquareVision(pos, vision); //Si on est sur une tour, la vision est carrée
        }

        position liste visionCone;
        bool liste estBloqué[2 * range + 3, false];

        entier South <- (direction = ORIENTATION_SUD) - (direction = ORIENTATION_NORD); // si on regarde vers le nord, South vaut -1 et le cône est inversé
        entier East <- (direction = ORIENTATION_EST) - (direction = ORIENTATION_OUEST); // si on regarde vers l'Ouest, East vaut -1 et le cône est inversé

        pour i allant de 0 à vision
        {
            pour j allant de -(i + 1) à (i + 1)
            {
                entier x <- pos.x + i * East + j * South;
                entier y <- pos.y + i * South + j * East;

                si position_non_valide(position({x,y})) ou estBloqué[j + vision + 1]
                {
                  continuer la boucle à la prochaine itération;
                }

                zone_type zoneType <- type_case(map_[y][x]); // Type de la case devant la position courante

                //Si zoneType est une forêt et qu'on est pas à la lisière, ou si il y a un mur
                si (non proche(x, y, pos) et zoneType = ZONE_FORET) ou ((non proche(x, y, pos) ou i = 1) et zoneType = ZONE_MUR)
                {
                    isBlocked[j + vision + 1] = true; // La case est bloquée
                }
                sinon si zoneType différent de ZONE_MUR // Si on n'est pas devant un mur
                {
                    visionCone.ajouter(position({x, y})); // La case est visible, on l'ajoute à la liste à retourner
                }
            }
        }
        retourner visionCone;
    }


Attaques
========

Que se passe-t'il quand mon personnage se fait toucher par deux ``Fus Roh Dah`` ?
---------------------------------------------------------------------------------

Il meurt, son corps ne résistant pas au choc de deux attaques si puissantes.

L'attaque "Traîtrise" du Voleur attaque-t-elle mes unités ?
-----------------------------------------------------------

Non, car le Voleur est suffisament intelligent pour reconnaitre ses copains.

L'attaque normale du Barbare attaque-t-elle mes unités ?
--------------------------------------------------------

Oui, le Barbare est un peu débile.


Chemin
======

La fonction ``chemin`` est-elle rapide ?
----------------------------------------

Oui car le calcul des distances n'est effectué qu'une seule fois par le
champion lors du chargement de la carte.

Que renvoit la fonction ``distance`` en cas de positions invalides ?
--------------------------------------------------------------------

Elle renvoit -1.

La fonction ``chemin`` renvoit parfois des valeurs abhérates
------------------------------------------------------------

On sait.

Mort
====

Quelle est l'orientation de mon personnage quand il revit ?
-----------------------------------------------------------

Il est orienté vers le Nord.

Map
===

Quelle est la taille maximale de la map ?
-----------------------------------------

Il n'y a pas de maximum théorique. Cependant, les chemins sont calculés à
l'initialisation de la partie avec un algorithme en O(N^3), c'est pourquoi
lors de la correction nous ne testerons pas vos champions sur des maps
de dimensions supérieures à *200x200*.

Misc
====

Quelle est la limite de mémoire ?
---------------------------------

Veillez à ce que votre champion ne prenne pas plus de ``10mio`` de mémoire.

Quelle est la limite de temps ?
-------------------------------

Chaque tour (``deplacement``, ``placement`` ou ``attaque``) ne doit pas prendre
plus d'une seconde sinon votre champion sera interrompu et vos actions ne
seront pas prisent en compte.

En c++
======

Beuh, j'ai un comportement étrange (segfault) à des endroits encore plus étranges.
----------------------------------------------------------------------------------

Vous ne pouvez pas appeler vos classes par les noms suivants :

- class Ability
- class ActionAck
- class ActionAttack
- class ActionMove
- class Api
- class Barbare
- class BarbareAttaque
- class Bastoooon
- class Cell
- class Elfe
- class ElfeAttaque
- class FusRoDah
- class Game
- class GameState
- class ISee
- class Loto
- class Map
- class Palantir
- class Rules
- class Traitrise
- class Unit
- class Voleur
- class VoleurAttaque

En java
=======

Ça ne compile pas
-----------------

Maintenant ça fonctionne, si vous avez toujours des problèmes venez nous voir.

En python
=========

``No module named prologin``
----------------------------

Vous devez lancer ``stechec-client`` dans le même dossier que le champion.
