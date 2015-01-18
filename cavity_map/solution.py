#!/usr/bin/env python

import sys
import cStringIO
import textwrap


def convertIfCavity(x, y, data):
    if (data[y][x] > data[y + 1][x]
        and data[y][x] > data[y - 1][x]
        and data[y][x] > data[y][x + 1]
        and data[y][x] > data[y][x - 1]):
        return 'X'
    return data[y][x]


def cavity_map(stream):
    result = cStringIO.StringIO()
    data = stream.read().split()
    size = int(data[0])
    data = ['9' + x + '9' for x in data[1:]]
    line = ''.join('9' for _ in xrange(size + 2))
    data = [line] + data + [line]

    for y in xrange(size):
        line = ''
        for x in xrange(size):
            line += convertIfCavity(x + 1, y + 1, data)
        print >> result, line

    return result


if __name__ == '__main__':
    io = cStringIO.StringIO(textwrap.dedent("""
        4
        1112
        1912
        1892
        1234
    """))
    print cavity_map(io).getvalue()
