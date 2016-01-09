//
//  _deque.hpp
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

#include "wrap.hpp"

VIRTUAL void * operator[](size_t index) BODY({
    return this->v[index]._;
})

VIRTUAL size_t size() BODY({
    return this->v.size();
})

VIRTUAL void clear() BODY({
    return this->v.clear();
})

VIRTUAL void insert(size_t index, const void *values, size_t count) BODY({
    this->v.insert(this->v.begin() + index, (const element *)values, (const element *)values + count);
})

VIRTUAL void erase(size_t index, size_t count) BODY({
    this->v.erase(this->v.begin() + index, this->v.begin() + index + count);
})

VIRTUAL void push_back(const void *value) BODY({
    this->v.push_back(*(const element *)value);
})

VIRTUAL void pop_back() BODY({
    this->v.pop_back();
})

VIRTUAL void push_front(const void *value) BODY({
    this->v.push_front(*(const element *)value);
})

VIRTUAL void pop_front() BODY({
    this->v.pop_front();
})
