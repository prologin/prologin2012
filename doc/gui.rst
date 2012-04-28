===
GUI
===

Elle était attendu, la voilà !

Vous pouvez trouver la GUI dans /home/sgoinfre/gui. La GUI est en réalité un
client presque comme votre champion. La seule différence c'est qu'elle n'est pas
soumise à la dictature de la sandbox, ce qui lui permet de bloquer l'exécution
du serveur pour vous permettre de mieux observer l'état du jeu lors de chaque
tour.

Pour l'utiliser, vous devez lancer votre stechec2-client spécifique à la GUI
dans le dossier même de ses sources et rajouter quelques lignes à votre fichier
de conf. Mais comme quelques exemples valent mieux qu'une longue explication :

::

    [stechec2.server]
    rules = /usr/lib/libprolo2012.so
    nb_clients = 2
    map = /home/sgoinfre/maps/simple.map
    log = 3

    [stechec2.client.1]
    rules = /usr/lib/libprolo2012.so
    champion = ./champion.so
    map = /home/sgoinfre/maps/simple.map
    log = 3

    [stechec2.client.2]
    rules = /usr/lib/libprolo2012.so
    champion = ./champion.so
    map = /home/sgoinfre/maps/simple.map
    log = 3

    [stechec2.client.gui]
    rules = /usr/lib/libprolo2012.so
    champion = ./gui.so
    map = /home/sgoinfre/maps/simple.map
    log = 3
    spectator = 1

Vous devez lancer depuis votre ligne de commande la GUI ainsi : ::

    prompt$ stechec2-client -c config.cfg -n gui

**Vous devez être dans le dossier de la gui pour la lancer !**

PS : désolé pour le retard.
