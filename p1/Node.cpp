#include "declaration.hpp"
#include <iostream>
#include <cmath>

Node::Node(double x, double y):
x(x),
y(y),
nextChild_(nullptr){ 
    distance =  sqrt(pow(x,2) +pow(y,2));
}

Node::~Node(){
    //when using the delete keyword, the destructor gets called.
    // x =0;
    // y= 0;
    // nextChild_ =nullptr;
    // std::cout<<"destructor is called"<<std::endl;
}

void Node::setDistance(double t){
    distance =t;
}

void Node::setX(double xNew){
    x = xNew;
}

void Node::setY(double yNew){
    y = yNew;
}
double Node::getDistance(){
    return distance;
}
void Node::setNextChild(Node *next){
    nextChild_= next;
}
Node *Node::getNextChild(){
    return nextChild_;
}
double Node::getX(){
    return x;
}
double Node::getY(){
    return y;
}
