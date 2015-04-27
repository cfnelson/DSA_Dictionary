//////////////////////////////////////////////////////////////////////////////////////////////
// Filename:		HashTable.cpp
// Author:			Charles Nelson - s2884951
// Date Modified:	09/05/2014 Created
//					09/05/2014 Updated 
// Description:		This file contains the implementation of the Hash Table Class.
/////////////////////////////////////////////////////////////////////////////////////////////
#include "HashTable_H.h"

//==================================== PRIVATE FUNCTIONS ==========================================

/*****************************************************************
* Description:		This function writes the suggested word
*					 to the "Spelling Suggestions.txt" file.
*
* Returns:			NIL
*
* Parameters:		std::string inputString; 
*		
*
* Preconditions:	Hashtable is completed and ready to be exported.
*
* Postconditions:	NIL
*****************************************************************/
void HashTable::WriteToSpellingSuggestionFile( std::string inputString )
{
	std::ofstream spellSugestionFile ( "Spelling Suggestions.txt", std::ios::app );
	if ( spellSugestionFile.is_open() )
	{
		spellSugestionFile << inputString << "\n";
		spellSugestionFile.close();
	}
	else 
	{
		std::cout << "Unable to open file." << std::endl;
	}
}																//- End of WriteToSpellingSuggestionFile Function

//==================================== PUBLIC FUNCTIONS ===========================================
/**************************************************************************************************
* Description:		This function is the Constructor for the HashTable.
*
* Returns:			NIL - (Is the Constructor)
*
* Parameters:		NIL
*
* Preconditions:	static const TABLE_SIZE must have been defined.
*
* Postconditions:	A HashTable object is constructed with an array containing Pointers to empty 
*					DictionaryWord Structs.
**************************************************************************************************/
HashTable::HashTable()											//- Default Constructor 
{
	for ( int i = 0; i < TABLE_SIZE; i++ )						//- Loop through and initialise all elements to empty DictionaryWord Structs.
	{
		hashTable[i] = new DictionaryWord;						//- Constructing default empty DictionaryWord Struct for each element in the hashTable array.
		hashTable[i]  -> word = "EMPTY";						//- Setting to EMPTY.
		hashTable[i]  -> next = NULL;							//- Setting to NULL.
	}
	CheckIfSpellingSuggestionFileExists();						//- Checking if file exists, if it does we delete it.
}																//- End of the Constructor Function.

/*****************************************************************
* Description:		This function is the Destructor for the HashTable.
*					
*
* Returns:			NIL - (Is the Destructor)
*
* Parameters:		NIL
*		
*
* Preconditions:	HashTable object exists. 
*
* Postconditions:	Memory has been freed.
*****************************************************************/
HashTable::~HashTable()											//- Default Destructor. 
{
	for ( int i = 0; i < TABLE_SIZE; i++ )
	{
		DictionaryWord* ptrTemp = hashTable[i] -> next;
		DictionaryWord* ptrToDelete = NULL;
		
		while ( ptrTemp != NULL  )								//- Loop until all DictWords have been deleted
		{
			ptrToDelete = ptrTemp;								//- Assigning the struct to delete
			ptrTemp  = ptrTemp -> next;							//- Moving to the next struct
			delete ptrToDelete;									//- Deleting the DictWord Struct
			ptrToDelete = NULL;									//- Setting to NULL
		}
		delete hashTable[i];									//- Deleting the DictWord Struct
		hashTable[i] = NULL;									//- Setting to NULL
	}
}																//- End of the Destructor Function.
	
