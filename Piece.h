#ifndef DEF_PIECE
#define DEF_PIECE

#include<string>
class Piece{
    private:
        int x;
        int y;
        std::string nom_piece;
        std::string color;
    public:
    Piece();
    Piece(int abs,int ord,std::string n_piece,std::string col);
    std::string getNomPiece();
    int getAbs();
    int getOrd();
    std::string getColor();
    void setAbs(int n);
    void setOrd(int n);
    void setColor(std::string str);
    void setNomPiece(std::string str);
    void deplacement(std::string str);
    void promotion(std::string str);
    void elimner(std::string str);
    void info();
};


#endif