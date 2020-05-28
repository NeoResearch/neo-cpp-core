#!/bin/bash

mkdir -p build/

# note that the following command with execute TWO FOLDERS BEFORE => -v $(pwd)/../../:/src
docker run --rm -v $(pwd)/../../:/src trzeci/emscripten em++ --pre-js ./packages/neopt-cpp-lib-js/src/prefix-node-require.js --std=c++17 -g -O3 -Wall  -s WASM=1   -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall",  "cwrap", "UTF8ToString", "stringToUTF8"]' -s DISABLE_EXCEPTION_CATCHING=1   -s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1 -s 'EXPORT_NAME="neopt_raw_lib"'  --js-library packages/neopt-cpp-lib-js/src/neo3-cpp-bindings-js/web-libcore_exports.js -I./src/ -I./libs/ -I./packages/neopt-cpp-lib-js/src/ -o ./packages/neopt-cpp-lib-js/build/neopt_raw_lib.js ./packages/neopt-cpp-lib-js/src/neopt_raw_lib.cpp

#(cd .. &&                                            em++ --pre-js prefix-node-require.js --std=c++17 -g -O3 -Wall  -s WASM=1   -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall",  "cwrap", "UTF8ToString", "stringToUTF8"]' -s DISABLE_EXCEPTION_CATCHING=1   -s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1 -s 'EXPORT_NAME="neopt-raw-lib"'  --js-library src/neo3-cpp-bindings/general-libcore_exports.js -I./thirdparty/neo3-cpp-core/src/ -I./thirdparty/neo3-cpp-core/libs/ -I./src/ -o ./fib-test-to-neopt/ourtest.js ./fib-test-to-neopt/neopt-test2.cpp )
