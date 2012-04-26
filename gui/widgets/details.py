# -*- coding: utf-8 -*-

import pygame

from api import *

import data
import game
import utils
from widgets.scrolled import ScrolledWidget

class DetailsWidget(ScrolledWidget):
    PADDING = 8
    LINE_HEIGHT = 30

    def __init__(self, *args):
        self.font = pygame.font.Font(data.get_font('font.ttf'), 12)
        super(DetailsWidget, self).__init__(*args)
        self.game_state = None
        self.position = None

        self.directions = {
            ORIENTATION_NORD: self.font.render(u'↑', True, utils.WHITE),
            ORIENTATION_EST: self.font.render(u'→', True, utils.WHITE),
            ORIENTATION_SUD: self.font.render(u'↓', True, utils.WHITE),
            ORIENTATION_OUEST: self.font.render(u'←', True, utils.WHITE),
        }

    def plug(self, widgets):
        self.map_widget = widgets['map']

    def update_game(self, game):
        self.game_state = game
        if self.position:
            self.update_position(*position)

    def update_position(self, x, y):
        if not self.game_state:
            return
        if (
            x < 0 or self.game_state.map_width <= x or
            y < 0 or self.game_state.map_height <= y
        ):
            self.list_surface = None
            self.scroll(0)
            return

        self.position = (x, y)
        units = self.game_state.map_units[y][x]
        self.set_list_length(len(units) + 1)
        self._display_position(x, y)
        self._display_cell(self.game_state.map[y][x])
        for i, unit in enumerate(units, 1):
            self._display_unit(self.game_state.units[unit], i)

        self.scroll(0)

    def _display_position(self, x, y):
        text = self.font.render(
            u'Position : (%d, %d)' % (x, y),
            True, utils.WHITE
        )
        self.list_surface.blit(text, (0, 0))

    def _display_cell(self, cell):
        text = self.font.render(
            {
                ZONE_HERBE: u'Herbe',
                ZONE_ROUTE: u'Route',
                ZONE_FORET: u'Forêt',
                ZONE_MARAIS: u'Marais',
                ZONE_MUR: u'Mur',
                ZONE_TOUR: u'Tour',
            }[cell],
            True, utils.WHITE
        )
        self.list_surface.blit(text, (0, self.LINE_HEIGHT / 2))

    def _display_unit(self, unit, i):
        top_shift = i * self.LINE_HEIGHT
        left_shift = data.WIDTH + self.PADDING

        self.list_surface.blit(data.pix_cls[unit.class_], (
            0,
            top_shift + (self.LINE_HEIGHT - data.HEIGHT - data.OVERLAY) / 2
        ))

        # Display unit direction
        self.list_surface.blit(self.directions[unit.direction], (
            data.WIDTH * 3 / 4, top_shift + self.LINE_HEIGHT / 4
        ))

        # Display life bar
        bar_w = self.width - 3 * self.PADDING - data.WIDTH
        self.list_surface.fill(utils.RED, (
            left_shift, top_shift + 3,
            bar_w, 4
        ))
        self.list_surface.fill(utils.GREEN, (
            left_shift, top_shift + 3,
            bar_w * unit.life / unit.life_max, 4
        ))

        # Display unit class
        text_top_shift = top_shift + 3 + 4 + 3
        text = self.font.render(
            {
                PERSO_VOLEUR: u'Voleur',
                PERSO_BARBARE: u'Barbare',
                PERSO_ELFE: u'Elfe',
            }[unit.class_],
            True, utils.GREY
        )
        self.list_surface.blit(text, (left_shift, text_top_shift))

        # Display life
        text = self.font.render(
            u'%d / %d' % (unit.life, unit.life_max),
            True, utils.WHITE
        )
        text_left_shift = (self.width - text.get_size()[0]) / 2
        self.list_surface.blit(text, (text_left_shift, text_top_shift))

        # Display team number
        text = self.font.render(u'Équipe %d' % unit.player, True,
                utils.LIGHT_GREY)
        text_left_shift = self.width - 2 * self.PADDING - text.get_size()[0]
        self.list_surface.blit(text, (text_left_shift, text_top_shift))

    def handle_click(self, x, y, but1, but2, but3):
        result = super(DetailsWidget, self).handle_click(
            x, y, but1, but2, but3
        )
        if result:
            return True
        if not self.position:
            return False

        item = self.is_click_inside(x, y)
        if not item:
            return False
        if not but1:
            return True
        item -= 1
        units = self.game_state.map_units[self.position[1]][self.position[0]]
        if item < len(units):
            self.map_widget.update_subjective(
                self.game_state.units[units[item]]
            )
        else:
            return False
