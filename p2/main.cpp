#include <iostream>
#include <string>
#include <fstream>
#include "declaration.hpp"

int main(){
    std::string command;
    std::cin>>command;
    int size;
    double x0,y0,x1,y1;
    std::cin>>size;
    Hashmap h = Hashmap(size,x0,x1,y0,y1);
    std::cout<<"success"<<std::endl;
    while(true){
        std::cin>>command;
        //std::cout<<"cur command: "<< command<<std::endl;
        if(command == "INSERT"){
            std::string word;
            std::cin>>word;
            std::cout<<h.insert(word)<<std::endl;
        }
        else if(command == "PRINT"){
            int k;
           // std::cout<<"print command: "<<k<<std::endl;
            std::cin>>k;
            h.print(k);
        }
        else if (command == "TOKENIZE"){
            std::string word;
            std::cin>>word;
            h.tokenize(word, true);
        }
        else if (command == "RETRIEVE"){
            int idx;
            std::cin>>idx;
            h.retrieve(idx, true);
        }
        //turn token into words
        else if (command == "STOK"){
            std::cin>>command;
            while(command != "_DONE_"){
                h.tokenize(command, false);
                std::cin>>command;
            }
            std::cout<<std::endl;
        }
        else if (command == "TOKS"){
            int idx;
            std::cin>>idx;
            while(idx != -1){
                h.retrieve(idx, false);
                std::cin>>idx; 
            }
            std::cout<<std::endl;
        }
/*
	CITATION:
	
	This is an adaptation of Mike's resizable array posted on LEARN.
*/  
        else if(command == "READ"){
            std::string fileName;
            std::cin>>fileName;
            std::fstream fin(fileName.c_str());
            if(h.Readfile(fin)){
                std::cout<<"success"<<std::endl;
            }
            else{
                std::cout<<"failure"<<std::endl;
            }

        }
        else if(command == "EXIT"){
            break;
        }
    }
}