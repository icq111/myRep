#include "znak.h"


char Znak::sprawdz() {              //funkcja zwraca stan sprawdzonego pola jako znak 'O', 'X' lub '.'
    return stan;
}

void Znak::ustaw(char temp) {       //funkcja ustawia stan znaku 'O' lub 'X' (na pocz¹tku wszystkie pola domyœlnie maj¹ stan '.')
    stan = temp;
}
