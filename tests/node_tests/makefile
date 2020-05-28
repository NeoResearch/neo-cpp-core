EMCC_FLAGS = -g -O3 -Wall -s DISABLE_EXCEPTION_CATCHING=1 -s ALLOW_MEMORY_GROWTH=1 --std=c++17

#-s DISABLE_EXCEPTION_CATCHING=0
# -s ALLOW_MEMORY_GROWTH=1
#EMCC_EXPORTED_FUNCTIONS = -s EXPORTED_FUNCTIONS="['_mytest', '_main']"
EMCC_EXPORTED_FUNCTIONS = -s EXPORTED_FUNCTIONS="['_mytest', '_myteststr', '_c_API_CreateSignatureRedeemScript']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap', 'UTF8ToString', 'stringToUTF8']"

NEO3_SRC=../../src/

js: ./jstest.cpp
	mkdir -p build/
	@echo "We need Emscripten to proceed (tested with 1.39.16)"
	echo 
	em++ --version
	@echo " ==== Compiling 'jstest.cpp' into './build/librarytest.js' ====== "
	em++ -I../../libs/ -I../../packages/ --pre-js ../../packages/neopt-cpp-lib-js/src/prefix-node-require.js --bind $(EMCC_EXPORTED_FUNCTIONS) $(EMCC_FLAGS) ./jstest.cpp -I$(NEO3_SRC) --js-library ../../packages/neopt-cpp-lib-js/src/neo3-cpp-bindings-js/web-libcore_exports.js -o ./build/librarytest.js  -s 'EXPORT_NAME="Neo3CppLib"' -s ASSERTIONS=1

run_js:
	@echo
	@echo "======= testing 'node_test.js' ======="
	@echo
	npm install csbiginteger
	npm install crypto-js
	node ./node_test.js
