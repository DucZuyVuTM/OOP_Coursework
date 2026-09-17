all:
	g++ main.cpp classes/* -o program -std=c++20

clean:
	rm -f program
