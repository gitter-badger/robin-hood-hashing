➵ robin_hood::unordered_map  [![Release](https://img.shields.io/github/release/martinus/robin-hood-hashing.svg)](https://github.com/martinus/robin-hood-hashing/releases) [![GitHub license](https://img.shields.io/github/license/martinus/robin-hood-hashing.svg)](https://raw.githubusercontent.com/martinus/robin-hood-hashing/master/LICENSE)
============


[![Travis CI Build Status](https://travis-ci.com/martinus/robin-hood-hashing.svg?branch=master)](https://travis-ci.com/martinus/robin-hood-hashing)
[![Appveyor Build Status](https://ci.appveyor.com/api/projects/status/github/martinus/robin-hood-hashing?branch=master&svg=true)](https://ci.appveyor.com/project/martinus/robin-hood-hashing)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/9308495247b542c9802016caa6fd3461)](https://www.codacy.com/app/martinus/robin-hood-hashing?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=martinus/robin-hood-hashing&amp;utm_campaign=Badge_Grade)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/martinus/robin-hood-hashing.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/martinus/robin-hood-hashing/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/martinus/robin-hood-hashing.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/martinus/robin-hood-hashing/context:cpp)
[![Coverage Status](https://coveralls.io/repos/github/martinus/robin-hood-hashing/badge.svg)](https://coveralls.io/github/martinus/robin-hood-hashing) [![Join the chat at https://gitter.im/martinus/robin-hood-hashing](https://badges.gitter.im/martinus/robin-hood-hashing.svg)](https://gitter.im/martinus/robin-hood-hashing?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

`robin_hood::unordered_map` is a platform independent replacement for `std::unordered_map` which is both faster and more memory efficient for real-world use cases.

## Installation & Usage

1. Add [`robin_hood.h`](https://github.com/martinus/robin-hood-hashing/releases) to your C++ project.
1. Use `robin_hood::unordered_map` instead of `std::unordered_map`.

## Benchmarks

Please see extensive benchmarks at [Hashmaps Benchmarks](https://martin.ankerl.com/2019/04/01/hashmap-benchmarks-01-overview/). In short: `robin_hood` is always among the fastest maps and uses far less memory than `std::unordered_map`.

## Design Choices

- **Two memory layouts**. Data is either stored in a flat array, or with node indirection. Access for `unordered_flat_map` is extremely fast due to no indirection, but references to elements are not stable. It also causes allocation spikes when the map resizes, and will need plenty of memory for large objects. Node based map has stable references and uses `const Key` in the pair. It is a bit slower due to indirection. The choice is yours; you can either use `robin_hood::unordered_flat_map` or `robin_hood::unordered_node_map` directly. If you use `robin_hood::unordered_map` It tries to choose the layout that seems appropriate for your data.

- **Custom allocator**. Node based representation has a custom bulk allocator that tries to make few memory allocations. All allocated memory is reused, so there won't be any allocation spikes. It's very fast as well.

- **Optimized hash**. `robin_hood::hash` has custom implementations for integer types and for `std::string` that are very fast and falls back to `std::hash` for everything else.

- **Depends on good Hashing**. For a really bad hash the performance will not only degrade like in `std::unordered_map`, the map will simply fail with an `std::overflow_error`. In practice, when using the standard `robin_hood::hash`, I have never seen this happening.

## License

Licensed under the MIT License. See the [LICENSE](https://github.com/martinus/robin-hood-hashing/blob/master/LICENSE) file for details.

by martinus
