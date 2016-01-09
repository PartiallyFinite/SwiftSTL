//
//  containerfunctions.cpp
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

#include "sizetype.hpp"

// make life easier for the script by marking lines that should be ignored
#define SKIP

#include <deque>

struct deque {

    SKIP typedef sizetype<0> element;
    SKIP std::deque<element> v;

    const void * get_index(size_t index) const {
        return this->v[index]._;
    }

    void * index(size_t index) {
        return this->v[index]._;
    }

    size_t size() const {
        return this->v.size();
    }

    void clear() {
        this->v.clear();
    }

    void insert(size_t index, const void *values, size_t count) {
        this->v.insert(this->v.begin() + index, (const element *)values, (const element *)values + count);
    }

    void erase(size_t index, size_t count) {
        this->v.erase(this->v.begin() + index, this->v.begin() + index + count);
    }

    void push_back(const void *value) {
        this->v.push_back(*(const element *)value);
    }

    void pop_back() {
        this->v.pop_back();
    }

    void push_front(const void *value) {
        this->v.push_front(*(const element *)value);
    }

    void pop_front() {
        this->v.pop_front();
    }

};

