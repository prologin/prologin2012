# -*- coding: utf-8 -*-

import pygame

import data
from widgets.scrolled import ScrolledWidget
import utils


class ScoresWidget(ScrolledWidget):

    SCREEN_PADDING = 50
    SCORE_WIDTH = 150
    BORDER = 2
    PADDING = 16
    LINE_HEIGHT = 15

    def __init__(self, screen_width, screen_height):
        self.font = pygame.font.Font(data.get_font('font.ttf'), 12)
        super(ScoresWidget, self).__init__(
            self.SCREEN_PADDING, self.SCREEN_PADDING,
            screen_width - 2 * self.SCREEN_PADDING,
            screen_height - 2 * self.SCREEN_PADDING
        )
        self.scores_by_line = self.width // self.SCORE_WIDTH

    def _determine_length(self, scores_len):
        return (scores_len + self.scores_by_line - 1) // self.scores_by_line

    def update_scores(self, scores):
        self.set_list_length(self._determine_length(len(scores)))
        x = 0
        y = 0
        for i, score in enumerate(scores):
            text = self.font.render(
                u'Équipe %d: %d' % (i, score),
                True, utils.WHITE
            )
            self.list_surface.blit(text, (
                x * self.SCORE_WIDTH,
                y * self.LINE_HEIGHT
            ))
            x += 1
            if x >= self.scores_by_line:
                x = 0
                y += 1
        self.scroll(0)

    def clean_surface(self):
        self.surface.fill(utils.WHITE)
        self.surface.fill(utils.BLACK, (
            self.BORDER, self.BORDER,
            self.width - 2 * self.BORDER,
            self.height - 2 * self.BORDER,
        ))
