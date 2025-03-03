#include "declaration.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <climits>
#include <exception>
using namespace std;


Quadtree::Quadtree(int m, double xi0, double xi1,double yi0,double yi1){
    x0 = xi0;
    x1 = xi1;
    y1 = yi1;
    y0 = yi0;
    maxCap = m;
    num =0;
    head_ = new Node(m,x0,x1,y0,y1);// we are initializing the head.
    cout<<"success"<<endl;
}
/*
	CITATION:
    Destructor for the project. The idea for this destructor was inspired by 
    a stack Overflow response on the destructor for binary search trees.
https://stackoverflow.com/questions/34170164/destructor-for-binary-search-tree
*/
Quadtree::~Quadtree(){
    Node *temp = head_;
    if(temp){
        recursiveDelete(temp);
    }
}
void Quadtree::recursiveDelete(Node *n){
    if(n){
        recursiveDelete(n->getLD());
        recursiveDelete(n->getLU());
        recursiveDelete(n->getRD());
        recursiveDelete(n->getRU());
        delete n;
    }
}
//literally iterate through all the points check for distance
void Quadtree::Nearest(double x, double y){
    Node * temp = head_;
    
    if (Num() ==0){
        cout<<"no point exists"<<endl;
        return;
    }
    //if the head is null
    if(!head_){
        cout<<"no point exists"<<endl;
        return;
    }
    //general algorithm to traverse the tree and check everypoint
    /*
    1. traverl to the every node containing x and y
    2. check if the distance is less than distance.
    3. check all points
    */
   double distance = INT_MAX;
   double xloc = (x0+x1)/2;
   double yloc =(y0+y1)/2;
   bool update = false;
   recursiveCheckDistance(distance, x,y,xloc,yloc,head_,update);
   if(update){
    cout<<xloc<<" "<<yloc<<endl;
   }
   else{
    cout<<"no point exists"<<endl;
   }
}
//garenteed to be within the quadtree

void Quadtree::recursiveCheckDistance(double &distance, double x, double y, double &xpt, double &ypt, Node * node,bool &update){
   // cout<<"called"<<endl;
    //if its not leaf we keep checking
    if(!node->getLeaf()){
        recursiveCheckDistance(distance, x,y,xpt, ypt,node->getLD(),update);
        recursiveCheckDistance(distance, x,y,xpt, ypt,node->getRD(),update);
        recursiveCheckDistance(distance, x,y,xpt, ypt,node->getLU(),update);
        recursiveCheckDistance(distance, x,y,xpt, ypt,node->getRU(),update);
    }
    //base case: it is leaf
    else{
       // cout<<"the capacity of the node"<< node->getCurCap()<<" node: "<<node<<endl;
        for(int i =0; i<node->getCurCap();i++){
            double xcord = node->getPoints()[2*i];
            double ycord = node->getPoints()[2*i+1];
          //  cout<<"xpt and ypt cord "<<xpt<<"  ,"<<ypt<<endl;
            double ourD = sqrt(pow(xcord - x,2)+pow(y-ycord,2));
            if(ourD<distance){
                //cout<<"we updated distance with "<<xpt<<", "<<ypt<<endl;
                xpt = xcord;
                ypt = ycord;
                distance = ourD;
                update = true; 
            }
            else if(ourD == distance){
                if(xpt < xcord){
                    //cout<<"we updated distance rgergeerg with "<<xpt<<", "<<ypt<<endl;
                    xpt = xcord;
                    ypt = ycord;
                }
                update = true;
            }
        }
    }
}


// remember to check for illegal arguments


