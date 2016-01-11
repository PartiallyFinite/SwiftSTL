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

/*
 * NOTE: This file is _not_ compiled as part of the project; it is processed by containers.py to generate wrappers.
 * This file exists instead of a table of butchered strings in order to provide a maintainable and standalone testable development area.
 * This file is designed to be able to be compiled on its own for testing purposes.
 * 
 * All top-level structs, and all their member functions, will be converted into template wrappers.
 * Lines that are not required for this process, but are only used to allow this file to compile on its own, should be prepended with SKIP.
 * All preprocessor statements and comments will be eliminated automatically.
 */

#include "sizetype.hpp"

// used to mark ignored lines
#define SKIP
// used to mark the STL container declaration in each struct
#define STL

SKIP typedef sizetype<1> element;

// Define the allowed argument and return types. These types must also be present in vartypes in containers.py.
// Only capital letters and underscores are allowed.
#define VOID void
#define ELEMS void *
#define CONST_ELEMS const void *
#define ELEM void *
#define CONST_ELEM const void *
#define INDEX size_t
#define ELEM_COMP _comparator
#define ITER const void *

#include <deque>

struct deque {

    STL std::deque<element> v;

    CONST_ELEM get_index(INDEX index) const {
        return this->v[index]._;
    }

    ELEM index(INDEX index) {
        return this->v[index]._;
    }

    INDEX size() const {
        return this->v.size();
    }

    VOID clear() {
        this->v.clear();
    }

    VOID insert(INDEX index, CONST_ELEMS values, INDEX count) {
        this->v.insert(this->v.begin() + index, (const element *)values, (const element *)values + count);
    }

    VOID erase(INDEX index, INDEX count) {
        this->v.erase(this->v.begin() + index, this->v.begin() + index + count);
    }

    VOID push_back(CONST_ELEM value) {
        this->v.push_back(*(const element *)value);
    }

    VOID pop_back() {
        this->v.pop_back();
    }

    VOID push_front(CONST_ELEM value) {
        this->v.push_front(*(const element *)value);
    }

    VOID pop_front() {
        this->v.pop_front();
    }

};

#include <vector>

struct vector {

    STL std::vector<element> v;

    CONST_ELEM get_index(INDEX index) const {
        return this->v[index]._;
    }

    ELEM index(INDEX index) {
        return this->v[index]._;
    }

    INDEX size() const {
        return this->v.size();
    }

    VOID clear() {
        this->v.clear();
    }

    VOID insert(INDEX index, CONST_ELEMS values, INDEX count) {
        this->v.insert(this->v.begin() + index, (const element *)values, (const element *)values + count);
    }

    VOID erase(INDEX index, INDEX count) {
        this->v.erase(this->v.begin() + index, this->v.begin() + index + count);
    }

    VOID push_back(CONST_ELEM value) {
        this->v.push_back(*(const element *)value);
    }

    VOID pop_back() {
        this->v.pop_back();
    }

};

#include <set>

struct set {

    STL std::set<element, szt_func_comp<max>> v;

    VOID set_comparator(ELEM_COMP comp) {
        *this->v.value_comp().func = comp;
    }

    ITER begin() const {
        auto it = this->v.begin();
        void *v = malloc(sizeof(it));
        *(typeof(it) *)v = it;
        return v;
    }

    INDEX size() const {
        return this->v.size();
    }

    VOID insert(CONST_ELEMS values, INDEX count) {
        this->v.insert((const element *)values, (const element *)values + count);
    }

    INDEX count(CONST_ELEM e) {
        return this->v.count(*(const element *)e);
    }

};

