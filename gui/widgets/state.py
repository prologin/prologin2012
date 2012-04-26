# -*- coding: utf-8 -*-

import pygame

import data
import utils
from widgets.base import BaseWidget

class StateWidget(BaseWidget):

    TEXT_SIZE = 12
    TEXT_HEIGHT = 15
    LINES = 4

    HEIGHT = TEXT_HEIGHT * LINES

    def __init__(self, x, y, width):
        super(StateWidget, self).__init__(x, y, width, self.HEIGHT)
        self.font = pygame.font.Font(data.get_font('font.ttf'), self.TEXT_SIZE)
        self.turn = 0
        self.last_turn = None

    def _display_text(self, text, height, color):
        '''
        Display a centered text at a given height.
        '''
        surf = self.font.render(text, True, color)
        surf_w, surf_h = surf.get_size()
        self.surface.blit(surf, ((self.width - surf_w) / 2, height))

    def _display_turn(self):
        self._display_text(
            (
                u'Tour %d / %d' % (self.turn, self.last_turn)
                if self.last_turn else
                u'Tour %d' % self.turn
            ),
            0, utils.WHITE
        )

    def _display_help(self):
        self._display_text(
            u'H: afficher/cacher l’aide', 3 * self.TEXT_HEIGHT, utils.WHITE
        )

    def update_turn(self, turn, last_turn=None):
        self.turn = turn
        self.last_turn = last_turn
        self.surface.fill(utils.BLACK)
        self._display_turn()
        self._display_help()

    def update_wait(self):
        self.surface.fill(utils.BLACK)
        self._display_turn()
        self._display_text(u'Attente du prochain', self.TEXT_HEIGHT, utils.GREY)
        self._display_text(u'champion…', 2 * self.TEXT_HEIGHT, utils.GREY)
        self._display_help()

    def update_end(self):
        self.surface.fill(utils.BLACK)
        self._display_turn()
        self._display_text(u'Match terminé', self.TEXT_HEIGHT, utils.GREY)
        self._display_help()

    def update_wait_end(self, turn):
        self.turn = turn
        self.surface.fill(utils.BLACK)
        self._display_turn()
        self._display_text(u'Attente de la fin', self.TEXT_HEIGHT, utils.RED)
        self._display_text(u'du match', 2 * self.TEXT_HEIGHT, utils.RED)
        self._display_help()
