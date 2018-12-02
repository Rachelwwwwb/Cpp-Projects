In this project, I am asked to write the AI of "scrabble".
I created an additional AIPlayer class, which is seperate from player class
(not inheritence). It is used to deal with anything related with AI.
In the main, if a detect that a player is an AI, I create a corresponding AI varaible for it,
and find moves based on the player. There are a constructor, a destructor, a isCPUS and
a getMove function. When finding the move with longest word/largest score, if there's
a tie, I simply break the tie using the order of permutation. 
if (legalMoves[i]->getNewScore() > highest_score)

If it appears first, which means the letters it used are in the front, 
then I will pick that one. 

In the Trie class, I build a trie which used to find whether a certain permuatation
of letters is a prefix of any word. If not, I will not need to preceed checking.
It saves a lot of runtime. I include Trie.h and Trie.cpp under the same folder as
my main function