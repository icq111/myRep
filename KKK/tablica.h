#pragma once
#include <iostream>
#include "znak.h"
using namespace std;
//klasa obs³uguj¹ca wybory które dokonuje algorytm komputera + ustawienie znaków w tablicy, sprawdzenie który z graczy wygra³
class Tablica {

private:
    Znak tab[20][20];
    int priorytety[20][20];

public:
    void ustaw_priorytet(char znak, char znak_p, int rozmiar, float waga);                                          //funkcja ustawiaj¹ca priorytet
    void licz_wartosc_pri(int x, int y, int rozmiar, int kier_x, int kier_y, char znak, char znak_p, float waga);   //fumkcja obliczaj¹ca wartoœæ priorytetu ustawionych znaków 
    void szukaj_max(int &x, int &y, int rozmiar);                                                                   //funkcja szukaj¹ca maksymalnego priorytetu
    void postaw_znak(int x, int y, char znak);                                                                      //funkcja ustawiaj¹ca znak w odpowiednim miejscu tablicy            
    void zeruj_pri();                                                                                               //funkcja zeruj¹ca priorytrty pól
    bool sprawdz_kto_wygral(char znak, char znak_p, int rozmiar);                                                   //funkcja sprawdza czy mamy 5 jednakowych znaków w linii                         
    int licz_ile (int x, int y, int rozmiar, int kier_x, int kier_y, char znak, char znak_p);                       //funkcja zwraca ile mamy ustawionych znaków w linii     
    char sprawdz_znak(int x, int y);                                                                                //funkcja sprawdzaj¹ca znak która zwraca nam inormacjê o tym jaki znak zosta³ ustwionny w danej komórce
    void wyczysc();                                                                                                 //funkcja która czyœci tablicê tab[x][y] ze znaków 'X' i 'O'
    Tablica();
};





    
