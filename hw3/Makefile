all: parser

parser: parser.cpp circular_list_int.cpp stackint.cpp
	g++ -g -Wall -std=c++11 stackint.cpp circular_list_int.cpp parser.cpp -o parser


.PHONY:clean
clean:
	rm -rf parser