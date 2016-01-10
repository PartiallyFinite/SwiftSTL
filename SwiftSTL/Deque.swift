//
//  Deque.swift
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

public struct STLDeque<Element> : CollectionType, MutableCollectionType {

    private var nonmutatingImpl = _STLDequeImpl<Element>()
    private var impl: _STLDequeImpl<Element> {
        mutating get {
            if !isUniquelyReferenced(&nonmutatingImpl) {
                nonmutatingImpl = _STLDequeImpl(nonmutatingImpl)
            }
            return nonmutatingImpl
        }
    }

    public init() { }

    public init<S : SequenceType where S.Generator.Element == Element>(_ s: S) {
        appendContentsOf(s)
    }

    public var startIndex: Int {
        return 0
    }

    public var endIndex: Int {
        return nonmutatingImpl.size()
    }

    public subscript(index: Int) -> Element {
        get {
            return nonmutatingImpl.getIndex(index)
        }
        set {
            nonmutatingImpl.index(index).memory = newValue
        }
    }

}

extension STLDeque {

    public var count: Int {
        return nonmutatingImpl.size()
    }

}

extension STLDeque : RangeReplaceableCollectionType {

    public mutating func replaceRange(subRange: Range<Int>, with newElements: UnsafeBufferPointer<Element>) {
        if newElements.count > subRange.count {
            // insert the extra elements
            impl.insert(subRange.endIndex, values: newElements.baseAddress, count: newElements.count - subRange.count)
        }
        else if newElements.count < subRange.count {
            // erase extra elements
            impl.erase(subRange.startIndex + newElements.count, count: subRange.count - newElements.count)
        }
        // set the values of the common range
        for (i, e) in zip(subRange, newElements) {
            impl.index(i).memory = e
        }
    }

    public mutating func replaceRange<C : CollectionType where C.Generator.Element == Element>(subRange: Range<Int>, with newElements: C) {
        ContiguousArray(newElements).withUnsafeBufferPointer {
            replaceRange(subRange, with: $0)
        }
    }

    /// - Complexity: Amortised O(1).
    public mutating func append(newElement: Element) {
        impl.pushBack(newElement)
    }

    /// - Complexity: Amortised O(1).
    public mutating func prepend(newElement: Element) {
        impl.pushFront(newElement)
    }

    /// - Complexity: Amortised O(1).
    /// - Requires: `!self.isEmpty`.
    public mutating func removeFirst() -> Element {
        let x = last!
        impl.popFront()
        return x
    }

    /// - Complexity: Amortised O(1).
    /// - Requires: `!self.isEmpty`.
    public mutating func removeLast() -> Element {
        let x = last!
        impl.popBack()
        return x
    }

    public mutating func removeAll(keepCapacity keepCapacity: Bool) {
        impl.clear()
    }

}

extension STLDeque {

    public mutating func popFirst() -> Element? {
        return count > 0 ? removeFirst() : nil
    }

    public mutating func popLast() -> Element? {
        return count > 0 ? removeLast() : nil
    }

}

extension STLDeque : ArrayLiteralConvertible {

    public init(arrayLiteral elements: Element...) {
        self.init(elements)
    }

}

func ==<Element : Equatable>(lhs: STLDeque<Element>, rhs: STLDeque<Element>) -> Bool {
    guard lhs.count == rhs.count else { return false }
    for (a, b) in zip(lhs, rhs) {
        guard a == b else { return false }
    }
    return true
}