/*****************************************************************
* Description:		This is the hash function for calculating where our word 
*					is to be stored in our hashtable.
*
* Returns:			unsigned int index; Index of where to store our word
*
* Parameters:		const std::string& str; Word to hash 
*		
*
* Preconditions:	The array to store the DictWords has been created.
*
* Postconditions:	Returns the index of where to insert the word.
*****************************************************************/
unsigned int HashTable::APHash( const std::string& str )						//- APHash retreived from General Purpose Hash Function Library
{
	/* This function has more collisions and chains -
	   doesnt improve accuracy of spelling suggestions ethier. */
	/*char* tempString = new char[str.length()+1];
	std::strcpy( tempString, str.c_str() );
	int sl = strlen(tempString);
	int si = 0;
	unsigned int rv = 0;
	for(int i = 0; i < 5; i++)
	{
		rv += ((unsigned int)((unsigned char)tempString[si]));
		si++;
		si %= sl;
	}
	return rv;
	*/

	/* The below algorithm's max chain length for the provided text file's is 1 */	
	int index = 0;
	unsigned int hash = 0xAAAAAAAA;

	for ( std::size_t i = 0; i < str.length(); i++ )
	{
		hash ^= ( ( i & 1 ) == 0 ) ? (  ( hash <<  7 ) ^ str[i] * ( hash >> 3 ) ) 
				: ( ~( ( hash << 11 ) + ( str[i] ^ ( hash >> 5 ) ) ) );
	}

	index = hash % TABLE_SIZE;													//- Creating index from the hash function
	//std::cout << "index "  << " = "<< hash	<< std::endl;					//- Used for testing purposes
    //std::cout << "index "  << " = "<< index	<< std::endl;					//- Used for testing purposes
	return index;
}																				//- End of APHash Function

/*****************************************************************
* Description:		This function counts the number of words in our Dictionary
*					
*
* Returns:			int count; The number of words in the Dictionary.
*
* Parameters:		NIL
*		
*
* Preconditions:	Hashtable has been constructed.
*
* Postconditions:	Returned the count.
*****************************************************************/
int HashTable::CountNumberOfWordsInDictionary( )								
{
	int count = 0;
	for ( int i = 0; i < TABLE_SIZE; i++ )										//- Loop through the hashtable
	{
		if ( hashTable[i] -> word != "EMPTY" )									//- Check if it is Empty
		{
			count++;
			DictionaryWord* ptr_iterator = hashTable[i] -> next;				//- Creating an pointer to move through our list
		
			while ( ptr_iterator != NULL )										//- Loop until the end
			{
				 count++;														//- Add to the count
				 ptr_iterator = ptr_iterator -> next;							//- Move to the next DictionaryWord Struct
			}
		}
	}
	//std::cout << count<< std::endl;											//- Used for Testing 
	return count;
}																				//- End of CountNumberOfWordsInDictionary Function

/*****************************************************************
* Description:		This function adds a word to our dictionary.
*					We are using a HashTable with chaining for hash collisions.
*
* Returns:			NIL
*
* Parameters:		std::string dictWord; Word to add
*		
*
* Preconditions:	hashtable has been instantiated and exists.
*
* Postconditions:	dictWord has been inserted into are hashtable.
*****************************************************************/
void HashTable::AddDictionaryWord( std::string dictWord )
{
	int index = APHash( dictWord );															//- Creating index from the hash function
	if ( hashTable[index] -> word == "EMPTY")												//- Check to see if element doesn't already contain a word.
	{
		hashTable[index] -> word = dictWord;												//- Adding new word to the dictionary.
		hashTable[index] -> next = NULL;													//- Setting to NULL
		//std::cout <<"index " << dictWord << std::endl;									//- Used for testing Purposes.
	}
	else 
	{
		DictionaryWord* ptr_iterator = hashTable[index];									//- Pointer to the first dictionary word currently stored at that index.
		DictionaryWord* chainNewWord = new DictionaryWord;									//- Creating new Struct for the hash chain.
		chainNewWord -> word = dictWord;													//- Setting the new DictionaryWord's word to the dictWord to be added to Dictionary. 
		chainNewWord -> next = NULL;														//- Setting the pointer to the next DictionaryWord Struct to NULL.
		
		while ( ptr_iterator -> next != NULL )												//- Iterate throught he chain until we reach the end. So we can add the dictionary word to the end.
		{
			ptr_iterator = ptr_iterator -> next;											//- Moving to the next word in the chain e.g The Next DictionaryWord Struct.
		}
		ptr_iterator -> next = chainNewWord;												//- Adding new Dictionary word to the end of the Chain. E.G - A new DictionaryWord Struct.
	}
}																							//- End of AddDictionaryWord Function.

