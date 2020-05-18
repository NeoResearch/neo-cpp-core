all:
	g++ main-test.cpp -o build/app_main



run:
	./build/app_main


vendor:
	(cd libs/libcrypton && git submodule update --init --recursive && git submodule update --recursive)
	(cd libs/libcrypton && make vendor)
	