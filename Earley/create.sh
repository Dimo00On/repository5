#!/bin/bash
mkdir build
cd build || return 1
cmake ..
make
cd .. || return 1
bin/tests
lcov -t "result" -o result.info -c -d build/CMakeFiles/lib.dir/src
genhtml -o report result.info
