#include "znak.h"


char Znak::sprawdz() {              //funkcja zwraca stan sprawdzonego pola jako znak 'O', 'X' lub '.'
    return stan;
}

void Znak::ustaw(char temp) {       //funkcja ustawia stan znaku 'O' lub 'X' (na pocz�tku wszystkie pola domy�lnie maj� stan '.')
    stan = temp;
}
