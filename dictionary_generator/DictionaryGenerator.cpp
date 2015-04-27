//////////////////////////////////////////////////////////////////////////////////////////////
// Filename:		DictionaryGenerator.cpp
// Author:			Charles Nelson - s2884951
// Date Modified:	03/05/2014 Created
//					07/06/2014 Updated 
// Description:		This file contains the implementation of the Dictionary Generator Class.
/////////////////////////////////////////////////////////////////////////////////////////////
#include "DictionaryGenerator_H.h"

//================================= PUBLIC FUNCTIONS ===========================================

	/*******************************************************************************************	
	* Description:		This function is the Default Constructor for the DictionaryGenerator.	
	*																							
	* Returns:			Is Constructor															
	*																							
	* Parameters:		NIL
	*
	* Preconditions:	NIL
	*
	* Postconditions:	A default Dictionary Generator object has been constructed.
	*******************************************************************************************/	
	DictionaryGenerator::DictionaryGenerator()															//- Default Constructor
	{
		wordCount = 0;																					//- Initialising the values
		ptrRoot = NULL;																					//- Initialising the values
	}

	/*******************************************************************************************	
	* Description:		This function is the Default Destructor for the DictionaryGenerator.
	*
	* Returns:			Is Destructor
	*
	* Parameters:		NIL
	*
	* Preconditions:	NIL
	*
	* Postconditions:	DictionaryGenerator memory has been freed.
	*******************************************************************************************/
	DictionaryGenerator::~DictionaryGenerator()															//- Default Destructor 
	{
		DeleteInOrder(ptrRoot);																			//- Deletes the tree in order and clears the memory	
	}

	/*******************************************************************************************	
	* Description:		This function returns the number of words in the BST and Dictionary.
	*
	* Returns:			Word Count.
	*
	* Parameters:		NIL
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Has successfully returned the number of words in the BST and Dictionary.
	*******************************************************************************************/
	int DictionaryGenerator::numberOfWordsInBST()														//- Returns the number of words contained in the dictionary. 
	{
		return wordCount;
	}

	/*******************************************************************************************	
	* Description:		This function calculates the height of the BST.
	*
	* Returns:			Height of the BST.
	*
	* Parameters:		BstNode* ptrRoot 
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Returned the height of the BST
	*******************************************************************************************/
	int DictionaryGenerator::heightOfBST( BstNode* ptrRoot )											//- Returns the height of the Binary Search Tree.
	{
		if (ptrRoot == NULL)
		{
			return 0; 
		}
		else 
		{
		/*	int leftHeight = heightOfBST( ptrRoot -> left );											//- First way for calculating height of BST
			int rightHeight = heightOfBST( ptrRoot -> right );											//- New way has less lines of code
			if ( leftHeight > rightHeight )
			{
				return 1 + leftHeight;
			}
			else 
			{
				return 1 + rightHeight;
			}
		*/
		return std::max( heightOfBST( ptrRoot -> left ), heightOfBST( ptrRoot -> right ) ) + 1;			//- Uses the max function from the std to find the highest value using recursion
		}
	}
	
	/*******************************************************************************************	
	* Description:		This function will delete a specified word if it is contained within the BST.
	*
	* Returns:			BstNode*
	*
	* Parameters:		NIL
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Word contained within the BST will have been successfully delete.
	*******************************************************************************************/
	DictionaryGenerator::BstNode* DictionaryGenerator::DeleteWord( BstNode* ptrRoot, char* word )		//- Deletes the specified word from the Binary Search Tree.
	{
		if ( ptrRoot == NULL ) 
		{
			return ptrRoot; 
		}
		else if ( word < ptrRoot -> word ) 
		{
			ptrRoot -> left = DeleteWord( ptrRoot -> left, word );
		}
		else if ( word > ptrRoot -> word ) 
		{
			ptrRoot -> right = DeleteWord( ptrRoot -> right, word );
		}	
		else																							//- Found the node to be deleted. 
		{
			if ( ptrRoot -> left == NULL && ptrRoot -> right == NULL )									//- Case 1: Node to be deleted has no children.
			{ 
				delete ptrRoot;
				ptrRoot = NULL;
			}
			else if ( ptrRoot -> left == NULL )															//- Case 2: Node to be deleted has one child node.
			{
				BstNode* temp = ptrRoot;
				ptrRoot = ptrRoot -> right;
				delete temp;
			}
			else if ( ptrRoot -> right == NULL )														//- Case 2: Node to be deleted has one child node.
			{
				BstNode* temp = ptrRoot;
				ptrRoot = ptrRoot -> left;
				delete temp;
			}
			else																						//- Case 3: Node to be deleted has 2 children
			{ 
				BstNode* temp = FindNodeContainingFirstWord( ptrRoot -> right );
				ptrRoot -> word = temp -> word;
				ptrRoot -> right = DeleteWord( ptrRoot -> right, temp -> word );
			}
		}
		wordCount--;																					//- Decreases wordCount by 1;
		return ptrRoot;
	}
	
	/*******************************************************************************************	
	* Description:		This function will insert a new word into the BST as well as balance it after.
	*					If the word to be inserted is already contained within the lest then it will not insert the word.
	*
	* Returns:			Bstnode*
	*
	* Parameters:		 BstNode* ptrRoot, char* word
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Inserted a word succsessfully and balances it or has returned the prtRoot if word already exists.
	*******************************************************************************************/
	DictionaryGenerator::BstNode*  DictionaryGenerator::InsertWord( BstNode* ptrRoot, char* word )		//- Inserts a word into the Binary Search Tree.
	{
		if ( ptrRoot == NULL )																			//- Checks to see if BST is empty
		{ 
			ptrRoot = CreateNewBstNode( word );
		}
		else if ( word[0] < ptrRoot -> word[0] )														//- Checks to see if the word to be inserted is <=, if so then it is inserted into the left hand side of the BST subtree. 
		{
			ptrRoot -> left = InsertWord( ptrRoot -> left, word );										//- Inserting the word into the tree.
			ptrRoot = BalanceTree(ptrRoot);																//- Balancing the word in the tree.
		}
		else if ( word[0] == ptrRoot -> word[0] )														//- This here is for when char's are equal. 
		{
			int i = 0;
			while ( word[i] == ptrRoot -> word[i])														//- Loop until there is a difference between the two. 
			{
				if ( word[i] == '\0' && ptrRoot -> word[i] == '\0' )									//- If this happens then the word must be the same. So we do not add it to the BST
				{
					/*std::cout << "\n" << 
					"Gracefully Handling Insertion of Existing Word in BST. Word = " <<
					ptrRoot -> word<< "\n" << std::endl; */												//- Used for validation testing
					return ptrRoot;																		//- Does not insert as current Node is the same.
				}
				i++;																					//- Iterate the count
			}
			if ( word[i] < ptrRoot -> word[i] )
			{
				ptrRoot -> left = InsertWord( ptrRoot -> left, word );									//- Inserting the word into the tree.
				ptrRoot = BalanceTree(ptrRoot);															//- Balancing the word in the tree.
			}
			else 
			{
				ptrRoot -> right = InsertWord( ptrRoot -> right, word );								//- Inserting the word into the tree.
				ptrRoot = BalanceTree(ptrRoot);															//- Balancing the word in the tree.
			}
		}
		else																							//- Word must be larger, so insert into the right hand side of the BST subtree
		{
			ptrRoot -> right = InsertWord( ptrRoot -> right, word );									//- Inserting the word into the tree.
			ptrRoot = BalanceTree(ptrRoot);																//- Balancing the word in the tree.
		}
		return ptrRoot;																					//- Returns the prtRoot of the node
	}
	
	/*******************************************************************************************	
	* Description:		This function creates a new BST Node for the tree.
	*
	* Returns:			BstNode*
	*
	* Parameters:		char* word
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Successfully created a new BST Node
	*******************************************************************************************/
	DictionaryGenerator::BstNode* DictionaryGenerator::CreateNewBstNode( char* word)					//- Creates a new node with a word
	{
		BstNode* newBstNode = new BstNode();															//- Creates a new BstNode
		newBstNode -> word = word;
		newBstNode -> left = newBstNode -> right = NULL;
		wordCount++;																					//- Adds 1 to the word count
		return newBstNode;	
	}
	
	/*******************************************************************************************	
	* Description:		This function searches the Binary Search Tree for the specified word in the BST.
	*
	* Returns:			True if the word is found in the tree or false if the word is not found
	*
	* Parameters:		BstNode* ptrRoot, char* word
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Returns Bool, informing if word is contained within the tree.
	*******************************************************************************************/
	bool DictionaryGenerator::SearchBST( BstNode* ptrRoot, char* word )									//- Searches the Binary Search Tree for the specified word in the BST.
	{
		if ( ptrRoot == NULL ) 
		{
			return false;																				//- Returns false as the function has reached the end of the tree and word not found.
		}
		else if ( ptrRoot -> word[0] == word[0] ) 
		{
			return true;																				//- Word found
		}
		else if ( word[0] <= ptrRoot -> word[0] ) 
		{
			return SearchBST( ptrRoot -> left, word );													//- Search for word in the left node.
		}
		else 
		{
			return SearchBST( ptrRoot -> right, word );													//- Search for word in the right node	
		}
	}
	
	/*******************************************************************************************	
	* Description:		This function searches and returns the first word (Alphabetical order) in the BST.
	*
	* Returns:			char* word
	*
	* Parameters:		BstNode* ptrRoot
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Returned the first  word (Alphabetical order) in the BST 
	*******************************************************************************************/
	char* DictionaryGenerator::FindFirstWord( BstNode* ptrRoot )										//- Searches the Binary Search Tree for the first word in the Dictionary in Alphabetical Order. E.G - This is equivilant to finding the smallest number in the BST e.g findMin() 
	{
		while( ptrRoot -> left != NULL )																//- Iterating until the end, always moving to the left node
		{
			ptrRoot = ptrRoot -> left;
		}
		return ptrRoot -> word;																			//- Return the first word stored in the tree.
	}
	
	/*******************************************************************************************	
	* Description:		This function searches and returns the last word (Alphabetical order)  in the BST.
	*
	* Returns:			NIL
	*
	* Parameters:		BstNode* ptrRoot
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Returned the last word (Alphabetical order) in the BST
	*******************************************************************************************/
	char* DictionaryGenerator::FindLastWord( BstNode* ptrRoot )											//- Searches the Binary Search Tree for the last word in the Dictionary in Alphabetical Order. E.G - This is equivilant to finding the largest number in the BST e.g findMin() 
	{
		while( ptrRoot -> right != NULL )																//- Iterating until the end, always moving to the right node
		{
			ptrRoot = ptrRoot -> right;																					
		}
		return ptrRoot -> word;																			//- Returns the last word in the BST
	}

	/*******************************************************************************************	
	* Description:		This function finds the node containing the first word in the Dictionary's BST.
	*
	* Returns:			NIL
	*
	* Parameters:		BstNode* ptrRoot
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Returns the node containing the first word
	*******************************************************************************************/
	DictionaryGenerator::BstNode* DictionaryGenerator::FindNodeContainingFirstWord( BstNode* ptrRoot )										
	{
		while ( ptrRoot -> left != NULL )															
		{
			ptrRoot = ptrRoot -> left;
		}
		return ptrRoot;																					//- Can use this for deleting the node containing the first word in alphabet order
	}
	
	/*******************************************************************************************	
	* Description:		Used for Testing - Prints to Console the Words of the BST in alphabetical order.
	*
	* Returns:			NIL
	*
	* Parameters:		BstNode* ptrRoot
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Words printed to console in alphabetical order.
	*******************************************************************************************/
	void DictionaryGenerator::CheckInOrder( BstNode* ptrRoot )											//- Prints out the Words of the BST in alphabetical order, So user can verify if BST is in order. Note: If output is not in alphabetical order then the BST is not ordered correctly. 
	{
		if ( ptrRoot == NULL ) return;																	//- Returns when ptrRoot is equal to NULL
		
		CheckInOrder( ptrRoot ->  left );																//- Check the Left Hand side of the BST Subtree
		//std::cout << ptrRoot -> word	<< std::endl;													//- Printing out the word												
		CheckInOrder( ptrRoot -> right );																//- Check the Right Hand side of the BST Subtree
		//std::cout << ptrRoot -> word	<< std::endl;													//- Printing out the word		
	}

	/*******************************************************************************************	
	* Description:		This function exports the Dictionary BST in alphabetical order to the "dict.txt" file.
	*
	* Returns:			NIL
	*
	* Parameters:		BstNode* ptrRoot
	*
	* Preconditions:	NIL
	*
	* Postconditions:	"dict.txt" file is successfully created.
	*******************************************************************************************/
	void DictionaryGenerator::ExportInOrder( BstNode* ptrRoot )											//- Exports the words contained within the BST in alphabetical order to a .txt file.
	{
		if ( ptrRoot == NULL ) return;																	//- Returns when ptrRoot is equal to NULL
 
		ExportInOrder( ptrRoot ->  left );																//- Check the Left Hand side of the BST Subtree
		std::ofstream myOutputFile ( "dict.txt",std::ios::app );										//- Opens File and appends any string to the end
		if ( myOutputFile.is_open() )
		{
			myOutputFile << ptrRoot -> word << "\n";
			myOutputFile.close();
		}
		else 
		{
			std::cout << "Unable to open file";
		}
		ExportInOrder( ptrRoot -> right );																//- Check the Right Hand side of the BST Subtree
	}

	/*******************************************************************************************	
	* Description:		This function Parses the input and Generates the Dictionary's BST which is also a Balanced AVL Tree.
	*
	* Returns:			NIL
	*
	* Parameters:		DictionaryGenerator &Dictionary, BstNode* &ptrRoot
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Dictionary's BST is created and balanced.
	*******************************************************************************************/
	void DictionaryGenerator::GenerateDictionaryBST( DictionaryGenerator &Dictionary, BstNode* &ptrRoot )
	{
		std::string line;																				//- Stores string's for parsing and input reading.
		std::string newLine;																			//- Stores string's for parsing and input reading.
		std::string str;																				//- Stores the complete input from the textfile.
		std::vector<std::string> textFileLine;															//- Vector String to store and split the Lines collected from the provided text file which is stored in the str string.

		FILE *file;
		char filename[] = "Ass2Dictionary.txt";															//- Stores the name of the file to open
		if (fopen_s(&file, filename, "r") == 0)															//- Opens the specified text file
		{
			char buf[255];																				//- Buffer for the reading of char's from the text file
			while ( !feof(file) )																		//- Reads(e.g loops) until the End Of File is reached
			{
				int numBytes = fread( buf,sizeof(char), 254, file );									//- Reading the input text file up until 254 char's.
				buf[numBytes] = '\0';																	//- Adding the null char to the end of the string.
				str += buf;																				//- Appending the current buffer(char array) to the string
			}
		}
		else 
		{
			fprintf( stderr, "Cannot open file: %s\n", filename );										//- Error output
		}
		fclose( file );																					//- Closing the file. 
	
		for ( int i = 0; i < str.size(); i++ )
		{
			if ( str[i] != '\n' )																		//- Check to see if the current char is the new line char
			{
				line += str[i];																			//- Adding the char to the string
				//std::cout << line << std::endl;														//- Used for testing purposes
			}
			else																						//- If char is == new line char then it will add the current string to the vector 
			{
				textFileLine.push_back(line);
				//std::cout << line << std::endl;														//- Used for testing purposes
				line = "";
			}
		}
	
		std::vector<std::string>::iterator lineIterator = textFileLine.begin(); 

		while ( lineIterator != textFileLine.end() )													//- Iterating through the vector until the end is reached
		{
			if ( lineIterator -> empty() )																//- Checking to see if the string is empty
			{
				//- Left intentionally empty
			}
			else if ( lineIterator -> at( lineIterator -> length()-1 ) == '-' 
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
				token = lineIterator -> substr(0, pos);													//- Stores the substring created with the delimiter
				
				char* cstr_token = new char [token.length()+1];											//- Creating pointer to a c style string array with a null char termination e.g '\0' of the specified size of the Token string 
				std::strcpy( cstr_token, token.c_str() );												//- Copying and converting string into the cstr_line as a c style string.  
				
				for ( int i = 0; cstr_token[i] != '\0'; i++ )											//- Looping through and converting any Upper Case letters to Lower Case letters.  
				{
					wordContainsDigit = ConvertUpperCaseToLowerCaseAndCheckIsDigit(cstr_token);			//- Converts to lower case and checks for digits
				}
				
				if ( !isspace( cstr_token[0] ) && strlen( cstr_token ) >= 1  &&							
					 !wordContainsDigit && !CheckForBadInput( token ) )									//- Check to not insert any blank spaces into the BST & If their is no number in the word then add it to the array. Else skip it
				{
					//std::cout << ":" << cstr_token << ":\n" << std::endl;								//- Used for validation testing
					char endStopGrammarCase[] = {".,?:;!"};
					int i = 0;
					while ( endStopGrammarCase[i] != NULL )
					{
						if ( token.at(token.length()-1) == endStopGrammarCase[i] )						//- Handling if word ends with fullstop. c++11 code used
						{
							token = token.substr(0,token.length()-1);									//- Deleting the last char in the string
							cstr_token = new char [token.length()+1];									//- Creating pointer to a c style string array with a null char termination e.g '\0' of the specified size of the Token string 
							std::strcpy( cstr_token, token.c_str() );									//- Copying and converting string into the cstr_line as a c style string.  
						}
						i++;																			
					}
					wordContainsDigit = ConvertUpperCaseToLowerCaseAndCheckIsDigit(cstr_token);			//- Converts to lower case and checks for digits
					ptrRoot	= Dictionary.InsertWord( ptrRoot, cstr_token );								//- Inserting words into the Dictionary BST
				}
				if ( lineIterator -> begin() <  lineIterator -> end() )
				{
						lineIterator -> erase( 0, pos + delimiter.length() );							//- Removing the token from the string line
				}
			}

			char* cstr_line = new char [lineIterator -> length()+1];									//- Creating pointer to a c style string array with a null char termination e.g '\0' of the specified size of the line string 
			std::strcpy( cstr_line, lineIterator -> c_str() );											//- Copying and converting string into the cstr_line as a c style string.  
			bool wordContainsDigit = false;																//- Bool for checking if their is a number in the string
			
			if( !isspace( cstr_line[0] ) && strlen ( cstr_line ) >= 1 )									//- check to not insert any blank spaces into the BST 
			{
				//std::cout << ":" << cstr_line << ":\n" << std::endl;									//- Used for validation testing
				wordContainsDigit = ConvertUpperCaseToLowerCaseAndCheckIsDigit( cstr_line );			//- Converts to lower case and checks for digits
				
				if ( !wordContainsDigit && !CheckForBadInput( *lineIterator ) )							//- If their is no number in the word then add it to the array. Else skip it
				{
					int i = 0;
					char endStopGrammarCase[] = {".,?:;!"};
					while ( endStopGrammarCase[i] != NULL )
					{
						if ( lineIterator -> at( lineIterator -> length()-1) == endStopGrammarCase[i] )	//- Handling if word ends with fullstop. c++11 code used
						{
							*lineIterator =  lineIterator -> substr( 0, lineIterator -> length()-1 );	//- Deleting the last char in the string
							cstr_line = new char [ lineIterator -> length()+1];							//- Creating pointer to a c style string array with a null char termination e.g '\0' of the specified size of the Token string 
							std::strcpy( cstr_line, lineIterator -> c_str() );							//- Copying and converting string into the cstr_line as a c style string.  
						}
						i++;
					}
					wordContainsDigit = ConvertUpperCaseToLowerCaseAndCheckIsDigit( cstr_line );		//- Converts to lower case and checks for digits
					ptrRoot	= Dictionary.InsertWord( ptrRoot, cstr_line );								//- Inserting words into the Dictionary BST	
				}
			}																							//- End check for not inserting blank spaces into the BST
			lineIterator++;		
		}
		CheckIfDictionaryFileExists();																	//- Checking if file exists, if it does we delete it 
	}

