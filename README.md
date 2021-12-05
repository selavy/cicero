# cicero
C scrabble engine and library

# Run tests
```
$ mkdir build
$ cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=On -GNinja ..
$ cd build
$ ninja -j14
$ ./tests/run_tests.sh
```
