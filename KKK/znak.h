#pragma once

class Znak {
//klasa odpowiedzialna za sprawdzenie czy dane pole nie jest zaj�te i ustawienie znaku
private:
    char stan;
public:
    char sprawdz();     //funkcja zwraca stan sprawdzonego pola jako znak 'O', 'X' lub '.'
    void ustaw(char);   //funkcja ustawia stan znaku 'O' lub 'X' (na pocz�tku wszystkie pola domy�lnie maj� stan '.')
    
};
     
