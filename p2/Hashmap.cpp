#include "declaration.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
Hashmap::Hashmap(int size){
    mapSize = size;
    index =1;
    arrSize =11;
    dictionary = new resizableArray(arrSize);
    slots = new Linked_list*[size];
    for(int i =0;i<size;i++){
        slots[i] = nullptr;
    }
}

Hashmap::~Hashmap(){
    for(int i =0;i<mapSize;i++){
        //if it have elements we will do delete them
       // std::cout<<"here is the linked-list addresses: "<<slots[i]<<std::endl;
        if(slots[i]){
            Node *walk = slots[i]->getHead();
            //deactive all the node in the linked list
            while(walk != nullptr){
                Node *child {walk};
                walk = walk->getNextNode();
                delete child;
                child = nullptr;
            } 
            delete slots[i];
            slots[i] = nullptr;
        }
    }
    delete [] slots;
    //delete the pointer to a pointer first and then delete the pointer.
    slots = nullptr;
    delete dictionary;
}

//need to call this from main
bool Hashmap::Readfile(std::fstream &fin){
    std::string read;
    //perform input vaildation
    bool success = false;
    while(fin>>read){
        bool proper =true;
        for(int i =0; i< read.length();i++){
            int character = (int) read[i];
            //  std::cout<<character<<std::endl;
            if(character <65 || character > 122 || (character>=90 && character<=96)){
                //std::cout<<"failure 54 with "<<character<<std::endl;
                proper = false;
                break;
            }
        }
        if(proper){
            std::string cmd  = insert(read);
            if(cmd == "success"){
                success = true;
            }
        }
    }
    return success;
}

std::string Hashmap::insert(std::string word){
    int key =0;
    for(int i=0;i<word.length();i++){
        key+= int (word[i]);
        if(word[i] < 65 || word[i] > 122 || (word[i]>=90 && word[i]<=96)){
            return "failure";
        }
    }
    std::string returnval;
    int slotNum = key % mapSize;
    //if the slot have not been intialized
    bool noDuplicate = true;
    if(slots[slotNum] == nullptr){
        slots[slotNum] = new Linked_list();
        slots[slotNum]->setHead(new Node(word,index,key));
        //std::cout<<"word and the index: "<<slots[slotNum]->getHead()->getWord()<<" : "<<slots[slotNum]->getHead()->getIndex()<<std::endl;
        returnval = "success"; 
    }
    else{
        //std::cout<<"called "<<std::endl;
        returnval = slots[slotNum]->insert_Linked_ist(word,index, key, noDuplicate);
        
    }
    //std::cout<<"duplicate: "<< noDuplicate<<std::endl;
    //push it onto the dictionary
    if(noDuplicate){
        dictionary->push(word);
        //std::cout<<"current index: for the word "<<index <<" :"<<word<<std::endl;
        index++;
    }
    return returnval;
}
//print all the entries of the linked-list
void Hashmap::print(int k){

    if(slots[k] ==nullptr){
        std::cout<<"chain is empty"<<std::endl;
    }
    else{
    Node *walk = slots[k]->getHead();
        while(walk != nullptr){
            std::cout<<walk->getkey()<<" ";
            walk = walk->getNextNode();
        }
        std::cout<<std::endl;
    }
}
//given word, return the token
void Hashmap::tokenize(std::string word , bool ptnewline){
    int key =0;
    for(int i=0;i<word.length();i++){
        key+= int (word[i]);
    }
    int slotNum = key % mapSize;
    //the linked-list is empty -> the element must not exist
    if(slots[slotNum] == nullptr){
        if(ptnewline){
            std::cout<<"0"<<std::endl;
        }
        else{
            std::cout<<"0 ";
        }
        return;
    }
    Node *walk = slots[slotNum]->getHead();
    //std::cout<<"slot[slotnum]: "<<slots[slotNum]<<std::endl;
    // std::cout<<"walk: "<<walk<<std::endl;
    bool found = false;
    while (walk != nullptr){
        if(walk->getWord() == word){
            found = true;
            if(ptnewline){
                std::cout<<walk->getIndex()<<std::endl;
            }
            else{
                std::cout<<walk->getIndex()<<" ";
            }
            break;
        }
        walk = walk->getNextNode();
    }
    //std::cout<<"reached here"<<std::endl;
    if(!found){
        if(ptnewline){
            std::cout<<"0"<<std::endl;
        }
        else{
            std::cout<<"0 ";
        }
    }
   //std::cout<<"function exited"<<std::endl;
}

void Hashmap::retrieve(int index, bool ptnewline){
    if(index<=dictionary->getSize() && index >=0){
        if(ptnewline){
            std::cout<<dictionary->getAt(index-1)<<std::endl;
        }
        else{
            std::cout<<dictionary->getAt(index-1)<<" ";
        }
    }
    else{
        if(ptnewline){
            std::cout<<"UNKNOWN"<<std::endl;
        }
        else{
            std::cout<<"UNKNOWN ";
        }
    }
}

