#pragma once

class Znak {
//klasa odpowiedzialna za sprawdzenie czy dane pole nie jest zajête i ustawienie znaku
private:
    char stan;
public:
    char sprawdz();     //funkcja zwraca stan sprawdzonego pola jako znak 'O', 'X' lub '.'
    void ustaw(char);   //funkcja ustawia stan znaku 'O' lub 'X' (na pocz¹tku wszystkie pola domyœlnie maj¹ stan '.')
    
};
     
