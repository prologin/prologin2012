# -*- coding: utf-8 -*-

from collections import namedtuple

Unit = namedtuple('Unit', 'player class_ life life_max x y direction')

def unit_from_json(unit):
    kwargs = dict(unit)
    kwargs['class_'] = kwargs.pop('class')
    return Unit(**kwargs)

def unit_cmp(unit1, unit2):
    return unit1.class_ == unit2.class_ and unit1.player == unit2.player

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

    def get_unit_position(self, unit):
        for i, my_unit in enumerate(self.map_units[unit.y][unit.x]):
            if unit_cmp(unit, self.units[my_unit]):
                return i
        return None
