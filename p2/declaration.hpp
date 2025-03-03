#ifndef DECLARATION_HPP
#define DECLARATION_HPP
#include <string>
class Node{
    private:
    std::string word;
    int key;
    int index;
    Node *nextNode;

    public:
    Node(std::string inputStr, int index, int key);
    ~Node();
    int getkey();
    std::string getWord();
    Node* getNextNode();
    void setNextNode(Node *next);
    int getIndex();
};

class Linked_list{
public:
    Linked_list();
    ~Linked_list();
    std::string insert_Linked_ist(std::string word, int index, int key, bool &noDuplicate); //don't need to insert the key
    void setHead(Node * head);
    Node* getHead();
private:
    Node *listHead_;
};
//credit: Mike from learn 
class resizableArray{
	private:
		int initCapacity;
		int currentCapacity;
		int size;
		std::string* array;
	public:
		resizableArray(int initCap);
		~resizableArray();
		int getSize();
		int getCapacity();
		void push(std::string word);
		std::string getAt(int indx);
};

class Hashmap{
public: 
    Hashmap(int size); 
    ~Hashmap();
    std::string insert(std::string word);
    void print(int k);
    void tokenize(std::string word, bool ptnewline);
    void retrieve(int index, bool ptnewline);

    bool Readfile(std::fstream &fin);
private:
    Linked_list **slots;    
    int mapSize;
    int arrSize;
    int index;
    resizableArray *dictionary; 
    
};
#endif