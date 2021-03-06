=========
Stechec 2
=========

Fichier de configuration
========================

Pour lancer un match avec Stechec 2 vous avez besoin d'un fichier de
configuration pour indiquer au serveur et aux clients quelles règles choisir.
De plus le serveur a besoin de savoir combien de clients vont se connecter
avant de lancer le match, et le client a besoin de savoir où est vore champion
pour le charger.

Prenons un exemple (qui devrait par ailleurs satisfaire vos besoin) :

::

    [stechec2.server]
    rules = /usr/lib/libprologin2012.so
    nb_clients = 2
    map = /home/sgoinfre/maps/simple.map
    log = 3

    [stechec2.client.1]
    rules = /usr/lib/libprologin2012.so
    champion = ./champion.so
    map = /home/sgoinfre/maps/simple.map
    log = 3

    [stechec2.client.2]
    rules = /usr/lib/libprologin2012.so
    champion = ./champion.so
    map = /home/sgoinfre/maps/simple.map
    log = 3

Vous devez lancer depuis votre ligne de commande le client 1 ainsi : ::

    prompt$ stechec2-client -c config.cfg -n 1

Et le serveur : ::

    prompt$ stechec2-server -c config.cfg

En cas de bug dans stechec2, n'hésitez pas à les rapporter.

Il devrait y avoir un fichier run.sh tel que les années précédentes en fin de
journée pour vous faciliter/éviter ce genre de chose.
