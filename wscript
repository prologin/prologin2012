#! /usr/bin/env python2

def options(opt):
    pass

def configure(cfg):
    pass

def build(bld):
    bld.shlib(
        source = '''
            src/rules.cc
            src/entry.cc
            src/map.cc
            src/unit.cc
            src/cell.cc
            src/ability.cc
            src/game.cc
            src/api.cc
            src/action-move.cc
            src/action-attack.cc
            src/action-ack.cc
            src/dumper.cc
            src/interface.cc
        ''',
        target = 'prologin2012',
        use = ['stechec2-net', 'stechec2-rules', 'stechec2-utils'],
        defines = ['MODULE_COLOR=ANSI_COL_PURPLE',
            'MODULE_NAME="prologin2012"'],
        lib = ['dl'],
    )

    for test in ['unit', 'cell', 'ability', 'map', 'game', 'api']:
        bld.program(
            features = 'gtest',
            source = 'src/tests/test-%s.cc' % test,
            target = 'prologin2012-test-%s' % test,
            use = ['prologin2012', 'stechec2-utils'],
            includes = ['.'],
            defines = ['MODULE_COLOR=ANSI_COL_PURPLE',
                'MODULE_NAME="prologin2012"'],
        )

    bld.install_files('${PREFIX}/share/stechec2/prologin2012', [
        'prologin2012.yml',
    ])

