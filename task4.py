# -*- coding: utf-8 -*-

# Here we have single-linked list 1->2->...->N. We want to reorder it in such way:
# 1->N->2->N-1->...
# Example: 1-2-3-4-5-6-7-8  =>  1-8-2-7-3-6-4-5

# Efficient solution would be to split list in half and reverse second part
# There are examples that suppose to do it in O(n) in this way:
# 1. Find middle element using tortoise and hare (2N) operations
# 2. Invert second half of the list: 5*N/2 = 2N +N/2 operations 
# 3. Create new list from these two: 6*N/2 = 3N(we need to do checks constantly if we reached the middle of original list)
# Total: 2N + 2N + N/2 + 3N = 7N+N/2 operations

################ Basic single-linked list implementation taken from here: http://ls.pwd.io/2014/08/singly-and-doubly-linked-lists-in-python/

class Node(object):
 
    def __init__(self, data, next):
        self.data = data
        self.next = next
 
 
class SingleList(object):
 
    head = None
    tail = None # we won't use this one, to have exactly the same task as in C++ version
 
    def show(self):
        print "Showing list data:"
        current_node = self.head
        while current_node is not None:
            print current_node.data, " -> ",
            current_node = current_node.next
        print None
 
    def append(self, data):
        node = Node(data, None)
        if self.head is None:
            self.head = self.tail = node
        else:
            self.tail.next = node
        self.tail = node
 
    def remove(self, node_value):
        current_node = self.head
        previous_node = None
        while current_node is not None:
            if current_node.data == node_value:
                # if this is the first node (head)
                if previous_node is not None:
                    previous_node.next = current_node.next
                else:
                    self.head = current_node.next
 
            # needed for the next iteration
            previous_node = current_node
            current_node = current_node.next

    ################ New functions:
        
    # find middle of the list, it has 2N operations
    def find_middle(self):
        
        if self.head is None:
            print "List is empty"
            return None
        
        search_middle = self.head;
        search_end = self.head;
        
        while True:
            if search_end.next is not None:
                if search_end.next.next is not None:
                    #advance in different steps
                    search_middle=search_middle.next;
                    search_end=search_end.next.next;
                else:
                    break
            else:
                break
        return search_middle
    
    # fill list with sequence of numbers
    def fill_list_with_sequence(self, N):
        if N<0:
            print "Wrong number"
            return
        for i in range(0,N):
            self.append(i)
        
    # print list
    def print_list(self):
        if self.head is None:
            print "List is empty"
            return
        
        current_node = self.head
        while current_node is not None:
            print current_node.data,
            current_node = current_node.next
        print #line break
    
    #The function to reverse list, it is 5*N operations
    def __reversesublist(self,start):
        
        if self.head is None:
            print "List is empty"
            return None
        
        list_residual = start.next #the part of the list that is still not arranged
        current = start #current beginning of the rearranged part
        current.next = None #cut to avoid infinite loop
        
        while list_residual is not None:
            #take first element from old sequence and attach new sequence to it
            temp = list_residual
            list_residual = list_residual.next
            temp.next = current
            current = temp
            
        return current
    
    # Requested function to rearrange existing list
    def rearrange_list(self):
        
        if self.head is None:
            print "List is empty"
            return None
        
        #find middle of the list, where we should stop
        middle = self.find_middle() #2N
        
        #find reversed second part of the list
        tail = self.__reversesublist(middle.next) #5*(N/2)
        #after this list should be truncated
        #because tail has its own order now
        middle.next = None
        
        current = self.head
        
        #start concatenation
        #take into account that middle part is bigger
        
        while tail is not None:
            #6*(N/2)
            temp = current.next
            current.next = tail        
            tail = tail.next
            current.next.next = temp
            current = temp
        
        
#################################################

# main function

if __name__ == "__main__":
    
    s = SingleList()
    s.fill_list_with_sequence(11)
    s.print_list()
    
    s.rearrange_list()
    s.print_list()
    
        
                        

