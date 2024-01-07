#ifndef Dugum_h
#define Dugum_h

class Dugum
{
public:
    Dugum(int veri,int* sayilar,int count);
    int veri;
    int* sayilar;
    int count;
    int yukseklik;
    Dugum* sol;
    Dugum* sag;
};

#endif