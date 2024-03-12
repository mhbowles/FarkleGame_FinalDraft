/*
* Author:		Milo Bowles
* Email:		milo.bowles@snhu.edu
* Date:			12/5/2023
* Class:		IT-312 Software Devel w/C++
* Assignment:	7-1 Final Project - Farkle Game
*
* Contains function definitions for the generic linked list class.
* Circular and singularly linked.
*/
#include <iostream>
#include "LinkedList.h"
#include "Player.h" // for the final line to fix .cpp template linker errors

using namespace std;

//------------------------------------------------
//              PRIVATE FUNCTIONS
//------------------------------------------------

/*
* Inserts a data node if the list is empty
* @param    data    - data to be added to the list
*/
template <typename T>
void LinkedList<T>::addToEmpty(T data) {
    
    if (last == NULL) {
        // allocate and declare new node
        Node<T>* newNode = new Node<T>(data);

        // assign last to new node
        last = newNode;

        // create link to itself
        last->next = newNode;
    }
}

//------------------------------------------------
//              PUBLIC FUNCTIONS
//------------------------------------------------

template <typename T>
LinkedList<T>::LinkedList() {
    last = NULL;
}

/*
* Inserts a data node to the front of the list
* @param    data    - data to be added to the list
*/
template <typename T>
void LinkedList<T>::addToFront(T data) {

    //if list is empty, add to empty
    if (last == NULL) {
        addToEmpty(data);
    }
    else {

        //allocate and declare new node
        Node<T>* newNode = new Node<T>(data);

        //store address of the front to the next of new node,
        //to "Hang on" to the original list as not to lost it
        newNode->next = last->next;

        //make new node the new front
        last->next = newNode;

    }
}

/*
* Inserts a data node to the end of the list
* @param    data    - data to be added to the list
*/
template <typename T>
void LinkedList<T>::addToEnd(T data) {

    // if list is empty, add to empty
    if (last == NULL) {
        addToEmpty(data);
    }
    else {

        // allocate and declare new node
        Node<T>* newNode = new Node<T>(data);

        // store address of the front node to the next of new node,
        // to "Hang on" to the rest of the list
        newNode->next = last->next;

        // point current last to new node
        last->next = newNode;

        // make new node the new last
        last = newNode;
    }
}

/*
* Deletes the data node at the front of the list
*/
template <typename T>
void LinkedList<T>::deleteAtFront() {

    //if the list is empty, do nothing
    if (last != NULL) {

        //if the list has one element, clear it
        if (last->next == last) {

            delete last;
            last = NULL;
            
        }
        else {
            // otherwise, set the lasts next to the second element
            // effectivily hopping over (and forgetting) the head
            // don't forget to delete the original front

            Node<T>* OGFront = last->next;
            last->next = last->next->next; //hop over front
            delete OGFront;
        }
    }
}

/*
* Deletes the data node at the end of the list
*/
template <typename T>
void LinkedList<T>::deleteAtEnd() {

    // if the list is empty, do nothing
    if (last != NULL) {

        // if the list has one element, clear it
        if (last->next == last) {
            delete last;
            last = NULL;
        }
        else {

            // mark the original last (to be deleted)
            Node<T>* OGLast = last;

            // traverse to the second to last element
            Node<T>* temp = last;
            while (temp->next != last) {
                temp = temp->next;
            }

            // set second to last element's next to the first,
            // hopping over the last
            temp->next = temp->next->next;

            // set the new last
            last = temp;

            // delete the original last
            delete OGLast;
        }
    }
}

/*
* clears all items in the list
*/
template <typename T>
void LinkedList<T>::clear() {

    // delete each node one at a time,
    // until list is empty
    while (last != NULL) {
        deleteAtFront();
    }
    deleteAtFront();
}

/*
* retrieves the number of items in the list
* @returns  the number of items in the list
*/
template <typename T>
int LinkedList<T>::size() {

    int size = 0;
    if (last != NULL) {
        
        // start at the front
        Node<T>* temp = last->next;
        // traverse the list and iterate size
        do {
            size++;
            temp = temp->next;
        } while (temp != last->next); // stop when the front is reached again

    }
    return size;
}

/*
* returns the last element in the list,
* where last's next points to the front of the list
*/
template <typename T>
Node<T>* LinkedList<T>::getLast() const {
    return last;
}

// have to do this for each type the user may use
template class LinkedList<Player>;