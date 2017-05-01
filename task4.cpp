// Here we have single-linked list 1->2->...->N. We want to reorder it in such way:
// 1->N->2->N-1->...
// Example: 1-2-3-4-5-6-7-8  =>  1-8-2-7-3-6-4-5

// Efficient solution would be to split list in half and reverse second part
// There are examples that suppose to do it in O(n) in this way:
// 1. Find middle element using tortoise and hare (2N) operations
// 2. Invert second half of the list: 5*N/2 = 2N +N/2 operations 
// 3. Create new list from these two: 6*N/2 = 3N(we need to do checks constantly if we reached the middle of original list)
// Total: 2N + 2N + N/2 + 3N = 7N+N/2 operations



// This requires -std=c++11 to compile!




#include<iostream>


class Node{  //Node of our list. We will use our own simple implementation instead of what STL has
public:
    int value;
    Node* next = nullptr;
    
    ~Node(){
        if (next != nullptr) {
            delete next;
        }
    }
};

Node* begin=nullptr; //That is the beginning of our list

//simple function to add node element to the end of existing list
int add_node(Node* node, int value){
    
    if (node==nullptr) {
        std::cout<<"Address is null"<<std::endl; 
        return 1;
    }
    if (node->next != nullptr){
        std::cout<<"There is next element"<<std::endl; 
        return 1;
    }
    
    Node* newnode = new Node;
    newnode->value = value;
    
    node->next = newnode;
    
    return 0;    
}

//simple function to find last element in the list
Node* find_last(Node* start){
    
    if (start==nullptr) {
        std::cout<<"Address is null"<<std::endl; 
        return nullptr;
    }
    
    Node* current = start;
    // search for the last node that does not have successor
    while(current->next != nullptr){
        current = current->next;
    }
    
    return current;
    
}

// simple function to fill our list with a sequence 1...N
void fill_list_with_sequence(Node* &start, unsigned N){
    
    if (start!=nullptr) {
        std::cout<<"List is not empty"<<std::endl; 
        return;
    }
    // N is always >=0
    Node* current = new Node;
    current->value = 0;
    start = current;
    
    if (N>0){
        
        // fill the rest of the list
        for (int i=1;i<=N;i++){
            
            add_node(current,i);
            current = current->next;
        }
    }
}


// simple function to print our list
void print_list(Node* start){
    
    if (start==nullptr) {
        std::cout<<"Address is null"<<std::endl; 
        return;
    }
    
    Node* current = start;
    
    // loop list
    while (current != nullptr){
       std::cout<<current->value<<" ";
       current=current->next;
    }
    std::cout<<std::endl;
}

// find middle of the list, it has 2N operations
Node* find_middle(Node* start){
    
    if (start==nullptr) {
        std::cout<<"Address is null"<<std::endl; 
        return nullptr;
    }
    
    Node* search_middle = start;
    Node* search_end = start;
    
    while (true){
        if(search_end->next != nullptr){ //N/2
            if(search_end->next->next != nullptr){ //N/2
                //advance in different steps
                search_middle=search_middle->next; //N/2
                search_end=search_end->next->next; //N/2
            } else break;
        } else break;
    }
    
    return search_middle;
    
}


// The function to reverse list, it is 5*N operations
Node* reverse_list(Node* start){
    
    if (start==nullptr) {
        std::cout<<"Address is null"<<std::endl; 
        return nullptr;
    }
    
    Node* list_residual = start->next; //the part of the list that is still not arranged
    Node* current = start; //current beginning of the rearranged part
    current->next = nullptr; //cut to avoid infinite loop
    Node* temp;
    
    while (list_residual != nullptr){  // take first element from old sequence and attach new sequence to it
        temp = list_residual;
        list_residual = list_residual->next;
        temp->next = current;
        current = temp;
    }
    
    return current;
}

// Requested function to rearrange existing list
void rearrange_list(Node* start){
    
    if (start==nullptr) {
        std::cout<<"Address is null"<<std::endl; 
        return;
    }
    
    // find middle of the list, where we should stop
    Node* middle = find_middle(start); //2N
    
    // find reversed second part of the list
    Node* tail = reverse_list(middle->next); //5*(N/2)
    //after this list should be truncated
    // because tail has its own order now
    middle->next = nullptr;
    
    Node* current = start;
    Node* temp;
    //start concatenation
    //take into account that middle part is bigger

    while(tail!=nullptr){ //6*(N/2)
        
        temp = current->next;        
        current->next = tail;        
        tail = tail->next;        
        current->next->next = temp;
        current = temp;
        
    }
    
}


int main(){
    
    
    
    fill_list_with_sequence(begin, 11);
    
    print_list(begin);
    
    rearrange_list(begin);
    
    print_list(begin);
    
    delete begin;
    
    return 0;
}