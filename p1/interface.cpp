#include <iostream>
#include "declaration.hpp"
//author: Rain Luo 20997318
int main()
{
    std::string input = "";
    std::cin >> input;
    Linked_list listOfKids;
    while (true)
    {
        if(input == "SPAWN"){
            double x,y;
            std::cin>>x;
            std::cin>>y;  
            listOfKids.callSpawn(x,y);
        }
        if(input == "NUM"){
            listOfKids.getNum();
        }
        if(input == "TIME"){
            double t =0;
            std::cin>>t;
            listOfKids.move(t);
        }
        if(input == "PRT"){
            double d;
            std::cin>>d;
            listOfKids.printLocation(d);
        }
        if(input == "OVER"){
            listOfKids.over();
            break;
        }
        std::cin>>input;
    }
}