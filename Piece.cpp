#include <iostream>
#include"Piece.h"
#include<string>

using namespace std;
    Piece::Piece():x(0),y(0),nom_piece("XX"),color("Null"){

    }
    Piece::Piece(int abs,int ord,string n_piece,string col):x(abs),y(ord),nom_piece(n_piece),color(col){

    }
    string Piece::getNomPiece(){
        return nom_piece;
    }
    int Piece::getAbs(){
        return x;
    }
    int Piece::getOrd(){
        return y;
    };
    string Piece::getColor(){
        return color;
    }
    void Piece::setAbs(int n){
        x=n;
    };
    void Piece::setOrd(int n){
        y=n;
    };
    void Piece::setNomPiece(std::string str){
        nom_piece=str;
    };
    void Piece::setColor(std::string str){
        color=str;
    };
    void Piece::deplacement(std::string str){

    };
    void Piece::promotion(std::string str){

    };
    void Piece::elimner(std::string str){

    };

    void Piece::info(){
        cout<<" x :"<<x<<"\n y : "<<y<<"\n color : "<<color<<"\n nom_piece : "<<nom_piece<<"\n";
    }
