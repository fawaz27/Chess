#include <iostream>
#include"Point.h"
#include<string>

using namespace std;

    Point::Point():x(0),y(0){
        
    };
    Point::Point(int abs,int ord):x(abs),y(ord){

    };
    int Point::getAbs(){
        return x;
    };
    int Point::getOrd(){
        return y;
    };
    void Point::setAbs(int n){
        x=n;
    };
    void Point::setOrd(int n){
        y=n;
    };
    void Point::info(){
        cout<<" x :"<<x<<"\n y :"<<y<<"\n";
    }
