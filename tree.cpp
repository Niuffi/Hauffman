#include "tree.h"

Tree::Tree(int value, char character) {
    this->value = value;
    this->character = character;
    this->left = nullptr;
    this->right = nullptr;
}

Tree::Tree(std::map <char,std::string> keysMap) {
    this->value = 0;
    this->character = '\0';
    this->left = nullptr;
    this->right = nullptr;

    for (auto& k: keysMap) {
        addLeaf(k.second,k.first);
    }
}

Tree::~Tree() {
    delete this->left;
    delete this->right;
}

std::map <char,std::string> Tree::mapKeys(std::string path) {
    std::map <char,std::string> targetMap;
    std::map <char,std::string> sourceMap;
    std::string newPath;

    if (left == nullptr && right == nullptr) {
        targetMap[character] = path;
        return targetMap;
    }

    if (left != nullptr) {
        newPath = path + '0';
        sourceMap = left->mapKeys(newPath);
        targetMap.insert(sourceMap.begin(),sourceMap.end());
    }

    sourceMap.erase(sourceMap.begin(),sourceMap.end());

    if (right != nullptr) {
        newPath = path + '1';
        sourceMap = right->mapKeys(path += '1');
        targetMap.insert(sourceMap.begin(),sourceMap.end());
    }

    return targetMap;
}

std::string Tree::find(std::string code) {
    if (code.empty()) {
        if (left == nullptr && right == nullptr) {
            std::string output;
            output += character;
            return output;
        } else {
            return "";
        }

    } else {

        if (code[0] == '0') {
            return left->find(code.substr(1));
        } else {
            return right->find(code.substr(1));
        }
    }
}

Tree * Tree::joinTrees(Tree * tree1, Tree * tree2) {
    int newValue = tree1->value + tree2->value;
    Tree * newTree = new Tree(newValue);
    newTree->left = tree1;
    newTree->right = tree2;
    return newTree;
}

int Tree::getValue() { return value; };

void Tree::addLeaf(std::string code,char character) {
    if (code.empty()) {
        this->character = character;
        return;
    }

    if (code[0] == '0') {
        if (left == nullptr) {
            Tree * newTree = new Tree(0);
            this->left = newTree;
        }

        this->left->addLeaf(code.substr(1), character);

    } else {
        if (right == nullptr) {
            Tree * newTree = new Tree(0);
            this->right = newTree;
        }
        this->right->addLeaf(code.substr(1), character);
    }
}