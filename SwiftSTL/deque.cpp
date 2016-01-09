//
//  deque.cpp
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

#include <deque>
#include <array>
#include "deque.h"
#include "containerbase.hpp"

#define MAKE DECL
_CONTAINER_BASE(deque)
#include "_deque.hpp"
};
#undef MAKE
#define MAKE IMPL
_CONTAINER(deque)
#include "_deque.hpp"
};
#undef MAKE

_STLDequeRef _STLDequeCreate(size_t size) {
    return (_deque_base *)_deque<>::make(size);
}

_STLDequeRef _STLDequeCreateCopy(const _STLDequeRef ref) {
    return (_deque_base *)ref->clone();
}

void _STLDequeDestroy(_STLDequeRef ref) {
    delete ref;
}


const void * _STLDequeGetIndex(const _STLDequeRef ref, size_t i) {
    return (*ref)[i];
}

void * _STLDequeIndex(_STLDequeRef ref, size_t i) {
    return (*ref)[i];
}


size_t _STLDequeSize(const _STLDequeRef ref) {
    return ref->size();
}


void _STLDequeClear(_STLDequeRef ref) {
    ref->clear();
}


void _STLDequeInsert(_STLDequeRef ref, size_t index, const void *values, size_t count) {
    ref->insert(index, values, count);
}

void _STLDequeErase(_STLDequeRef ref, size_t index, size_t count) {
    ref->erase(index, count);
}

void _STLDequePushBack(_STLDequeRef ref, const void *value) {
    ref->push_back(value);
}

void _STLDequePopBack(_STLDequeRef ref) {
    ref->pop_back();
}

void _STLDequePushFront(_STLDequeRef ref, const void *value) {
    ref->push_front(value);
}

void _STLDequePopFront(_STLDequeRef ref) {
    ref->pop_front();
}
