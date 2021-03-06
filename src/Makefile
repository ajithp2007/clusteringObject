.PHONY: debug, clean

test: main.cpp kmeans.h jpeg.h jpeg.cpp
	g++ -O3 -std=c++11 -o test *.cpp -ljpeg -lboost_filesystem

debug: main.cpp jpeg.h jpeg.cpp
	g++ -g -O0 -std=c++14 -Wall -Wextra -Wpedantic -Werror -o test *.cpp -ljpeg

clean:
	rm -f test 1.txt clusters.txt
