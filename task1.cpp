#include<iostream>
#include<vector>
#include<math.h>

// The problem is to count numbers from 1 to N and factorize each one. 
// It means, that numbers aren't supposed to be big and usage of some advanced prime factorization algorithms 
// like Pollard’s Rho is not beneficial. Trial division is used here:

// function that factorizes one positive integer (size_t is unsigned type)
// result is written to std::vector container


// this require -std=c++11 to compile!

std::vector< std::vector<size_t> > divisors; // matrix containing database of divisors for each number

// function that factorizes one number by division and database search
void factorize_to_primes(size_t number){
    
    //add factorized number to the database
    std::vector<size_t> current;
    divisors.push_back(current);
    
    size_t half = number/2;//(size_t) sqrt(number); //prime divisors of N are located in between 1..N/2; (NOT 1..sqrt(N) : see 6 or 10 for example)
    // note, that we have already passed all the numbers 1..N/2 for their divisors
    
    // check for divisors in the database, starting from the biggest
    for(size_t i = half; i>0; i--){ // >0 for compatibility
        if (number % i == 0){ // if i is a divisor
            if (divisors[i-1].size() == 1) {//if it does not have any divisors recorded in the database, except 1 and itself                                        
                //record it as prime divisor
                divisors[number-1].push_back(i);
            }
        }
        
    }
    
}

// proposed function to factorize numbers from 1 to N
void facrorize_sequence(size_t number){
    
    if (number == 0) return; //in this case we have nothing to do
    
    // adding 1 as prime number, just to leave less code in the function body
    std::vector<size_t> one;
    one.push_back(1);    
    divisors.push_back(one);    
    
    if (number > 1){ // if we have more to do
        
        // main loop, from 2 up to number requested
        for (int num = 2; num <= number; num++){
            factorize_to_primes(num);
        }
        
        // one more pass to make results neat (include actual number)
        // we cannot do that in function above, because checking for 2 (instead of 1) divisors in the database 
        // can be errorneous: for example 4 will have two: 2,1.
        // So let's do one more pass instead of extra checks
        for (int num = 2; num <= number; num++){
            if (divisors[num-1].size() == 1) {divisors[num-1].push_back(num);}
        }
    }
    
}

//print database number by number
void print_results(){
    
    for (int i=0;i<divisors.size();i++){
        
        std::cout<<i+1<<": ";
        for (int j=0;j<divisors[i].size();j++){
            std::cout<<divisors[i][j]<<" ";
        }
        std::cout<<std::endl;
        
    }
}


int main(){
    
        
    
    facrorize_sequence(30);
    
    print_results();
    
    return 0;
}