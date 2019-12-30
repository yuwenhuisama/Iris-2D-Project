#!/usr/bin/env python3
'''
Configuration of clang parser.
'''

class CONFIG:
    CLANG_LIBRARY_PATH =\
         "/Applications/Xcode.app/Contents/Developer/Toolchains\
             /XcodeDefault.xctoolchain/usr/lib/libclang.dylib"
    CLANG_COMPILE_ARGS = ['-x', 'c++', '-std=c++11', '-D__CODE_GENERATOR__']
