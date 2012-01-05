========================
Serveur 2012 - Prototype
========================

Nom du jeu : TA BITE Empire (?)

Règles {{{
----------

Villes {{{
^^^^^^^^^^

À chaque tour la population augmente du nombre de villes adjacentes.

Une ville commence avec une niveau égal à 10. Le niveau d'une ville correspond à
la population maximum qu'elle est capable d'accueillir.

Augmenter le niveau d'une ville coute de la valeur du niveau suivante (ex. si on
est au niveau 10, passer au niveau 20 coutera 20 or)

}}}

Armée {{{
^^^^^^^^^

À chaque tour, dans chaque ville, l'armée augmente en fonction de la population.
La quantité pourra dépendre de la note de réputation et/ou de la spécialisation
de la ville.

On peut en déplacer une partie ou le tout d'une ville à une autre chaque tour.

}}}

Mercenaires {{{
^^^^^^^^^^^^^^^

Un joueur peut recruter dans chaque ville un nombre de mercenaire dépendant de
la population pour compléter son armée.

Chaque mercenaire est recruter pour un nombre déterminé de tours (son prix étant
fonction de nombre).

On ne peut déplacer que tous les mercenaires ensembles d'une ville à une autre.
Cela implique une fusion automatique d'un groupe de mercenaire arrivant dans un
ville avec le groupe de mercenaires déjà présent. Ils gardent cependant chacun
le nombre de jours restants. Il n'y a pas de déplacement individuel possible
comme avec les soldats.

}}}

Système d'alliance ? {{{
~~~~~~~~~~~~~~~~~~~~~~~~

}}}

Note de réputation ? {{{
~~~~~~~~~~~~~~~~~~~~~~~~

La note de réputation sert permet des caractéristiques propres à un joueur :

Réputation positive : le joueur gagne plus d'argent et de population
Réputation négative : le joueur a plus d'armée, peut acheter des mercenaires à
un meilleur prix

Éventuellement la rendre persistante entre les parties.

Down
^^^^

 - Ne pas prévenir avant d'attaquer
 - Attaquer ses alliés
 - Acheter des mercenaires
 - ...

Up
^^

 - Prévenant avant d'attaquer
 - S'allier avec un joueur
 - Aider ses alliés
 - ...

}}}

}}}

API
---

Constantes {{{
~~~~~~~~~~~~~~

MERCENAIRE_COUT = 42
MERCENAIRE_MAX_TOUR = 4224342432

ERREURS

}}}

joueur
~~~~~~

joueur_mon_id()
  :retourne: l'id du joueur (entier)

joueur_villes(joueur_id)
  :retourne: la liste des villes possedés par le joueur_id (liste de city_id)

joueur_reputation(joueur_id)
  :retourne: la réputation du joueur (entier relatif)

armee
~~~~

armee_deplace(depuis_ville_id, vers_ville_id)

ville
~~~~~

ville_proprietaire(ville_id)

ville_population(ville_id)

ville_ameliorer(ville_id)

ville_specialisation(ville_id)

ville_armee(ville_id)
  :ville_id: une ville id (entier)
  :retourne: la taille actuelle de l'armee pour cette ville_id (entier)

ville_routes(ville_id)
  :ville_id: une ville id (entier)
  :retourne: une liste de ville_id accessible depuis cette ville_id (liste
  d'entiers)

ville_or(ville_id)
  :ville_id: une ville id (entier)
  :retourne: la quantité courante d'or pour cette ville_id (entier)

ville_mercenaires(ville_id)
  :retourne: liste de mercenaires_id

mercenaires
~~~~~~~~~~~

mercenaires_acheter(ville_id, quantite, nombre_de_tours)

mercenaires_deplace(depuis_ville_id, vers_ville_id)

mercenaires_restants(ville_id)

mercenaires_info(mercenaire_id)

vim:set tw=80 fdm=marker:
