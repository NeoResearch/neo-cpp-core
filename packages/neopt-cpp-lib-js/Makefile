EXPORT_NAME='EXPORT_NAME="neopt_raw_lib"'

# note that the following command with execute TWO FOLDERS BEFORE => -v $(pwd)/../../:/src
$EMCC_SOURCE_DOCKER=docker run --rm -v $(pwd)/../../:/src trzeci/emscripten em++

PRE_NODE_LOAD=./packages/neopt-cpp-lib-js/src/prefix-node-require.js
EXTRA_EXPORTED=EXTRA_EXPORTED_RUNTIME_METHODS='["ccall",  "cwrap", "UTF8ToString", "stringToUTF8"]'
LIB_JS_TO_BIND=../../packages/neopt-cpp-lib-js/src/neo3-cpp-bindings-js/web-libcore_exports.js
NEO3_SRC=./src/
LIBS=./libs/
LIBS_JS_BUNDLE=./packages/neopt-cpp-lib-js/src/
MAIN_CPP=./packages/neopt-cpp-lib-js/src/neopt_raw_lib.cpp
EXTRA_PARAMS=--std=c++17 -g -O3 -Wall -s WASM=1 -s DISABLE_EXCEPTION_CATCHING=1 -s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1

compile:
	@echo
	@echo "======= compiling neoopt-cpp-lib-js ======="
	@echo
	$(EMCC_SOURCE_DOCKER) $(EXTRA_PARAMS) --pre-js $(PRE_NODE_LOAD) -s $(EXTRA_EXPORTED) -s $(EXPORT_NAME) --js-library $(LIB_JS_TO_BIND) -I$(NEO3_SRC) -I$(LIBS) -I$(LIBS_JS_BUNDLE) $(MAIN_CPP) -o ./packages/neopt-cpp-lib-js/build/neopt_raw_lib.js
	#(cd .. &&                                            em++ --pre-js prefix-node-require.js --std=c++17 -g -O3 -Wall  -s WASM=1   -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall",  "cwrap", "UTF8ToString", "stringToUTF8"]' -s DISABLE_EXCEPTION_CATCHING=1   -s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1 -s 'EXPORT_NAME="neopt-raw-lib"'  --js-library src/neo3-cpp-bindings/general-libcore_exports.js -I./thirdparty/neo3-cpp-core/src/ -I./thirdparty/neo3-cpp-core/libs/ -I./src/ -o ./fib-test-to-neopt/ourtest.js ./fib-test-to-neopt/neopt-test2.cpp )
