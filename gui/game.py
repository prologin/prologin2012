# -*- coding: utf-8 -*-

from collections import namedtuple
import struct

from api import *

Unit = namedtuple('Unit', 'player class_ life life_max x y direction')

ACTION_MOVE = 0
ACTION_ATTACK = 1
ACTION_ACK = 2

CLASSES = {
    PERSO_VOLEUR: u'voleur',
    PERSO_BARBARE: u'barbare',
    PERSO_ELFE: u'elfe',
}

ATTACKS = {
    ATTAQUE_NORMALE: u'normale',
    ATTAQUE_PALANTIR: u'palantir',
    ATTAQUE_TRAITRISE: u'traitrise',
    ATTAQUE_BASTOOOON: u'bastoooon',
    ATTAQUE_FUS_RO_DAH: u'fus ro dah',
    ATTAQUE_I_SEE: u'I see what you did here',
    ATTAQUE_LOTO: u'Loto, à qui le tour',
}

action_id = struct.Struct('i')
action_ack = struct.Struct('i') # Player_id
action_attack = struct.Struct(
    'iiii'  # perso_info(equipe, classe, vie, direction)
    'i'     # attaque_type
    'ii'    # position
)
action_move_first = struct.Struct(
    'iiii'  # perso_info(equipe, classe, vie, direction)
    'i'     # path_length
)
action_move_path_element = struct.Struct('ii') # position
action_move_last = struct.Struct(
    'ii'    # direction and player
)

def unit_from_json(unit):
    kwargs = dict(unit)
    kwargs['class_'] = kwargs.pop('class')
    return Unit(**kwargs)

def unit_cmp(unit1, unit2):
    return unit1.class_ == unit2.class_ and unit1.player == unit2.player

def actions_from_buffer(buf):

    def consume(buf, struct):
        length = struct.size
        chunk, buf = buf[:length], buf[length:]
        return buf, struct.unpack(chunk)

    actions = []
    while buf:
        buf, (id, ) = consume(buf, action_id)
        if id == ACTION_MOVE:
            buf, (equipe, classe, vie, direction, path_length) = consume(buf, action_move_first)
            path = [consume(action_move_path_element) for i in range(path_length)]
            buf, (direction, player) = consume(action_move_last)
            actions.append(
                u'Éq%s : Dépl. %s %s' % (
                    equipe, CLASSES[classe],
                    u' → '.join(u'(%s, %s)' % position for position in path)
                )
            )
        elif id == ACTION_ATTACK:
            buf, (equipe, classe, vie, direction, atq_type, pos) = consume(buf, action_attack)
            actions.append(
                u'Éq%s : %s attaque %s en (%s, %s)' % (
                    equipe, CLASSES[classe], ATTACKS[atq_type], pos[0], pos[1]
                )
            )
        elif id == ACTION_ACK:
            buf, _ = consume(buf, action_ack)
        else:
            actions.append(u'ATTENTION : action invalide !')
    return actions

class GameState(object):

    def __init__(self, json):
        self.turn = json['turn']
        self.turn_max = json['turn_max']
        self.scores = json['scores']
        self.units = [unit_from_json(unit) for unit in json['units']]
        self.actions = actions_from_buffer(json['actions'])

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
