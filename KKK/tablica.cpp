#include "tablica.h"


Tablica::Tablica() {                         //konstruktor klasy Tablica
    for (int y = 0; y < 20; y++) {           //ustawia w tablicy tab[x][y] domyœlny obiekt znak '.'=0
        for (int x = 0; x < 20; x++) {
            tab[x][y].ustaw('.');
        }
    }
} 

void Tablica::zeruj_pri() {                  //funkcja zeruj¹ca priorytrty pól
     for (int y = 0; y < 20; y++) {          //po ka¿dej rozgrywce priorytet ka¿dego pola tablicy priorytety ustawiany jest na 0
         for (int x = 0; x < 20; x++) {
             priorytety[x][y] = 0;
         }
     }
}

void Tablica::wyczysc() {                    //funkcja która czyœci tablicê tab[x][y] ze znaków 'X' i 'O'
     for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            tab[x][y].ustaw('.');            //ustawienie w ka¿dej komórce tablicy '.' z priorytetem = 0
        }
    }
}
     

char Tablica::sprawdz_znak(int x, int y) {   //funkcja sprawdzaj¹ca znak która zwraca nam inormacjê o tym jaki znak zosta³ ustwionny w danej komórce
    return tab[x][y].sprawdz();
}

void Tablica::szukaj_max(int &x, int &y, int rozmiar) {             //funkcja szukaj¹ca maksymalnego priorytetu
     int max = 0;                                                   //przy ka¿dym wywo³aniu funkcji zerujemy licznik
        
     for (int i = 0; i < rozmiar; i++) {
         for (int j = 0; j < rozmiar; j++) {
             if (priorytety[i][j] > max) {
                 max = priorytety[i][j];
                 x = i;
                 y = j;
             }
         }
     }
}

void Tablica::ustaw_priorytet(char znak, char znak_p, int rozmiar, float waga) {  //f-cja ustawiaj¹ca priorytet 
     
     for (int y = 0; y < rozmiar; y++) {
         for (int x = 0; x < rozmiar; x++) {
             if (tab[x][y].sprawdz() == '.') {
                 licz_wartosc_pri(x, y, rozmiar, -1, 1, znak, znak_p, waga);      //liczymy wartoœci priorytetów w 4 kierunkach
                 licz_wartosc_pri(x, y, rozmiar, 0, 1, znak, znak_p, waga);
                 licz_wartosc_pri(x, y, rozmiar, 1, 1, znak, znak_p, waga);
                 licz_wartosc_pri(x, y, rozmiar, 1, 0, znak, znak_p, waga);
                 
             }
         }
     }     
}

