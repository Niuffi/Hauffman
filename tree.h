
#ifndef AIKD1_TREE_H
#define AIKD1_TREE_H

#include <map>
#include <vector>
#include <string>



class Tree {

private:
    int value;

    char character;

    Tree * left;

    Tree * right;

public:

    explicit Tree(int value, char character = '\0');

    explicit Tree(std::map <char,std::string> keysMap);

    ~Tree();

    std::map <char,std::string> mapKeys(std::string path = "");

    std::string find(std::string code);

    static Tree * joinTrees(Tree * tree1, Tree * tree2);

    int getValue();

private:

    void addLeaf(std::string code,char character);

};

#endif //AIKD1_TREE_H