//================================= PRIVATE  FUNCTIONS =========================================

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
	std::string DictionaryGenerator::MergeHyphen( std::string lineToCheck, std::string lineToMergeWith )
	{
		std::string tempNewLine = lineToCheck.substr(0,lineToCheck.length()-1);							//- Removing the last char from the string e.g '-'		
		std::string  tempLine = tempNewLine;															//- Temp string to store my new string i am going to merge
		tempLine += lineToMergeWith;																	//- Adding the strings together
		lineToCheck = tempLine;																			//- Reseting line to the merged string	
		
		return lineToCheck;
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
	bool DictionaryGenerator::CheckForBadChar( char inputChar )											//- If returns true then it contains a bad input, otherwise if returns false then that is a good input
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
	bool DictionaryGenerator::CheckSecondLastCharForBadInput( char inputChar )							//- if returns true then it contains a bad input, otherwise if returns false then that is a good input
	{
		char badInput[] = { '\'','.', ';', '-', '!', '~', '@', '#', '$', '%', '^', 
			'&', '*', '(', ')', '_', '=', '+', '|', '\\', ']', '}', '[', '{', '"', 
			';', '.',':', ',', '<', '>', '/', '?', '\0' };												//- Bad Input Char's
		int i = 0;
		while ( badInput[i] != NULL )
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
	bool DictionaryGenerator::CheckForGrammarAtEOL( char inputChar1, char inputChar2 )			
	{
		int i = 0;
		char endStopCase[] = {".,?':;!"};																//- Allowed Grammar char's
		char whiteSpace[] = {" "};																		//- Allowed Char after Grammar Char's
		while ( ( inputChar2 == whiteSpace[0] || inputChar2 == NULL ) && endStopCase[i] != NULL )
		{
			if ( inputChar1 == endStopCase[i] )
			{
				return true;																			//- good char e.g - hello. howdy, ok! - these words are ok and should be allowed to pass
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
	bool DictionaryGenerator::CheckForBadInput( std::string &checkWord )								//- if returns true then dont add word as it contains a bad input, otherwise if returns false then add to file
	{
		int i = 0;
		char * cstr_checkWord = new char [checkWord.length()+1];										//- Creating pointer to a c style string array with a null char termination e.g '\0' of the specified size of the Token string 
		std::strcpy( cstr_checkWord, checkWord.c_str() );												//- Copying and converting string into the cstr_line as a c style string.  
		char specialInput[] = {"-'"};
		char endStopCase[] = {".,?':;!"};
		char whiteSpace[] = {" "};

		while ( cstr_checkWord[i] != NULL )
		{
			if ( CheckForGrammarAtEOL( cstr_checkWord[i], cstr_checkWord[i+1] ) )						
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
	* Description:		This function checks if the dictionary file has already been created.
	*					If it has then it deletes it so we can rewrite it.
	*
	* Returns:			NIL
	*
	* Parameters:		NIL
	*
	* Preconditions:	NIL
	*
	* Postconditions:	File has been successfully deleted or errors if unable to delete.
	*******************************************************************************************/
	void DictionaryGenerator::CheckIfDictionaryFileExists()
	{
		if ( remove( "dict.txt" ) != 0 )															//- Deletes the dict.txt file if it exists. This ensures that we do not keep on writing to the same output.  
		{
			perror( "Error deleting file" );														//- Errors if unsucessful in deleting the file. 
		}
		else
		{
			puts( "File successfully deleted" );													//- Displays this message if successful in deleting the file
		}
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
	bool DictionaryGenerator::ConvertUpperCaseToLowerCaseAndCheckIsDigit( char* &cstr_line )
	{
		for ( int i = 0; cstr_line[i] != '\0'; i++ )												//- Looping through and converting any Upper Case letters to Lower Case letters.  
		{
			cstr_line[i] = tolower( cstr_line[i] );													//- Converting to Lower Case. 	
			if ( isdigit( cstr_line[i] ) )															//- Checking if their is a digit in the word
			{
				return true;
			}	
		}
		return false;
	}

	/*******************************************************************************************	
	* Description:		This deletes all the nodes in order.
	*
	* Returns:			NIL
	*
	* Parameters:		BstNode* ptrRoot
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Cleared the tree by deleting every node contained within.
	*******************************************************************************************/
	void DictionaryGenerator::DeleteInOrder ( BstNode* ptrRoot )									//- Deletes the the BST Nodes in order
	{
		if ( ptrRoot == NULL ) 
		{
			return;																					//- Returns when ptrRoot is equal to NULL
		}
		DeleteInOrder( ptrRoot ->  left );															//- Check the Left Hand side of the BST Subtree								
		DeleteInOrder( ptrRoot -> right );															//- Check the Right Hand side of the BST Subtree
		wordCount--;																				//- Decreases wordCount by 1;
		delete ptrRoot;																				//- If both subtree's are empty then must be a leaf, It is ok to delete the node 
	}

	/*******************************************************************************************	
	* Description:		This function checks if the BST is AVL Balanced
	*
	* Returns:			Bool True if balanced or False if not
	*
	* Parameters:		BstNode* ptrRoot
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Returns if AVL Balanced
	*******************************************************************************************/
	bool DictionaryGenerator::CheckIfBalanced( BstNode* ptrRoot )
	{
		if ( ptrRoot == NULL )
		{
			return true;																			//- Returns when ptrRoot is equal to NULL
		}
		else 
		{
			return	CheckIfBalanced( ptrRoot -> left )	&& 
					CheckIfBalanced( ptrRoot -> right )	&&
					std::abs( BalanceFactor( ptrRoot -> left ) - 
					BalanceFactor( ptrRoot ->right ) ) <= 1;										//- Returns if the Binary Tree is balanced, this will fail as it is more strict then our correct balancing method
		}
	} 

	/*******************************************************************************************	
	* Description:		This function calculates the balanceFactor for the node
	*
	* Returns:			int BalanceFactor
	*
	* Parameters:		BstNode* ptrRoot
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Returned the correct Balance Function value.
	*******************************************************************************************/
	int DictionaryGenerator::BalanceFactor( BstNode* ptrRoot )
	{
		if ( ptrRoot == NULL ) return 0;
		int balanceFactor = heightOfBST( ptrRoot -> left ) - heightOfBST( ptrRoot -> right );		//- Calculates the balance factor. If balanceFactor is -1,0 or + 1 then no rotations are necessary
		return balanceFactor;																		//- Return the balanceFactor of the node
	}

	/*******************************************************************************************	
	* Description:		This function Balances the BST Tree after Insertion
	*
	* Returns:			BstNode*
	*
	* Parameters:		BstNode* ptrRoot
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Balanced tree after instertion.
	*******************************************************************************************/
	DictionaryGenerator::BstNode* DictionaryGenerator::BalanceTree( BstNode* ptrRoot  )				//- Balance the tree
	{
		int balanceFactor = BalanceFactor( ptrRoot );												//- Calculates the balance factor. If balanceFactor is -1,0 or + 1 then no rotations are necessary
		if ( balanceFactor > 1 )																	//- Left side of the column e.g LR and LL Case's as specified in AVL WIKIPEDIA Page
		{ 
			if ( BalanceFactor( ptrRoot -> left ) > 0)												//- Left Right Case
			{
				ptrRoot = Rotate_LL( ptrRoot );														//- Balance tree by reducing from the LR Case to the LL case to a balanced tree.
			}
			else 
			{
				ptrRoot = Rotate_LR( ptrRoot );														//- Reduce tree from LL Case to a Balanced tree
			}
		} 
		else if ( balanceFactor < -1 ) 																//- Right side of column	e.g RL and RR Case's as specified in AVL WIKIPEDIA Page
		{ 
			if ( BalanceFactor( ptrRoot -> left ) > 0)												//- Right Left Case
			{
				ptrRoot = Rotate_RL( ptrRoot );														//- Balance tree by reducing from the RL Case to the RR case to a balanced tree.
			}
			else 
			{
				ptrRoot = Rotate_RR( ptrRoot );														//- Reduce tree from RR Case to a Balanced tree
			}
		}
		return ptrRoot;
	}

	/*******************************************************************************************	
	* Description:		This function Converts rotates for the Right-Right Case.
	*
	* Returns:			BstNode*
	*
	* Parameters:		BstNode* parentNode 
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Tree is now balanced.
	*******************************************************************************************/
	DictionaryGenerator::BstNode* DictionaryGenerator::Rotate_RR( BstNode* parentNode )				//- Rotate - "Right-Right Case"
	{
		BstNode* tempChild;																			//- Temp ptr to store reference of the parents child tree. 
		tempChild = parentNode -> right;															//- Move pointer to the child node
		parentNode -> right = tempChild -> left;													//- Setting parentNode's right tree to tempChilds left tree.
		tempChild -> left = parentNode;																//- Setting tempChild's left tree to parent node. Rotation/Swapp

		return tempChild;																			//- Returns the rotated node
	}

	/*******************************************************************************************	
	* Description:		This function rotates for the Left-Left Case
	*
	* Returns:			BstNode*
	*
	* Parameters:		BstNode* parentNode 
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Tree is now balanced.
	*******************************************************************************************/
	DictionaryGenerator::BstNode* DictionaryGenerator::Rotate_LL( BstNode* parentNode )				//- Rotate - "Left-Left Case"
	{
		BstNode* tempChild;																			//- Temp ptr to store reference of the parents child tree. 
		tempChild = parentNode -> left;																//- Move pointer to the child node
		parentNode -> left = tempChild -> right;													//- Setting parentNode's left tree to tempChilds right tree.
		tempChild -> right = parentNode;															//- Setting tempChild's right tree to parent node. Rotation/Swapp

		return tempChild;																			//- Returns the rotated node
	}
 
	/*******************************************************************************************	
	* Description:		This function Rotates - Left-Right Case
	*
	* Returns:			BstNode*
	*
	* Parameters:		BstNode* parentNode 
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Tree is now balanced.
	*******************************************************************************************/
	DictionaryGenerator::BstNode* DictionaryGenerator::Rotate_LR( BstNode* parentNode )				//- Rotate - "Left-Right Case"
	{
		BstNode* tempChild;																			//- Temp ptr to store reference of the parents child tree. 
		tempChild = parentNode -> left;																//- Move pointer to the next node
		parentNode -> left = Rotate_RR ( tempChild );												//- Rotating the parent's left subtree with the RR Case

		return Rotate_LL ( parentNode );															//- Rotating and returning the ParentNode
	}
 
	/*******************************************************************************************	
	* Description:		This function Rotates for the Right-Left Case
	*
	* Returns:			BstNode*
	*
	* Parameters:		BstNode* parentNode 
	*
	* Preconditions:	NIL
	*
	* Postconditions:	Tree is now balanced.
	*******************************************************************************************/
	DictionaryGenerator::BstNode* DictionaryGenerator::Rotate_RL( BstNode* parentNode )				//- Rotate - "Right-Left Case"
	{
		BstNode* tempChild;																			//- Temp ptr to store reference of the parents child tree. 
		tempChild = parentNode -> right;															//- Move pointer to the child node	
		parentNode -> right = Rotate_LL ( tempChild );												//- Rotating the parents right Subtree with the LL Case

		return Rotate_RR ( parentNode );															//- Rotating and returning the ParentNode
	}
////////////////////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////////////////////