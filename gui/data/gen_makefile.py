# -*- coding: utf-8 -*-

import os, sys
import subprocess

declarations = {
    'LAYER_FILTER': '$(PYTHON) svg-layer-filter.py',
    'PYTHON': '/usr/bin/env python2',
    'VECT_TO_PIX': '/usr/bin/env inkscape',
}

images_count = 0
images_progress = 0

export_dpi = float(90) * 2

classes = ('voleur', 'barbare', 'elfe')
cases = ('herbe', 'route', 'foret', 'marais', 'mur', 'tour')
specials = ('cadavre', 'many')

images = {
    'images.svg': (
        [(classe, (classe, )) for classe in classes] +
        [(case, ('herbe', case)) for case in cases] +
        [(name, (name, )) for name in specials]
    ),
    }

def gen_makefile(images, f):
    decls = dict(declarations)
    img_res = []
    img_inter = []
    rules = ''
    for svg, products in images.items():
        for img, layers in products:
            img_res.append('%s.png' % img)
            img_inter.append('%s.tmp.svg' % img)
            rules += '''
%(img)s.tmp.svg: %(svg)s
\t$(LAYER_FILTER) $< $@ %(layers)s

%(img)s.png: %(img)s.tmp.svg
\t$(VECT_TO_PIX) --file=$< --export-png=$@ --export-area-page --export-dpi=%(dpi)i
''' % {
        'svg': svg, 'img': img,
        'layers': ' '.join(layers), 'dpi': export_dpi
        }

    decls['PRODUCTS'] = ' '.join(img_res)
    decls['INTERMEDIARIES'] = ' '.join(img_inter)

    for (name, content) in decls.items():
        f.write('%s = %s\n' % (name, content))
    f.write('''
all: $(PRODUCTS)
clean:
\trm -f $(INTERMEDIARIES)
distclean: clean
\trm -f $(PRODUCTS)
''')
    f.write(rules)

gen_makefile(images, open('Makefile', 'w'))
