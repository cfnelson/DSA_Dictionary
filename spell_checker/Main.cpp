////////////////////////////////////////////////////////////////////////////////////
// Filename:		Main.cpp
// Author:			Charles Nelson - s2884951
// Date Modified:	09/05/2014 Created
//					09/05/2014 Updated 
// Description:		This file contains the main function
////////////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER								
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "HashTable_H.h"

int main ( void )
{
	char tempLine[64];											//- Templine for the input dict file																										
	HashTable myHashTable;
	std::ifstream myDictFile ( "dict.txt" );					//- Creating input file stream from the specified text file
	
	if ( myDictFile.is_open() )
	{
		int count = 1;											//- Count the number of lines
		while ( myDictFile.getline ( tempLine, 64 ) )
		{
			myHashTable.AddDictionaryWord( tempLine );			//- Add the line to the dict
			//std::cout << count << std::endl;					//- Used for Testing Purposes
			count++;
		}
		myDictFile.close();
	}
	else 
	{
		std::cout << "Unable to open file"; 
	}
												
	//myHashTable.PrintHashTable();								//- Checking to see if hash table works by printing to console.
	myHashTable.SpellingWordCheck( myHashTable );				//- Checking if words are in the dictionary.
	system( "PAUSE" );
	return 0;
};
///////////////////////////////////////////////////////////////////////////////////
// END OF FILE
///////////////////////////////////////////////////////////////////////////////////