//
// Created by administrator on 4/9/22.
//

#ifndef SISTE_BIBLIOTECA_CPP_BIBLIOTECA_H
#define SISTE_BIBLIOTECA_CPP_BIBLIOTECA_H

#include "list"
#include "optional"
#include "carte.h"

//mergem pe un sistem similar cu cel din go, in care vom folosi un bool pentru a returna 1 cand avem o eroare
class Biblioteca {
public:
    explicit Biblioteca(std::string& nume);
    //fa-l din ala nebun care daca ii dai parametrii construieste cartea direct aici
//    template< class... Args>
//    void Append(Args&&... args);

    void Append(Carte& carte);
    void AppendNewCarte();

    Carte* FindCarteByIsbn(std::string& isbn);
    Carte* FindCarteByIndex(size_t index);
    Carte* FindCarteByCriteriu(bool (*criteriu) (Carte&));
    bool DeleteCarteByIndex(size_t index);
    bool DeleteCarteByISBN(std::string& isbn);
    void DisplayCarteByCriteriu(bool (*f) (Carte& carte));
    void Display();

    bool BorrowByISBN(std::string& ISBN);
    bool BorrowByCriteriu(bool (*criteriu) (Carte&));
    bool ReturnByISBN(std::string& ISBN);

    void ReadCarti();
    void SaveCarti();
private:
    std::string nume; //folosit pt nume fisier
    std::list<Carte> carti;
    size_t size = 0; //in append faci asta++

    std::list<Carte> utilizator;
    size_t userSize = 0;
};


#endif //SISTE_BIBLIOTECA_CPP_BIBLIOTECA_H
