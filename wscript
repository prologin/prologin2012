#! /usr/bin/env python2

def options(opt):
    pass

def configure(cfg):
    pass

def build(bld):
    bld.shlib(
        source = '''
            src/map.cc
            src/unit.cc
            src/cell.cc
            src/ability.cc
            src/game.cc
            src/api.cc
            src/action-move.cc
        ''',
        target = 'prolo2012',
        use = ['net', 'rules', 'utils'],
        defines = ['MODULE_COLOR=ANSI_COL_PURPLE', 'MODULE_NAME="prolo2012"'],
    )

    for test in ['unit', 'cell', 'ability', 'map', 'api']:
        bld.program(
            features = 'gtest',
            source = 'src/tests/test-%s.cc' % test,
            target = 'prologin2012-test-%s' % test,
            use = ['prolo2012', 'utils'],
            includes = ['.'],
            defines = ['MODULE_COLOR=ANSI_COL_PURPLE', 'MODULE_NAME="prolo2012"'],
        )

    bld.install_files('${PREFIX}/share/stechec2/prologin2012', [
        'prolo2012.yml',
    ])

