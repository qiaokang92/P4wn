"""
General helper functions.
"""

from __future__ import print_function
import sys

def eprint(*args, **kwargs):
    '''Print to stderr'''
    print(*args, file=sys.stderr, **kwargs)
