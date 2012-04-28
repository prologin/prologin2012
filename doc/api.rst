

===
API
===

..
   This file was generated using gen/make_sphinx.rsphinx
   Do not modify unless you are absolutely sure of what you are doing

Constantes
==========


.. c:var:: VOLEUR_VISION

  :Valeur: 5
  :Description:
    Vision du Voleur

    

.. c:var:: VOLEUR_DEPLACEMENT

  :Valeur: 10
  :Description:
    Déplacement du Voleur

    

.. c:var:: VOLEUR_VIE

  :Valeur: 10
  :Description:
    Vie du Voleur

    

.. c:var:: VOLEUR_ATTAQUE

  :Valeur: 5
  :Description:
    Attaque du voleur

    

.. c:var:: VOLEUR_PALANTIR_CD

  :Valeur: 3
  :Description:
    Cooldown de l'attaque "Palantir" du Voleur

    

.. c:var:: VOLEUR_TRAITRISE_CD

  :Valeur: 5
  :Description:
    Cooldown de l'attaque "Traîtrise" du Voleur

    

.. c:var:: BARBARE_VISION

  :Valeur: 4
  :Description:
    Vision du Barbare

    

.. c:var:: BARBARE_DEPLACEMENT

  :Valeur: 8
  :Description:
    Déplacement du Barbare

    

.. c:var:: BARBARE_VIE

  :Valeur: 10
  :Description:
    Vie du Barbare

    

.. c:var:: BARBARE_ATTAQUE

  :Valeur: 3
  :Description:
    Attaque du Barbare

    

.. c:var:: BARBARE_BASTOOOON_CD

  :Valeur: 3
  :Description:
    Cooldown de l'attaque "Bastoooon" du Barbare

    

.. c:var:: BARBARE_BASTOOOON_PORTEE

  :Valeur: 3
  :Description:
    Portée de l'attaque "Bastoooon" du Barbare

    

.. c:var:: BARBARE_FUS_RO_DAH_CD

  :Valeur: 5
  :Description:
    Cooldown de l'attaque "Fus Ro Dah" du Barbare

    

.. c:var:: ELFE_VISION

  :Valeur: 4
  :Description:
    Vision de l'Elfe

    

.. c:var:: ELFE_DEPLACEMENT

  :Valeur: 6
  :Description:
    Déplacement de l'Elfe

    

.. c:var:: ELFE_VIE

  :Valeur: 10
  :Description:
    Vie de l'Elfe

    

.. c:var:: ELFE_ATTAQUE

  :Valeur: 2
  :Description:
    Attaque de l'Elfe

    

.. c:var:: ELFE_LOTO_CD

  :Valeur: 5
  :Description:
    Cooldown de l'attaque "Loto, à qui le tour ?" de l'Elfe

    

.. c:var:: ELFE_I_SEE_CD

  :Valeur: 5
  :Description:
    Cooldown de l'attaque "I See What You Did There" de l'Elfe

    


Énumérations
============



.. c:type:: perso_classe

  :Description:
      Type de personnage
  :Valeurs:
    
      :PERSO_VOLEUR:
        Voleur

    
      :PERSO_BARBARE:
        Barbare

    
      :PERSO_ELFE:
        Elfe

    


.. c:type:: zone_type

  :Description:
      Type de zone
  :Valeurs:
    
      :ZONE_HERBE:
        Herbe

    
      :ZONE_ROUTE:
        Route

    
      :ZONE_FORET:
        Forêt

    
      :ZONE_MARAIS:
        Marais

    
      :ZONE_MUR:
        Mur

    
      :ZONE_TOUR:
        Tour de guet

    
      :ZONE_ERREUR:
        Erreur, case impossible

    


.. c:type:: attaque_type

  :Description:
      Type d'attaque
  :Valeurs:
    
      :ATTAQUE_NORMALE:
        Attaque normale dont les dégats dépendent du personnage

    
      :ATTAQUE_PALANTIR:
        Attaque 'Palantir' du Voleur

    
      :ATTAQUE_TRAITRISE:
        Attaque 'Traîtrise' du Voleur

    
      :ATTAQUE_BASTOOOON:
        Attaque 'Bastoooon' de du Barbare

    
      :ATTAQUE_FUS_RO_DAH:
        Attaque 'Fus Ro Dah' du Barbare

    
      :ATTAQUE_I_SEE:
        Attaque 'I see what you did there.' de l'Elfe

    
      :ATTAQUE_LOTO:
        Attaque 'Loto, à qui le tour' de l'Elfe

    


.. c:type:: orientation

  :Description:
      Orientation du personnage
  :Valeurs:
    
      :ORIENTATION_NORD:
        Orienté au nord

    
      :ORIENTATION_EST:
        Orienté à l'est

    
      :ORIENTATION_SUD:
        Orienté au sud

    
      :ORIENTATION_OUEST:
        Orienté à l'ouest

    


.. c:type:: erreur

  :Description:
      Erreurs possibles
  :Valeurs:
    
      :POSITION_IMPOSSIBLE:
        La position n'existe pas

    
      :PERSONNAGE_IMPOSSIBLE:
        Le personnage n'existe pas ou ne vous appartient pas

    
      :CHEMIN_IMPOSSIBLE:
        Le chemin est impossible

    
      :ATTAQUE_INDISPONIBLE:
        L'attaque n'est pas utilisable pour le moment

    
      :OK:
        Pas d'erreur

    


Structures
==========



