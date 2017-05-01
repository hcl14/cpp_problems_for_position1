// We need to divide vector of size N into M<N equal parts. Extra elements can be located at the beginning and at the end of segmented area,
// and the size of these tails should be minimal
// The result should be indices of beginning and the end of each part 

// Needs -std=c++11 option to compile !

#include<iostream>
#include<vector>
#include<algorithm>


int main(){
    
    std::vector<int> data(31, 0); // our vector to split
    
    int M = 7; // number of parts to split
    
    
    
    
    std::vector<int> beginnings(M); // indices of the beginning of each chunk
    std::vector<int> ends(M);// indices of the end of each chunk
    
    int extra = data.size() % M; // number of extra elements
    int lesser_tail = extra % 2; //size of lesser left tail
    int step = data.size() / M; //length of one chunk
    
    // filling data vectors
    int n = -1;
    std::generate(beginnings.begin(), beginnings.end(), [&n, &step, &lesser_tail]{n++; return (lesser_tail + n*step); });
    n = 0;
    std::generate(ends.begin(), ends.end(), [&n, &step, &lesser_tail]{n++; return (lesser_tail + n*step-1); });
    
    
    // output
    std::cout<<"Array dims: 0.."<<data.size()-1<<std::endl;
    std::cout<<"Left tail: "<<lesser_tail<<std::endl;
    std::cout<<"step: "<<step<<std::endl;
    
    for(int i=0;i<M;i++){
        std::cout<<beginnings[i]<<" "<<ends[i]<<std::endl;
    }
    
    
    return 0;
    
}
