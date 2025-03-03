#ifndef DECLARATION_HPP
#define DECLARATION_HPP

class Linked_list;
class Node;

class Node{
public:
    double getX();
    double getY();
    void setX(double xNew);
    void setY(double yNew);
    double getDistance();
    void setDistance(double t);
    Node *getNextChild();
    void setNextChild(Node *next);
    Node(double x, double y);
    ~Node();
private:
    double x;
    double y;
    double distance;
    Node *nextChild_;

};

class Linked_list{
public:
    // using these to check and validate inputs
    void callSpawn(double x, double y);
    void getNum();
    void over(); // return if there are one or more children
    void printLocation(double D);
    Linked_list();
    ~Linked_list();
    void move (double t);
    void removeChild(Node *prev);
    void removehead(Node*& head);
    void remove(bool removeCondition);
private:
    int numberOfChildren;
    void Spawn(double x, double y);
    Node *firstChild_;
};
#endif