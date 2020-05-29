NEO3_SRC=../../src/
PRE_JS_FILE=../../packages/lib-neopt-core-js/src/prefix-node-require.js
LIB_JS_TO_BIND=../../packages/lib-neopt-core-js/src/bindings-cpp-js/web-libcore_exports.js
MODULE_NAME='EXPORT_NAME="Neo3CppLib"'
ASSERTIONS=ASSERTIONS=1
LIBS_TP=../../libs/
LIBS_JS=../../packages/
EMCC_FLAGS = -g -O3 -Wall -s DISABLE_EXCEPTION_CATCHING=1 -s ALLOW_MEMORY_GROWTH=1 --std=c++17
#-s DISABLE_EXCEPTION_CATCHING=0
# -s ALLOW_MEMORY_GROWTH=1
#EMCC_EXPORTED_FUNCTIONS = -s EXPORTED_FUNCTIONS="['_mytest', '_main']"
EMCC_EXPORTED_FUNCTIONS =  -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap', 'UTF8ToString', 'stringToUTF8']" # -s EXPORTED_FUNCTIONS="['_c_API_CreateSignatureRedeemScript']"


js: ./jstest.cpp
	mkdir -p build/
	@echo "We need Emscripten to proceed (tested with 1.39.16)"
	echo 
	em++ --version
	@echo " ==== Compiling 'jstest.cpp' into './build/librarytest.js' ====== "
	em++ --bind -I$(LIBS_TP) -I$(LIBS_JS) --pre-js $(PRE_JS_FILE) $(EMCC_EXPORTED_FUNCTIONS) $(EMCC_FLAGS) ./jstest.cpp -I$(NEO3_SRC) --js-library $(LIB_JS_TO_BIND) -s $(MODULE_NAME) -s $(ASSERTIONS) -o ./build/librarytest.js

run_js:
	@echo
	@echo "======= testing 'node_test.js' ======="
	@echo
	npm install csbiginteger
	npm install crypto-js
	node ./node_test.js
