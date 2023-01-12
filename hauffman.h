#ifndef AIKD1_HAUFFMAN_H
#define AIKD1_HAUFFMAN_H

#include <string>
#include <map>
#include <vector>
#include <utility>
#include <fstream>
#include <cstring>
#include <sstream>
#include <bitset>
#include "tree.h"





class Hauffman {

private:

    int inputFileSize;

    int outputFileSize;

    std::string fileContent;

    std::map <char, int> charFrequency;

    std::vector <std::pair <char, int> > charVector;

    std::map <char,std::string> charKeys;

    std::string header;

public:

    void importFile(char * path);

    void exportFile(char * path);

    std::string getHeader();

    std::string getCompresionRatio();

    void compress();

    void decompress();

private:

    void countEachCharacter();

    char stringToByte(std::string byte);

    void getFileSize(char * path, int * output);

};



#endif //AIKD1_HAUFFMAN_H
