// STACKS! :) 

#include <iostream>
#include "dynamic-stack.h"

DynamicStack::DynamicStack() { // constructor with preset value of 16
    init_capacity_ = 16;
    capacity_ = 16;
    items_ = new StackItem [capacity_];
    size_ = 0;
}

DynamicStack::DynamicStack(unsigned int capacity){ // constructor with capacity passed as variable
    init_capacity_ = capacity;
    capacity_ = capacity;
    items_ = new StackItem [capacity_];
    size_ = 0;
}

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -9999; // used for empty stack, is set to the value of -9999

DynamicStack::~DynamicStack() { // destructor which deletes the dynamic stack
    delete [] items_;
}

bool DynamicStack::empty() const { // checks if the stack is empty
    if (size_ == 0) { // if size is zero returns true
        return true;
    }
    else { // otherwise returns false
        return false;
    }

}

int DynamicStack::size() const { // returns the size of the dynamic stack
    return size_;
}

void DynamicStack::push(StackItem value) { // function for pushing
    if (size_ == capacity_){
        int *newItemsArray = new int [2*capacity_]; // create a new stack if the stack is full
        capacity_ = 2*capacity_;
        for(int i = 0; i < size_; i++){ //loops through the stack
            newItemsArray[i] = items_[i]; // adds previous items into a new stack
        }
        int *temp = items_;
        items_ = newItemsArray;
        delete [] temp; // deletes the temporary array
    }
    if (size_ >= 0 && size_ < capacity_){ // if statement to add the stackitem value to the stack
        items_[size_] = value;
        size_++;
    }
}

DynamicStack::StackItem DynamicStack::pop() { // function for popping
    if(size_ == 0){
        return EMPTY_STACK;   // returns the empty stack
    }
    if (size_ < 0){
        return 0;
    }
    else{
        int popped_value = items_[size_-1]; //pops the top value
        size_--;//decreases size
        if(size_<capacity_/6) { // if the size is less than the capacity divided by 6 (too big)
            capacity_ = capacity_/2; // decrease capacity by half
        }
        return popped_value;
    }
}

DynamicStack::StackItem DynamicStack::peek() const { // function to peek the top of the stack
    //checks if there is anything in the stack
    if(size_ == 0){ // if the size is 0 it is an empty stack
        std::cout<<"Empty stack!" <<std::endl;
        return EMPTY_STACK;   //returns that there is an empty stack
    }
    else{
        int peeked_value = items_[size_-1]; // peeks the item that is closest to the top
        return peeked_value; // returns the peeked value
    }

}

void DynamicStack::print() const { // this function prints the stack
    //check if there is anything to print
    if(size_ == 0){ // if the stack is empty it outputs a message
        std::cout<<"Empty stack! Cannot print." <<std::endl;
        return; // returns
    }
    else{ // otherwise it prints the stack
        for(int i = size_ - 1; i >= 0; i--){ // loops through the output n times
            std::cout<<items_[i]<<std::endl;
        }
        std::cout<<std::endl;
    }
}

// QUEUES!! :) 

#include "circular-queue.h"
#include <iostream>

CircularQueue::CircularQueue() { // circular queue constructor without capacity given
    //set to 16 by default
    capacity_ = 16;
    items_ = new QueueItem [capacity_];
    size_ = 0;
    head_ = 0;
    tail_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity) {// circular queue constructor with capacity given
    // initial capacity given as parameter
    capacity_ = capacity;
    items_ = new QueueItem [capacity_];
    size_ = 0;
    head_ = 0;
    tail_ = 0;
}
const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -9999; // empty queue variable

CircularQueue::~CircularQueue() { // circular queue destructor
    delete [] items_;
}

bool CircularQueue::empty() const { // function for detecting if the queue is empty or not
    if (size_ == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularQueue::full() const { // lets you know if the queue is full or not
    if (size_ == capacity_) {
        return true;
    }
    else {
        return false;
    }
}

int CircularQueue::size() const { // returns the size of the queue
    return size_;
}

bool CircularQueue::enqueue(QueueItem value) {
    //check if queue is full
    if (size_ == capacity_) {
        std::cout<<"Sorry! The Queue is full and means that you cannot Enqueue an item."<<std::endl;
        return false;
    }
        //enqueue at iRear
        //inserts the value at the rear of the queue after the last item and returns true
        if (head_ == tail_ && (head_ == 0)) {
            items_[tail_] = value;
            head_ = 0;
            tail_ = 1;
            size_++;
            return true;
        }
        else {
            items_[tail_] = value;
            tail_++;
            size_++;
            return true;
        }
}

CircularQueue::QueueItem CircularQueue::dequeue() {
    //check if there is anything to dequeue
    if (size_ == 0){
        std::cout<<"Sorry! The queue is empty and therefore you cannot dequeue the circular queue."<<std::endl;
        return EMPTY_QUEUE;
    }
        // dequeue from iFront
        // removes the item from the front of the queue and returns it
        int return_dequeue = items_[head_];
        items_[head_]= -1;
        head_++;
        size_--;
        return return_dequeue;
}

CircularQueue::QueueItem CircularQueue::peek() const {
    //check if there is any node
    if (size_ == 0) {
        std::cout<<"Sorry! The queue is empty which means you cannot peek it!"<<std::endl;
        return EMPTY_QUEUE;
    }
    else {
        ///peek

        // returns the value at the front of the queue without removing it from the queue
        int peeked_value = items_[head_];
        return peeked_value;
    }
}

void CircularQueue::print() const {
    //if statement to check if there is any value that exists to print
    if (size_ == 0){
        std::cout<<"Sorry! The queue is empty which means you cannot print anything."<<std::endl;
        return;
    }
    else {
        // prints the circular array queue items sequentially and in order
        for (int index = head_; index <= size_; index++){
            std::cout<<items_[index];
        }
    }
}

