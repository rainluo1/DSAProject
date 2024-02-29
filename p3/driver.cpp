#include <iostream>
#include <string>
#include <exception>
#include "declaration.hpp"
using namespace std;
int main(){

    
     Quadtree *qt;
        string cmd;
        while(cin>>cmd){
        try{
            if(cmd == "INIT"){
                int m;
                double x0;
                double x1;
                double y0;
                double y1;
                cin>>m>>x0>>y0>>x1>>y1;
                if(x0>=x1 || y0>=y1){
                    throw ExceptionBad();
                }
                qt = new Quadtree(m,x0,x1,y0,y1);
            }
            if(cmd =="INSERT"){
                double x,y;
                cin>>x;
                cin>>y;
                qt->Insert(x,y);
            }
            if(cmd == "EXIT"){
                break;
            }
            if(cmd == "SEARCH"){
                double x,y,d;
                cin>>x>>y>>d;
                qt->Search(x,y,d);
            }
            if(cmd == "EXIT"){
                break;
            }
            if(cmd == "NUM"){
                cout<<qt->Num()<<endl;
            }
            if(cmd =="NEAREST"){
                double x,y;
                cin>>x>>y;
                qt->Nearest(x,y);
            }
            if(cmd =="RANGE"){
                double x1,x2,y1,y2;
                cin>>x1>>y1>>x2>>y2;
                if(x1>=x2 || y1>=y2){
                    throw ExceptionBad();
                }   
                qt->Range(x1,y1,x2,y2);
            }
        }
        catch(ExceptionBad l){
            cout<<l.msg()<<endl;
        }
    }
    delete qt;  
}