/*****************************************************************
* Description:		This function prints the hashtable.
*					
*
* Returns:			NIL
*
* Parameters:		NIL
*		
*
* Preconditions:	hashtable has been instantiated and exists.
*
* Postconditions:	Printed the hashtable to console.
*****************************************************************/
void HashTable::PrintHashTable()														//- Prints the HashTable 
{
	int wordCount = 1;
	for ( int i = 0; i < TABLE_SIZE; i++ )
	{
		if ( hashTable[i] -> word != "EMPTY" )
		{
			std::cout << "Word " << wordCount << " = " << 
						 hashTable[i] -> word << std::endl; 
			int chainCount = 0;
			DictionaryWord* ptr_iterator = hashTable[i] -> next;						//- Ptr to the first dictionary word currently stored in the chain
			while ( ptr_iterator != NULL )												//- Iterate throught the chain until we reach the end. 
			{
				chainCount++;
				wordCount++;
				std::cout << "Word " << wordCount << " : Chain " <<	chainCount
						  << " = " << ptr_iterator -> word		 << std::endl;
				ptr_iterator = ptr_iterator -> next;									//- Moving to the next word in the chain.
			}
			wordCount++;
		}
	}																					//- End of For Loop
}																						//- End of PrintHashTable Function

/*****************************************************************
* Description:		This function checks to see if the spelling file exists.
*					
*
* Returns:			NIL
*
* Parameters:		NIL
*		
*
* Preconditions:	NIL
*
* Postconditions:	Checked if the file exists.
*****************************************************************/
void HashTable::CheckIfSpellingSuggestionFileExists()
{
	if ( remove( "Spelling Suggestions.txt" ) != 0 )										//- Deletes the Spelling Suggestions.txt file if it exists. This ensures that we do not keep on writing to the same output.  
	{
		perror( "Error deleting file" );
	}
	else
	{
		puts( "File successfully deleted" );
	}
}																							//- End of CheckIfSpellingSuggestionFileExists Function

/*****************************************************************
* Description:		This function checks for spelling suggestions on the 
*					right hand side of the array index and prints the first 2.
*
* Returns:			NIL
*
* Parameters:		int index ; Index to start the searching from.
*		
*
* Preconditions:	index of hashed word is ready.
*
* Postconditions:	Suggestions have been returned
*****************************************************************/
void HashTable::SearchRHSForSuggestions( int index )	
{
	int countRHS = 0;																		//- Holds the count of spelling suggestions for the RHS of the provided hashTable index.
	int array_RHS_Iterator = index + 1;
	while ( countRHS != 2 && array_RHS_Iterator < TABLE_SIZE )
	{
		if ( hashTable[array_RHS_Iterator] -> word == "EMPTY")
		{
			array_RHS_Iterator++;															//- Moving to the next element in the array
		}
		else if ( hashTable[array_RHS_Iterator] -> word != "EMPTY" )
		{
			WriteToSpellingSuggestionFile( "Spelling Suggestion - RHS : " + 
											hashTable[array_RHS_Iterator] -> word );		//- Writing to spelling suggestion file
			/*std::cout << "Spelling Suggestion - RHS : " << 
							hashTable[array_RHS_Iterator] -> word << std::endl;*/			//- Used for testing purposes
			countRHS++;																		//- Incrementing the Count by one.	
			while ( hashTable[array_RHS_Iterator] -> next != NULL && countRHS != 2 )
			{
				DictionaryWord* ptr_temp = hashTable[array_RHS_Iterator] -> next;
				WriteToSpellingSuggestionFile( "Spelling Suggestion - Chain : " + 
												ptr_temp -> word );							//- Writing to spelling suggestion file
				/*std::cout << "Spelling Suggestion - Chain : " << 
								ptr_temp -> word << std::endl;*/
				ptr_temp = ptr_temp -> next; 
				countRHS++;																	//- Incrementing the Count by one.	
			}
			array_RHS_Iterator++;															//- Moving to the next element in the array
		}
	}
}																							//- End of SearchRHSForSuggestions Function

