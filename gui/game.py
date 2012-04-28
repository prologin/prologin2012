# -*- coding: utf-8 -*-

from collections import namedtuple

Unit = namedtuple('Unit', 'player class_ life life_max x y direction')

def unit_from_json(unit):
    kwargs = dict(unit)
    kwargs['class_'] = kwargs.pop('class')
    return Unit(**kwargs)

class GameState(object):

    def __init__(self, json):
        self.turn = json['turn']
        self.turn_max = json['turn_max']
        self.scores = json['scores']
        self.units = [unit_from_json(unit) for unit in json['units']]
        self.actions = json['actions']

        map = json['map']
        self.map_width = map['width']
        self.map_height = map['height']
        self.map = map['cells']
        self.map_units = [
            [[] for i in range(map['width'])]
            for i in range(map['height'])
        ]

        for i, unit in enumerate(self.units):
            self.map_units[unit.y][unit.x].append(i)
