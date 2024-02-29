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
    std::cout << walk << std::endl;
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

void Linked_list::Spawn(double x, double y){
    //For the first node (List head)
    if(firstChild_ == nullptr){
        firstChild_ = new Node(x, y);
    }
    else{
        //transvgh terse throuhe linked list
        Node *walk = firstChild_;
        while(walk->getNextChild()){
            //walks through the linked list 
            walk = walk->getNextChild();
        }
        walk->setNextChild(new Node(x,y)); 
        Node *curNode = walk ->getNextChild();
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
    Node *cur = firstChild_ ->getNextChild();
    //deactive all the information
    if(t>0){
        prev-> setDistance(prev->getDistance()-t);
        double xDis = prev->getX();
        double yDis = prev->getY();
        prev->setX(prev->getX()-t*cos(atan2(yDis,xDis)));
        prev->setY(prev->getY()-t*sin(atan2(yDis,xDis)));
        if(prev->getDistance()<0){
            removehead(prev);
        }

        //walk through the linked list, if current child's distance is 
        //less than 1m, pass the previous to the removeChild function.
        
//if the delete keyowrd is called on the head, this have the potencial
//of being the new head
        while(cur){
            //std::cout<<"Current "<<cur<<std::endl;
            //std::cout<<"FirstChild_ "<<firstChild_<<std::endl;
            
            cur->setDistance(cur->getDistance() -t);
            xDis = cur->getX();
            yDis = cur->getY();
            cur->setX(cur->getX()-t*cos(atan2(yDis,xDis)));
            cur->setY(cur->getY()-t*sin(atan2(yDis,xDis)));
            if(cur->getDistance()<0){
                if(cur == firstChild_){
                    removehead(cur);
                }
                //keep remove node as usual
                else{ 
                    removeChild(prev);
                }

                std::cout << "Caught bug" << std::endl;
                std::cout << prev << std::endl;
                
            }
            std::cout<<cur<<std::endl;
            prev = cur;
            cur = cur->getNextChild();
        }
    }
    else{
        if(prev->getDistance()<1){
            removehead(prev);
        }
        // what if the first node is removed

        //but the second node also need to be removed? Now the second node is head and 

        //I should not use removeChild on it?


        //walk through the linked list, if current child's distance is 
        //less than 1m, pass the previous to the removeChild function.

        while(cur){
            if(cur == firstChild_){
                //check if it needs to be removed...
            }
            if(cur->getDistance()<1){
                removeChild(prev);
            }
            prev = cur;
            cur = cur ->getNextChild();
        }
    }
    std::cout<<"number of children still playing: "<<numberOfChildren<<std::endl;
}




//passing in the node before the node that has to be removed
void Linked_list::removeChild(Node *prev){
    std::cout << "is my theory right?\n";
    Node *badkid = prev->getNextChild();
    std::cout << "no its not \n";

    prev->setNextChild(badkid->getNextChild());
    //deallowcate node code here
    // std::cout<<badkid;

    if(badkid == firstChild_) {
        std::cout << "Oops!\n"; exit(0);
    }
    if(badkid != nullptr){
        std::cout << badkid->getX() << std::endl;
    }
    else{
        std::cout << "deleting a nullptr...\n";
    }


    delete badkid;
    badkid = nullptr;
    numberOfChildren--;
    //end of deallowcae head code here
}   

void Linked_list::removehead(Node *& head){
//change the head 
    firstChild_= head->getNextChild();

//deallowcate head code here
    if(head != nullptr){
        std::cout << head->getX() << std::endl;
    }
    else{
        std::cout << "deleting a nullptr...\n";
    }
    delete head;
    head = nullptr;
    numberOfChildren--;
//end of deallowcae head code here
}

void Linked_list::over(){
    if(numberOfChildren>0){
        std::cout<<"the player wins"<<std::endl;
    }
    else{
        std::cout<<"the wolf wins"<<std::endl;
    }
}

//walk through the Linked list and then print the location of each linkded list 
//if their distance is less than d

//ERROR -> location is messed up. 
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
