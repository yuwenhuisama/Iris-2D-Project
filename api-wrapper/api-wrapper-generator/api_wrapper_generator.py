#!/usr/bin/env python3
'''
Script for automatically generate wrapper code from C++ header file
'''

import sys
import clang.cindex
from configure import CONFIG

def init():
    clang.cindex.Config.set_library_file(CONFIG.CLANG_LIBRARY_PATH)
    index = clang.cindex.Index.create()
    translation_unit = index.parse(sys.argv[1], CONFIG.CLANG_COMPILE_ARGS)

init()
