#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include<string>
using namespace std;
class Node {
    friend class LinkedList;
public:
    Node(string& name, int no)
        :itemName(name), itemNo(no)
    {
        this->next = NULL;
    }
private:
    string itemName;
    int itemNo;
    Node* next;
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    int size() const;
    void addToStart(Node*);
    void addToEnd(Node*);
    void printList();
    bool removeFromStart();
    bool removeFromEnd();
    void removeNodeFromList(int);
    void removeNodeFromList(string);
private:
    Node* myHead;
    Node* myTail;
    int mySize;
};
#endif

