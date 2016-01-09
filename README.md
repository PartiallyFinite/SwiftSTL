# SwiftSTL

Swift wrappers for C++ STL containers.

Includes:

- `STLDeque`: wrapper around `std::deque`

**Memory usage note**: due to lack of bridging between Swift generics and C++ templates, the C++ data structures are initialised with elements sized to the smallest power of 2 that fits the Swift object. This may create an up to 50% memory usage overhead on larger objects.

