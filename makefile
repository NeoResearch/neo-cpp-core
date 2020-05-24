# openssl
OPENSSL_PATH=./libs/libcrypton/build/openssl

all:
	mkdir -p build/
	g++ -std=c++17 main-test.cpp src/neo3-cpp-core/ExternalCrypto.cpp -Isrc/ -Ilibs/ -Ilibs/libcrypton/src -I$(OPENSSL_PATH)/include -L$(OPENSSL_PATH)  libs/libcrypton/src/CryptoNeoOpenSSL.cpp -L./libs/csbiginteger-cpp/lib -o build/app_main -lcsbiginteger -lgmp -lgmpxx           -llinux-openssl-crypto-x86_64 -lpthread -ldl 



run:
	./build/app_main


vendor: update_submodules get_libcrypton get_csbiginteger  #get_bn-js already provided
	@echo "Finished 'make vendor' successfully"

get_bn-js:
	npm install bn.js --prefix libs/ -g
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
EMCC_FLAGS = -g -O3 -Wall -s DISABLE_EXCEPTION_CATCHING=1 -s ALLOW_MEMORY_GROWTH=1 --std=c++17
OPENMP_FLAGS = #-fopenmp -lpthread

#-s DISABLE_EXCEPTION_CATCHING=0
# -s ALLOW_MEMORY_GROWTH=1
#EMCC_EXPORTED_FUNCTIONS = -s EXPORTED_FUNCTIONS="['_mytest', '_main']"
EMCC_EXPORTED_FUNCTIONS = -s EXPORTED_FUNCTIONS="['_mytest', '_myteststr']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap', 'UTF8ToString', 'stringToUTF8', 'writeStringToMemory', 'getValue', 'setValue']"
####PATH_EMCC = "em++"
RESTSDK_FGLAS = #-lboost_system -lcrypto -lssl -lcpprest

BN_JS=./libs/lib/node_modules/bn.js/lib/bn.js

NEO3_SRC=./src/

jstest: ./jstest.cpp
	mkdir -p build/
	#em++ ./src/main.cpp --js-library src/mycrypto.js -o librarytest.html
	@echo "We need Emscripten to proceed (tested with 1.39.16)"
	echo 
	em++ --version
	@echo " ==== Compiling 'jstest.cpp' into './build/librarytest.js' ====== "
	em++ -Ilibs/ --bind $(EMCC_EXPORTED_FUNCTIONS) $(EMCC_FLAGS) ./jstest.cpp -I$(NEO3_SRC) --js-library src/libcore-js/libcore_exports.js --js-library $(BN_JS) -o ./build/librarytest.js # -s MODULARIZE=1 -s 'EXPORT_NAME="Neo3CPP"' -s ASSERTIONS=1
	#### -s EXPORT_ES6=1 -s MODULARIZE=1 -s USE_ES6_IMPORT_META=0
	#
	#nodejs testnode.js
	@echo
	@echo "======= testing 'node_test.js' ======="
	@echo
	nodejs node_test.js
	@echo
	@echo " ====== testing node_bn_test.js ====== "
	@echo
	nodejs node_bn_test.js

run:
	nodejs build/test.js


clean: 
	rm -f build/*
