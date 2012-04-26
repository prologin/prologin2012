# -*- coding: utf-8 -*-

import traceback
import sys

import pygame

import data
import logs
import utils
from widgets import (
    ActionsWidget, DetailsWidget, HelpWidget, MapWidget, ScoresWidget,
    StateWidget
)


class State:
    TURN_FPS = 1

    def __init__(self):
        self.looping = False
        self.ticks = 0
        self.loop_delay = 1000 / State.TURN_FPS
        self.display_help = False
        self.display_scores = False
        self.is_closed = False

    def switch_help(self):
        if self.display_scores:
            return
        self.display_help = not self.display_help

    def switch_scores(self):
        if self.display_help:
            return
        self.display_scores = not self.display_scores

    def switch_looping(self):
        self.looping = not self.looping
        self.ticks = 0

    def check_loop(self):
        if not self.looping:
            return False
        ticks = pygame.time.get_ticks()
        if ticks - self.ticks >= State.TURN_FPS:
            self.ticks = ticks
            return True
        return False

    def close(self):
        self.is_closed = True


class Window(object):
    FPS = 20

    def __init__(self, state_reader):
        self.state = State()
        self.state_reader = state_reader
        self.current_state = None

        map_rect = (5, 5, 700, 500)
        actions_rect = (5, 510, 700, ActionsWidget.HEIGHT)
        minimap_rect = (710, 5, 250, 100)
        state_rect = (710, 110, 250, StateWidget.HEIGHT)
        details_rect = (
            710, 115 + StateWidget.HEIGHT,
            250, 510 + ActionsWidget.HEIGHT - (115 + StateWidget.HEIGHT)
        )

        flags = pygame.DOUBLEBUF | pygame.HWSURFACE
        screen_dim = (
            minimap_rect[0] + minimap_rect[2],
            actions_rect[1] + actions_rect[3]
        )
        self.screen = pygame.display.set_mode(screen_dim, flags)
        self.clock = pygame.time.Clock()
        data.load_images()

        self.map_widget = MapWidget(*map_rect)
        self.actions_widget = ActionsWidget(*actions_rect[:3])
        # self.minimap_rect = MinimapWidget(*minimap_rect)
        self.state_widget = StateWidget(*state_rect[:3])
        self.details_widget = DetailsWidget(*details_rect)
        self.help_widget = HelpWidget(*screen_dim)
        self.scores_widget = ScoresWidget(*screen_dim)

        self.widgets = {
            'map': self.map_widget,
            'actions': self.actions_widget,
            #'minimap': self.minimap_widget,
            'state': self.state_widget,
            'details': self.details_widget,
            'help': self.help_widget,
        }
        for widget in self.widgets.values():
            widget.plug(self.widgets)

    def run(self):
        try:
            self.loop()
        except Exception as e:
            type, value, tb = sys.exc_info()
            logs.write('An unhandled exception was caught:\n%s\n%s: %s' % (
                ''.join(line for line in traceback.format_tb(tb)),
                type.__name__, value
            ))
        self.release()

    def loop(self):
        while (
            not self.state.is_closed and
            not self.state_reader.is_ended()
        ):
            self.clock.tick(self.FPS)
            self.update_state()
            self.handle_events()
            self.update_window()

        # The game is finished or the user has quitted: if the used hasn’t
        # quitted, display a final screen.
        self.state_widget.update_end()
        while not self.state.is_closed:
            self.clock.tick(self.FPS)
            self.looping = self.handle_events()
            self.update_window()

        if self.state.is_closed and self.state_reader.can_quit():
            self.release()
            sys.exit(0)

        # This must not be called if can_quit returned False. This is used to
        # wait for stechec to stop.
        self.state_reader.wait_end()
        while not self.state_reader.is_ended():
            self.state_widget.update_wait_end(self.state_reader.get_turn())
            self.update_window()
            self.clock.tick(self.FPS)

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.state.close()

            if self.state.display_help:
                if event.type == pygame.KEYDOWN and event.key == pygame.K_h:
                    self.state.switch_help()
                continue

            if event.type == pygame.KEYDOWN:
                widget = (
                    self.details_widget
                    if pygame.key.get_mods() & pygame.KMOD_LCTRL else
                    self.actions_widget
                )
                if event.key == pygame.K_SPACE:
                    self.state.switch_looping()
                    if self.state.looping:
                        self.go_next_turn()
                elif not self.state.looping and event.key == pygame.K_n:
                    self.go_next_turn()

                elif event.key == pygame.K_DOWN:
                    widget.scroll(1)
                elif event.key == pygame.K_UP:
                    widget.scroll(-1)

                elif event.key == pygame.K_h:
                    self.state.switch_help()
                elif event.key == pygame.K_s:
                    self.state.switch_scores()

            elif event.type == pygame.MOUSEBUTTONDOWN:
                for widget in self.widgets.values():
                    if widget.handle_click(*(
                        pygame.mouse.get_pos() + pygame.mouse.get_pressed()
                    )):
                        break

    def go_next_turn(self):
        self.state_reader.go_next()
        self.state_widget.update_wait()

    def update_state(self):
        if self.state_reader.is_ended():
            return

        if self.state.display_help or self.state.display_scores:
            return

        game_state = self.state_reader.get_next_state()
        if game_state is not None:
            self.game_state = game_state
            self.map_widget.update_game(game_state)
            self.details_widget.update_game(game_state)
            # self.minimap_widget.update_game(game_state)
            self.state_widget.update_turn(game_state.turn, game_state.turn_max)
            self.actions_widget.update_actions(game_state.actions)
            self.scores_widget.update_scores(game_state.scores)

            if self.state.check_loop():
                self.go_next_turn()

    def update_window(self):
        self.screen.fill(utils.BLACK)
        #self.minimap_widget.display(self.screen)
        self.map_widget.display(self.screen)
        self.state_widget.display(self.screen)
        self.details_widget.display(self.screen)
        self.actions_widget.display(self.screen)
        if self.state.display_help:
            self.help_widget.display(self.screen)
        elif self.state.display_scores:
            self.scores_widget.display(self.screen)
        pygame.display.flip()

    def release(self):
        pygame.quit()
