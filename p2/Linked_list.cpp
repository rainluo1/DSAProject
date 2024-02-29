#include "declaration.hpp"
#include <iostream>
#include <string>
Linked_list::Linked_list(): 
listHead_(nullptr){
}

Linked_list::~Linked_list(){
}

//we already accounted for the fact that listHead is not a nullptr
std::string Linked_list::insert_Linked_ist(std::string word, int index, int key, bool &noDulicate){
    Node *walk = listHead_;
    if(walk->getWord()== word){
        noDulicate = false;
        return "failure";
    }
    while(walk->getNextNode()!= nullptr){
        if(walk->getNextNode()->getWord() == word){
            noDulicate = false;
            return "failure";
        }
        walk = walk->getNextNode();
    }
    //we reached to the end of the linked-list
    Node *newNode = new Node(word,index, key);
    walk->setNextNode(newNode);
    return "success";
}

void Linked_list::setHead(Node *head){
    listHead_ = head;
}

Node * Linked_list::getHead(){
    return listHead_;
}