void Quadtree::Range(double xr0,double yr0, double xr1, double yr1){
    if(xr0>=xr1 || yr0>=yr1){
        cout<<"illegal argument"<<endl;
        return;
    }
    
    if(num == 0){
        cout<<"no points within range"<<endl;
        return;
    }
    /*
    1. check if one of the 4 endpoints falls into one quad
    2. go to that quad and repeat 1 until we get to Leaf
    3. iterate through the the node 
    
    */
    //1. 
    bool foundElement = false;
    FindElement(head_ , xr0,yr0,xr1,yr1, foundElement);
    if(foundElement){
        cout<<endl;
    }
    else{
        cout<<"no points within range"<<endl;
    }
}
/*
p1 (xr0, yr0)
p2 (xr1, yr1)
p3 (xr0, yr1)
p4 (xr1, yr0)

*/
void Quadtree::FindElement(Node* node, double xr0,double yr0, double xr1, double yr1, bool &foundElement){
    if(!node->getLeaf()){
        //cout<<"we should see this printed twice"<<endl;
        //check if any end points fall in leftdown
        //xr0 falls under leftDown or/and leftUp
        double xLower = node->getLD()->xl();
        double xUpper = node->getLD()->xu();
        double yLower = node->getLD()->yl();
        double yUpper = node->getLD()->yu();
        //check if all 4 points falls under leftDown
        if(
            (xr0 <=xUpper && xr0>= xLower && yr0 <=yUpper && yr0 >= yLower) || // this is for p1
            (xr1 <=xUpper && xr1>= xLower && yr1 <=yUpper && yr1 >= yLower) || // for p2
            (xr0 <=xUpper && xr0>= xLower && yr1 <=yUpper && yr1 >= yLower) || //for p3
            (xr1 <=xUpper && xr1>= xLower && yr0 <=yUpper && yr0 >= yLower) ||
            //case where the node is entirely bounded by the range
            (xLower >=xr0 && xLower <=xr1 && yLower >=yr0 && yLower <=yr1)|| // bottom left cord
            (xUpper >=xr0 && xUpper <=xr1 && yLower >=yr0 && yLower <=yr1)|| // bottom right cord
            (xUpper >=xr0 && xUpper <=xr1 && yUpper >=yr0 && yUpper <=yr1)|| // top right
            (xLower >=xr0 && xLower <=xr1 && yUpper >=yr0 && yUpper <=yr1) // top left
        ) // for p4
            {
             //   cout<<"we went somewhere LD"<<endl;
                FindElement(node->getLD(), xr0,yr0,xr1,yr1, foundElement);
            }
        
        //check if any of the 4 points fall under leftUp
        
        xLower = node->getLU()->xl();
        xUpper = node->getLU()->xu();
        yLower = node->getLU()->yl();
        yUpper = node->getLU()->yu();
        if(
            (xr0 <=xUpper && xr0>= xLower && yr0 <=yUpper && yr0 >= yLower) || // this is for p1
            (xr1 <=xUpper && xr1>= xLower && yr1 <=yUpper && yr1 >= yLower) || // for p2
            (xr0 <=xUpper && xr0>= xLower && yr1 <=yUpper && yr1 >= yLower) || //for p3
            (xr1 <=xUpper && xr1>= xLower && yr0 <=yUpper && yr0 >= yLower) || // for p4
            //case where the node is entirely bounded by the range
            (xLower >=xr0 && xLower <=xr1 && yLower >=yr0 && yLower <=yr1)|| // bottom left cord
            (xUpper >=xr0 && xUpper <=xr1 && yLower >=yr0 && yLower <=yr1)|| // bottom right cord
            (xUpper >=xr0 && xUpper <=xr1 && yUpper >=yr0 && yUpper <=yr1)|| // top right
            (xLower >=xr0 && xLower <=xr1 && yUpper >=yr0 && yUpper <=yr1) // top left
        ){
           // cout<<"we went somewhere LU"<<endl;
            FindElement(node->getLU(), xr0,yr0,xr1,yr1, foundElement);
        }
        //check if any of the 4 points fall under rightUP
        xLower = node->getRU()->xl();
        xUpper = node->getRU()->xu();
        yLower = node->getRU()->yl();
        yUpper = node->getRU()->yu();
        if(
            (xr0 <=xUpper && xr0>= xLower && yr0 <=yUpper && yr0 >= yLower) || // this is for p1
            (xr1 <=xUpper && xr1>= xLower && yr1 <=yUpper && yr1 >= yLower) || // for p2
            (xr0 <=xUpper && xr0>= xLower && yr1 <=yUpper && yr1 >= yLower) || //for p3
            (xr1 <=xUpper && xr1>= xLower && yr0 <=yUpper && yr0 >= yLower) || // for p4
            //case where the node is entirely bounded by the range  
            (xLower >=xr0 && xLower <=xr1 && yLower >=yr0 && yLower <=yr1)|| // bottom left cord
            (xUpper >=xr0 && xUpper <=xr1 && yLower >=yr0 && yLower <=yr1)|| // bottom right cord
            (xUpper >=xr0 && xUpper <=xr1 && yUpper >=yr0 && yUpper <=yr1)|| // top right
            (xLower >=xr0 && xLower <=xr1 && yUpper >=yr0 && yUpper <=yr1) // top left
        ){
            //cout<<"we went somewhere RU"<<endl;
            FindElement(node->getRU(), xr0,yr0,xr1,yr1, foundElement);
        }
        //check if any of the 4 points fall under rightDown
        xLower = node->getRD()->xl();
        xUpper = node->getRD()->xu();
        yLower = node->getRD()->yl();
        yUpper = node->getRD()->yu();
        if(
            (xr0 <=xUpper && xr0>= xLower && yr0 <=yUpper && yr0 >= yLower) || // this is for p1
            (xr1 <=xUpper && xr1>= xLower && yr1 <=yUpper && yr1 >= yLower) || // for p2
            (xr0 <=xUpper && xr0>= xLower && yr1 <=yUpper && yr1 >= yLower) || //for p3
            (xr1 <=xUpper && xr1>= xLower && yr0 <=yUpper && yr0 >= yLower) || // for p4
            //case where the node is entirely bounded by the range
            (xLower >=xr0 && xLower <=xr1 && yLower >=yr0 && yLower <=yr1)|| // bottom left cord
            (xUpper >=xr0 && xUpper <=xr1 && yLower >=yr0 && yLower <=yr1)|| // bottom right cord
            (xUpper >=xr0 && xUpper <=xr1 && yUpper >=yr0 && yUpper <=yr1)|| // top right
            (xLower >=xr0 && xLower <=xr1 && yUpper >=yr0 && yUpper <=yr1) // top left
        ){
            //cout<<"we went somewhere RD"<<endl;
            FindElement(node->getRD(), xr0,yr0,xr1,yr1, foundElement);
        }
        
    }
    //its leaf we iterate linearly 
    else{
      //  cout<<"bound"<<xr0<<" "<<yr0<<" "<<xr1<<" "<<yr1<<endl;
        for(int i =0; i<node->getCurCap();i++){
            double x = node->getPoints()[2*i];
            double y = node->getPoints()[2*i+1];
           // cout<<"x and y cord"<<x<<"  ,"<<y<<endl;
            if( x > xr0 && x <xr1 && y >yr0 && y<yr1){
                cout<<x<<" "<<y<<" ";
                foundElement = true;
            }
        }
    }
}

