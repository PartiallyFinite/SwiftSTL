#
#   containers.py
#   SwiftSTL
# 
#   The MIT License (MIT)
# 
#   Copyright (c) 2016 Greg Omelaenko
# 
#   Permission is hereby granted, free of charge, to any person obtaining a copy
#   of this software and associated documentation files (the "Software"), to deal
#   in the Software without restriction, including without limitation the rights
#   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#   copies of the Software, and to permit persons to whom the Software is
#   furnished to do so, subject to the following conditions:
# 
#   The above copyright notice and this permission notice shall be included in all
#   copies or substantial portions of the Software.
# 
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#   SOFTWARE.
# 

import re
from collections import namedtuple

Func = namedtuple('Func', 'type name args const body')

def camel(name):
    return name.title().replace('_', '')

def argscall(args):
    return re.sub(r".+?\W([A-Za-z0-9$_]+)(, |$)", r"\1\2", args)

text = open('containerfunctions.cpp').read()

# delete comments, preprocessor statements, and explicitly marked SKIP lines
text = re.sub(r'(?://|#|SKIP).*$', '', text, flags = re.MULTILINE)
# delete multiline comments
text = re.sub(r'/\*.*?\*/', '', text, flags = re.MULTILINE | re.DOTALL)

types = {}

reType = re.compile(r'''
        struct \s+ (\w+)  # type name with preceding space
        \s*  # optional spaces between name and brace
        \{  # opening brace
        (.*?)  # struct body
        ^\};\s*$  # closing brace and semicolon at the start of the line, followed only by trailing whitespace (if any).
        ''', re.MULTILINE | re.VERBOSE | re.DOTALL)

reFunc = re.compile(r'''
        ([A-Za-z$_0-9\s\*]+)  # return type, non-greedy
        (?<=[*\s])  # whitespace or pointer star adjacent to function name
        ([A-Za-z$_][A-Za-z$_0-9]*)  # function name
        \s*
        \(  # opening bracket
        ([^)]*)  # function arguments (CANNOT CONTAIN PARENTHESES)
        \) # closing bracket
        \s*
        (const)?  # const attribute
        \s*
        \{ (.*?)  # function body
        ^\s*\}\s*$  # closing brace, must be alone on line, apart from whitespace.
        ''', re.MULTILINE | re.VERBOSE | re.DOTALL)

for (type, text) in reType.findall(text):
    funcs = []
    for m in reFunc.findall(text):
        f = Func(*map(str.strip, m))
        funcs.append(f)
    types[type] = funcs


