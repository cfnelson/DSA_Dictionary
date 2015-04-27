//////////////////////////////////////////////////////////////////////////////////////////
// Filename:		DictionaryGenerator_H.H
// Author:			Charles Nelson - s2884951
// Date Modified:	03/05/2014 Created
//					07/06/2014 Updated 
// Description:		This file contains the prototypes of the Dictionary Generator Class.
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef DictionaryGenerator_H
#define DictionaryGenerator_H

#include <list>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip> 
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

class DictionaryGenerator
{
public:
	struct BstNode																		//- Binary Search Tree Node 
	{
		char* word;																		//- Contains an array of chars that make up a word in the dictionary. Max Size of a word is 15 characters. NOTE NEED TO CHECK THE END NULL CHAR FOR STRINGS ETC. C/C++
		BstNode* left;																	//- Pointer to the left hand side, sub node in the Binary Search Tree.
		BstNode* right;																	//- Pointer to the left hand side, sub node in the Binary Search Tree.
	};
	
	BstNode* ptrRoot;																	//- Stores the address of the root node
	const char* inputWord;
	int wordCount;																		//- Stores the number of words in the BST

	DictionaryGenerator			();														//- Default Constructor
	~DictionaryGenerator		();														//- Default Destructor 

	int numberOfWordsInBST		();														//- Returns the number of words contained in the dictionary. 
	int heightOfBST				( BstNode* ptrRoot );									//- Returns the height of the Binary Search Tree.

	BstNode* InsertWord			( BstNode* ptrRoot, char* word );						//- Inserts a word into the Binary Search Tree.
	BstNode* DeleteWord			( BstNode*, char* word );								//- Deletes the specified word from the Binary Search Tree.
	BstNode* CreateNewBstNode	( char* word);											//- Creates a new node with a word
	
	bool SearchBST				( BstNode* ptrRoot, char* word );						//- Searches the Binary Search Tree for the specified word in the BST.
	bool CheckIfBalanced		( BstNode* prtRoot );									//- Checks to see if the tree is Balanced

	char* FindFirstWord			( BstNode* ptrRoot );									//- Searches the Binary Search Tree for the first word in the Dictionary in Alphabetical Order. E.G - This is equivalent to finding the smallest number in the BST e.g findMin() 
	char* FindLastWord			( BstNode* ptrRoot );									//- Searches the Binary Search Tree for the last word in the Dictionary in Alphabetical Order. E.G - This is equivalent to finding the largest number in the BST e.g findMax() 
	
	void CheckInOrder			( BstNode* ptrRoot );									//- Prints out the Words of the BST in alphabetical order, So user can verify if BST is in order. Note: If output is not in alphabetical order then the BST is not ordered correctly. 
	void ExportInOrder			( BstNode* ptrRoot );									//- Exports the words contained within the BST in alphabetical order to a .txt file.
	void DeleteInOrder			( BstNode* ptrRoot );									//- Deletes the the BST Nodes in order
	
	
	BstNode* BalanceTree		( BstNode* ptrRoot  );									//- Balances the tree
	BstNode* FindNodeContainingFirstWord( BstNode* ptrRoot );							//- Searches the SubTree of the Binary Search Tree for the node containing the first word of the SubTree Node. E.G - find min.  
	
	void GenerateDictionaryBST	( DictionaryGenerator &Dictionary, BstNode* &ptrRoot );	//- Creates & Generates the BST 
	
	
private:

	int BalanceFactor						( BstNode* ptrRoot );						//- Provides the balanceFactor for that specific node
	
	BstNode* Rotate_LR						( BstNode* parentNode );					//- Rotate - "Left-Right Case"
	BstNode* Rotate_LL						( BstNode* parentNode );					//- Rotate - "Left-Left Case"
	BstNode* Rotate_RR						( BstNode* parentNode );					//- Rotate - "Right-Right Case"
	BstNode* Rotate_RL						( BstNode* parentNode );					//- Rotate - "Right-Left Case"
	
	std::string MergeHyphen					(	std::string lineToCheck, 
												std::string lineToMergeWith );			//- Merges a line that ends with a hypen to the next line, it also removes this hypen when joining the lines together.

	bool CheckForBadChar					( char inputChar );							//- Checks for a bad char
	bool CheckForBadInput					( std::string &checkWord );					//- Checks for bad input
	bool CheckForGrammarAtEOL				( char inputChar1, char inputChar2 );		//- Checks for bad cases of grammar
	bool CheckSecondLastCharForBadInput		( char inputChar );							//- Confirms that no bad bad input's have occured.

	void CheckIfDictionaryFileExists		();											//- Checks and deletes file if it already exists so we can create a new one

	bool ConvertUpperCaseToLowerCaseAndCheckIsDigit		( char* &cstr_line );			//- Converts all upper case char's to lowercase char's
};
#endif
////////////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////////////