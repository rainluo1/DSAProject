#ifndef DECLARATION_HPP
#define DECLARATION_HPP
#include <string>
#include <exception>
class ExceptionBad : public std::exception{
    public:
    std::string msg() const { return "illegal argument"; }
};
class Node{
public: 
    Node(int m, double xlower, double xupper, double ylower, double yupper); 
    ~Node();   
    bool insert(double x,double y);
    void setLeaf(); //toggles the Leaf;
    bool getLeaf();
    Node *getLU();
    Node *getLD();
    Node *getRU();
    Node *getRD();
    void setLU(Node *n);
    void setLD(Node *n);
    void setRU(Node *n);
    void setRD(Node *n);
    double xl();
    double xu();
    double yl();
    double yu();
    Node *getParent();
    void setParent(Node *p);
    double *getPoints();
    bool Search(double xref, double yref, double d); 
    int getCurCap();
    int getMaxCap();
    //repositioning all the elements back into the array
    void distribute();
private: 
    
    Node *parent_;
    double *points; //size of m*2 array to rep x and y cord.
    //the 4 children
    Node *rightUp_;// first quad
    Node *leftUp_; //second quad
    Node *leftDown_; //3rd quad
    Node *rightDown_; // 4th quad
    
    //current and max capacites. 
    int curCap;
    int maxCap;
    //range that can be stored into the quad tree.
    double xLower;
    double xUpper;
    double yLower;
    double yUpper;
    //variable to check that if it can store a node
    bool Leaf;
    //
    
};

class Quadtree{
private:
    Node *head_;
    int num;
    double x0,x1,y0,y1;
    int maxCap;
    Node* Traverse(double x, double y);
    void recursiveDelete(Node *n);
    void recursiveCheckDistance(double &distance, double x, double y, double &xpt, double &ypt, Node * node, bool &update);
public:
    Quadtree(int m, double x0, double x1,double y0,double y1);
    ~Quadtree();
    void Insert(double x, double y);
    void Search(double x, double y, double d);//look for a point
    void Nearest(double x, double y); // find the nearest node
    void Range(double xr0,double yr0, double xr1, double yr1);
    int Num(); //return num 
    void FindElement(Node* node, double xr0,double yr0, double xr1, double yr1, bool &foundElement);
};


#endif