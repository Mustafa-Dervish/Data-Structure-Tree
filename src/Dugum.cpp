#include "Dugum.h"

Dugum::Dugum(int veri,int* sayilar,int count)
{
    this->veri = veri;
    this->sayilar = sayilar;
    this->count = count;
    sol = sag = 0;
    yukseklik = 1;
}