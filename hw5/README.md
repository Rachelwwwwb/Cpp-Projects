Wenbei Wang
Homework 5

Problem 1:
This question asks me to create the classes structure for a car racing game. I draw the graph by hand
and upload it as a pdf in the Game.pdf. The game class is the largest class containing the whole game.
It should HAS some arbitary number of players in it. For each player, he/she HAS-A car, HAS-A item and 
HAS-A characteristics. Both item and characteristics class should be abstract, since a player cannot
have an item or characteristics without specifying what it is. Then the car is composed by a chassis,
a color and a engine, so no inherit here, only composition. The color class is used for the player
to set the color. Since each color should have the same uses, so there should be no different
functions for any specific color. As a result, the color class has no inheritance. Both the chasis
and the engine class are abstract classes, with several specific subclasses which publically
inherit from them.The item class has several classes publically inherit from it, as each of them
IS-A item. The weapons class should be an abstract one, with several sepecfic weapons publically inherit 
from it. For the same reason, the characterstics class has three subclasses strength, experience, and control.
They share some common things, but each has different propertities. So each of them IS-A characterstics,
so public inheritance. 

Problem 2:
Suppose the array of size 12 has elements 0-11.
One of the worst possible pivot selection over all calls to partition would be:
0 2 4 6 8 10 1 3 5 7 9 11
The worst case would be for the quicksort would be each time seperatinig only one
element out. Since it is the median-of-3, the pivot can't be the smallest. So I 
make the cases where pivot is the second largest/smallest elements of the remaining
as much as possible. For example, in the first round, the median-of-3 will pick the
pivot between 0,10,11. So it will pick 10 and in this round, only 10 and 11 will be sorted.
Before the second round, the array will be:
0 2 4 6 8 1 3 5 7 9 10 11  
From the unsorted 0 - 7, it will pick a pivot among 0,8,9. And again the second smallest
is picked and so on.

Problem 4d:
The runtime analysis of the k-way templated Merge Sort is in the runtime.pdf.
When k = n, it resembles the insertion sort: selection the first unsorted element, sort
it and then the unsorted element index ++;
In this case, the run time would be n^2.
