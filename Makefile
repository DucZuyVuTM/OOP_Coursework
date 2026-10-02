all:
	g++ main.cpp classes/* -o program -std=c++20 -Iheaders

clean:
	rm -f program