/*****************************************************************
* Description:		This function checks for spelling suggestions on the 
*					left hand side of the array index and prints the first 2.
*
* Returns:			NIL
*
* Parameters:		int index ; Index to start the searching from.
*		
*
* Preconditions:	index of hashed word is ready.
*
* Postconditions:	Suggestions have been returned
*****************************************************************/
void HashTable::SearchLHSForSuggestions( int index )	
{
	int countLHS = 0;																		//-  Holds the count of spelling suggestions for the LHS of the provided hashTable index.
	int array_LHS_Iterator = index - 1;
	while ( countLHS != 2 && array_LHS_Iterator > -1 )										//- Iterates through the hashTable until 2 suggestions are found or it reaches the starting index of the hashTable.
	{
		if ( hashTable[array_LHS_Iterator] -> word == "EMPTY")								//- Checks to see if the current index is empty. If it is EMPTY then move to the next element in array.  E.G - Checks if it has a dictionary word. 
		{
			array_LHS_Iterator--;															//- Moving to the next element in the array. NOTE: Moving Backwards here
		}
		else if ( hashTable[array_LHS_Iterator] -> word != "EMPTY" )						//- Check to see if the current index contains a pointer to a dictionary word. If the Element is not empty then it will enter the condition.
		{
			/*std::cout << "Spelling Suggestion - LHS : " << 
							hashTable[array_LHS_Iterator] -> word << std::endl;	*/			//- Used for testing purposes
			WriteToSpellingSuggestionFile( "Spelling Suggestion - LHS : " + 
											hashTable[array_LHS_Iterator] -> word );		//- Writing to spelling suggestion file
			countLHS++;																		//- Incrementing the Count by one.																										

			while ( hashTable[array_LHS_Iterator] -> next != NULL && countLHS != 2 )		//- Iterate through the DictionaryWord Chain until 2 Suggestions have been found
			{
				DictionaryWord* ptr_temp = hashTable[array_LHS_Iterator] -> next;
				/*std::cout << "Spelling Suggestion - Chain : " << 
								ptr_temp -> word << std::endl; */							//- Used for testing purposes
				WriteToSpellingSuggestionFile( "Spelling Suggestion - Chain : " + 
												ptr_temp -> word );							//- Writing to spelling suggestion file
				ptr_temp = ptr_temp -> next;												//- Moving to the next DictionaryWord Struct.
				countLHS++;																	//- Incrementing the Count by one.
			}
			array_LHS_Iterator--;															//- Moving to the next element in the array. NOTE: Moving Backwards here
		}
	}
}																							//- End of SearchLHSForSuggestions Function

/*****************************************************************
* Description:		This function provides spelling suggestions from our Dictionary. 
*				
*
* Returns:			NIL
*
* Parameters:		std::string wordToSpellCheck; Word to provide spelling 
*					suggestions for/		
*
* Preconditions:	Hashtable is created.
*
* Postconditions:	Suggestions have been returned.
*****************************************************************/
void HashTable::SuggestOtherWords( std::string wordToSpellCheck  )							//- Function searches hashTable and suggests up to 4 words for the user via writing to the "Spelling Suggestions.txt" file.
{
	int index = 0;																			//- Index of the hashTable Array
	index = APHash( wordToSpellCheck );														//- Setting starting point for search hashTable for word suggestions.
	SearchLHSForSuggestions( index );														//- Searches the LHS of the hashTable for the 2 closest words and writes them to "Spelling Suggestions.txt" file.
	SearchRHSForSuggestions( index );														//- Searches the RHS of the hashTable for the 2 closest words and writes them to "Spelling Suggestions.txt" file.
}																							//- End of SuggestOtherWords Function

/*****************************************************************
* Description:		This function checks if the word is in our HashTable.
*					
*
* Returns:			NIL
*
* Parameters:		std::string wordToSpellCheck; Word to Check
*		
*
* Preconditions:	Hashtable is created.
*
* Postconditions:	NIL
*****************************************************************/
bool HashTable::checkIfWordIsInHashTable( std::string wordToSpellCheck )
{
	int index = -1;																						//- Not sure if this is bad but its outside array so it will cause a crash if my APHASH function fucks up
	index = APHash( wordToSpellCheck );																	//- Setting index to the value specified by the hash function.
	
	if ( hashTable[index] -> next != NULL && hashTable[index] -> word != wordToSpellCheck  )			//- If word's do not match and there is chaining occuring						
	{
		DictionaryWord* ptr_iterator = hashTable[index];
		while ( ptr_iterator -> next != NULL )
		{
			if ( wordToSpellCheck == ptr_iterator -> word )
			{
				return true;																			//- Word is in the dictionary 
			}
			else
			{
				ptr_iterator = ptr_iterator -> next;													//- Iterating to the next DictionaryWord Struct
			}
		}
		//std::cout << "\n" << "Word is not in dictionary : "  << wordToSpellCheck << std::endl;
		WriteToSpellingSuggestionFile( "\nWord is not in dictionary : " + wordToSpellCheck );			//- Writing the word that is not in the dictionary to "Spelling Suggestions.txt" file
		SuggestOtherWords( wordToSpellCheck );															//- Checking for possible word suggestions and exporting to "Spelling Suggestions.txt" file
		return false;																					//- Word not in dictionary 
	}
	else if ( hashTable[index] -> word != "EMPTY" && hashTable[index] -> word == wordToSpellCheck ) 
	{
		return true;																					//- Word is in the dictionary 
	}
	else 
	{
		//std::cout << "\n" << "Word is not in dictionary : "  << wordToSpellCheck << std::endl;
		WriteToSpellingSuggestionFile( "\nWord is not in dictionary : " + wordToSpellCheck );			//- Writing the word that is not in the dictionary to "Spelling Suggestions.txt" file
		SuggestOtherWords( wordToSpellCheck );															//- Checking for possible word suggestions and exporting to "Spelling Suggestions.txt" file
		return false;																					//- Word is not in the dictionary 
	}
}																										//- End of checkIfWordIsInHashTable Function