void Quadtree::Insert(double x, double y){
    Node *temp = head_;
    if(x <=x0 || y<= y0 ||x>=x1||y>=y1){
        cout<<"failure"<<endl;
        return;
    }
    //if the node is a Leaf, we are going to try to insert.
    if(temp->getLeaf()){
        //we can insert normally
        if(temp->getMaxCap() > temp->getCurCap()){
            if(temp->insert(x,y)){
                cout<<"success"<<endl;
                num++;
            }
            else{
                cout<<"failure"<<endl;
            }
        }
        else{
            while(temp->getMaxCap() <= temp->getCurCap()){
                temp->distribute();
                temp = Traverse(x,y);
            }
            if(temp->insert(x,y)){
                cout<<"success"<<endl;
                num++;
            }
            else{
                cout<<"failure"<<endl;
            }
        }
    }
    else{//check which sub child the node falls under.
        temp = Traverse(x,y);
        while(temp->getMaxCap() <= temp->getCurCap()){
            temp->distribute();
            temp = Traverse(x,y);
        }
        if(temp->insert(x,y)){
                cout<<"success"<<endl;
                num++;
            }
        else{
            cout<<"failure"<<endl;
        } //maybe work maybe not
    }
}
int Quadtree::Num(){
    return num;
}

//go to the Leaf that contains x and y.
Node *Quadtree::Traverse(double x, double y){
    Node * temp = head_;
    //keep going until we reaching LeafW
    //wait just realized I am implement a better algorithm.
    //logic: find x mid,ymid, if it is less than x mid
    //
   // cout<<"traverse to insert "<<x<<" "<<y<<endl;
    while(!temp->getLeaf()){
        
        double xmid = (temp->xl()+temp->xu())/2;
        double ymid = (temp->yl()+temp->yu())/2;
        //special case 1: it falls on (xmid,ymid)
        if(x == xmid && y == ymid){
            temp = temp ->getLU();
        }
        //special case 2, it falls on the verticle border
        //we put it on the left
        else if(x == xmid){
            if(y <ymid){
                temp = temp ->getLD();
            }
            if(y >ymid){
                temp = temp ->getLU();
            }
        }
        //special case 2, it falls on the horizontal border
        //we put it on the up
        else if(y == ymid){
            if(x<xmid){
                temp = temp->getLU();
            }
            if(x>xmid){
                temp = temp->getRU();
            }
        }
        //regular case
        else{
            if(x < xmid && y < ymid){
                temp = temp->getLD();
            }
            else if(x < xmid && y > ymid){
                temp = temp->getLU();
            }
            else if(x > xmid && y < ymid){
                temp = temp->getRD();
            }
            else if(x>xmid && y>ymid){
                temp = temp->getRU();
            }
        }
    }
    return temp;
}

void Quadtree::Search(double x, double y, double d){
   // cout<<"i made a huge mistake quadtree::search"<<endl;
    //step 1: go to the leaf
    Node* searchBound = Traverse(x,y);
    
    //step 2: check to see if the Leaf covers the entire distance
    bool contained = true;
    //too far right
    if(x+d > searchBound->xu() || x-d < searchBound->xl()){
        contained = false;
    }
    if(y+d > searchBound->yu() || y-d < searchBound->yl()){
        contained = false;
    }
    // we go up the tree until it is contained or we reached the Leaf
    while(!contained && searchBound->getParent()){
        //cout<<"we went up"<<endl;
        searchBound = searchBound->getParent();
        if(y+d < searchBound->yu() && y-d > searchBound->yl()){
            if(x+d < searchBound->xu() && x-d > searchBound->xl()){
                contained = true;
            }
        }
    }

    //step 3: try to find a point
    bool found = searchBound->Search(x,y,d);
    
    //step 4: return
    if(found){
        cout<<"point exists"<<endl;
    }
    else{
        cout<<"no point exists"<<endl;
    }

}