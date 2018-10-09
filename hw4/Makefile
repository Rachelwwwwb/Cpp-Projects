all: scrabble

scrabble: scrabble.cpp Player.o Bag.o Dictionary.o Move.o Board.o ConsolePrinter.o
	g++ -g -Wall -std=c++11 scrabble.cpp Player.o Bag.o Dictionary.o Move.o Board.o ConsolePrinter.o -o scrabble

Player.o: Player.cpp	
	g++ -g -Wall -c -std=c++11 Player.cpp -o Player.o

Bag.o: Player.cpp
	g++ -g -Wall -c -std=c++11 Bag.cpp -o Bag.o

Dictionary.o: Dictionary.cpp
	g++ -g -Wall -c -std=c++11 Dictionary.cpp -o Dictionary.o

Move.o: Move.cpp
	g++ -g -Wall -c -std=c++11 Move.cpp -o Move.o

Board.o: Player.cpp
	g++ -g -Wall -c -std=c++11 Board.cpp -o Board.o

ConsolePrinter.o: ConsolePrinter.cpp
	g++ -g -Wall -c -std=c++11 ConsolePrinter.cpp -o ConsolePrinter.o


.PHONY: clean

clean:
	rm -f Player.o Bag.o Dictionary.o Move.o Board.o ConsolePrinter.o scrabble.o

