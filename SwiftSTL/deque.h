//
//  deque.h
//  SwiftSTL
//
//  The MIT License (MIT)
//
//  Copyright (c) 2016 Greg Omelaenko
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//

#ifndef deque_h
#define deque_h

#include <unistd.h>

__BEGIN_DECLS

typedef struct _deque_base * _STLDequeRef;

_STLDequeRef _STLDequeCreate(size_t size);
_STLDequeRef _STLDequeCreateCopy(const _STLDequeRef);
void _STLDequeDestroy(_STLDequeRef);

const void * _STLDequeGetIndex(const _STLDequeRef, size_t);
void * _STLDequeIndex(_STLDequeRef, size_t);

size_t _STLDequeSize(const _STLDequeRef);

void _STLDequeClear(_STLDequeRef);

void _STLDequeInsert(_STLDequeRef, size_t index, const void *values, size_t count);
void _STLDequeErase(_STLDequeRef, size_t index, size_t count);
void _STLDequePushBack(_STLDequeRef, const void *value);
void _STLDequePopBack(_STLDequeRef);
void _STLDequePushFront(_STLDequeRef, const void *value);
void _STLDequePopFront(_STLDequeRef);

__END_DECLS

#endif /* deque_h */
