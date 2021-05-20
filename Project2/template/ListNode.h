//
// Created by Lorne Zhang on 11/27/20.
//

#ifndef DAILYPROGRAMMER_LISTNODE_H
#define DAILYPROGRAMMER_LISTNODE_H

template <class T>
class ListNode {
public:
    // constructor
    ListNode() {
    }
    // set value of node
    void setValue(T value) {
        this->value = value;
    }
    // set pointer of node
    void setPointer(ListNode* pointer) {
        this->pointer = pointer;
    }
    // set pointer to null
    void setPointerNull() {
        pointer = nullptr;
    }
    // get pointer
    ListNode* getNext() {
        return pointer;
    }
    // get value
    T getValue() {
        return value;
    }
private:
    T value;
    ListNode* pointer;
};


#endif //DAILYPROGRAMMER_LISTNODE_H
