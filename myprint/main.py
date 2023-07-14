#!/usr/bin/env python

# import了一个package
import print_complex
# import了package下的一个module
import print_float
# import了package下的一个module，引用时可以不带package name
import print_int

if __name__ == '__main__':
    print(print_complex.default_complext)
    print(print_float.default_float)
    print(print_int.default_int)
