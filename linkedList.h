#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

class node{
    private:
    string data;
    node* next;
    node* previous;
    public:
    node(){}
    node(string data){
        this->data=data;
        next=nullptr;
        previous=nullptr;
    }
    node* getNext(){
        return next;
    }
    node* getPrev(){
        return previous;
    }
    string getData(){
        return data;
    }
    void setNext(node* Node){
        next=Node;
        return;
    }
    void setPrevious(node* Node){
        previous=Node;
        return;
    }
};
class linkedList{
    //using circular  doubly linked list for easier insertion
    private:
    node* head;
    public:
    linkedList(){
        head=nullptr;
    }
    void insert(node* newNode){
        if(head==nullptr){
            head=newNode;
            head->setNext(newNode);
            head->setPrevious(newNode);
            return;
        }
        //insertion at tail
        node* tail = head->getPrev();
        newNode->setNext(head);
        newNode->setPrevious(tail);
        head->setPrevious(newNode);
        tail->setNext(newNode);
    }
    void remove(string name){
        //removing by value 
        if(head==nullptr){
            return;
        } 
        node* temp=head;
        do{
            temp=temp->getNext();
        }while((temp!=head && temp->getData()!=name));
        //temp is now at value 
        temp->getPrev()->setNext(temp->getNext());
        temp->getNext()->setPrevious(temp->getPrev());
        delete temp;
        return;
    }
    void display(){
        if(head==nullptr){
            return;
        }
        node* temp=head;
        cout<<"Displaying actors' names: "<<endl;
        do{
            cout<<"Actor: "<<temp->getData()<<endl;
            temp=temp->getNext();
        }while((temp!=head));
        return;
    }
};
#endif
