# -*- coding: utf-8 -*-

import pygame

import data
import game
import utils
from widgets.scrolled import ScrolledWidget

class ActionsWidget(ScrolledWidget):
    PADDING = 8
    LINE_HEIGHT = 15
    LINES = 3

    HEIGHT = LINE_HEIGHT * LINES + 2 * PADDING

    def __init__(self, x, y, width):
        self.font = pygame.font.Font(data.get_font('font.ttf'), 12)
        super(ActionsWidget, self).__init__(x, y, width, self.HEIGHT)

    def update_actions(self, actions):
        '''
        Update the list of displayed actions. Should be updated when changing
        turn.
        '''
        self.set_list_length(len(actions))
        vshift = 0
        for action in actions:
            text = self.font.render(unicode(action), True, utils.WHITE)
            self.list_surface.blit(text, (0, vshift))
            vshift += text.get_size()[1]
        self.scroll(0)
