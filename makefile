all:
	mkdir -p build/
	g++ main-test.cpp -Isrc/ -o build/app_main



run:
	./build/app_main


vendor: update_submodules get_libcrypton get_csbiginteger  #get_bn-js already provided

get_bn-js:
	npm install bn.js --prefix libs/ -g

update_submodules:
	git submodule update --init --recursive
	git submodule update --recursive

get_libcrypton:
	(cd libs/libcrypton && git submodule update --init --recursive && git submodule update --recursive)
	(cd libs/libcrypton && make vendor)

get_csbiginteger:
	(cd libs/csBigInteger_cpp && git submodule update --init --recursive && git submodule update --recursive)
	(cd libs/csBigInteger_cpp && rm -rf tests/libgtest/build)
	(cd libs/csBigInteger_cpp && make vendor)
	


GCC_FLAGS = -g -O3 -Wall --std=c++17 -fno-exceptions
EMCC_FLAGS = -g -O3 -Wall -s DISABLE_EXCEPTION_CATCHING=1 -s ALLOW_MEMORY_GROWTH=1 --std=c++17
OPENMP_FLAGS = #-fopenmp -lpthread

#-s DISABLE_EXCEPTION_CATCHING=0
# -s ALLOW_MEMORY_GROWTH=1
#EMCC_EXPORTED_FUNCTIONS = -s EXPORTED_FUNCTIONS="['_mytest', '_main']"
EMCC_EXPORTED_FUNCTIONS = -s EXPORTED_FUNCTIONS="['_mytest', '_myteststr']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']"
####PATH_EMCC = "em++"
RESTSDK_FGLAS = #-lboost_system -lcrypto -lssl -lcpprest

jstest: ./jstest.cpp
	mkdir -p build/
	#em++ ./src/main.cpp --js-library src/mycrypto.js -o librarytest.html
	echo "We need Emscripten to proceed (tested with 1.39.16)"
	echo 
	em++ --version
	echo 
	em++ $(EMCC_EXPORTED_FUNCTIONS) $(EMCC_FLAGS) ./jstest.cpp --js-library src/js-crypto/mycrypto.js -o ./build/librarytest.js
	#nodejs testnode.js
	echo "testing build!!"
	nodejs node_test.js

run:
	nodejs build/test.js


clean: 
	rm -f build/*
