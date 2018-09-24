Wenbei Wang
wenbeiwa@usc.edu
USCID: 3692163617
CS104 Hw3

In this homework assignment, I was first asked to finish some problems regarding 
the runtime analysis, stacks and queues. The answers are in hw3.txt. I wrote each step
of my thinking process and derived conclusions from that. For problem 4 and 5, I was
asked to implement a compositional class, which changed the class I created in the last
homework and made it fit in the requirements of this homework. I find this strategy very 
useful, specially when we are work in the group project in the future, it allows I to 
use the existing class and also write my own version of interface. The parser programming 
takes much time then I expected, as it is very cases sensitive. Basically we are just 
detecting the number and positions of parenthesis in each line of arithmetic expressions
in a given file. It should compile circular_list_int.cpp, stackint.cpp and parser.cpp
at the same time, and use the command line to enter the name of the input file. The output
will be printed on the screen in cout. I also wrote a makefile for the parser.cpp, which
makes the compilation much easier. I did not compile those cpp files into object files 
seperately though. Rather, I compile them at the same time. I made a make clean to help
clean the object file which user may not want.  