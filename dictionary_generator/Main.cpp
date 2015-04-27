////////////////////////////////////////////////////////////////////////////////////
// Filename:		Main.cpp
// Author:			Charles Nelson - s2884951
// Date Modified:	03/05/2014 Created
//					07/06/2014 Updated 
// Description:		This file contains the main function
////////////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER								
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "DictionaryGenerator_H.h"

int main (void)
{
	DictionaryGenerator Dictionary;																			//- Creating an instance of our Dictionary Generator called Dictionary
	DictionaryGenerator::BstNode* ptrRoot = NULL;															//- Creating a DictionaryNode Struct which will be the root for our BST
	
	Dictionary.GenerateDictionaryBST( Dictionary, ptrRoot );												//- Generates the Dictionary BST
	
	std::cout << "Exporting Dictionary to \"dict.txt\" in alphabetical order." << "\n" << std::endl;		//- Informs user that we are writing the dictionary to the "dict.txt" file
	
	Dictionary.ExportInOrder( ptrRoot );																	//- Writing to the "dict.txt file"

	//std::cout << "Displaying BST In Alphabetical Order" << "\n" << std::endl;								//- Used For Testing Purposes - Informs user that we are printing to console
	
	//Dictionary.CheckInOrder( ptrRoot );																	//- Used For Testing Purposes - Displaying the BST In Order on console screen

	std::cout << "Number of Nodes in BST: " << Dictionary.wordCount << "\n" << std::endl;					//- Prints out the number of nodes in the tree.

	int treeHeight = Dictionary.heightOfBST( ptrRoot );														//- Caluclates the height of the tree from the first node in the tree

	std::cout << "Tree Height of BST: " << treeHeight << "\n" << std::endl;									//- Prints out the tree height to Console.
	system( "PAUSE" );
	
	return 0;
};
///////////////////////////////////////////////////////////////////////////////////
// END OF FILE
///////////////////////////////////////////////////////////////////////////////////