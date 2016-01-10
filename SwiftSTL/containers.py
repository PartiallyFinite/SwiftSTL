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

def lcamel(name):
    s = camel(name)
    return s[:1].lower() + s[1:]

def carg(arg):
    return vartypes[arg[0]].c + ' ' + arg[1]

def swiftarg(arg):
    return arg[1] + ': ' + vartypes[arg[0]].swift

def argsdecl(args):
    return ', '.join(map(carg, args))

def argscall(args):
    return ', '.join(map(lambda arg: arg[1], args))

def swiftargsdecl(args):
    return ', '.join(map(swiftarg, args))

VarType = namedtuple('VarType', 'c swift retcast cconv')

vartypes = {
    'VOID': VarType('void', '()', '', ''),
    'ELEMS': VarType('void *', 'UnsafeMutablePointer<Element>', 'UnsafeMutablePointer<Element>', 'withCast'),
    'CONST_ELEMS': VarType('const void *', 'UnsafePointer<Element>', 'UnsafePointer<Element>', 'withCast'),
    'ELEM': VarType('void *', 'UnsafeMutablePointer<Element>', 'UnsafeMutablePointer<Element>', 'withCast'),
    'CONST_ELEM': VarType('const void *', 'Element', 'getElem', 'withPtr'),
    'INDEX': VarType('size_t', 'Int', '', ''),
}

def ctype(f):
    return vartypes[f.type].c

def swifttype(f):
    return vartypes[f.type].swift

def swiftcallwrap(f):
    pre, post = '', ''
    for arg in f.args:
        t = vartypes[arg[0]]
        if len(t.cconv):
            pre += t.cconv + '(' + arg[1] + ') { ' + arg[1] + ' in return '
            post += ' }'
    retcast = vartypes[f.type].retcast
    if len(retcast):
        pre += retcast + '('
        post = ')' + post
    return (pre, post)


text = open('containerfunctions.cpp').read()

# delete comments, preprocessor statements, and explicitly marked SKIP lines
text = re.sub(r'(?://|#|SKIP).*$', '', text, flags = re.MULTILINE)
# delete multiline comments
text = re.sub(r'/\*.*?\*/', '', text, flags = re.MULTILINE | re.DOTALL)

types = {}

# matches a variable declaration with a type
rsDecl = r'''
        ([A-Za-z$_0-9\s\*]+?)  # type, non-greedy
        \s*  # trailing whitespace excluded from type
        (?<=[*\s])  # whitespace or pointer star adjacent to function name
        ([A-Za-z$_][A-Za-z$_0-9]*)  # variable name
        \s*  # optional whitespace
        '''

# matches a parenthesised argument list
rsArgs = r'\(([^)]*)\)'

# matches a struct declaration
reWrap = re.compile(r'''
        struct \s+ (\w+)  # type name with preceding space
        \s*  # optional spaces between name and brace
        \{  # opening brace
        (.*?)  # struct body
        ^\};\s*$  # closing brace and semicolon at the start of the line, followed only by trailing whitespace (if any).
        ''', re.MULTILINE | re.VERBOSE | re.DOTALL)

# matches a function
reFunc = re.compile(rsDecl + rsArgs + r'''
        \s*
        (const)?  # const attribute
        \s*
        \{ (.*?)  # function body
        ^\s*\}\s*$  # closing brace, must be alone on line, apart from whitespace.
        ''', re.MULTILINE | re.VERBOSE | re.DOTALL)

# matches an argument in an argument list
reArg = re.compile(rsDecl + r'\s*(?:,|$)\s*', re.MULTILINE | re.VERBOSE | re.DOTALL)

for (type, text) in reWrap.findall(text):
    funcs = []
    for m in reFunc.findall(text):
        (ret, name, args, const, body) = map(str.strip, m)
        args = reArg.findall(args)
        funcs.append(Func(ret, name, args, const, body))
    types[type] = funcs

