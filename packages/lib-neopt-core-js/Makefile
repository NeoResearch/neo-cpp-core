
EXTRA_EXPORTED=EXTRA_EXPORTED_RUNTIME_METHODS='["ccall",  "cwrap", "UTF8ToString", "stringToUTF8"]'
NEO3_SRC=./src/
LIBS=./libs/
EXTRA_PARAMS=--std=c++17 -g -O3 -Wall -s WASM=1 -s DISABLE_EXCEPTION_CATCHING=1 -s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1
EXPORT_NAME='EXPORT_NAME="neopt_raw_lib"'
PRE_NODE_LOAD=./packages/lib-neopt-core-js/prefix-node-require.tmp.js   # note this is temporary file
LIB_JS_TO_BIND=./packages/lib-neopt-core-js/src/bindings-cpp-js/web-libcore_exports.js
LIBS_JS_BUNDLE=./packages/lib-neopt-core-js/src/
MAIN_CPP=./packages/lib-neopt-core-js/src/lib-neopt-core-js.cpp
OUTPUT_FILE=./packages/lib-neopt-core-js/build/neopt_raw_lib.js

# note that the following command with execute TWO FOLDERS BEFORE => -v $(pwd)/../../:/src
EMCC_SOURCE_DOCKER=docker run --rm -v $(PWD)/../../:/src trzeci/emscripten em++

compile:
	@echo
	@echo "======= compiling neoopt-cpp-lib-js ======="
	@echo
	mkdir -p build
	cp src/prefix-node-require.js prefix-node-require.tmp.js
	echo "" >> prefix-node-require.tmp.js
	echo "Module['core-hash'] = '$(shell git rev-parse HEAD)';" >> prefix-node-require.tmp.js
	echo "" >> prefix-node-require.tmp.js
	echo "Module['core-date'] = '$(shell git log -1 --format=%cd)';" >> prefix-node-require.tmp.js
	#
	# export methods automatically
	./export-api-methods.sh
	#
	$(EMCC_SOURCE_DOCKER) $(EXTRA_PARAMS) --pre-js $(PRE_NODE_LOAD) -s $(EXTRA_EXPORTED) -s $(EXPORT_NAME) --js-library $(LIB_JS_TO_BIND) -I$(NEO3_SRC) -I$(LIBS) $(MAIN_CPP) -o $(OUTPUT_FILE)
	#(cd .. &&                                            em++ --pre-js prefix-node-require.js --std=c++17 -g -O3 -Wall  -s WASM=1   -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall",  "cwrap", "UTF8ToString", "stringToUTF8"]' -s DISABLE_EXCEPTION_CATCHING=1   -s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1 -s 'EXPORT_NAME="neopt-raw-lib"'  --js-library src/neo3-cpp-bindings/general-libcore_exports.js -I./thirdparty/neo3-cpp-core/src/ -I./thirdparty/neo3-cpp-core/libs/ -I./src/ -o ./fib-test-to-neopt/ourtest.js ./fib-test-to-neopt/neopt-test2.cpp )

test:
	./make-test.sh
