NEO3_SRC=../../src/
LIBS_TP=../../libs/
LIBS_JS=../../packages/
PRE_JS_FILE=../../packages/lib-neopt-core-js/src/prefix-node-require.js
LIB_JS_TO_BIND=../../packages/lib-neopt-core-js/src/bindings-cpp-js/web-libcore_exports.js
MODULE_NAME='EXPORT_NAME="Neo3CppLib"'
ASSERTIONS=ASSERTIONS=1
EMCC_FLAGS = -g -O3 -Wall -s DISABLE_EXCEPTION_CATCHING=1 -s ALLOW_MEMORY_GROWTH=1 --std=c++17
EMCC_EXPORTED_FUNCTIONS_EXTRA = -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap', 'UTF8ToString', 'stringToUTF8']"
# EMCC_EXPORTED_FUNCTIONS = -s EXPORTED_FUNCTIONS="['_mytest', '_main']"
# EXPORTED_FUNCTIONS="['_c_API_CreateSignatureRedeemScript']"
EMCC_SOURCE_DOCKER=docker run --rm -v $(PWD)/../../:/src trzeci/emscripten em++
NEO3_SRC_DOCKER=./src/
LIBS_TP_DOCKER=./libs/
LIBS_JS_DOCKER=./packages/
PRE_JS_FILE_DOCKER=./packages/lib-neopt-core-js/src/prefix-node-require.js
LIB_JS_TO_BIND_DOCKER=./packages/lib-neopt-core-js/src/bindings-cpp-js/web-libcore_exports.js

js: ./jstest.cpp
	mkdir -p build/
	@echo "We need Emscripten to proceed (tested with 1.39.16)"
	echo 
	em++ --version
	@echo " ==== Compiling 'jstest.cpp' into './build/librarytest.js' ====== "
	em++ --bind -I$(LIBS_TP) -I$(LIBS_JS) --pre-js $(PRE_JS_FILE) $(EMCC_EXPORTED_FUNCTIONS_EXTRA) $(EMCC_FLAGS) ./jstest.cpp -I$(NEO3_SRC) --js-library $(LIB_JS_TO_BIND) -s $(MODULE_NAME) -s $(ASSERTIONS) -o ./build/librarytest.js

js_docker:
	mkdir -p build/
	@echo "We need docker trzeci/emscripten"
	echo 
	$(EMCC_SOURCE_DOCKER) --version
	@echo " ==== Compiling 'jstest.cpp' into './build/librarytest.js' ====== "
	$(EMCC_SOURCE_DOCKER) --bind -I$(LIBS_TP_DOCKER) -I$(LIBS_JS_DOCKER) --pre-js $(PRE_JS_FILE_DOCKER) $(EMCC_EXPORTED_FUNCTIONS_EXTRA) $(EMCC_FLAGS) ./tests/node_tests/jstest.cpp -I$(NEO3_SRC_DOCKER) --js-library $(LIB_JS_TO_BIND_DOCKER) -s $(MODULE_NAME) -s $(ASSERTIONS) -o ./tests/node_tests/build/librarytest.js

run_js:
	@echo
	@echo "======= testing 'node_test.js' ======="
	@echo
	npm install csbiginteger
	npm install crypto-js
	node ./node_test.js