.. c:type:: position

  .. code-block:: c

    struct position {
        int x;
        int y;
    };

  :Description: Représente une position sur le terrain du jeu

  :Champs:
    :x: coordonnée en X
    :y: coordonnée en Y
    


.. c:type:: perso_info

  .. code-block:: c

    struct perso_info {
        int equipe;
        perso_classe classe;
        int vie;
        orientation direction;
    };

  :Description: Représente les informations sur un personnage

  :Champs:
    :equipe: Équipe à laquelle appartient le personnage
    :classe: Classe du personnage
    :vie: Vie courante du personnage
    :direction: Orientation du personnage
    


Fonctions
=========



.. c:function:: position carte_taille()

    Retourne la taille de la carte.

    



  


.. c:function:: position carte_depart()

    Retourne la position de départ des personnages sur la map.

    



  


.. c:function:: zone_type carte_zone_type(position pos)

    Retourne la nature de la zone désignée par ``pos``.

    


    

    
      
    :param pos: Position
      
    


  


.. c:function:: perso_info array carte_zone_perso(position pos)

    Retourne la liste des personnages sur la zone.

    


    

    
      
    :param pos: Position de la zone
      
    


  


.. c:function:: int distance(position p1, position p2)

    Renvoie le nombre de points nécessaires pour parcourir le chemin le plus court entre deux points. Renvoie -1 en cas de positions invalides ou de chemin inexistant.

    


    

    
      
    :param p1: position de départ
      
    
      
    :param p2: position d'arrivée
      
    


  


.. c:function:: position array chemin(position p1, position p2)

    Renvoie le chemin le plus court entre deux points. Si le chemin n'existe pas, ou si les positions sont invalides, le chemin renvoyé est vide.

    


    

    
      
    :param p1: position de départ
      
    
      
    :param p2: position d'arrivée
      
    


  


.. c:function:: erreur perso_deplace(perso_info perso, position array chemin, orientation direction)

    Déplace le personnage ``perso`` en suivant un le chemin ``chemin`` donné sous forme d'une suite de ``position``, orientant le personnage sur la zone d'arrivée dans la direction ``orientation``.

    


    

    
      
    :param perso: Personnage à déplacer
      
    
      
    :param chemin: Tableau de ``position`` composants le chemin
      
    
      
    :param direction: Orientation sur la dernière zone d'arrivée
      
    


  


.. c:function:: position array perso_penombre(perso_info perso)

    Récupère la liste des zones sur lesquelles des personnages ont été aperçus dans la pénombre par ``perso``.

    


    

    
      
    :param perso: Personnage
      
    


  


.. c:function:: position array perso_vision(perso_info perso)

    Récupère la liste des zones dans le champs de vision de ``perso``.

    


    

    
      
    :param perso: Personnage
      
    


  


.. c:function:: position array perso_vision_personnages(perso_info perso)

    Récupère la liste des zones dans le champs de vision de ``perso`` où sont situés un ou plusieurs personnages (amis ou ennemis).

    


    

    
      
    :param perso: Personnage
      
    


  


.. c:function:: position array palantir_vision()

    Récupère la liste des positions sur lesquelles le palantír du voleur voit d'autre personnages.

    



  


.. c:function:: position array elfe_vision()

    Récupère la liste des zones sur lesquelles l'elfe peut voir via son attaque "I See What You Did There".

    



  


.. c:function:: erreur perso_attaque(perso_info perso, attaque_type attaque, position pos)

    Effectue l'attaque ``attaque`` avec le personnage ``perso`` sur la zone ``pos``.

    


    

    
      
    :param perso: Personnage
      
    
      
    :param attaque: Attaque à utiliser
      
    
      
    :param pos: Zone à attaquer
      
    


  


.. c:function:: int perso_attaque_recharge(perso_info perso, attaque_type attaque)

    Retourne le temps de recharge restant pour l'attaque ``attaque`` du personnage ``perso``.

    


    

    
      
    :param perso: Personnage
      
    
      
    :param attaque: Attaque à vérifier
      
    


  


.. c:function:: position perso_position(perso_info perso)

    Retourne la position du personnage ``perso``.

    


    

    
      
    :param perso: Personnage
      
    


  


.. c:function:: perso_info perso_classe_info(perso_classe classe)

    Retourne le personnage de type ``classe`` de sa propre équipe.

    


    

    
      
    :param classe: Classe
      
    


  


.. c:function:: int mon_equipe()

    Retourne le numéro de votre équipe

    



  


.. c:function:: int array scores()

    Retourne les scores de chaque équipe

    



  


.. c:function:: int nombre_equipes()

    Retourne le nombre d'équipes sur le terrain

    



  


.. c:function:: int tour_actuel()

    Retourne le numéro du tour actuel

    



  


.. c:function:: int nombre_tours_placement()

    Retourne le nombre de tours de placements

    



  


.. c:function:: int nombre_tours()

    Retourne le nombre total de tours

    



  


Fonctions utilisateur
=====================



.. c:function:: void partie_init()

    Fonction appellée au début de la partie

    



  


.. c:function:: void jouer_placement()

    Fonction appellée pendant la phase de placement

    



  


.. c:function:: void jouer_deplacement()

    Fonction appellée pendant la phase de déplacement

    



  


.. c:function:: void jouer_attaque()

    Fonction appellée pendant la phase d'attaque

    



  


.. c:function:: void partie_fin()

    Fonction appellée à la fin de la partie

    



  

