// The task is to write getopt function for arguments of types "--my-option-name my-option-val", "--my-option-name=my-option-val", "--my-boolean-option"
// parameters are strings, doubles, etc. Also parameter can be either required or optional
// --help should print info, optional parameters in []

// I did not dig much into error processing for the arguments (i.e. correct signed/unsingned/float type, numbers+characters, etc), so it will ignore, for example, junk data, or string parameter can just accep what comes after it, even if it is another parameter. That can be processed as additional checks in the corresponding process functions

// I think it is possible to do the same in Python, as dictionary:
/*
def p1( args ):
    whatever

def p2( more args):
    whatever

myDict={
    "P1": p1,
    "P2": p2,
    ...
    "Pn": pn
}

def myMain(name):
    myDict[name]()
    */

// Requires -std=c++11 to compile !


// check it with the following strings:
// ./a.out --arg1=1 --arg4=foo --arg2 2.1 --arg3 13 --arg5
// ./a.out --arg1=1 --arg4=foo --arg2 2.1 --arg3 13
// ./a.out --help
// ./a.out --arg1=bar --arg4=foo --arg2 2.1 --arg3 13 --arg5
// ./a.out --arg4=foo --arg5
// etc

#include<iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>


/******************** Global variables to be set */
// g++ initilizes global variables to 0 by default

int arg1;
float arg2; 
unsigned arg3;
std::string arg4;
bool arg5 = false;

/******************** Global variable triggers are stored as map of keys and lambda functions that set appropriate global variables */

// The idea behind this is to find the map entry by string key and then trigger function that will convert string data into appropriate format
// and assign global variable, thus avoiding vast decision trees and making addition of new elements easy. 

// int argument indicates whether we need to just display help
typedef std::function<int(std::string&,int&)> process_func; // the type of function that we will store in the map

typedef std::pair<process_func, int> map_data; // objects that out map will store. int variable will indicate whether parameter is required

typedef std::map<std::string, map_data > triggers_map; // we need to store map type to work with iterators

triggers_map global_variable_triggers; // map itself

// function to assign keys and processing functions
void initialize_global_variable_triggers(){
    
    // adding function to process global variable int arg1
    global_variable_triggers.insert(std::pair<std::string, std::pair<std::function<int(std::string&, int&)>, int> >
            ("--arg1",map_data([](std::string& s, int& show_help) { 
                                                            if (show_help){
                                                                std::cout<<"[--arg1=int]"<<std::endl;
                                                                return 0;
                                                            }
                                                            try {
                                                                arg1 = std::stoi(s); //setting global variable
                                                            } catch(std::exception const & e)  {
                                                                std::cout<<"error in arg1: " << e.what() <<std::endl;
                                                                return 1;
                                                            }
                                                            std::cout<<"OK: "<<s<<std::endl; //some output
                                                            return 0; // returning execution result
                                                          }
                                    , 0)
            )
                                   );
    
    //********************************************

    // adding function to process global variable float arg2
    global_variable_triggers.insert(std::pair<std::string, std::pair<std::function<int(std::string&, int&)>, int> >
            ("--arg2",map_data([](std::string& s, int& show_help) { 
                                                            if (show_help){
                                                                std::cout<<"[--arg2=float]"<<std::endl;
                                                                return 0;
                                                            }
                                                            try {
                                                                arg2 = std::stof(s); //setting global variable
                                                            } catch(std::exception const & e)  {
                                                                std::cout<<"error in arg2: " << e.what() <<std::endl;
                                                                return 1;
                                                            }
                                                            std::cout<<"OK: "<<s<<std::endl; //some output
                                                            return 0; // returning execution result
                                                          }
                                    , 0)
            )
                                   );
    //********************************************
    
    // adding function to process global variable unsigned arg3
    global_variable_triggers.insert(std::pair<std::string, std::pair<std::function<int(std::string&, int&)>, int> >
            ("--arg3",map_data([](std::string& s, int& show_help) {
                                                            if (show_help){
                                                                std::cout<<"[--arg3=uint]"<<std::endl;
                                                                return 0;
                                                            }
                                                            if(s[0]=='-') {std::cout<<"Error, arg3<0"<<std::endl; return 1;}
                                                            try {
                                                                arg3 = std::stoul(s); //setting global variable
                                                            } catch(std::exception const & e)  {
                                                                std::cout<<"error in arg3: " << e.what() <<std::endl;
                                                                return 1;
                                                            }  
                                                            std::cout<<"OK: "<<s<<std::endl; //some output
                                                            return 0; // returning execution result
                                                          }
                                    , 0)
            )
                                   );
    //********************************************
    // adding function to process global variable string arg4 (required)
    global_variable_triggers.insert(std::pair<std::string, std::pair<std::function<int(std::string&, int&)>, int> >
            ("--arg4",map_data([](std::string& s, int& show_help) { 
                                                            if (show_help){
                                                                std::cout<<"--arg4=string"<<std::endl;
                                                                return 0;
                                                            }
                                                            if (s.size()==0) {std::cout<<"Error, need arg4"<<std::endl; return 1;}
                                                            arg4 = s; //setting global variable
                                                            std::cout<<"OK: "<<s<<std::endl; //some output
                                                            return 0; // returning execution result
                                                          }
                                    , 1)
            )
                                   );
    //********************************************
    // adding function to process global variable bool arg5 (required)
    global_variable_triggers.insert(std::pair<std::string, std::pair<std::function<int(std::string&, int&)>, int> >
            ("--arg5",map_data([](std::string& s, int& show_help) { 
                                                            if (show_help){
                                                                std::cout<<"--arg5 bool (yes, required to be always true)"<<std::endl;
                                                                return 0;
                                                            }
                                                            arg5 = true; //setting global variable
                                                            std::cout<<"OK: "<<s<<std::endl; //some output
                                                            return 0; // returning execution result
                                                          }
                                    , 1)
            )
                                   );
    //********************************************







    
}









