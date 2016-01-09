//
//  containerbase.hpp
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

#ifndef containerbase_h
#define containerbase_h

#include <cstdint>
#include <cassert>

typedef uint16_t szv_t;

static const szv_t _max_size = 2048;

template <szv_t size>
struct sizetype {
    char _[size ?: 1];
};

#define DECL 1
#define IMPL 2

#define _CONTAINER_BASE(T, ...) \
class _##T##_base { \
public: \
    virtual _##T##_base * clone() const { abort(); };

#define _CONTAINER(T) \
template <szv_t max = _max_size> \
class _##T : public _##T##_base { \
    typedef sizetype<max> element; \
    std::T<element> v; \
     \
    _##T() { } \
     \
    _##T(const std::T<element>& v) { \
        this->v = std::T<element>(v); \
    } \
     \
public: \
    static _##T##_base * make(szv_t size) { \
        assert(size <= max); \
        if (size <= max / 2) return _##T<max / 2>::make(size); \
        return new _##T(); \
    } \
     \
    _##T * clone() const override { \
        return new _##T(v); \
    }

#endif /* containerbase_h */
