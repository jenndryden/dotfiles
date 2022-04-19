#include "doubly-linked-list.h"
#include <new>
#include <iostream>

DoublyLinkedList::Node::Node(DataType data):
        value(data),
        next(NULL),
        prev(NULL)
{
}

DoublyLinkedList::DoublyLinkedList()
//initializes an empty doubly linked list
        :head_(NULL),
        tail_(NULL),
        size_(0)
{
}

DoublyLinkedList::~DoublyLinkedList()
{
    //destructor which fees all the dynamically allocated memory, if there is any
    while (head_){ // while head still exists, it loops and deletes nodes
        Node* temporaryNode = head_;
        head_ = head_->next;
        delete temporaryNode;
    }
}

unsigned int DoublyLinkedList::size() const
{
    // returns the number of elements nodes in the list
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    //this function returns the maximum number of elements that the list can hold
    return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
    //this function returns true if the list is empty, and false if it is not empty
    if (size_ == 0){
        return true;
    }
    return false;
}

bool DoublyLinkedList::full() const
{
    // if the list is full or at capacity, this function will return true. otherwise it will return false
    if (size() == CAPACITY){
        return true;
    }
    return false;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    // this function returns the value at the given index in the list
    //if the index is invalid it will return the last element
    Node* selectNode = getNode(index);
    if (!selectNode) { // if selectNode doesnt exist and the index is not found, then it returns the last element
        return tail_->value;
    }
    return selectNode->value;
}

unsigned int DoublyLinkedList::search(DataType value) const
{
    //this function searches for the given value following the order head to tail
    //if the index is not found, this function returns the size of the list
    Node *searchNode = head_;
    unsigned int counter = 0;
    //if it is found, it returns the index of the value
    while (searchNode){
        if(searchNode->value == value){
            return counter;
        }
        ++counter;
        searchNode = searchNode->next;
    }
    return size_;
}

void DoublyLinkedList::print() const
{
    //prints out all the elements in a standard output
    std::cout <<" Printing out linked list elements "<<std::endl;
    std::cout <<" Elements: "<<std::endl; // prints out text for elements
    Node *printNodes = head_; // initializes node to head
    while(printNodes) { // while printNodes exists
        std::cout << printNodes->value << std::endl;
        printNodes = printNodes->next; // goes to the next node
    }
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    //returns a pointer at the node at index.
    Node* getNode = head_;
    unsigned int counter = 0;
    //returns NULL if the index is invalid
    if (index < 0 || index>size_) {
        return NULL;
    }
    while ((getNode) && index > counter) {
        getNode = getNode -> next;
        ++counter;
    }
    return getNode;
}

bool DoublyLinkedList::insert_front(DataType value)
{
    //inserts a value at the beginning of the list
    //returns false if not successful
    //returns true if the insert is successful
    Node *node1 = new Node(value);
    if (!node1) { // if the new node does not exist, then the function will return false
        return false;
    }
    if (!head_) { // if the head does not exist
        head_ = node1;
        tail_ = node1;
    }
    else {
        head_ -> prev = node1;
        node1 -> next = head_;
        head_ = node1;
    }
    ++size_;
    return true; // returns true after inserting it into the front of the linkedlist
}

bool DoublyLinkedList::insert_back(DataType value)
{
    //inserts a value at the end of the list
    //returns false if the insert is not successful
    //returns true if the insert is successful
    Node *node1 = new Node(value);
    if (!node1){ // if the node does not exist, it will return false
        return false;
    }
    if (!head_) { // if the head does not exist, the node is now the head and the tail
        head_ = node1;
        tail_ = node1;
    }
    else {
        node1 -> prev = tail_;
        tail_ -> next = node1;
        tail_ = node1;
    }
    ++size_;
    return true; // returns true after inserting the new node into the list at the end
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    //inserts a value into the list at a given index
    //returns false if not successful
    //returns true if the insert is successful
    if (index < 0 || index > size_) { // if the index is out of range, return false
        return false;
    }
    if (index == 0) { // if the index is 0, then insert the value in the front
        return insert_front(value);
    }
    if (index == size()){ // if the index is the current size of the array, then put the node at the back of the linkedlist
        return insert_back(value);
    }
    else { //insert function for when it is a random node in the list (not the front or the ack
        Node* node1 = getNode(index);
        Node *node2 = new Node(value);
        if (!node2){
            return false;
        }
        node2 -> prev = node1-> prev;
        node1 -> prev -> next = node2;
        node2 -> next = node1;
        node1 -> prev = node2;
    }
    ++size_;
    return true; //return true since it inserted the node
}

bool DoublyLinkedList::remove(unsigned int index)
{
    //deletes the value from the list at the given index
    //returns true if successful and false otherwise
    if (index >= size() || index < 0) { //if it does not meet the boundaries, it will return false
        return false;
    }
    if (index == size()-1){ //if the index is currently the last node, remove the last node
        return remove_back();
    }
    if (index == 0) {
        return remove_front();
    }
    //code for removing the nodes when it is not the front or the back
    Node* newNode = getNode(index);
    newNode -> prev -> next = newNode -> next;
    newNode -> next -> prev = newNode -> prev;

    //after you remove it, you need to delete the newNode we made and decrease the size
    delete newNode;
    --size_;
    return true;
}

bool DoublyLinkedList::remove_front()
{
    //deletes the value from the beginning of the list
    //returns true if the removal is successful and false otherwise
    if (empty()) { // if the linked list is empty, you cannot remove the front
        return false;
    }

    Node* removeFront = head_;
    head_ = head_ -> next;
    delete removeFront;
    --size_;
    if(head_) { // if the head exists, set it to the previous
        head_ -> prev = NULL;
    }
    else { // set the tail to null if the head does not exist
        tail_ = NULL;
    }
    return true; // returns true once the front is removed
}

bool DoublyLinkedList::remove_back()
{
    //deletes the value at the end of the list
    //returns true if the removal is successful and false otherwise
    if (empty()){ //if the function is empty, you cannot remove the back
        return false;
    }
    Node* removeBack = tail_;
    tail_ = tail_ -> prev;
    delete removeBack; // delete the new node we created once we set the tail node to the previous one
    --size_;
    if (tail_) { // if the tail_ still exists, we want to set it to next
        tail_ -> next = NULL;
    }
    else { // if the tail doesnt exist, we want to set the head of the linked list to NULL
        head_ = NULL;
    }
    return true; // the function returns true once the node has been removed from the linked list
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    //replaces the value at the given index with the given value
    //returns true if successful and false otherwise
    DataType *replaceValue = &getNode(index) -> value; // we set the replaceValue to the address of the getNode index
    if (!replaceValue) { // if replace value does not exist, then we need to return false since there is nothing to return
        return false;
    }
    *replaceValue = value;
    return true; // we can return true once the value at a given index has been replaced
}
