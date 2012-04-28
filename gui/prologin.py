# -*- coding: utf-8 -*-

import threading

try:
    import psyco
    psyco.full()
except:
    pass

import pygame
pygame.init()

from api import *

import settings
from state_reader import StechecReader
from window import Window


settings.load([])
state_reader = StechecReader()
window = Window(state_reader)
gfx_thread = threading.Thread(target=window.run)


def partie_init():
    gfx_thread.start()

def jouer_placement():
    state_reader.put_state()

def jouer_deplacement():
    pass

def jouer_attaque():
    pass

def partie_fin():
    state_reader.do_end()
