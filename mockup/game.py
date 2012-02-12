from collections import defaultdict

import pydot

class Squad:
    def __init__(self):
        pass

class City:
    def __init__(self, gold=0):
        self.gold = gold
        self.roads = []

    def add_road(self, city):
        self.roads.append(city)

class Map:
    def __init__(self):
        self.cities = []
        self.roads = defaultdict(list)

    def add_city(self, city):
        self.cities.append(city)

    def add_road(self, city1, city2):
        city1.add_road(city2)
        city2.add_road(city1)

        self.roads[city1.id].append(city2.id)
        self.roads[city2.id].append(city1.id)

class Player:
    def __init__(self, game, id):
        self.id = id
        self.game = game

    def play(self):
        whattodo = raw_input()
        eval(whattodo)

class Game:
    def __init__(self):
        self.map = Map()

    def turn(self):
        pass

    def run(self):
        while self.running:
            self.turn()
            self.output()

if __name__ == "__main__":
    game = Game()
    game.run()
