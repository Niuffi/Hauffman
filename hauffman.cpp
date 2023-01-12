#include "hauffman.h"
#include <iostream>




void Hauffman::importFile(char * path) {

    std::ifstream file (path, std::ios::binary);
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            fileContent += line + "\n";
        }
        fileContent.pop_back();
        file.close();
    } else {
        printf("Open file error");
    }

    getFileSize(path,&inputFileSize);


}

void Hauffman::exportFile(char * path) {
    std::ofstream file;
    file.open (path, std::ios::binary);
    file << this->header + "\n\n\n";
    file << this->fileContent;
    file.close();
    getFileSize(path,&outputFileSize);
}

std::string Hauffman::getHeader() { return header; }

std::string Hauffman::getCompresionRatio() {
    double compressionRatio = double(inputFileSize)/double(outputFileSize);
    return std::to_string(compressionRatio);
}

void Hauffman::compress() {

    std::vector <Tree *> trees;
    countEachCharacter();

    for (auto& c : charFrequency) {
        trees.push_back(new Tree(c.second,c.first));
    }

    auto lambda = [](Tree* a, Tree* b){ return a->getValue() < b->getValue(); };

    while (trees.size() > 1) {
        std::sort(trees.begin(), trees.end(),lambda);
        trees.push_back(Tree::joinTrees(trees[0],trees[1]));
        trees.erase(trees.begin());
        trees.erase(trees.begin());
    }

    this->charKeys = trees[0]->mapKeys();

    std::string binaryContent;
    for (auto& c : fileContent) {
        binaryContent += charKeys[c];
    }

    fileContent = "";
    int size = binaryContent.size();
    while (binaryContent.size() % 8 != 0) {
        binaryContent += "0";
    }

    char letter;
    std::string byte;
    for (int i = 0; i < binaryContent.size(); i+=8) {
        byte = binaryContent.substr(i,8);
        letter = stringToByte(byte);
        fileContent += letter;
    }



    header += std::to_string(size);
    header += '\n';


    for (auto& i : charKeys) {
        this->header.push_back(i.first);
        this->header += ":" + i.second + "\n";
    }

    delete trees[0];

}

void Hauffman::decompress() {

    std::stringstream ss;
    ss.str(fileContent);
    std::vector <std::string> headerArray;
    std::string line;

    header = fileContent.substr(0,fileContent.find("\n\n\n"));
    fileContent = fileContent.substr(fileContent.find("\n\n\n") + 4, fileContent.size());

    ss.str(header);

    while(std::getline(ss, line)) {
        headerArray.push_back(line);
    }

    int size = stoi(headerArray[0]);

    for (int i = 1; i < headerArray.size(); i++) {
        if (headerArray[i].substr(0,1) == ":" && headerArray[i].substr(1,1) != ":") {
            continue;
        }

        if (headerArray[i].empty()) {
            charKeys['\n'] = headerArray[i+1].substr(1,headerArray.size());
        } else {
            charKeys[headerArray[i][0]] = headerArray[i].substr(2,headerArray.size());
        }

    }

    this->header = "";
    Tree tree = Tree(charKeys);
    std::string binaryContent;

    for (auto& c : fileContent) {
        binaryContent += std::bitset<8>(c).to_string();
    }

    binaryContent.erase(binaryContent.end() - (8 - (size%8)), binaryContent.end());

    int start = 0;
    std::string letter;
    fileContent = "";
    for (int i = 0; i < binaryContent.size(); i++) {
        std::string sub = binaryContent.substr(start,i-start+1);
        letter = tree.find(sub);
        if (!letter.empty()) {
            start = i + 1;
        }
        fileContent += letter;
    }
}

void Hauffman::countEachCharacter(){
    for (char c : this->fileContent) {
        if (this->charFrequency.contains(c)) {
            this->charFrequency[c]++;
        } else {
            this->charFrequency[c] = 1;
        }
    }
}

char Hauffman::stringToByte(std::string byte) {
    char output = 0b0;
    for (int i = 0; i < 8; i++) {
        output = output << 1;
        if (byte[i] == '1') {
            output += 0b1;
        }
    }
    return output;
}

void Hauffman::getFileSize(char * path, int * output) {
    long begin, end;
    std::ifstream file (path);
    begin = file.tellg();
    file.seekg (0, std::ios::end);
    end = file.tellg();
    file.close();
    *output = end - begin;
}
