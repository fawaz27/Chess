#ifndef DEF_POINT
#define DEF_POINT

#include<string>
class Point{
    private:
        int x;
        int y;
    public:
        Point();
        Point(int abs,int ord);
        int getAbs();
        int getOrd();
        void setAbs(int n);
        void setOrd(int n);
        void info();
};
#endif