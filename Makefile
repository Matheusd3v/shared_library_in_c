run: 
	@bin/libcsv

build:
	@gcc -DPROD_BUILD src/*.c -Iinclude -o bin/libcsv

run-dev: build run 

shared-library:
	gcc -shared -fPIC -Iinclude -o libcsv.so src/*.c

build-test:
	@gcc -DTEST_BUILD -Iinclude -Itests/helper/unity -o bin/test_runner tests/*.c tests/helper/unity/*.c src/*.c tests/helper/*.c

run-tests:
	@bin/test_runner

tests: build-test run-tests
	@rm -rf ./bin/*
