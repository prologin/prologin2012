==================
Serveur 2012 - API
==================

----------
Constantes
----------

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

Case
====

::

  CASE_TYPE_HERBE   = 0
  CASE_TYPE_ROUTE   = 1
  CASE_TYPE_FORET   = 2
  CASE_TYPE_MARAIS  = 3
  CASE_TYPE_COLLINE = 4
  CASE_TYPE_MUR     = 5

---------
Fonctions
---------

carte
=====

.. function:: carte_taille()

  :rtype: taille de la carte : tuple (x, y)

.. function:: carte_case_type(pos_s)

  :param pos_s: la case désignée : tuple position (x, y)
  :rtype: la nature de la case : enum_case_type

.. function:: carte_case_cadavre(pos_s)
  
  Retourne ``true`` si un cadavre se trouve sur la case ``pos_s``, ``false``
  sinon.

  :param pos_s: tuple position
  :rtype: bool
