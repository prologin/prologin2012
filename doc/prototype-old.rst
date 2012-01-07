========================
Serveur 2012 - Prototype
========================

Nom du jeu : TA BITE Empire (?)

------
Règles
------

Villes
======

À chaque tour la population augmente du nombre de villes alliées adjacentes.

Une ville commence avec un niveau égal à 10. Le niveau d'une ville correspond à
la population maximum qu'elle est capable d'accueillir.

Augmenter la taille d'une ville coute la valeur de la taille suivante (ex. si on
est au niveau 10, passer au niveau 20 coutera 20 or). Une taille s'augmente de
10 en 10. Exemple :

+--------+------+------------+
| Taille | Coût | Coût total |
+--------+------+------------+
|   20   |  20  |     20     |
+--------+------+------------+
|   30   |  30  |     50     |
+--------+------+------------+
|   40   |  40  |     90     |
+--------+------+------------+
|   50   |  50  |    140     |
+--------+------+------------+
|   ...  |  ... |    ...     |
+--------+------+------------+

Armée
=====

À chaque tour, dans chaque ville, l'armée augmente en fonction de la population.
La quantité pourra dépendre de la note de réputation et/ou de la spécialisation
de la ville.

Une ville ne peut pas contenir plus d'armée que de population.

On peut en déplacer une partie ou le tout d'une ville à une autre adjacente
chaque tour.

Mercenaires
===========

Un joueur peut recruter dans chaque ville un nombre de mercenaire dépendant de
la population pour compléter son armée.

Chaque mercenaire est recruter pour un nombre déterminé de tours (son prix étant
fonction de nombre).

On ne peut déplacer que tous les mercenaires ensembles d'une ville à une autre.
Cela implique une fusion automatique d'un groupe de mercenaire arrivant dans un
ville avec le groupe de mercenaires déjà présent. Ils gardent cependant chacun
le nombre de jours restants. Il n'y a pas de déplacement individuel possible
comme avec les soldats.


Système d'alliance
==================

À définir.

Réputation
==========

Chaque joueur possède une caractéristique de réputation sous forme de note.
Selon cette note, le joueur possède les avantages suivants :

- Réputation positive : le joueur gagne plus d'argent et de population
- Réputation négative : le joueur a plus d'armée, peut acheter des mercenaires
                        à un meilleur prix

!IDÉE! Éventuellement la rendre persistante entre les parties.

Cette note varie selon les évènements suivants :

Augmente
--------

 - Prévenant avant d'attaquer
 - S'allier avec un joueur
 - Aider ses alliés
 - ...

Diminue
-------

 - Ne pas prévenir avant d'attaquer
 - Acheter des mercenaires
 - Attaquer ses alliés
 - ...

Formules
------------

/!\ Les formules suivantes sont à affiner avec le prototype

nombre_de_soldat / ville / tour = sup(racine_carree(population))
nombre_de_mercenaire / ville / tour = sup(racine_carree(population)) / 2
prix_mercenaire = 10 * coefficient(reputation) <= À trouver

---
API
---

Constantes
==========

MERCENAIRE_COUT = 42
MERCENAIRE_MAX_TOUR = 4224342432

ERREURS

joueur
======

joueur_mon_id()
  :retourne: L'id du joueur (entier)

joueur_villes(joueur_id)
  :joueur_id: Identifiant du joueur
  :retourne: La liste des villes possedés par le joueur_id (liste de city_id)

joueur_reputation(joueur_id)
  :joueur_id: Identifiant du joueur
  :retourne: La réputation du joueur (entier relatif)

armee
=====

armee_deplace(depuis_ville_id, vers_ville_id)
  :depuis_ville_id: Identifiant de la ville de départ
  :vers_ville_id: Identifiant de la ville d'arrivée
  :retourne: Succès (bool)

ville
=====

ville_proprietaire(ville_id)
  :ville_id: Un identifiant de ville (entier)
  :retourne: Le player_id du propriétaire de la ville

ville_population(ville_id)
  :ville_id: Un identifiant de ville (entier)
  :retourne: La population totale de la ville (entier)

ville_ameliorer(ville_id)
  :ville_id: Un identifiant de ville (entier)
  :retourne: Succès (bool)

ville_specialisation(ville_id)
  :ville_id: Un identifiant de ville (entier)
  :retourne: La spécialisation de la ville (voir constantes)

ville_armee(ville_id)
  :ville_id: Un identifiant de ville (entier)
  :retourne: La taille actuelle de l'armee pour cette ville_id (entier)

ville_routes(ville_id)
  :ville_id: Un identifiant de ville (entier)
  :retourne: Une liste de ville_id accessible depuis cette ville_id (liste
    d'entiers)

ville_or(ville_id)
  :ville_id: Un identifiant de ville (entier)
  :retourne: La quantité courante d'or pour cette ville_id (entier)

ville_mercenaires(ville_id)
  :ville_id: Un identifiant de ville (entier)
  :retourne: Liste de mercenaires_id

mercenaires
===========

mercenaires_acheter(ville_id, quantite, nombre_de_tours)
  :ville_id: Un identifiant de ville (entier)
  :quantite: Nombre de mercenaires à acheter
  :nombre_de_tours: Nombre de tours que vont rester les mercenaires
  :retourne: Succès (bool)

mercenaires_deplace(depuis_ville_id, vers_ville_id)
  :depuis_ville_id: Identifiant de la ville de départ
  :vers_ville_id: Identifiant de la ville d'arrivée
  :retourne: Succès (bool)

mercenaires_restants(ville_id)
  :ville_id: Un identifiant de ville (entier)
  :retourne: Nombre de mercenaires restants dans la ville (entier)

mercenaires_info(mercenaire_id)
  :mercenaire_id: Un identifiant de mercenaire
  :retourne: Nombre de tours restants pour le mercenaire (entier)

vim:set tw=80:
