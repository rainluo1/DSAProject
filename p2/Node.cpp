#include "declaration.hpp"
#include <iostream>
#include <string>
#include <cmath>

//Node::Node() : nextNode(nullptr), word(""),key(0){}
Node::Node(std::string inputStr, int index, int key): nextNode(nullptr), word(inputStr), index(index), key(key){}
Node::~Node(){}
Node *Node::getNextNode(){
    return nextNode;
}
void Node::setNextNode(Node *next){
    nextNode = next;
}

std::string Node::getWord(){
    return word;
}

int Node::getIndex(){
    return index;
}

int Node::getkey(){
    return key;
}