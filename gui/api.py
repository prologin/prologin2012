# -*- coding: iso-8859-1 -*-

# Vision du Voleur
VOLEUR_VISION = 4

# Déplacement du Voleur
VOLEUR_DEPLACEMENT = 8

# Vie du Voleur
VOLEUR_VIE = 10

# Attaque du voleur
VOLEUR_ATTAQUE = 3

# Portée de l'arme du Voleur
VOLEUR_ATT_PORTEE = 1

# Zone de dégats de l'arme du Voleur
VOLEUR_ATT_ZONE = 1

# Vision du Barbare
BARBARE_VISION = 5

# Déplacement du Barbare
BARBARE_DEPLACEMENT = 8

# Vie du Barbare
BARBARE_VIE = 10

# Attaque du Barbare
BARBARE_ATTAQUE = 5

# Portée de l'arme du Barbare
BARBARE_ATT_PORTEE = 5

# Zone de dégats de l'arme du Barbare
BARBARE_ATT_ZONE = 2

# Vision de l'Elfe
ELFE_VISION = 5

# Déplacement de l'Elfe
ELFE_DEPLACEMENT = 8

# Vie de l'Elfe
ELFE_VIE = 10

# Attaque de l'Elfe
ELFE_ATTAQUE = 2

# Portée de l'arme de l'Elfe
ELFE_ATT_PORTEE = 8

# Zone de dégats de l'arme de l'Elfe
ELFE_ATT_ZONE = 1

# Type de personnage
(
    PERSO_VOLEUR, # <- Voleur
    PERSO_BARBARE, # <- Barbare
    PERSO_ELFE, # <- Elfe
) = range(3)


# Type de zone
(
    ZONE_HERBE, # <- Herbe
    ZONE_ROUTE, # <- Route
    ZONE_FORET, # <- Forêt
    ZONE_MARAIS, # <- Marais
    ZONE_MUR, # <- Mur
    ZONE_TOUR, # <- Tour de guet
    ZONE_ERREUR, # <- Erreur, case impossible
) = range(7)


# Type d'attaque
(
    ATTAQUE_NORMALE, # <- Attaque normale dont les dégats dépendent du personnage
    ATTAQUE_PALANTIR, # <- Attaque 'Palantir' du Voleur
    ATTAQUE_TRAITRISE, # <- Attaque 'Traîtrise' du Voleur
    ATTAQUE_BASTOOOON, # <- Attaque 'Bastoooon' de du Barbare
    ATTAQUE_FUS_RO_DAH, # <- Attaque 'Fus Ro Dah' du Barbare
    ATTAQUE_I_SEE, # <- Attaque 'I see what you did there.' de l'Elfe
    ATTAQUE_LOTO, # <- Attaque 'Loto, à qui le tour' de l'Elfe
) = range(7)


# Orientation du personnage
(
    ORIENTATION_NORD, # <- Orienté au nord
    ORIENTATION_EST, # <- Orienté à l'est
    ORIENTATION_SUD, # <- Orienté au sud
    ORIENTATION_OUEST, # <- Orienté à l'ouest
) = range(4)


# Erreurs possibles
(
    POSITION_IMPOSSIBLE, # <- La position n'existe pas
    PERSONNAGE_IMPOSSIBLE, # <- Le personnage n'existe pas ou ne vous appartient pas
    CHEMIN_IMPOSSIBLE, # <- Le chemin est impossible
    ATTAQUE_INDISPONIBLE, # <- L'attaque n'est pas utilisable pour le moment
    OK, # <- Pas d'erreur
) = range(5)


from collections import namedtuple

# Représente une position sur le terrain du jeu
position = namedtuple("position",
    'x ' # <- coordonnée en X
    'y ' # <- coordonnée en Y
)


# Représente les informations sur un personnage
perso_info = namedtuple("perso_info",
    'equipe ' # <- Équipe à laquelle appartient le personnage
    'classe ' # <- Classe du personnage
    'vie ' # <- Vie courante du personnage
    'direction ' # <- Orientation du personnage
)


