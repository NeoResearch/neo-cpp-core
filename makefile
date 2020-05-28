# openssl
OPENSSL_PATH=./libs/libcrypton/build/openssl

all:
	mkdir -p build/
	g++ -std=c++17 main-test.cpp src/neo3-cpp-core/ExternalCrypto.cpp -Isrc/ -Ilibs/ -Ilibs/libcrypton/src -I$(OPENSSL_PATH)/include -L$(OPENSSL_PATH)  libs/libcrypton/src/CryptoNeoOpenSSL.cpp -L./libs/csbiginteger-cpp/lib -o build/app_main -lcsbiginteger -lgmp -lgmpxx           -llinux-openssl-crypto-x86_64 -lpthread -ldl 



run:
	./build/app_main


vendor: vendor_js vendor_cpp  #get_bn-js already provided
	@echo "Finished 'make vendor' successfully"

vendor_js: update_submodules
	# empty

vendor_cpp: update_submodules get_libcrypton get_csbiginteger

get_bn-js:
	npm install bn.js --prefix libs/ -g
	####cp libs/lib/node_modules/bn.js/lib/bn.js xx-no-need-to-copy
	#npm install csbiginteger.js --prefix libs/ -g   ## TODO:
	npm install crypto-js --prefix libs/ -g

update_submodules:
	git submodule update --init --recursive
	git submodule update --recursive

get_libcrypton:
	(cd libs/libcrypton && git submodule update --init --recursive && git submodule update --recursive)
	(cd libs/libcrypton && make vendor && make test)

get_csbiginteger:
	(cd libs/csbiginteger-cpp && git submodule update --init --recursive && git submodule update --recursive)
	(cd libs/csbiginteger-cpp && rm -rf tests/libgtest/build)
	(cd libs/csbiginteger-cpp && make vendor && make test)
	


GCC_FLAGS = -g -O3 -Wall --std=c++17 -fno-exceptions
OPENMP_FLAGS = #-fopenmp -lpthread

####PATH_EMCC = "em++"
RESTSDK_FGLAS = #-lboost_system -lcrypto -lssl -lcpprest

NEO3_SRC=./src/

js:
	cd tests/node_tests && make js
#js: ./tests/node_tests/jstest.cpp
#	mkdir -p build/
#	@echo "We need Emscripten to proceed (tested with 1.39.16)"
#	echo 
#	em++ --version
#	@echo " ==== Compiling 'jstest.cpp' into './build/librarytest.js' ====== "
#	em++ -Ilibs/ -Ipackages/ --pre-js ./packages/neopt-cpp-lib-js/src/prefix-node-require.js --bind $(EMCC_EXPORTED_FUNCTIONS) $(EMCC_FLAGS) ./tests/node_tests/jstest.cpp -I$(NEO3_SRC) --js-library ./packages/neopt-cpp-lib-js/src/neo3-cpp-bindings-js/web-libcore_exports.js -o ./build/librarytest.js  -s 'EXPORT_NAME="Neo3CppLib"' # -s MODULARIZE=1 -s ASSERTIONS=1

run_js:
	cd tests/node_tests && make run_js

#run_js:
#	@echo
#	@echo "======= testing 'node_test.js' ======="
#	@echo
#	node ./tests/node_tests/node_test.js


test:
	cd tests && make

clean: 
	rm -f build/*
