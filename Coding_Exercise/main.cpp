///
///  main.cpp
///  Coding_Exercise
///
///  Created by BenBrewerBowman on 3/16/17.
///  Copyright © 2017 BenBrewerBowman. All rights reserved.
///

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>



/********************************************//**
* Holds:
*   each individual word
*   a count of the number of instances of the word
***********************************************/
typedef struct
{
    std::string name;
    int count;
} Word;


/********************************************//**
 *  Find a matching string within a vector of Word structs and return matching vector indice
 *  Arguments:
 *      Vector of structs of type 'Word'
 *      String to find match within vector
 *  Returns:
 *      If matching string is found, returns indice of vector with matching string
 *      If no matching string, returns vector.sizof, indicating to "push_back" a new word on the end
 ***********************************************/
int findWord (std::vector<Word> WordsVector, std::string name)
{
    int count;
    
    for ( count = 0; count < WordsVector.size(); ++count)
        if(WordsVector[count].name == name) break;
    
    return count;
}


/********************************************//**
 *  Bubble sorts a vector of Word structs by number of count members DESC
 *  Arguments:
 *      - Vector of structs of type 'Word'
 *  Returns:
 *      - Void
 ***********************************************/
void bubbleSort(std::vector<Word> &WordsVector)
{
    for (int i = 0; i < WordsVector.size(); ++i)
        
        for (int j = 0; j < (WordsVector.size() - i - 1); ++j)
            
            if (WordsVector[j].count < WordsVector[j + 1].count)
                std::swap(WordsVector[j], WordsVector[j+1]);
}


/********************************************//**
 *  Load each word from each file and:
 *  Strip any punctuation from leading and lagging word (second argument)
 *  Convert word (second argument) to lowercase
 *  Find out if the word (second argument) is already in vector of strings (first argument)
 *      If word matches one that is alread in the vector, increase count instance by 1
 *      Else add the word to list of words
 *  Return Void
 ***********************************************/
void wordPunctLCLoad (std::vector<Word> & WordsVector, Word & word)
{
    /// Remove leading and trailing punctuation
    if( ispunct( word.name.front() ) ) word.name.erase(0,1);
    if( ispunct( word.name.back() ) ) word.name.pop_back();
    
    /// Convert each leading letter to lowercase
    word.name.front() = tolower(word.name.front());
    
    /// stores index value where word is found.
    int index_of_found_word (0);
    
    /// Check if on stack. If index returned equals max size of array, then the word has not been found. If it returns any other value
    /// then it has been found
    if ( WordsVector.size() != 0 ) index_of_found_word = findWord (WordsVector, word.name);
    
    /// Word has not occured before. Initialize count to 1 and push onto end of stack.
    if ( (WordsVector.size() == index_of_found_word) || (WordsVector.size() == 0) )
    {
        word.count = 1;
        WordsVector.push_back(word);
    }
    /// If found on stack increment count by 1
    else WordsVector[index_of_found_word].count++;
}



int main(int argc, const char * argv[])
{
    
    /// Store CL arguments:
    /// First argument (input file)
    std::string inputFile = argv[1];
    /// Second argument (output file)
    std::string outputFile = argv[2];

    
    /**
     *  Opens a text file containing a list of filenames
     *  Stores each filename in a vector
     */
    
    /// List of input file names
    std::vector<std::string> inputFilesVector;
    
    /// Temp store each file name from read
    std::string line;
    
    /// Open read file
    std::ifstream readFile (inputFile);
    
    /// File opens correctly
    if (readFile.is_open())
    {
        while ( getline (readFile, line) )
        {
            /// Save each individual file from the input file
            inputFilesVector.push_back(line);
        }
        readFile.close();
    }
    /// File did not open correctly, print to user
    else std::cout << "Unable to open file: " << inputFile << std::endl;
    
    
    /** 
     *  Open each file from input.txt for reading. Store each line containing a text file into
     *  Load each word from each file and:
     *      - strip punctuation
     *      - convert to lowercase
     *  If the word exists, find it and increment it's count
     *  Else add the word to list of words
     */
    
    /// Holds each Word (name, count)
    std::vector<Word> WordsVector;
    
    /// Temporary word to store from file and then load into vector
    Word eachFileWord;
    
    /// For each filename listed
    for(int i = 0; i< inputFilesVector.size(); ++i)
    {
        /// Open file to read from
        readFile.open (inputFilesVector[i]);
    
        /// File opens correctly
        if (readFile.is_open())
        {
            while ( readFile.good() )
            {
                /// Store the next word in the file in a local variable.
                readFile >> eachFileWord.name;
                
                /// Strip punctuation, lowercase, load word and count into vector
                wordPunctLCLoad (WordsVector, eachFileWord);
            }
            readFile.close();
        }
        /// File did not open correctly, print to user
        else std::cout << "Unable to open " << inputFilesVector[i] << std::endl;
    }
    
    
    /// Bubble sort word list from most frequently occuring word to least occuring word
    bubbleSort (WordsVector);
    
    
    /**
     *  Write to output file with each different word and number of occurances
     */
    
    std::ofstream osfile (outputFile);
    /// File opens correctly
    if (osfile.is_open())
    {
        /// Write each word and count to file
        for(int i = 0; i < WordsVector.size(); ++i)
            osfile << WordsVector[i].name << " " << WordsVector[i].count << std::endl;
        
        osfile.close();
        std::cout << "Successfully generated: " << outputFile <<  std::endl;
    }
    /// File did not open correctly, print to user
    else std::cout << "Unable to open file: " << outputFile << std::endl;
    
    
    return 0;
}
