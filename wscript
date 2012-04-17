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
        ''',
        target = 'prolo2012',
        use = ['net', 'rules'],
    )

    for test in ['unit', 'cell', 'map']:
        bld.program(
            features = 'gtest',
            source = 'src/tests/test-%s.cc' % test,
            target = 'prologin2012-test-%s' % test,
            use = ['prolo2012'],
            includes = ['.']
        )

    bld.install_files('${PREFIX}/share/stechec2/prologin2012', [
        'prolo2012.yml',
    ])

