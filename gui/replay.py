#! /usr/bin/env python
# -*- coding: utf-8 -*-

import gzip
import sys

import pygame
pygame.init()

import logs
from state_reader import DumpReader
from window import Window

try:
    filename = sys.argv[1]
except IndexError:
    logs.write('Error: a file is needed.')

if filename.endswith('.gz'):
    dump_file = gzip.open(filename, 'r')
else:
    dump_file = open(filename, 'r')
state_reader = DumpReader(dump_file)
window = Window(state_reader)
window.run()
