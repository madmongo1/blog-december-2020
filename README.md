# blog-december-2020
Code to accompany December 2020 Blog

Tested with clang-11 on linux with cmake flags:
```
-DCMAKE_CXX_COMPILER="clang++" -DCMAKE_CXX_FLAGS="-stdlib=libc++ -std=c++20"
```

MSVC users may want to check that any `::max()` converted to `(::max)()` and that all `co_await`s are moved out of `assert()`s.
