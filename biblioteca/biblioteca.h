//
// Created by administrator on 4/9/22.
//

#ifndef SISTE_BIBLIOTECA_CPP_BIBLIOTECA_H
#define SISTE_BIBLIOTECA_CPP_BIBLIOTECA_H

#include "list"
#include "optional"
#include "carte.h"
#include <functional>

//mergem pe un sistem similar cu cel din go, in care vom folosi un bool pentru a returna 1 cand avem o eroare
class Biblioteca {
public:
    Biblioteca();
    explicit Biblioteca(std::string& nume);
    explicit Biblioteca(const char* nume);


    //Fa inca un append care foloseste list.emplace_back pt carte
    void Append(Carte& carte);
    void Append();

    Carte* FindCarteByIsbn(std::string& isbn);
    Carte* FindCarteByIndex(size_t index);
    Carte* FindCarteByCriteriu(const std::function <bool (Carte&)>& criteriu);

    bool DeleteCarteByIndex(size_t index);
    bool DeleteCarteByISBN(std::string& isbn);
    bool DeleteCarteByCriteriu(const std::function <bool (Carte&)>& criteriu);

    void DisplayCarteByCriteriu(const std::function <bool (Carte&)>& criteriu);
    void Display();

    bool BorrowByISBN(std::string& ISBN);
    bool BorrowByCriteriu(const std::function <bool (Carte&)>& criteriu);
    bool ReturnByISBN(std::string& ISBN);

    void ReadCarti(std::istream&);
    void ReadCarti(const char*);
    void ReadCarti();
    void ReadCarti(const std::string&);

    void SaveCarti(std::ostream&);
    void SaveCarti(const std::string&);
    void SaveCarti(const char*);
    void SaveCarti();

    std::string nume; //folosit pt nume fisier

    ~Biblioteca();
private:
    std::list<Carte> carti;
    size_t size = 0; //in append faci asta++

    std::list<Carte> utilizator;
    size_t userSize = 0;
};


#endif //SISTE_BIBLIOTECA_CPP_BIBLIOTECA_H
