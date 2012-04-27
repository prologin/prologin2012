Stechec2
========

Installer
---------

Cloner le dépot (trouvez un moyen quelquonque) et le sujet de 2012 : ::

  git clone ... stechec2
  cd stechec2/games/
  git clone ... prologin2012

Configurer & installer
----------------------

::

  cd stechec2
  ./waf.py configure --prefix=/tmp --with-games=prologin2012 --enable-debug install

Générer les fichiers de base des candidats
------------------------------------------

::

  $PREFIX/generator player ./games/prologin2012/prolo2012.yml home

Compiler
--------

::

  cd {c,cxx,...}
  vim prologin.{c,cpp,py,...}
  make

Lancer un match
---------------

::

  $PREFIX/stechec2-server -f ./default.map -u $PREFIX/lib/libprolo2012.so -n 2
  $PREFIX/stechec2-client -f ./default.map -u $PREFIX/lib/libprolo2012.so -a ./home/.../champion.so
  $PREFIX/stechec2-client -f ./default.map -u $PREFIX/lib/libprolo2012.so -a ./home/.../champion.so
