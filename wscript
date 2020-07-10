#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright (c) 2012-2020 Association Prologin <association@prologin.org>

import glob
import os.path

from wafgenerator import generator_player_install


def options(opt):
    pass


def configure(cfg):
    pass


def build(bld):
    bld.shlib(
        source='''
            src/ability.cc
            src/action-ack.cc
            src/action-attack.cc
            src/action-move.cc
            src/api.cc
            src/cell.cc
            src/dumper.cc
            src/entry.cc
            src/game.cc
            src/interface.cc
            src/map.cc
            src/rules.cc
            src/unit.cc
        ''',
        defines=['MODULE_COLOR=ANSI_COL_BROWN', 'MODULE_NAME="rules"'],
        target='prologin2012',
        use=['stechec2'],
    )

    abs_pattern = os.path.join(bld.path.abspath(), 'src/tests/test-*.cc')
    for test_src in glob.glob(abs_pattern):

        test_name = os.path.split(test_src)[-1]
        test_name = test_name[len("test-"):-(len(".cc"))]

        # Waf requires a relative path for the source
        src_relpath = os.path.relpath(test_src, bld.path.abspath())

        bld.program(
            features='gtest',
            source=src_relpath,
            target='prologin2012-test-{}'.format(test_name),
            use=['prologin2012', 'stechec2-utils'],
            includes=['.'],
            defines=['MODULE_COLOR=ANSI_COL_PURPLE',
                     'MODULE_NAME="prologin2012"'],
        )

    bld.install_files('${PREFIX}/share/stechec2/prologin2012', [
        'prologin2012.yml',
    ])

    generator_player_install(bld, 'prologin2012')

    bld.install_files('${PREFIX}/share/stechec2/prologin2012/www/css', [
        'www/css/main.css',
    ])
    bld.install_files('${PREFIX}/share/stechec2/prologin2012/www/img', [
        'www/img/back.png',
        'www/img/head.png',
        'www/img/medieval-abstract-ribbons-vector-547986.jpg',
        'www/img/medieval-ribbons-8b1a18.jpg',
    ])
    bld.install_files('${PREFIX}/share/stechec2/prologin2012/www/font', [
        'www/font/exocet-heavy.ttf',
    ])