/********************* Main part */



std::string delimiter = "="; // delimiter that finishes the parameter name part of the argument

// function to split single argument string and get parameter names
// then store them in the same vector
// such complication is needed to process two cases equally:
// --my-option-name my-option-val
// --my-option-name=my-option-val
void get_param_names_and_values(std::vector<std::string> &allArgs){
    
    for (int i = 1; i<allArgs.size();i++){
        // split string where delimiter is and replace one entry in the container with two
        
        
        // search for delimiter
        size_t pos = 0;
        if ((pos = allArgs[i].find(delimiter)) != std::string::npos){
            // copy string before delimiter
            std::string param_name = allArgs[i].substr(0, pos);
            // copy rest of the string after dilimiter, if present
            std::string other;
            if (pos<allArgs[i].size()){
                other = allArgs[i].substr(pos+1, allArgs[i].size());
            }            
            
            
            // replace part of the container with one or two new parts
            allArgs[i] = param_name;
            if (!other.empty()) allArgs.insert(allArgs.begin()+i+1,other);
            // we will have one more iteration after that, as element appeared on i+1 position,
            // but let it be - we can now process something like --arg1=--arg2=val
            
        }
        
    }
    allArgs.push_back(""); // adding empty element to the end for compatibility
}


// check if there is --help argument, and then call help on all the commands
int seek_and_call_help(std::vector<std::string> &allArgs){
    
    if (std::find(allArgs.begin(),allArgs.end(),"--help") !=  allArgs.end()){
        
        int show_help = 1; //we need to have it as variable, as we are sending pointer
        std::string some_string = ""; // for compatibility or maybe is needed
        
        // if there is help flag
        triggers_map::iterator it; //declaring iterator and looping through the map
        for ( it = global_variable_triggers.begin(); it != global_variable_triggers.end(); it++ ){
            map_data d = it->second; // accessing stored object
            process_func f = d.first; // accessing function (if present)            
            if (f) {f(some_string,show_help);} // executing function with help flag
        }
        
       return 1; 
    }  else {
        return 0;
    }
}

// one dedicated loop to check presence of all the required arguments in the string
// I think this is OK, because precessing arguments further (by invoking their process functions) can be expensive
// So it is good to know beforehead that everything's OK
int check_presence_of_required(std::vector<std::string> &allArgs){
    
    int result = 0; //will be >0 if we have errors
    
    triggers_map::iterator it;
    // looping our map
    for ( it = global_variable_triggers.begin(); it != global_variable_triggers.end(); it++ ){
        map_data d = it->second; // accessing stored object
        std::string key = it->first; //corresponding key
        int required = d.second; // getting 'required' flag
        if (required == 1 && std::find(allArgs.begin(),allArgs.end(),key) ==  allArgs.end()){ //if required key is missing
            std::cout<<"Required key is missing: "<<std::endl;
            int show_help = 1;
            process_func f = d.first;
            if (f) f(key,show_help); // show help on missing key
            
            result++; // we have errors
        }
        
    }
    return result;
}






// general getopt function to process argument list
int my_getopt(std::vector<std::string> &allArgs){    
    
    //prepare parameter database
    initialize_global_variable_triggers();
    
    //split argument names and values
    get_param_names_and_values(allArgs);
    
    int processing_results = 0; // this variable will store the sum of results, returned by parameter processing functions
                                // there will be ones, if some paramaters are ill-formed
    
    
    
    //checking whether we need to show help
    int show_help = 0; 
    
    if (seek_and_call_help(allArgs)) {return 2;} // if there was help to display, then exit
    
    if (check_presence_of_required(allArgs)>0) {return 3;} // if there are missing required args, then exit
    
    
    
    
    //start processing arguments   
    
    for (int i = 1; i<allArgs.size()-1;i++){ //the last one is empty value, just for compatibility
        
        std::cout<<allArgs[i]<<std::endl; // output of what we have
        
        //The map::operator[] searches the data structure for a value corresponding to the given key, and returns a reference to it.
        //If it can't find one it transparently creates a default constructed element for it. (If you do not want this behaviour you can use the map::at function instead.)
        map_data d = global_variable_triggers[allArgs[i]]; // search for function in the map
        process_func f = d.first; // there won't be correct function if key is not present in the map
        if (f) {processing_results += f(allArgs[i+1],show_help);} // if returned object is not empty, execute it, passing next entry in list, which can be the value we need
        
        
        
        
        
        
    }
    if (processing_results > 0) {
        std::cout<<"There were errors in parameters, exiting"<<std::endl;
        return 1;
    } else {
        return 0;
    }
    
}




/***********************************************/


int main(int argc, char **argv){
  
  std::cout<<std::endl; // add space  
    
  std::string current_exec_name = argv[0]; // Name of the current exec program
  
  //copy all arguments into a container of strings
  std::vector<std::string> allArgs(argv, argv + argc);
  
  // invoking our getopt
  int init_result = my_getopt(allArgs);
  
  
  
  // printing global variables
  std::cout<<std::endl;
  std::cout<<"So we have global variable values:"<<std::endl;
  std::cout<<"arg1: "<<arg1<<std::endl;
  std::cout<<"arg2: "<<arg2<<std::endl;
  std::cout<<"arg3: "<<arg3<<std::endl;
  std::cout<<"arg4: "<<arg4<<std::endl;
  std::cout<<"arg5: "<<arg5<<std::endl;
  
  return 0;
}