/*****************************************************************
* Description:		This function reads the provided text file that 
*					is to be spell checked agaisnt our dictionary.
*
* Returns:			NIL
*
* Parameters:		HashTable myHashTable; HashTable
*		
*
* Preconditions:	Hashtable is created.
*
* Postconditions:	File has been checked.
*****************************************************************/
void HashTable::SpellingWordCheck( HashTable myHashTable )
{
	int numOfWordsNotInDictionary = 0;
	int totalWord = 0;
	std::vector<std::string> textFileLine;																//- Vector String to store and split the Lines collected from the provided text file which is stored in the str string.
	std::string spellLine;																				//- Line from the buffer c-String.

	std::ifstream fileToSpellCheck ( "Eisenhower spell.txt" );	
	
	if ( fileToSpellCheck.is_open() )
	{
		fileToSpellCheck.seekg( 0, fileToSpellCheck.end );												//- Find the end of file
		int fileLength = fileToSpellCheck.tellg();														//- Get the number of char's in the file
		fileToSpellCheck.seekg( 0, fileToSpellCheck.beg );												//- Return to start of file
		
		char * buffer = new char [fileLength+1];														//- Creating C-string the length of the file
		fileToSpellCheck.read( buffer, fileLength );													//- Read and save the char's from the file to the buffer C-string
		buffer[fileLength+1] = '\0';																	//- Adding the null char to the end of the string.
		
		if ( fileToSpellCheck )
		{
			std::cout << "all characters read successfully.";											//- Alert the user to successfull reading to C-string.
		}
		else
		{
			 std::cout << "error: only " << fileToSpellCheck.gcount() << " could be read from file";	//- Error report for user if unable to retrieve char's from stream
		} 
		fileToSpellCheck.close();																		//- Close the file 	
		
		for ( int i = 0; i < fileLength; i++ )
		{
			if ( buffer[i] != '\n' )																	//- Check to see if the current char is the new line char
			{
				spellLine += buffer[i];																	//- Adding the char to the string
				//std::cout << line << std::endl;														//- Used for testing purposes
			}
			else																						//- If char is == new line char then it will add the current string to the vector 
			{
				textFileLine.push_back( spellLine );
				//std::cout << line << std::endl;														//- Used for testing purposes
				spellLine = "";
			}
		}
		
		std::vector<std::string>::iterator lineIterator = textFileLine.begin();							//- Setting the lineIterator to the start.

		while ( lineIterator != textFileLine.end() )													//- Iterating through the vector until the end is reached
		{
			if ( lineIterator -> empty() )																//- Checking to see if the string is empty
			{
				lineIterator++;
				continue;
				//- Left intentionally empty
			}
			else if  ( lineIterator -> at( lineIterator -> length()-1 ) == '-' 
					&& lineIterator -> at( lineIterator -> length()-2 ) != '-' )						//- Checking if last char is a hypen '-' if it is then we get the next line and join the lines. 
			{
				//std::cout << "Interesting"<< *lineIterator << "\n" << std::endl;						//- Used for testing purposes
				std::string checkLine1 = *lineIterator;													//- Stores the current text line we are on
				std::string checkLine2;																	//- Stores the next text line. So that we can merge them together.
				lineIterator ++;																		//- Moving Iterator to the next line
				checkLine2 = *lineIterator;																//- Stores the current line so we can merge them together.
				*lineIterator = MergeHyphen( checkLine1, checkLine2 );									//- Merging the two lines together
				//std::cout<< *lineIterator << std::endl;												//- Used for testing purposes
			}
		
			std::string delimiter = " ";
			std::string token;
			size_t pos = 0;

			while ( ( pos = lineIterator -> find( delimiter ) ) != std::string::npos )					//- Searching for the delimter, if delimiter is in string then enter
			{
				bool wordContainsDigit = false;															//- Bool for checking if their is a number in the string
				token = lineIterator -> substr( 0, pos );												//- Stores the substring created with the delimiter
				
				char* cstr_token = new char [token.length()+1];											//- Creating pointer to a c style string array with a null char termination e.g '\0' of the specified size of the Token string 
				std::strcpy( cstr_token, token.c_str() );												//- Copying and converting string into the cstr_line as a c style string.  
				
				for ( int i = 0; cstr_token[i] != '\0'; i++ )											//- Looping through and converting any Upper Case letters to Lower Case letters.  
				{
					wordContainsDigit = ConvertUpperCaseToLowerCaseAndCheckIsDigit( cstr_token );		//- Converts to lower case and checks for digits
				}

				if ( isascii( cstr_token[0] ) )
				{																						//- Check to not insert any blank spaces into the BST
					if ( !isspace( cstr_token[0] ) && strlen( cstr_token ) >= 1 &&
						!wordContainsDigit && !CheckForBadInput( token ) )								//- If their is no number in the word then add it to the array. Else skip it
					{
						//std::cout << ":" << cstr_token << ":\n" << std::endl;							//- Used for validation testing
						char endStopGrammarCase[] = {".,?:;!"};
						int i = 0;
						while ( endStopGrammarCase[i] != NULL )
						{
							if ( token.at(token.length()-1) == endStopGrammarCase[i] )					//- Handling if word ends with fullstop. c++11 code used
							{
								token = token.substr( 0,token.length()-1 );								//- Deleting the last char in the string
								cstr_token = new char [token.length()+1];								//- Creating pointer to a c style string array with a null char termination e.g '\0' of the specified size of the Token string 
								std::strcpy( cstr_token, token.c_str() );								//- Copying and converting string into the cstr_line as a c style string.  
							}
							i++;
						}

						wordContainsDigit = ConvertUpperCaseToLowerCaseAndCheckIsDigit( cstr_token );	//- Converts to lower case and checks for digits
						bool wordInDictionary = true;
						wordInDictionary = myHashTable.checkIfWordIsInHashTable( token );				//- Inserting words into the Dictionary BST	
						
						if ( !wordInDictionary )														//- Checks to see if word is in the dictionary
						{
							//std::cout << "Word is not in dictionary :  " 
							//			<< token << "\n" << std::endl;									//- Used for validation testing purposes.
							numOfWordsNotInDictionary++;												//- Counting number of words that faile the spell checked
						} 
						totalWord++;																	//- Counting number of words spell checked
					}
				}
				if ( lineIterator -> begin() <  lineIterator -> end() )
				{
						lineIterator -> erase( 0, pos + delimiter.length() );							//- Removing the token from the string line
				}
			}

			char * cstr_line = new char [lineIterator -> length()+1];									//- Creating pointer to a c style string array with a null char termination e.g '\0' of the specified size of the line string 
			
			std::strcpy( cstr_line, lineIterator -> c_str() );											//- Copying and converting string into the cstr_line as a c style string.  
			
			bool wordContainsDigit = false;																//- Bool for checking if their is a number in the string
			if ( isascii( cstr_line[0] ) )
			{
				if( !isspace( cstr_line[0] ) && strlen ( cstr_line ) >= 1 )								//- Check to not insert any blank spaces into the BST 
				{
					//std::cout << ":" << cstr_line << ":\n" << std::endl;								//- Used for validation testing
					wordContainsDigit = ConvertUpperCaseToLowerCaseAndCheckIsDigit( cstr_line );		//- Converts to lower case and checks for digits
				
					if ( !wordContainsDigit && !CheckForBadInput( *lineIterator ) )						//- If their is no number in the word then add it to the array. Else skip it
					{
						char endStopGrammarCase[] = {".,?:;!"};
						int i = 0;
						while ( endStopGrammarCase[i] != NULL )
						{
							if ( lineIterator -> at( lineIterator -> length()-1 ) == endStopGrammarCase[i] )//- Handling if word ends with fullstop. c++11 code used
							{
								*lineIterator =  lineIterator -> substr( 0, lineIterator -> length()-1 );	//- Deleting the last char in the string
								cstr_line = new char [ lineIterator -> length()+1];							//- Creating pointer to a c style string array with a null char termination e.g '\0' of the specified size of the Token string 
								std::strcpy( cstr_line, lineIterator -> c_str() );							//- Copying and converting string into the cstr_line as a c style string.  
							}
							i++;
						}
						wordContainsDigit = ConvertUpperCaseToLowerCaseAndCheckIsDigit( cstr_line );		//- Converts to lower case and checks for digits
						bool wordInDictionary = true;
						wordInDictionary = myHashTable.checkIfWordIsInHashTable( spellLine );				//- Inserting words into the Dictionary BST	
						if ( !wordInDictionary )
						{
							//std::cout << "Word is not in dictionary :  "	<< spellLine 
									//	<< "\n"								<< std::endl;					//- Used for validation testing purposes.
							numOfWordsNotInDictionary++;													//- counting number of words that faile the spell checked
						} 
						totalWord++;																		//- counting number of words spell checked
					}
				}																							//- End check for not inserting blank spaces into the BST
			}
			lineIterator++;																					//- Move Iterator
		}
	}
	else
	{
		std::cout << "Unable to open file";																	//- If the system was unable to open the file then this error will be printed to the console
	}
	
	std::cout << "\n" <<	"Total Number of Words  in Dictionary: "<< 
							CountNumberOfWordsInDictionary()		<< std::endl;
	std::cout << "\n" <<	"Total Number of Words  SpellChecked: " << 
							totalWord								<< std::endl;
	std::cout << "\n" <<	"Number of Words Failed SpellCheck  : " << 
							numOfWordsNotInDictionary				<< std::endl;
	std::cout << "\n" <<	"Number of Words Passed SpellCheck  : " << 
							totalWord-numOfWordsNotInDictionary		<< std::endl;
}

