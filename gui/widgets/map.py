# -*- coding: utf-8 -*-

import pygame

from api import *
import data
import game
import utils
from widgets.base import BaseWidget


class MapWidget(BaseWidget):

    def __init__(self, *args):
        super(MapWidget, self).__init__(*args)
        self.game_state = None
        self.position = None
        self.follow_unit = None
        self.map_surface = None
        self.font = pygame.font.Font(data.get_font('font.ttf'), 12)
        self.cells_width = self.width // data.WIDTH
        self.cells_height = (self.height - data.OVERLAY) // (data.HEIGHT - data.OVERLAY)
        self.center = (self.cells_width // 2, self.cells_height // 2)

    def plug(self, widgets):
        self.details_widget = widgets['details']
        self.minimap = widgets['minimap']

    def handle_view_click(self, x, y, but1, but2, but3):
        x = x // data.WIDTH + self.position[0]
        y = (y - data.OVERLAY) // (data.HEIGHT - data.OVERLAY) + self.position[1]
        if but1:
            self.details_widget.update_position(x, y)
            self.update_subjective()
        elif but3:
            self.update_display((x - self.center[0], y - self.center[1]))

    def handle_click(self, x, y, but1, but2, but3):
        coords = self.is_click_inside(x, y)
        if not coords:
            return False
        if self.game_state is None:
            return True
        self.handle_view_click(coords[0], coords[1], but1, but2, but3)
        return True

    def update_game(self, game_state):
        self.game_state = game_state
        self.position_max = (
            utils.set_between(game_state.map_width - self.cells_width, lower=0),
            utils.set_between(game_state.map_width - self.cells_height, lower=0)
        )
        # TODO: update the followed unit.
        self.follow_unit = None
        self.surface.fill(utils.BLACK)
        if self.game_state is None:
            return
        if not self.position:
            surf_size = (
                game_state.map_width * data.WIDTH,
                game_state.map_height * (data.HEIGHT - data.OVERLAY) + data.OVERLAY
            )
            self.map_surface = utils.make_surface(*surf_size)
            self.dark_surface = utils.make_surface(*surf_size)
            self.position = (0, 0)

        map = game_state.map
        map_units = game_state.map_units
        unit_numbers = []
        for y, (row, row_units) in enumerate(zip(map, map_units)):
            for x, (cell, units) in enumerate(zip(row, row_units)):
                coords = (data.WIDTH * x, (data.HEIGHT - data.OVERLAY) * y)
                self.map_surface.blit(data.pix_cells[cell], coords)
                if units:
                    self.map_surface.blit(data.pix['many'], coords)
                    unit_number = utils.make_bordered_text(str(len(units)), self.font)
                    unit_number_w, unit_number_h = unit_number.get_size()
                    unit_numbers.append((unit_number, (
                        coords[0] + data.WIDTH - unit_number_w,
                        coords[1] + data.HEIGHT - unit_number_h,
                    )))
        for args in unit_numbers:
            self.map_surface.blit(*args)

        self.update_display()

    def _remove_fog(self, x, y):
        self.dark_surface.fill((0, 0, 0, 0), (
            x * data.WIDTH, y * (data.HEIGHT - data.OVERLAY) + data.OVERLAY,
            data.WIDTH, data.HEIGHT - data.OVERLAY
        ))

    def update_subjective(self, unit=None):
        self.follow_unit = unit
        if not unit:
            return self.update_display()
        self.dark_surface.fill(utils.BLACK + (192, ))

        # Build the fog surface for the give unit.
        width = self.game_state.map_width
        height = self.game_state.map_height
        distance = {
            perso_classe.PERSO_VOLEUR: VOLEUR_VISION_PORTEE,
            perso_classe.PERSO_BARBARE: BARBARE_VISION_PORTEE,
            perso_classe.PERSO_ELFE: ELFE_VISION_PORTEE,
        }[unit.class_]
        if self.game_state.map[unit.y][unit.x] == zone_type.ZONE_TOUR:
            for x in range(unit.x - distance, unit.x + distance + 1):
                for y in range(unit.y - distance, unit.y + distance + 1):
                    if not utils.is_in_rect(x, y, width, height):
                        continue
                    cell = self.game_state.map[y][x]
                    if cell != zone_type.ZONE_MUR and cell != zone_type.ZONE_FORET:
                        self._remove_fog(x, y)
        else:
            is_blocked = [False] * (2 * distance + 3)
            dy = (
                -1 if unit.direction == orientation.ORIENTATION_NORD else
                (1 if unit.direction == orientation.ORIENTATION_SUD else 0)
            )
            dx = (
                -1 if unit.direction == orientation.ORIENTATION_OUEST else
                (1 if unit.direction == orientation.ORIENTATION_EST else 0)
            )
            for i in range(distance + 1):
                for j in range(-i - 1, i + 2):
                    x = unit.x + i * dx + j * dy
                    y = unit.y + i * dy + j * dx
                    if (
                        not utils.is_in_rect(x, y, width, height) or
                        is_blocked[j + distance]
                    ):
                        continue
                    cell = self.game_state.map[y][x]
                    not_near = not utils.is_near(x, y, unit.x, unit.y)
                    if (
                        (not_near and cell == zone_type.ZONE_FORET) or
                        (
                            (not_near or i == 1) and
                            cell == zone_type.ZONE_MUR
                        )
                    ):
                        is_blocked[j + distance] = True
                    elif (cell != zone_type.ZONE_MUR):
                        self._remove_fog(x, y)

        self.update_display((
            unit.x - self.center[0],
            unit.y - self.center[1]
        ))

    def update_display(self, position=None):
        self.surface.fill(utils.BLACK)
        if position:
            x = utils.set_between(
                position[0],
                lower=0, upper=self.position_max[0]
            )
            y = utils.set_between(
                position[1],
                lower=0, upper=self.position_max[1]
            )
            self.position = (x, y)

        self.surface.blit(self.map_surface, (0, 0), (
                self.position[0] * data.WIDTH,
                self.position[1] * (data.HEIGHT - data.OVERLAY),
                self.width, self.height
        ))
        if self.follow_unit:
            self.surface.blit(self.dark_surface, (0, 0), (
                self.position[0] * data.WIDTH,
                self.position[1] * (data.HEIGHT - data.OVERLAY),
                self.width, self.height
            ))

        self.minimap.update_view()
