//////////////////////////////////////////////////////////////////////////////////////////////
// Filename:		HashTable_H.h
// Author:			Charles Nelson - s2884951
// Date Modified:	09/05/2014 Created
//					09/05/2014 Updated 
// Description:		This file contains the prototypes of the Hash Table Class.
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef HashTable_H
#define HashTable_H

#include <list>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip> 
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <cctype>

class HashTable																			//- HashTable Class for a Spellchecking program.
{
private:

	static const int TABLE_SIZE = 3571;													//- Table Size is defined here as a constant, is a large prime number.
	void WriteToSpellingSuggestionFile( std::string inputString );						//- Exports and Writes the suggested word to the "Spelling Suggestions.txt" file 

protected: 

	
public:

	struct DictionaryWord																//- Used to handle hash collisions by implementing chaining.
	{
		std::string word;																//- Contains the dictionary word parsed in from the "dict.txt" file. 
		DictionaryWord* next;															//- Pointer to the next DictionaryWord struct, Used for when collisions happen on the same index. Will use chaining to resolve hash collision. 
	};

	DictionaryWord* hashTable[TABLE_SIZE];												//- HashTable array containing pointers to the DictionaryWord Struct. 
	HashTable();																		//- Default Constructor
	
	~HashTable();																		//- Default Destructor 
	
	unsigned int APHash( const std::string& str );										//- Hash function for our HashTable
	
	int CountNumberOfWordsInDictionary();												//- Count the Number of Words in the Dictionary

	void PrintHashTable();																//- Print the Hash Table to Console
	
	void SearchRHSForSuggestions( int index );											//- Search the Right Hand Side for Suggestions

	void SearchLHSForSuggestions( int index );											//- Search the Left Hand Side for Suggestions

	void CheckIfSpellingSuggestionFileExists();											//- Checks and deletes file if it already exists so we can create a new one				

	void AddDictionaryWord( std::string dictWord );										//- Adds Dict word to Hashtable

	void SpellingWordCheck( HashTable myHashTable );									//- Checks words to see if they are in the dictionary
	
	void SuggestOtherWords( std::string wordToSpellCheck  );							//- Suggests word to user via writing to file.

	bool CheckForBadChar					( char inputChar );							//- Checks for a bad char
	bool CheckForBadInput					( std::string &checkWord );					//- Checks for bad input
	bool CheckForGrammarAtEOL				( char inputChar1, char inputChar2 );		//- Checks for bad cases of grammar
	bool CheckSecondLastCharForBadInput		( char inputChar );							//- Confirms that no bad bad input's have occured.
	bool ConvertUpperCaseToLowerCaseAndCheckIsDigit		( char* &cstr_line );			//- Converts all upper case char's to lowercase char's
	bool HashTable::checkIfWordIsInHashTable( std::string wordToSpellCheck );			//- Checks if word is in the Hashtable
	std::string MergeHyphen					(	std::string lineToCheck, 
												std::string lineToMergeWith );			//- Merges a line that ends with a hypen to the next line, it also removes this hypen when joining the lines together.
};
#endif
/////////////////////////////////////////////////////////////////////////////////////////////
// END OF FILE
/////////////////////////////////////////////////////////////////////////////////////////////