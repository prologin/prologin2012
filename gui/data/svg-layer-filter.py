# -*- coding: utf-8 -*/

import sys

import lxml.etree as etree

f_in = open(sys.argv[1], 'r')
f_out = open(sys.argv[2], 'w')
layers = sys.argv[3:]

svg = etree.parse(f_in)
f_in.close()
svg = svg.getroot()
to_delete = []
for (num, layer) in enumerate(svg):
    if layer.tag.endswith('}g') and \
            layer.get('id') not in layers:
        to_delete.append(num)
    else:
        layer.set('style', 'display: inline;')
for layer in reversed(to_delete):
    del svg[layer]

f_out.write(etree.tostring(svg))
f_out.close()
