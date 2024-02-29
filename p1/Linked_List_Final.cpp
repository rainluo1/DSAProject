#include "declaration.hpp"
#include <iostream>
#include <cmath>

Linked_list::Linked_list():
firstChild_ {nullptr}, 
numberOfChildren{0}{
}

Linked_list::~Linked_list(){
    Node *walk = firstChild_;
    //deactive all the information
    while(walk != nullptr){
        Node *child {walk};
        walk = walk->getNextChild();
        delete child;
        child = nullptr;
    }
}

void Linked_list::callSpawn(double x, double y){
    if (x <= 0 || y <= 0){
        std::cout << "failure" << std::endl;
        return;
    }
    Linked_list::Spawn(x,y);
}
//insert in the front to ensure O(1) condition
void Linked_list::Spawn(double x, double y){
    //For the first node (List head)
    if(firstChild_ == nullptr){
        firstChild_ = new Node(x, y);
    }
    else{
        //replace the frist node
        Node *newNode = new Node(x,y);
        newNode->setNextChild(firstChild_);
        firstChild_ = newNode;       
    }
    numberOfChildren++;
    std::cout<<"success"<<std::endl;
}

void Linked_list::getNum(){
    std::cout<<"number of children still playing: "<<numberOfChildren<<std::endl;
}

void Linked_list::move(double t){
    //if no element in the list, return
    if(firstChild_ == nullptr){
        std::cout<<"number of children still playing: "<<numberOfChildren<<std::endl;
        return;
    }
    Node *prev = firstChild_;
    //walking through the linked-list and subtracking distance
    if(t>0){
        while(prev){
            double xDis = prev->getX();
            double yDis = prev->getY();
            prev->setDistance(prev->getDistance() -t);
            prev->setX(prev->getX()-t*cos(atan2(yDis,xDis)));
            prev->setY(prev->getY()-t*sin(atan2(yDis,xDis)));
            prev = prev->getNextChild();
        }
        //we remove nodes outside of the quadrant
        remove(true);
    }
    else{
        //remove distance within one meters.
        remove(false);
    }
    std::cout<<"number of children still playing: "<<numberOfChildren<<std::endl;
}
// if parameter passed in is true we remove for child outside of first quad
//if false we remove distance less than 1m
void Linked_list::remove(bool removeCondition){
    Node *prev = nullptr;
    Node *cur = firstChild_;
    if(removeCondition){
        while(cur){
            if((cur->getDistance()<=0 || cur->getX()<=0 || cur->getY()<=0)){
            //the node being removed is head
                if(prev == nullptr){
                    firstChild_ = cur ->getNextChild();
                }
               ////the node being removed is not head
               else{
                    prev->setNextChild(cur ->getNextChild());
               }
               Node *temp = cur;
               delete temp;
               cur = cur ->getNextChild();
               numberOfChildren--;
           }
           else{
            prev = cur;
            cur = cur->getNextChild();
           }          
        }
    }
    if(!removeCondition){
        while(cur){
            if((cur->getDistance()<1)){
            //the node being removed is head
                if(prev == nullptr){
                    firstChild_ = cur ->getNextChild();
                }
               ////the node being removed is not head
               else{
                    prev->setNextChild(cur ->getNextChild());
               }
               Node *temp = cur;
               delete temp;
               cur = cur ->getNextChild();
               numberOfChildren--;
           }
           else{
            prev = cur;
            cur = cur->getNextChild();
           }          
        }
    }
}
void Linked_list::over(){
    if(numberOfChildren>0){
        std::cout<<"the players win"<<std::endl;
    }
    else{
        std::cout<<"the wolf wins"<<std::endl;
    }
}

//walk through the Linked list and then print the location of each linkded list 
//if their distance is less than d
void Linked_list::printLocation(double D){
    Node *walk = firstChild_;
    bool isThereChild = false;
    //ensure the list if not empty
    if(walk){
        while(walk){
            if(walk->getDistance()<D){
                std::cout<<walk->getX()<<" ";
                std::cout<<walk->getY()<<" ";
                isThereChild = true;
            }
            walk = walk->getNextChild();
        }
        if(isThereChild){
            std::cout<<std::endl;
        }
    }
    if(!isThereChild){
        std::cout<<"no children within distance"<<std::endl;
    }
}
