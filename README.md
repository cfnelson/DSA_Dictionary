# DSA_Dictionary 

This project is written in C++ and was completed for a Data Structures & Algorithms course whilst at university.

I have uploaded this project here so that I may look back in a few years and see my code when I first learnt C++.

## Dictionary Generator

### Program Requirements

Write a C++ program to read in text from a nominated file, identify words, and add them
to a binary search tree structure. If the program encounters a word that is not in the tree,
then it adds it to the tree, otherwise it ignores that word and looks for the next. Insertion
in the tree should be in such a manner that the tree remains reasonably well balanced.
Convert all letters to lower-case so that “The” and “the” will count as two occurrences of
the same word.

A word consists of letters (a .. z, A .. Z) and a possible apostrophe (e.g. can’t) or a hyphen
(co-processor). Note that words containing numbers are ignored.
A hyphen at the end of a line probably suggests a word that is split, therefore delete it and
combine the two pieces.

A hyphen in the middle of a line suggests a hyphenated word, thus “co-processor” is a
single word. This scheme might miss some hyphenated words that happen to be split by
the end of a line.

Once the entire source document (or keyboard input) is processed, then the vital statistics
of the tree (number of nodes and maximum depth) should be reported to the user. An inorder
traversal of the tree can then be used to produce an alphabetical listing of all the
words found in the input. Store the resulting sorted strings into the file “dict.txt”
separating each word with a newline.

You can assume that the maximum number of unique words will be 500 with a maximum
length of 15 characters.

You must use the ‘C’ FILE functions ```<stdio.h>``` for all file ```IO``` and ```STL <string>``` handling.

### Program Notes:

The Dictionary Generator Parses the Ass2Dictionary.txt file 

During the parsing process it creates a Balanced BST containing 578 Nodes (unique words) with a maximum height of 11.	The parsing of the Ass2Dictionary.txt file allows for words that contain apostrophe's ( ' ) and hyphens ( - ), the parsing has also allowed Old English/French words such as 'ere,'nee' and o, as the input file is a theater script. 

The parsing also allows for all grammatically correct words. Such as words that end with !,?,:,;, . and , as long as they are followed by a blank white space e.g " ".

The BST's Balance is maintained by using [AVL](http://en.wikipedia.org/wiki/AVL_tree) Rotation's after each new word is inserted. 

The algorithm in pseudo-code from Wikipedia was read and adapted into c++, which can be seen below.  

```
	 if ( balance_factor(L) == 2 )    //The left column
	 {  
	   let P=left_child(L)
	   if (balance_factor(P) == -1)   //The "Left Right Case"
	   { 
	       rotate_left(P)             //reduce to "Left Left Case"
	   }
	   rotate_right(L);               //Left Left Case
	 } 
	 else                             //balance_factor(L) == -2, the right column
	 {                        
	   let P=right_child(L)
	   if (balance_factor(P) == 1)    //The "Right Left Case"
	   {  
	       rotate_right(P)            //reduce to "Right Right Case"
	   }
	   rotate_left(L);                //Right Right Case
	 }
``` 
## Spell Checker

### Program Requirements

Write a C++ program that reads in the file “dict.txt” that was generated in the previous
program and stores each word into a hash table. Hash tables (see chap. 9) are commonly
used in the implementation of spelling checkers to speed up access to the dictionary.

The program should then read in text from a file, identifying words in the same way as
the first program and checking them against the dictionary list. If a match is not found
then the mismatched word should be reported to the user with some suggested spellings.
Your program must use a hash table to store the dictionary words (or pointers to words or
structures).

As in the previous section you can assume that there will be a maximum
number of 500 words in the dictionary with a maximum length of 15 characters. Word
size in the input stream to be checked is indeterminate (i.e. may be >15 characters).

You must use the “C++” stream functions for all ```IO``` and ```clib <string.h>``` functions but not
```STL string``` or ```STL <unordered_map>``` or ```<unordered_set>```.

### Program Notes:

The spelling suggestions are saved to "Spelling Suggestions.txt" file which is approximately 2600 lines.

The spell checker uses the same parsing process as the generator, this was done to meet the requriements.

For every word that has failed a spelling check 4 word suggestions are provided to the user.
