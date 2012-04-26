===============
FAQ Casus Belli
===============

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

La fonction ``perso_vision`` renvoit-elle le contenu de la case où est situé le personnage ?
--------------------------------------------------------------------------------------------

Oui, votre personnage voit les personnages sur la même case que lui.

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

Mort
====

Quelle est l'orientation de mon personnage quand il revit ?
-----------------------------------------------------------

Il est orienté vers le Nord.

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
