#include "AVLAgaci.h"
#include <cmath>
#include <iomanip>
#include<iostream>
#include<queue>
using namespace std;
AVLAgaci::AVLAgaci()
{
    kok = 0;
}
AVLAgaci::~AVLAgaci()
{

}
bool AVLAgaci::varmi(int veri)
{
   return varmi(veri, kok);
}
void AVLAgaci::ekle(int eklenecek,int* sayilar,int count)
{
    kok = ekle(eklenecek, kok,sayilar,count);

}
void AVLAgaci::sil(int veri)
{
    kok = sil(veri, kok);
}
int AVLAgaci::yukseklik()
{
    return yukseklik(kok);
}
void AVLAgaci::preOrder() {
    preOrder(kok);
    cout << endl;
}
void AVLAgaci::yukseklikKontrol() {
    yukseklikKontrol(kok);
}
void AVLAgaci::yukseklikKontrol(Dugum* aktif) {
    
    if (aktif) {
       
        if (aktif->yukseklik < yukseklik(aktif)) {
            aktif->count--;
        }
        else if (aktif->yukseklik > yukseklik(aktif)) {

            for (int i = 1; i < aktif->count; i++) {
                aktif->sayilar[i - 1] = aktif->sayilar[i];
            }
        }
        yukseklikKontrol(aktif->sag);
        yukseklikKontrol(aktif->sol);
    }
    
}
void AVLAgaci::preOrder(Dugum* aktif)
{
    if (aktif)
    {
        
        cout << aktif->veri << " :  ";
        for (int j = 0; j < aktif->count; j++)
        {
                cout << aktif->sayilar[j] << "   ";
        }
        cout << endl;
        preOrder(aktif->sol);
        preOrder(aktif->sag);
    }
}

int AVLAgaci::yukseklik(Dugum* aktifDugum)
{
    if (aktifDugum)
    {
        return 1 + max(yukseklik(aktifDugum->sol),
            yukseklik(aktifDugum->sag));
    }
    return -1;
}
Dugum* AVLAgaci::ekle(int veri, Dugum* aktifDugum,int* sayilar,int count)
{
    int i = 0;
    if (aktifDugum == 0)
    {
        i++;
        
        return new Dugum(veri, sayilar, count);
        
    }

    else if (aktifDugum->veri < veri)
    {
        i++;

        aktifDugum->sag = ekle(veri, aktifDugum->sag, sayilar,count);
        aktifDugum->yukseklik = i;
        if (yukseklik(aktifDugum->sag) - yukseklik(aktifDugum->sol) > 1)
        {
            if (veri > aktifDugum->sag->veri)
                aktifDugum = solaDondur(aktifDugum);

            else
            {
                aktifDugum->sag = sagaDondur(aktifDugum->sag);
                aktifDugum = solaDondur(aktifDugum);
            }
        }
        
    }
    else if (aktifDugum->veri > veri)
    {
        i++;
        aktifDugum->sol = ekle(veri, aktifDugum->sol,sayilar,count);
        aktifDugum->yukseklik = i;
        if (yukseklik(aktifDugum->sol) - yukseklik(aktifDugum->sag) > 1)
        {

            if (veri < aktifDugum->sol->veri)
                aktifDugum = sagaDondur(aktifDugum);
            else
            {
                aktifDugum->sol = solaDondur(aktifDugum->sol);
                aktifDugum = sagaDondur(aktifDugum);
            }
        }
        
    }
    

    
    return aktifDugum;
}
Dugum* AVLAgaci::solaDondur(Dugum* buyukEbeveyn)
{
    Dugum* sagCocuk = buyukEbeveyn->sag;
    buyukEbeveyn->sag = sagCocuk->sol;
    sagCocuk->sol = buyukEbeveyn;
    return sagCocuk;
}
Dugum* AVLAgaci::sagaDondur(Dugum* buyukEbeveyn)
{
    Dugum* solCocuk = buyukEbeveyn->sol;
    buyukEbeveyn->sol = solCocuk->sag;
    solCocuk->sag = buyukEbeveyn;
    return solCocuk;
}
int AVLAgaci::maxDeger(Dugum* aktif)
{
    if (aktif->sag)
        return maxDeger(aktif->sag);

    return aktif->veri;
}
bool AVLAgaci::varmi(int aranan, Dugum* aktif)
{
    if (aktif->veri < aranan)
    {
        if (aktif->sag)
            return varmi(aranan, aktif->sag);
        else
            return 0;
    }
    else if (aktif->veri > aranan)
    {
        if (aktif->sol)
            return varmi(aranan, aktif->sol);
        return 0;
    }
    else
    {
        return aktif;
    }
}
Dugum* AVLAgaci::sil(int veri, Dugum* aktif)
{
    if (aktif == 0)
        return 0;

    if (veri < aktif->veri)
    {
        aktif->sol = sil(veri, aktif->sol);
    }
    else if (veri > aktif->veri)
    {
        aktif->sag = sil(veri, aktif->sag);
    }
    else//aradığımız düğümü bulduk
    {
        if (aktif->sol == 0 && aktif->sag == 0)
        {
            delete aktif;
            aktif = 0;
        }
        else if (aktif->sol == 0)
        {
            Dugum* sil = aktif->sag;
            *aktif = *aktif->sag;
            delete sil;
        }
        else if (aktif->sag == 0)
        {
            Dugum* sil = aktif->sol;
            *aktif = *aktif->sol;
            delete sil;
        }
        else
        {
            aktif->veri = minDeger(aktif->sag);
            sil(aktif->veri, aktif->sag);
        }


    }


    int denge = dengesizlikYonu(aktif);

    if (denge > 1) //sol tarafta dengesizlik
    {
        //sol sol dengesizliği
        if (dengesizlikYonu(aktif->sol) >= 0)
        {
            return sagaDondur(aktif);
        }
        //sol sag durumu
        if (dengesizlikYonu(aktif->sol) < 0)
        {
            aktif->sol = solaDondur(aktif->sol);
            return sagaDondur(aktif);
        }
    }
    else if (denge < -1)//sag tarafta dengesizlik
    {
        //sağ sağ durumu
        if (dengesizlikYonu(aktif->sag) <= 0)
        {
            return solaDondur(aktif);
        }
        //sağ sol durumu
        if (dengesizlikYonu(aktif->sag) > 0)
        {
            aktif->sag = sagaDondur(aktif->sag);
            return solaDondur(aktif);
        }
    }
    return aktif;
}
int AVLAgaci::minDeger(Dugum* aktif)
{
    if (aktif->sol)
        return maxDeger(aktif->sol);

    return aktif->veri;
}
void AVLAgaci::boslukBirak(int adet) {
    int baslangicBosluk = pow(2, adet) - 1;
    for (int i = 0; i < baslangicBosluk; i++)
        cout << "  ";
}
int AVLAgaci::dengesizlikYonu(Dugum* aktif)
{
    if (aktif == 0)
        return 0;
    return yukseklik(aktif->sol) - yukseklik(aktif->sag);
}
