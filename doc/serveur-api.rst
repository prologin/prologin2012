==================
Serveur 2012 - API
==================

.. default-domain:: c

-------------------
Constantes et types
-------------------

*À affiner empiriquement*

Personnages
===========

::

  ECLAIREUR_VISION      = 8
  ECLAIREUR_DEPLACEMENT = 8
  ECLAIREUR_VIE         = 3
  ECLAIREUR_ATTAQUE     = 3

::

  BARBARE_VISION      = 8
  BARBARE_DEPLACEMENT = 8
  BARBARE_VIE         = 3
  BARBARE_ATTAQUE     = 5


::

  ELITE_VISION      = 8
  ELITE_DEPLACEMENT = 8
  ELITE_VIE         = 3
  ELITE_ATTAQUE     = 2


.. type:: personnage_classe

  Type de personnage.

  .. code-block:: c

    enum personnage_classe {
      PERSONNAGE_ECLAIREUR,
      PERSONNAGE_BARBARE,
      PERSONNAGE_ELITE,
    }

.. type:: personnage_info

  Structure représentant un personnage.

  .. code-block:: c

    struct personnage_info {
      int equipe, // l'équipe à laquelle appartient le personnage
      int vie, // la vie courrante du personnage
    }

Case et carte
=============

.. type:: position

  Représente une position sur le terrain de jeu.

  .. code-block:: c

    struct position {
      int x; // coordonnée en x
      int y; // coordonnée en y
    }

.. type:: case_type
  
  .. code-block:: c

    enum case_type {
      CASE_TYPE_HERBE,
      CASE_TYPE_ROUTE,
      CASE_TYPE_FORET,
      CASE_TYPE_MARAIS,
      CASE_TYPE_COLLINE,
      CASE_TYPE_MUR
    }

---------
Fonctions
---------

Namespace carte
===============

.. function:: position carte_taille()

  Retourne la taille de la carte sous la forme d'une :c:type:`position`
  correspondant aux coordonées du point extrême.

.. function:: case_type carte_case_type(position pos)

  Retourne la natude de la case désignée par ``pos``.

.. function:: bool carte_case_cadavre(position pos)
  
  Retourne ``true`` si un cadavre se trouve sur la case ``pos``, ``false``
  sinon.

Namespace personnage
====================

.. function:: personnage_info personnage_info(int personnage_id)

  Retourne la struction personnage_info correspondant au personnage
  ``personnage_id``.

.. function:: position array personnage_vision(int personnage_id)

  Retourne l'ensembles des cases vue par le personnage désigné par
  ``personnage_id``.
