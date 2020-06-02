# openssl
OPENSSL_PATH=./libs/libcrypton/build/openssl

all:
	mkdir -p build/
	g++ -std=c++17 main-test.cpp src/neo3-cpp-core/ExternalCrypto.cpp -Isrc/ -Ilibs/ -Ilibs/libcrypton/src -I$(OPENSSL_PATH)/include -L$(OPENSSL_PATH)  libs/libcrypton/src/CryptoNeoOpenSSL.cpp -L./libs/csbiginteger-cpp/lib -o build/app_main -lcsbiginteger -lgmp -lgmpxx           -llinux-openssl-crypto-x86_64 -lpthread -ldl 

run:
	./build/app_main

test:
	cd tests && make
	
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
	
js:
	cd tests/node_tests && make js

js_docker:
	cd tests/node_tests && make js_docker

run_js:
	cd tests/node_tests && make run_js

jslib:
	make vendor_js
	# clean remote 'dist/'
	rm -f ./packages/lib-neopt-core-js/dist/*
	cd ./packages/lib-neopt-core-js/ && make compile
	cd ./packages/lib-neopt-core-js/ && make test

clean: 
	rm -f build/*
