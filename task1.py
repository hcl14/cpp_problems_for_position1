# -*- coding: utf-8 -*-

# The problem is to count numbers from 1 to N and factorize each one. 
# It means, that numbers aren't supposed to be big and usage of some advanced prime factorization algorithms 
# like Pollard’s Rho is not beneficial. Trial division is used here:

# function that factorizes one positive integer (size_t is unsigned type)
# result is written to std::vector container
 
import numpy as np

# we need an object array that contains lists of different length
divisors=np.empty((1,),dtype=object) #array of lists containing database of divisors for each number
# unfortunately, we lose numpy speedup this way, another memory-costy variant is to initialize big matrix Nx(N/2) and have zeros there


# function that factorizes one number by division and database search
def factorize_to_primes( number ):
    #add factorized number to the database
    
    # np.append(divisors,[], axis=0) # does not work
    current_entry = np.empty((1,),dtype=object)    
    global divisors
    divisors = np.concatenate((divisors,current_entry))
    divisors[divisors.shape[0]-1] = []

    
    half = number/2 #prime divisors of N are located in between 1..N/2; (NOT 1..sqrt(N) : see 6 or 10 for example)
    #note, that we have already passed all the numbers 1..N/2 for their divisors
    
    #check for divisors in the database, starting from the biggest
    for i in range(half,0,-1):
        # if i is a divisor
        if number % i == 0:            
            # if it does not have any divisors recorded in the database, except 1 and itself     
            if len(divisors[i-1]) == 1:
                #record it as prime divisor
                divisors[number-1].append(i)



# proposed function to factorize numbers from 1 to N
def factorize_sequence(number):
    if number==0:
        return 1
    # adding 1 as prime number, just to leave less code in the function body
    divisors[0] = []
    divisors[0].append(1)
    
    #if we have more to do
    if number>1:
        # main loop, from 2 up to number requested
        for i in range(2,number+1):
            factorize_to_primes(i)
        
        #one more pass to make results neat (include actual number)
        #we cannot do that in function above, because checking for 2 (instead of 1) divisors in the database 
        #can be errorneous: for example 4 will have two: 2,1.
        #So let's do one more pass instead of extra checks
        for i in range(2,number+1):
            if len(divisors[i-1]) == 1:
                divisors[i-1].append(i)
    
    return 0;


def print_results():
    for i in range(0,divisors.shape[0]):
        print i+1, ": ", divisors[i] 


if __name__ == "__main__":
    
    
    factorize_sequence(12)
    print_results()