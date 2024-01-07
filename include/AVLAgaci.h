#ifndef AVLAgaci_h
#define AVLAgaci_h
#include<iostream>
#include "Dugum.h"
using namespace std;

class AVLAgaci
{
public:

	AVLAgaci();

	~AVLAgaci();
	bool varmi(int veri);
	void ekle(int veri,int* sayilar,int count);
	void sil(int veri);
	friend ostream& operator<<(ostream& os, AVLAgaci& kuyruk);
	int yukseklik();
	void preOrder();
	void boslukBirak(int adet);
	void yukseklikKontrol();
private:
	void yukseklikKontrol(Dugum* aktif);
	int dengesizlikYonu(Dugum* aktif);
	Dugum* solaDondur(Dugum* dugum);
	Dugum* sagaDondur(Dugum* dugum);
	int minDeger(Dugum* aktif);
	void preOrder(Dugum* aktif);
	int yukseklik(Dugum* aktifDugum);
	Dugum* ekle(int veri, Dugum* aktifDugum,int* sayilar,int count);
	bool varmi(int aranan, Dugum* aktif);
	Dugum* sil(int veri, Dugum* aktif);
	int maxDeger(Dugum* aktif);
	Dugum* kok;
};
//diger fonksiyonlar eklenecek
#endif