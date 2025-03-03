#include "declaration.hpp"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
Node::Node(int m, double xlower, double xupper, double ylower, double yupper){ 
    rightDown_= nullptr;
    rightUp_ = nullptr;
    leftDown_= nullptr;
    parent_= nullptr;
    leftUp_ = nullptr;    
    points = new double[2*m];
    curCap = 0;
    maxCap =m;
    Leaf = true;
    xLower = xlower;
    xUpper = xupper;
    yLower = ylower;
    yUpper = yupper;

}

Node::~Node(){
    delete [] points;
}
//we are gonna search
bool Node::Search(double xref, double yref, double d){
    if(Leaf){
        int count =0;
        while(count<curCap){
            double x = points[2*count];
            double y = points[2*count+1];
            //calculate distance
            double dis = sqrt(pow(x-xref,2) + pow(y-yref,2));
            //found
            if (dis<d){
                return true;
            }
            count++;
        }
        return false;
    }
    else{
        //cout<<"i made a huge mistake node::search"<<endl;
        if(leftDown_->Search(xref, yref,d)){
            return true;
        }
        if(leftUp_->Search(xref, yref,d)){
            return true;
        }

        if(rightDown_->Search(xref, yref,d)){
            return true;
        }
        if(rightUp_->Search(xref, yref,d)){
            return true;
        }
        return false;
    }
    //should never get to this line
    return false;
}

bool Node::insert(double x, double y){
    //just insert the points if it is not full and it is Leaf
    for(int i =  0;i<curCap;i++){
        if(points[2*i] == x){
            if(points[2*i+1] == y){
                return false; 
            }
        }
    }
    // cout<<"leaf: "<<Leaf<<endl;
    // cout<<"curcap: "<<curCap<<endl;
    // cout<<"maxcap: "<<maxCap<<endl;
    if(curCap < maxCap && Leaf){
        points[2*curCap]= x;
        points[2*curCap+1] =y;
        curCap+=1;
        return true;
    } 
    return false;
}
//idea: we are garenteed to not have violation here
void Node::distribute(){
   // cout<<"this should be called 3 times: "<<endl;
    Leaf = false;
    double xmid= (xLower+xUpper)/2;
    double ymid = (yLower+yUpper)/2;
    //make the 4 subchild
    leftDown_ = new Node(maxCap, xLower, xmid , yLower, ymid);
    leftDown_ ->setParent(this);
    leftUp_ = new Node(maxCap, xLower, xmid, ymid, yUpper);
    leftUp_ ->setParent(this);
    rightUp_ = new Node(maxCap, xmid, xUpper, ymid, yUpper);
    rightUp_ ->setParent(this);
    rightDown_= new Node(maxCap,xmid,xUpper,yLower,ymid);
    rightDown_ ->setParent(this);
    double x;
    double y;
    for(int i=0;i<2*maxCap;i+=2){
        x = points[i];
        y = points[i+1];
        //now we decide which point the child belongs in
        if(x == xmid && y == ymid){
            leftUp_->insert(x,y);
        }
        //special case 2, it falls on the verticle border
        //we put it on the left
        else if(x == xmid){
            if(y <ymid){
                leftDown_->insert(x,y);
            }
            if(y >ymid){
                leftUp_->insert(x,y);
            }
        }
        //special case 2, it falls on the horizontal border
        //we put it on the up
        else if(y == ymid){
            if(x<xmid){
                leftUp_->insert(x,y);
            }
            if(x>xmid){
                rightUp_->insert(x,y);
            }
        }
        //regular case
        else{
            if(x < xmid && y < ymid){
                leftDown_->insert(x,y);
            }
            else if(x < xmid && y > ymid){
                leftUp_->insert(x,y);
            }
            else if(x > xmid && y < ymid){
                rightDown_->insert(x,y);
            }
            else if(x>xmid && y>ymid){
                rightUp_->insert(x,y);
            }
        }
    }
   // cout<<"exited distribute"<<endl;
}
double * Node::getPoints(){
    return points;
}
Node *Node::getLU(){
    return leftUp_;
}
Node *Node::getLD(){
    return leftDown_;
}
Node *Node::getRU(){
    return rightUp_;
}
Node *Node::getRD(){
    return rightDown_;
}

void Node::setLU(Node *n){
    leftUp_ = n;
}
void Node::setLD(Node *n){
    leftDown_ = n;
}
void Node::setRU(Node *n){
    rightUp_ = n;
}
void Node::setRD(Node *n){
    rightDown_ = n;
}
void Node::setLeaf(){
    Leaf = ~Leaf;
}
bool Node::getLeaf(){
    return Leaf;
}
double Node::xu(){
    return xUpper;
}
double Node::xl(){
    return xLower;
}
double Node::yu(){
    return yUpper;
}
double Node::yl(){
    return yLower;
}
Node *Node::getParent(){
    return parent_;
}
void Node::setParent(Node *p){
    parent_ = p;
}

int Node::getCurCap(){
    return curCap;
}
int Node::getMaxCap(){
    return maxCap;
}