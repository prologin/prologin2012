#! /usr/bin/env python2

def options(opt):
    pass

def configure(cfg):
    pass

def build(bld):
    bld.shlib(
        source = '''
            src/api.cc
            src/client.cc
            src/game.cc
            src/map.cc
            src/server.cc
            src/square.cc
        ''',
        target = 'prolo2012',
        use = ['net', 'rules'],
    )
