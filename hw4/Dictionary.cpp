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
        string lower = "";
        string upper = "";
        for (size_t i = 0; i < word.size();i++){
            lower += tolower(word[i]);
            upper += toupper(word[i]);
        }
        bool _lower = _dictionary.find(lower) != _dictionary.end();
        bool _upper = _dictionary.find(upper) != _dictionary.end();
        return _lower || _upper;
    }
