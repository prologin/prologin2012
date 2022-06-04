# -*- coding: utf-8 -*-

import pygame

from api import *

import data
import game
import utils
from widgets.scrolled import ScrolledWidget

class DetailsWidget(ScrolledWidget):
    PADDING = 8
    LINE_HEIGHT = 36

    def __init__(self, *args):
        self.font = pygame.font.Font(data.get_font('font.ttf'), 12)
        super(DetailsWidget, self).__init__(*args)
        self.game_state = None
        self.position = None
        self.selection = None

        self.directions = {
            orientation.ORIENTATION_NORD: utils.make_bordered_text(u'↑', self.font),
            orientation.ORIENTATION_EST: utils.make_bordered_text(u'→', self.font),
            orientation.ORIENTATION_SUD: utils.make_bordered_text(u'↓', self.font),
            orientation.ORIENTATION_OUEST: utils.make_bordered_text(u'←', self.font),
        }

    def plug(self, widgets):
        self.map_widget = widgets['map']

    def update_game(self, game):
        selected_unit = None
        if self.selection is not None:
            selected_area = self.game_state.map_units[self.position[1]][self.position[0]]
            selected_unit = self.game_state.units[selected_area[self.selection]]
        self.game_state = game
        if selected_unit is not None and selected_unit.life > 0:
            self.update_position(
                selected_unit.x, selected_unit.y,
                self.game_state.get_unit_position(selected_unit)
            )
        elif self.position:
            self.update_position(*self.position)

    def update_position(self, x, y, selection=None):
        if not self.game_state:
            return
        if (
            x < 0 or self.game_state.map_width <= x or
            y < 0 or self.game_state.map_height <= y
        ):
            self.list_surface = None
            self.scroll(0)
            return

        self.selection = selection
        self.position = (x, y)
        units = self.game_state.map_units[y][x]
        self.set_list_length(len(units) + 1)
        self._display_position(x, y)
        self._display_cell(self.game_state.map[y][x])
        for i, unit in enumerate(units, 1):
            if self.selection == i - 1:
                self.list_surface.fill(utils.DARK_GREY, (
                    0, i * self.LINE_HEIGHT,
                    self.width, self.LINE_HEIGHT
                ))
                self.map_widget.update_subjective(self.game_state.units[unit])
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
                zone_type.ZONE_HERBE: u'Herbe',
                zone_type.ZONE_ROUTE: u'Route',
                zone_type.ZONE_FORET: u'Forêt',
                zone_type.ZONE_MARAIS: u'Marais',
                zone_type.ZONE_MUR: u'Mur',
                zone_type.ZONE_TOUR: u'Tour',
            }[cell],
            True, utils.WHITE
        )
        self.list_surface.blit(text, (0, self.LINE_HEIGHT // 2))

    def _display_unit(self, unit, i):
        top_shift = i * self.LINE_HEIGHT
        left_shift = data.WIDTH + self.PADDING

        self.list_surface.blit(data.pix_cls[unit.class_], (
            0,
            top_shift + (self.LINE_HEIGHT - data.HEIGHT - data.OVERLAY) // 2
        ))

        # Display unit direction
        self.list_surface.blit(self.directions[unit.direction], (
            data.WIDTH * 3 // 4, top_shift + self.LINE_HEIGHT // 4
        ))

        # Display life bar
        bar_w = self.width - 3 * self.PADDING - data.WIDTH
        self.list_surface.fill(utils.RED, (
            left_shift, top_shift + 3,
            bar_w, 4
        ))
        self.list_surface.fill(utils.GREEN, (
            left_shift, top_shift + 3,
            bar_w * unit.life // unit.life_max, 4
        ))

        # Display unit class
        text_top_shift = top_shift + 3 + 4 + 3
        text = self.font.render(
            {
                perso_classe.PERSO_VOLEUR: u'Voleur',
                perso_classe.PERSO_BARBARE: u'Barbare',
                perso_classe.PERSO_ELFE: u'Elfe',
            }[unit.class_],
            True, utils.GREY
        )
        self.list_surface.blit(text, (left_shift, text_top_shift))

        # Display life
        text = self.font.render(
            u'%d / %d' % (unit.life, unit.life_max),
            True, utils.WHITE
        )
        text_left_shift = (self.width - text.get_size()[0]) // 2
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
            self.update_position(self.position[0], self.position[1], item)
        else:
            return False
