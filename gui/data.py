# -*- coding: utf-8 -*-

import os.path
import re

import pygame

import api


paths = {
    "prefix": "/home/pmderodat/usr",
    "exec_prefix": "${prefix}",
    "sysconfdir": "${prefix}/etc",
    "imagesdir": "${prefix}/share/stechec/prolo2011/graphics",
    "cfgdir": "${prefix}/etc/stechec",
    "bindir": "${exec_prefix}/bin",
}

def expand_path(p):
    return re.sub(r'\$\{(.*?)\}', lambda m: expand_path(paths[m.group(1)]), p)

# paths = {name: expand_path(path) for name, path in paths.iteritems()}

# images_dir = paths['imagesdir']

images_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'data')

def get_image(name):
    return os.path.join(images_dir, name)

def get_font(name):
    return os.path.join(images_dir, name)



WIDTH = 16 * 2
HEIGHT = 24 * 2
OVERLAY = 8 * 2


classes = ('voleur', 'barbare', 'elfe')
cases = ('herbe', 'route', 'foret', 'marais', 'mur', 'tour')
specials = ('many',)
images = [
    (name, get_image('%s.png' % name))
    for name in classes + cases + specials
]

pix = None
pix_cls = None
pix_cells = None

def load_images():
    global pix, pix_cls, pix_cells
    pix = {}
    pix_cls = {}
    pix_cells = {}
    for name, path in images:
        img = pygame.image.load(path).convert_alpha()
        pix[name] = img
        if name in classes:
            pix_cls[getattr(api, 'PERSO_%s' % name.upper())] = img
        elif name in cases:
            pix_cells[getattr(api, 'ZONE_%s' % name.upper())] = img
