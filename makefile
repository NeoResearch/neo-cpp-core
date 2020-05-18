all:
	g++ main-test.cpp -Isrc/ -o build/app_main



run:
	./build/app_main


vendor:
	git submodule update --init --recursive
	git submodule update --recursive
	(cd libs/libcrypton && git submodule update --init --recursive && git submodule update --recursive)
	(cd libs/libcrypton && make vendor)
	


GCC_FLAGS = -g -O0 -Wall --std=c++17 -fno-exceptions
EMCC_FLAGS = -g -O0 -Wall -s DISABLE_EXCEPTION_CATCHING=1 -s ALLOW_MEMORY_GROWTH=1 --std=c++17
OPENMP_FLAGS = #-fopenmp -lpthread

#-s DISABLE_EXCEPTION_CATCHING=0
# -s ALLOW_MEMORY_GROWTH=1
#EMCC_EXPORTED_FUNCTIONS = -s EXPORTED_FUNCTIONS="['_mytest', '_main']"
EMCC_EXPORTED_FUNCTIONS = -s EXPORTED_FUNCTIONS="['_mytest']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']"
####PATH_EMCC = "em++"
RESTSDK_FGLAS = #-lboost_system -lcrypto -lssl -lcpprest

libtest: ./src/main.cpp
	#em++ ./src/main.cpp --js-library src/mycrypto.js -o librarytest.html
	em++ $(EMCC_EXPORTED_FUNCTIONS) $(EMCC_FLAGS) ./src/main.cpp --js-library src/mycrypto.js -o ./build/librarytest.js
	#nodejs testnode.js
#

run:
	nodejs build/test.js
