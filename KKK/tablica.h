#pragma once
#include <iostream>
#include "znak.h"
using namespace std;
//klasa obs�uguj�ca wybory kt�re dokonuje algorytm komputera + ustawienie znak�w w tablicy, sprawdzenie kt�ry z graczy wygra�
class Tablica {

private:
    Znak tab[20][20];
    int priorytety[20][20];

public:
    void ustaw_priorytet(char znak, char znak_p, int rozmiar, float waga);                                          //funkcja ustawiaj�ca priorytet
    void licz_wartosc_pri(int x, int y, int rozmiar, int kier_x, int kier_y, char znak, char znak_p, float waga);   //fumkcja obliczaj�ca warto�� priorytetu ustawionych znak�w 
    void szukaj_max(int &x, int &y, int rozmiar);                                                                   //funkcja szukaj�ca maksymalnego priorytetu
    void postaw_znak(int x, int y, char znak);                                                                      //funkcja ustawiaj�ca znak w odpowiednim miejscu tablicy            
    void zeruj_pri();                                                                                               //funkcja zeruj�ca priorytrty p�l
    bool sprawdz_kto_wygral(char znak, char znak_p, int rozmiar);                                                   //funkcja sprawdza czy mamy 5 jednakowych znak�w w linii                         
    int licz_ile (int x, int y, int rozmiar, int kier_x, int kier_y, char znak, char znak_p);                       //funkcja zwraca ile mamy ustawionych znak�w w linii     
    char sprawdz_znak(int x, int y);                                                                                //funkcja sprawdzaj�ca znak kt�ra zwraca nam inormacj� o tym jaki znak zosta� ustwionny w danej kom�rce
    void wyczysc();                                                                                                 //funkcja kt�ra czy�ci tablic� tab[x][y] ze znak�w 'X' i 'O'
    Tablica();
};





    
