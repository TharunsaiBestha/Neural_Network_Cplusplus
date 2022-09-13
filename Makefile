GPPPARAMS=-O3 -std=c++14 -Lbenchmark/build/src -lc++abi -Wl,-rpath=/lib64 -fno-exceptions -fno-rtti -Wall -pedantic -pthread -Werror -isystem benchmark/include 
bench=-lbenchmark
PRAMS=-O3 -std=c++14 -isystem benchmark/include -Lbenchmark/build/src -lc++abi -Wl,-rpath=/lib64 -fno-exceptions -fno-omit-frame-pointer -fno-rtti -Werror -pedantic -lbenchmark -lpthread
PLOT=-std=c++11 -I/usr/include/python2.7 -lpython2.7
CV='pkg-config --cflags --libs opencv'
%.o:%.cpp
		g++-7 $< ${PRAMS} -o $@
-std=c++11 -isystem benchmark/include \
  -Lbenchmark/build/src -lbenchmark
mat:
	g++-7 game_of_life.cpp ${PLOT} -o game_of_life.o 
OpenCV:
	g++-7 -ggdb image_test.cpp -o image_test.o `pkg-config --cflags --libs opencv` 
