

===
API
===

..
   Ce fichier a été généré avec gen/make_sphinx.rsphinx
   Ne faites pas l'autiste, ne le modifiez pas directement

Constantes
==========


.. c:var:: RANGER_VISION

  :Valeur: 8
  :Description:
    Vision du Ranger

    

.. c:var:: RANGER_DEPLACEMENT

  :Valeur: 8
  :Description:
    Déplacement du Ranger

    

.. c:var:: RANGER_VIE

  :Valeur: 3
  :Description:
    Vie du Ranger

    

.. c:var:: RANGER_ATTAQUE

  :Valeur: 3
  :Description:
    Attaque du ranger

    

.. c:var:: RANGER_ATT_PORTEE

  :Valeur: 1
  :Description:
    Portée de l'arme du Ranger

    

.. c:var:: RANGER_ATT_ZONE

  :Valeur: 1
  :Description:
    Zone de dégats de l'arme du Ranger

    

.. c:var:: BARBARE_VISION

  :Valeur: 8
  :Description:
    Vision du Barbare

    

.. c:var:: BARBARE_DEPLACEMENT

  :Valeur: 8
  :Description:
    Déplacement du Barbare

    

.. c:var:: BARBARE_VIE

  :Valeur: 3
  :Description:
    Vie du Barbare

    

.. c:var:: BARBARE_ATTAQUE

  :Valeur: 5
  :Description:
    Attaque du Barbare

    

.. c:var:: BARBARE_ATT_PORTEE

  :Valeur: 5
  :Description:
    Portée de l'arme du Barbare

    

.. c:var:: BARBARE_ATT_ZONE

  :Valeur: 2
  :Description:
    Zone de dégats de l'arme du Barbare

    

.. c:var:: ELFE_VISION

  :Valeur: 8
  :Description:
    Vision de l'Elfe

    

.. c:var:: ELFE_DEPLACEMENT

  :Valeur: 8
  :Description:
    Déplacement de l'Elfe

    

.. c:var:: ELFE_VIE

  :Valeur: 3
  :Description:
    Vie de l'Elfe

    

.. c:var:: ELFE_ATTAQUE

  :Valeur: 2
  :Description:
    Attaque de l'Elfe

    

.. c:var:: ELFE_ATT_PORTEE

  :Valeur: 8
  :Description:
    Portée de l'arme de l'Elfe

    

.. c:var:: ELFE_ATT_ZONE

  :Valeur: 1
  :Description:
    Zone de dégats de l'arme de l'Elfe

    


Énumérations
============



.. c:type:: perso_classe

  :Description:
      Type de personnage
  :Valeurs:
    
      :PERSO_RANGER:
        Ranger

    
      :PERSO_BARBARE:
        Barbare

    
      :PERSO_ELFE:
        Elfe

    


.. c:type:: case_type

  :Description:
      Type de case
  :Valeurs:
    
      :CASE_HERBE:
        Herbe

    
      :CASE_ROUTE:
        Route

    
      :CASE_FORET:
        Forêt

    
      :CASE_MARAIS:
        Marais

    
      :CASE_MUR:
        Mur

    
      :CASE_TOUR:
        Tour de guet

    


.. c:type:: attaque_type

  :Description:
      Type d'attaque
  :Valeurs:
    
      :ATTAQUE_NORMALE:
        Attaque normale

    
      :ATTAQUE_PALANTIR:
        Attaque 'Palantir' de l'Elfe

    
      :ATTAQUE_DANS_TO_DOS:
        Attaque 'Dans ton dos' de l'Elfe

    
      :ATTAQUE_BASTOOOON:
        Attaque 'Bastoooon' de du Barbare

    
      :ATTAQUE_FUS_RO_DAH:
        Attaque 'Fus Ro Dah' du Barbare

    
      :ATTAQUE_I_SEE:
        Attaque 'I see what you did there.' du Ranger

    
      :ATTAQUE_LOTO:
        Attaque 'Loto, à qui le tour' du Ranger

    


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
        orientation orientation;
    };

  :Description: Représente les informations sur un personnage

  :Champs:
    :equipe: Équipe à laquelle appartient le personnage
    :classe: Classe du personnage
    :vie: Vie courante du personnage
    :orientation: Orientation du personnage
    


Fonctions
=========



.. c:function:: position carte_taille()

    Retourne la taille de la carte sous la forme d'une position correspondant aux coordonnées du point extrême.

    



  


.. c:function:: case_type carte_case_type(position pos)

    Retourne la nature de la case désignée par ``pos``.

    


    

    
      
    :param pos: Position
      
    


  


.. c:function:: bool carte_case_cadavre(position pos)

    Retourne ``true`` si un cadavre se trouve sur la case ``pos``.

    


    

    
      
    :param pos: Position
      
    


  


.. c:function:: perso_info array carte_case_perso(position pos)

    Retourne la liste des personnages sur la case.

    


    

    
      
    :param pos: Position de la case
      
    


  


.. c:function:: position array chemin(position p1, position p2)

    Renvoie le chemin le plus court entre deux points (fonction lente)

    


    

    
      
    :param p1: position de départ
      
    
      
    :param p2: position d'arrivée
      
    


  


.. c:function:: erreur perso_deplace(perso_info perso, orientation array chemin, orientation orientation)

    Déplace le personnage ``perso`` en suivant un le chemin ``chemin`` donné sous forme d'une suite d'``orientation``, orientant le personnage sur la case d'arrivée dans la direction ``orientation``.

    


    

    
      
    :param perso: Personnage à déplacer
      
    
      
    :param chemin: Tableau d'``orientation`` composants le chemin
      
    
      
    :param orientation: Orientation sur la dernière case d'arrivée
      
    


  


.. c:function:: position array perso_penombre(perso_info perso, position case)

    Récupère la liste des cases sur lesquelles des personnages ont été aperçus dans la pénombre par ``perso`` lors de son passage sur une ``case`` de son déplacement.

    


    

    
      
    :param perso: Personnage
      
    
      
    :param case: Case de son déplacement
      
    


  


.. c:function:: position array perso_penombre_case(perso_info perso)

    Récupère la liste des cases sur lesquelles un personnage est passé au tour précédent.

    


    

    
      
    :param perso: Personnage
      
    


  


.. c:function:: position array perso_vision(perso_info perso)

    Récupère la liste des cases sur lesquelles ``perso`` voit d'autre personnages.

    


    

    
      
    :param perso: Personnage
      
    


  


.. c:function:: erreur perso_attaque(perso_info perso, attaque_type attaque, position pos)

    Effectue l'attaque ``attaque`` avec le personnage ``perso`` sur la case ``pos``.

    


    

    
      
    :param perso: Personnage
      
    
      
    :param attaque: Attaque à utiliser
      
    
      
    :param pos: Case à attaquer
      
    


  


.. c:function:: int perso_attaque_recharge(perso_info perso, attaque_type attaque)

    Retourne le temps de recharge restant pour l'attaque ``attaque`` du personnage ``perso``.

    


    

    
      
    :param perso: Personnage
      
    
      
    :param attaque: Attaque à vérifier
      
    


  


.. c:function:: bool annuler()

    Annule l'action précédente. Renvoie ``true`` si une action a été annulée, ``false`` sinon.

    



  


.. c:function:: int mon_equipe()

    Retourne le numéro de votre équipe

    



  


.. c:function:: int array scores()

    Retourne les scores de chaque équipe

    



  


.. c:function:: int nombre_equipes()

    Retourne le nombre d'équipes sur le terrain

    



  


.. c:function:: int tour_actuel()

    Retourne le numéro du tour actuel

    



  


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

    



  

