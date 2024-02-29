#include <iostream>
#include <cmath>
int main(){

    int x =3;
    int y =4;
    int t =5;
    change(t, x,y);
}

void change(int time, int a, int b){
    a = time*cos(atan2(a,b));
    b= time*sin(atan2(a,b));
}