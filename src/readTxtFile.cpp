#include <iostream>
#include <fstream>
#include <string>
#include "readTxtFile.h"
#include "AVLAgaci.h"
using namespace std;

string tp;
int rows = 10000, col = 200;
int i = 0, j = 0, m = 0;
int* countM = new int[rows];
int** x = new int* [rows];

readTxtFile::~readTxtFile() {
    delete[] x;
}

void readTxtFile::readTxt() {
    AVLAgaci Agac;
    fstream newfile;
    newfile.open("Sayilar.txt", ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()) {
        char mychar;
        while (newfile) {
            mychar = newfile.get();
            tp = tp + mychar;
        }
    }  
    string temp;
   for (int i = 0; i < rows; i++)
       {
           x[i] = new int[col];//col
       }
    while (i != tp.size()) {

        if (tp[i] == '\n') {
            x[m][j] = stoi(temp);
            j++;
            countM[m] = j;
            j=0;
            m++;
            if (m == rows) {
                resizeRows();
            }
            
            temp = "";
        }
        else if (tp[i] == ' ')
        {
            x[m][j] = stoi(temp);
            j++;
            countM[m] = j;
            if (j == col) {
                resizeCol();
            }
            temp = "";
        }
        else if(i==tp.size()-1){
            temp = temp + tp[i+1];
            x[m][j] = stoi(temp);
            j++;
            if (j == col) {
                resizeCol();
            }
            m++;
            countM[m] = j;
            temp = "";
        }
        else {
            temp = temp + tp[i];
        }
        i++;  
    }
   
    RadixSort();
    int toplam;
    for (int i = 0; i < m; i++) {
        toplam = 0;
        for (int j = 0; j < countM[i]; j++) {
            toplam += x[i][j];
        }
      Agac.ekle(toplam, x[i],countM[i]);
      Agac.yukseklikKontrol();
    }
   Agac.preOrder();/*
   /* for (int i = 0; i < m; i++)
   {
       for (int j = 0; j < countM[i]+1; j++)
       {
           cout << x[i][j] << "  ";
       }
       cout << endl;
   }*/
}

void readTxtFile::resizeRows() {
    rows = rows*2;
    int* newCountM = new int[rows];
    for (int i = 0; i < sizeof countM / sizeof countM[0]; i++)
    {
        newCountM[i] = countM[i];
    }
    delete []countM;
    countM = newCountM;
    newCountM = NULL;
    int** newX = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        newX[i] = new int[col];//col
    }
    
    for (int i = 0; i < m; i++)
    {
        
        for (int j = 0; j < countM[i] + 1; j++)
        {
            newX[i][j] = x[i][j];
        }
    }
    delete[] x;
    x = newX;
    newX = NULL;
}

void readTxtFile::resizeCol() {
    col = col*2;
    int** newX = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        newX[i] = new int[col];//col
    }
    
       
        for (int j = 0; j < countM[0]+1; j++)
        {
            newX[0][j] = x[0][j];

        }
    
    for (int i = 0; i < m+1; i++)
    {
        
        for (int j = 0; j < countM[i] ; j++)
        {
            newX[i][j] = x[i][j];

        }
    }
    delete[] x;
    x = newX;
    newX = NULL;
}


int readTxtFile::getMax(int arr[], int sizem)
{  

    int max = arr[0];
    for (int i = 0; i < sizem; i++) {
        
            if (arr[i] > max) {
                max = arr[i];
            }
    }
  //  cout << "Max :" << max<<endl;
    return max;
}

void readTxtFile::CountingSort(int arr[], int n, int exp)
{
        int* output=new int[n]; // output array
        int i, count[10] = { 0 };
        
        // Store count of occurrences in count[]
        for (i = 0; i < n; i++)
            count[(arr[i] / exp) % 10]++;

        // Change count[i] so that count[i] now contains actual
        // position of this digit in output[]
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];

        // Build the output array
        for (i = n - 1; i >= 0; i--) {
            
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        // Copy the output array to arr[], so that arr[] now
        // contains sorted numbers according to current digit
        for (i = 0; i < n; i++)
            arr[i] = output[i];
            
    

}

void readTxtFile::RadixSort() {
    for (int i = 0; i < m; i++) {
        int max = readTxtFile::getMax(x[i], countM[i] + 1);
        for (int div = 1; max / div > 0; div *= 10)
          CountingSort(x[i], countM[i], div);
        
    }

}
