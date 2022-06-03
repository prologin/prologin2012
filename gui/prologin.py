# -*- coding: utf-8 -*-

import threading

try:
    import psyco
    psyco.full()
except:
    pass

import pygame

from api import *

import settings
from state_reader import StechecReader
from window import Window


settings.load([])
state_reader = StechecReader()

def run_pygame():
    pygame.init()
    window = Window(state_reader)
    window.run()

def partie_init():
    gfx_thread = threading.Thread(target=run_pygame)
    gfx_thread.start()

def jouer_placement():
    state_reader.put_state()

def jouer_deplacement():
    state_reader.put_state()

def jouer_attaque():
    state_reader.put_state()

def partie_fin():
    state_reader.do_end()
