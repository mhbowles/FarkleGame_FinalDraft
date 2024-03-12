/*
* Author:		Milo Bowles
* Email:		milo.bowles@snhu.edu
* Date:			12/5/2023
* Class:		IT-312 Software Devel w/C++
* Assignment:	7-1 Final Project - Farkle Game
*
* Contains header declarations for a generic, circular, single-linked List class.
* Contains all code for a generic Node class.
* Linked List depends on Node
*/

#ifndef MILO_LINKEDLIST_H
#define MILO_LINKEDLIST_H

/*
* Generic node class to be used for the linked list
*/
template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T data) {
        this->data = data;
        this->next = NULL;
    }
};

/*
* Class for a generic, single-linked linked list
*/
template <typename T>
class LinkedList {

private:
    Node<T>* last;
    void addToEmpty(T data);

public:
    LinkedList();
    void addToFront(T data);
    void addToEnd(T data);
    void deleteAtFront();
    void deleteAtEnd();
    void clear();
    int size();
    Node<T>* getLast() const;
};



#endif MILO_LINKEDLIST_H