# SwiftSTL

Swift wrappers for C++ STL containers.

Includes hand-written wrappers with Swift-style API:

- `STLDeque`: wrapper around `std::deque`

And auto-generated wrappers mirroring C++ API:

- `_STLDequeImpl`
- `_STLVectorImpl`

**Memory usage note**: due to lack of bridging between Swift generics and C++ templates, the C++ data structures are initialised with elements sized to the smallest power of 2 that fits the Swift object. This may create an up to 50% memory usage overhead on larger objects.