void Tablica::licz_wartosc_pri(int x, int y, int rozmiar, int kier_x, int kier_y, char znak, char znak_p, float waga) {
//fumkcja obliczaj¹ca wartoœæ priorytetu ustawionych znaków     
     int ile = 0, ile_pom = 1;
     bool pom1 = false,            //pom1  informuje nas czy mamy blokowany znak 
          pom2 = false;
     int licz_x, licz_y;            //to samo co wy¿ej tylko ze z drugiej strony
     
     for (licz_x = x + kier_x, licz_y = y + kier_y; 
          (licz_x >= 0) && (licz_x < rozmiar) && (licz_y >= 0) && (licz_y < rozmiar); 
          licz_x += kier_x, licz_y += kier_y) {
                 
         if (tab[licz_x][licz_y].sprawdz() == znak || tab[licz_x][licz_y].sprawdz() == '.') {
             ile_pom++;
         }
         if (tab[licz_x][licz_y].sprawdz() == znak_p) {
             break;
         }
     }
     for (licz_x = x - kier_x, licz_y = y - kier_y; 
          (licz_x >= 0) && (licz_x < rozmiar) && (licz_y >= 0) && (licz_y < rozmiar); 
          licz_x -= kier_x, licz_y -= kier_y) {   
                 
         if (tab[licz_x][licz_y].sprawdz() == znak || tab[licz_x][licz_y].sprawdz() == '.') {
             ile_pom++;
         }
         if (tab[licz_x][licz_y].sprawdz() == znak_p) {
             break;
         }
     }
             
         for (licz_x = x + kier_x, licz_y = y + kier_y; 
             (licz_x >= 0) && (licz_x < rozmiar) && (licz_y >= 0) && (licz_y < rozmiar); 
             licz_x += kier_x, licz_y += kier_y) {
                 
             if (tab[licz_x][licz_y].sprawdz() == znak) {
                 ile++;
             }
             if (tab[licz_x][licz_y].sprawdz() == '.' || tab[licz_x][licz_y].sprawdz() == znak_p) {
                 if (tab[licz_x][licz_y].sprawdz() == '.') {
                     pom1 = true;    // priorytet mnozymy przez dwa
                 }
             
                 break;
             }
         }
         for (licz_x = x - kier_x, licz_y = y - kier_y; 
             (licz_x >= 0) && (licz_x < rozmiar) && (licz_y >= 0) && (licz_y < rozmiar); 
             licz_x -= kier_x, licz_y -= kier_y) {
                 
             if (tab[licz_x][licz_y].sprawdz() == znak) {
                 ile++;
             }
             if (tab[licz_x][licz_y].sprawdz() == '.' || tab[licz_x][licz_y].sprawdz() == znak_p) {
                 if (tab[licz_x][licz_y].sprawdz() == '.') {
                     pom2 = true;    // priorytet mno¿ymy przez dwa
                 } 
                 break;
             }
         }
         switch (ile) {
             case 0: ile = 0; break;              
             case 1: ile = 20; break;             //znaleŸliœmy 1 znak priorytet ustawiamy na 20
             case 2: ile = 100; break;            //znaleŸliœmy 2 znaki w linii priorytet ustawiamy na 100
             case 3: ile = 500; break;            //znaleŸliœmy 3 znaki w linii priorytet ustawiamy na 500
             case 4: ile = 2500; break;           //znaleŸliœmy 4 znaki w linii priorytet ustawiamy na 2500
             default: ile = 5000;
         }
         if (pom1 == true) {
             ile *= 2;                            //dodatkowo jeœli nie mamy blokowanych znaków w linii z jednej strony 
         }                                        //to zwiêkszamy priorytet *2 (zwiêkszamy wagê danego pola. 
                                                  //im wiêksza waga tym ko¿ystniej postawæ tu swój znak)
         if (pom2 == true) {                      //blokowanie znaków w linii z drugiej strony
             ile *= 2;
         }
         if (ile_pom >= 5) {
             ile *= waga;
         }
         else {
             ile = ile * (waga * 0.1);            //obliczenie wagi pola
         }                  
         priorytety[x][y] += ile;
}

bool Tablica::sprawdz_kto_wygral(char znak, char znak_p, int rozmiar) { //funkcja sprawdza czy mamy 5 jednakowych znaków w linii
     for (int y = 0; y < rozmiar; y++) {                                //preszukiwanie tablicy
         for (int x = 0; x < rozmiar; x++) {
             if (tab[x][y].sprawdz() == znak) {
                 if (licz_ile(x, y, rozmiar, -1, 1, znak, znak_p) >= 5) { return true; }//sprawdzamy czy mamy 5(lub wiêcej)jednakowych znaków w zadanym kierunku
                 if (licz_ile(x, y, rozmiar, 0, 1, znak, znak_p) >= 5) { return true; }
                 if (licz_ile(x, y, rozmiar, 1, 1, znak, znak_p) >= 5) { return true; }
                 if (licz_ile(x, y, rozmiar, 1, 0, znak, znak_p) >= 5) { return true; }
                 
             }
         }
     }
     return false; //jeœli brak 5tki zwracamy 0 logiczne
}

int Tablica::licz_ile (int x, int y, int rozmiar, int kier_x, int kier_y, char znak, char znak_p) {
//funkcja zwraca ile mamy ustawionych znaków w linii     
     int ile = 1; //domyœlnie jeden - przeszukiwanie zaczynamy od znalezionego juz znaku
     int licz_x, licz_y;
     for (licz_x = x + kier_x, licz_y = y + kier_y; 
          (licz_x >= 0) && (licz_x < rozmiar) && (licz_y >= 0) && (licz_y < rozmiar); 
          licz_x += kier_x, licz_y += kier_y) {
                 
         if (tab[licz_x][licz_y].sprawdz() == znak) {
             ile++;
         }
         if (tab[licz_x][licz_y].sprawdz() != znak) {
             break;
         }
     }
     return ile;
}

void Tablica::postaw_znak(int x, int y, char znak) { //funkcja ustawiaj¹ca znak w odpowiednim miejscu tablicy
     tab[x][y].ustaw(znak);
}
