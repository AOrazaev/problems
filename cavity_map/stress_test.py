#!/usr/bin/env python

import sys
import random
from cStringIO import StringIO
from solution import cavity_map
from subprocess import Popen, PIPE


def generate_ocean(n):
    data = [str(n)]
    for y in xrange(n):
        line = ''
        for x in xrange(n):
            line += str(random.randint(0, 9))
        data.append(line)
    return '\n'.join(data)


def main():
    for i in xrange(1000):
        ocean = generate_ocean(5)
        expected_result = cavity_map(StringIO(ocean)).getvalue()
        sys.stdout.write('.')
        p = Popen(['./a.out'], stdin=PIPE, stdout=PIPE)
        result = p.communicate(input=ocean)
        if result[0].strip() != expected_result.strip():
            print
            print 'expected:'
            print expected_result.strip()
            print '-'*30
            print 'got:'
            print result[0].strip()
            return


if __name__ == '__main__':
    main()