/*******************************************************************************************	
	* Description:		This function merges two lines together when the last char is a hypen
	*					e.g ('-') and removes the hyphen between the two words
	*
	* Returns:			string
	*
	* Parameters:		std::string lineToCheck, std::string lineToMergeWith 
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Merged the two words together and hypen has been removed.
	*******************************************************************************************/
	std::string HashTable::MergeHyphen( std::string lineToCheck, std::string lineToMergeWith )
	{
		std::string tempNewLine = lineToCheck.substr( 0, lineToCheck.length()-1 );						//- Removing the last char from the string e.g '-'		
		std::string  tempLine = tempNewLine;															//- Temp string to store my new string i am going to merge
		tempLine += lineToMergeWith;																	//- Adding the strings together
		lineToCheck = tempLine;																			//- Reseting line to the merged string	
		
		return lineToCheck;
	}

	/*******************************************************************************************	
	* Description:		This function Converts all char's to lowercase.
	*
	* Returns:			NIL
	*
	* Parameters:		NIL
	*
	* Preconditions:	NIL
	*
	* Postconditions:	All char's are converted to lower case.
	*******************************************************************************************/
	bool HashTable::ConvertUpperCaseToLowerCaseAndCheckIsDigit( char* &cstr_line )
	{
		for ( int i = 0; cstr_line[i] != '\0'; i++ )													//- Looping through and converting any Upper Case letters to Lower Case letters.  
		{
			if ( isascii( cstr_line[i] ) )																//- Checking that the input is within the range of ascii values
			{
				cstr_line[i] = tolower( cstr_line[i] );													//- Converting to Lower Case. 	
				if ( isdigit( cstr_line[i] ) )															//- Checking if their is a digit in the word
				{
					return true;
				}	
			}
		}
		return false;
	}

	/*******************************************************************************************	
	* Description:		This function parses the input Char's for bad input.
	*
	* Returns:			True if Char is a non allowed input or False if char is a allowed input 
	*
	* Parameters:		string checkWord
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Successfully parsed the char.
	*******************************************************************************************/
	bool HashTable::CheckForBadInput( std::string &checkWord )											//- If returns true then dont add word as it contains a bad input, otherwise if returns false then add to file
	{
		char * cstr_checkWord = new char [checkWord.length()+1];										//- Creating pointer to a c style string array with a null char termination e.g '\0' of the specified size of the Token string 
		std::strcpy( cstr_checkWord, checkWord.c_str() );												//- Copying and converting string into the cstr_line as a c style string.  
		int i = 0;
		char specialInput[] = {"-'"};
		char endStopCase[] = {".,?':;!"};
		char whiteSpace[] = {" "};
		while ( cstr_checkWord[i] != NULL )
		{
			if( CheckForGrammarAtEOL( cstr_checkWord[i], cstr_checkWord[i+1] ) )						//- warning c6385 read overrun for ms vs but is ok atm
			{
				return false;
			}		
			else if ( cstr_checkWord[i] == specialInput[0] || cstr_checkWord[i] == specialInput[1]  )
			{
				if ( CheckSecondLastCharForBadInput( cstr_checkWord[i+1] ) )							//- Checking to see the next char, if it is again a ' or - then it is a bad input.
				{
					return true;																		//- Bad input
				}
			}
			else if ( CheckForBadChar( cstr_checkWord[i] )  )											//- Checking if their is a bad input in the word
			{	
				return true;																			//- Bad input
			}
			i++;
		}
		return false;
	}
	/*******************************************************************************************	
	* Description:		This function checks for bad grammar usage and discludes any words that 
	*					have bad grammar.
	*
	* Returns:			True if allowed grammar else False if bad grammar has occured
	*
	* Parameters:		char inputChar1, char inputChar2 
	*
	* Preconditions:	NIL
	*
	* Postconditions:	True or False.
	*******************************************************************************************/
	bool HashTable::CheckForGrammarAtEOL( char inputChar1, char inputChar2 )			
	{
		char endStopCase[] = {".,?':;!"};																//- Allowed Grammar char's
		char whiteSpace[] = {" "};																		//- Allowed Char after Grammar Char's
		int i = 0;
		while ( ( inputChar2 == whiteSpace[0] || inputChar2 == NULL ) && endStopCase[i] != NULL )
		{
			if ( inputChar1 == endStopCase[i] )
			{
				return true;																			//- Good char e.g - hello. howdy, ok! - these words are ok and should be allowed to pass
			}
			i++;
		}
		return false;																					//- Bad char
	}

	/*******************************************************************************************	
	* Description:		This function parses the input Char's for bad input.
	*
	* Returns:			True if Char is a non allowed input or False if char is a allowed input 
	*
	* Parameters:		string checkWord
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Successfully parsed the char.
	*******************************************************************************************/
	bool HashTable::CheckSecondLastCharForBadInput( char inputChar )									//- If returns true then it contains a bad input, otherwise if returns false then that is a good input
	{
		char badInput[] = { '\'','.', ';', '-', '!', '~', '@', '#', '$', '%', '^', 
			'&', '*', '(', ')', '_', '=', '+', '|', '\\', ']', '}', '[', '{', '"', 
			';', '.',':', ',', '<', '>', '/', '?', '\0' };												//- Bad Input Char's
		int i = 0;
		while (badInput[i] != NULL)
		{
			if ( inputChar == badInput[i] )
			{
				return true;																			//- Char is not allowed
			}
			i++;
		}
		return false;																					//- Char is allowed
	}

	/*******************************************************************************************	
	* Description:		This function parses the input Char's for bad input.
	*
	* Returns:			True if Char is a non allowed input or False if char is a allowed input 
	*
	* Parameters:		string checkWord
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Successfully parsed the char.
	*******************************************************************************************/
	bool HashTable::CheckForBadChar( char inputChar )													//- If returns true then it contains a bad input, otherwise if returns false then that is a good input
	{
		char badInput[] = { '!', '~', '@', '#', '$', '%', '^', '&', '*', '(', ')', 
							'_', '=', '+', '|', '\\', ']', '}', '[', '{', '"', ';', 
							'.',':', ',', '<', '>', '/', '?', '\0' };									//- Bad Input Char's
		int i = 0;
		while ( badInput[i] != NULL )
		{
			if ( inputChar == badInput[i] )
			{
				return true;
			}
			i++;
		}
		return false;
	}
/////////////////////////////////////////////////////////////////////////////////////////////
// END OF FILE
/////////////////////////////////////////////////////////////////////////////////////////////