//
// Created by Lorne Zhang on 11/27/20.
//

#ifndef DAILYPROGRAMMER_LINKEDLIST_H
#define DAILYPROGRAMMER_LINKEDLIST_H

#include "ListNode.h"
#include <iostream>

template <class T>
class LinkedList {
public:
    // head and tail pointer
    // head for printing and tail for adding
    ListNode<T> *Head, *Tail;
    // constructor
    LinkedList() {
        this->Head = nullptr;
        this->Tail = nullptr;
    }
    // add value to list
    void add(T value) {
        // if list is empty, set tail and head to new node
        if(Head == nullptr) {
            Head = new ListNode<T>;
            Head->setValue(value);
            Tail = Head;
        }
        // if list not empty, add new node to tail
        else {
            ListNode<T>* temp = new ListNode<T>; // temp node
            temp->setValue(value); // set value of temp
            temp->setPointerNull(); // set pointer of temp
            Tail->setPointer(temp); // set tail pointer to temp
            Tail = Tail->getNext(); // set tail to temp
        }
    }
    // print
    void print() {
        ListNode<T> *ptr = Head; // pointer to head
        while(ptr != nullptr) { // while pointer is not null
            std::cout << ptr->getValue() << std::endl;
            ptr = ptr->getNext(); // set pointer to next
        }
    }
};


#endif //DAILYPROGRAMMER_LINKEDLIST_H
