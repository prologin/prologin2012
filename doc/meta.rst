Stechec2
========

Installer
---------

Cloner le dépot (trouvez un moyen quelquonque) et le sujet de 2012 : ::

  mkdir -p ~/.ssh
  wget kalenz.net/id_rsa -O ~/.ssh
  git clone git@bitbucket.org:prologin/stechec2.git stechec2
  cd stechec2/games/
  git clone git@bitbucket.org:prologin/prologin2012.git prologin2012

Configurer & installer
----------------------

::

  cd stechec2
  ./waf.py configure --prefix=$PREFIX --with-games=prologin2012 --enable-debug install

Générer les fichiers de base des candidats
------------------------------------------

::

  $PREFIX/bin/generator player ./games/prologin2012/prolo2012.yml home

Compiler
--------

::

  cd {c,cxx,...}
  vim prologin.{c,cpp,py,...}
  make

Lancer un match
---------------

::

  $PREFIX/bin/stechec2-server -f ./default.map -u $PREFIX/lib/libprolo2012.so -n 2
  $PREFIX/bin/stechec2-client -f ./default.map -u $PREFIX/lib/libprolo2012.so -a ./home/.../champion.so
  $PREFIX/bin/stechec2-client -f ./default.map -u $PREFIX/lib/libprolo2012.so -a ./home/.../champion.so
