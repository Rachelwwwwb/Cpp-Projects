#include <set>
#include <string>
#include <fstream>
#include "Dictionary.h"

using namespace std;
	/* The constructor gets passed the name of the file from which
	   to read the word list. */
	Dictionary::Dictionary (std::string dictionary_file_name){
        std::ifstream dicFileStream(dictionary_file_name);
	    if(!dicFileStream)
	    {
		   // throw FileException("DICTIONARY");
	    }

        while(!dicFileStream.eof()){
            string legalWord = "";
            dicFileStream >> legalWord;
            if (legalWord.size() <= 1) continue;
            
            _dictionary.insert(legalWord);
        }
    }

	Dictionary::~Dictionary (){
        return;
    }

	/* Checks whether the given word is in the dictionary, and returns true if so.
	   Case should not matter. Must run in O(logn) for the number of words in the dictionary. */
	bool Dictionary::isLegalWord (std::string const & word) const{
        return _dictionary.find(word) != _dictionary.end();
    }
