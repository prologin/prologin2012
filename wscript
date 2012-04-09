#! /usr/bin/env python2

def options(opt):
    pass

def configure(cfg):
    pass

def build(bld):
    bld.shlib(
        source = '''
        ''',
        target = 'prolo2012',
        use = ['net', 'rules'],
    )

    bld.install_files('${PREFIX}/share/stechec2/prologin2012', [
        'prolo2012.yml',
    ])
