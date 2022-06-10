#ifndef SISTE_BIBLIOTECA_CPP_BIBLIOTECA_H
#define SISTE_BIBLIOTECA_CPP_BIBLIOTECA_H

#include "list"
#include "optional"
#include "carte.h"
#include <functional>
#include <ostream>

class Biblioteca {
public:
    Biblioteca();
    explicit Biblioteca(std::string& nume);
    explicit Biblioteca(const char* nume);


    void Append(Carte& carte);
    void Append();

    Carte* FindCarteByIsbn(std::string& isbn);
    Carte* FindCarteByIndex(size_t index);
    Carte* FindCarteByCriteriu(const std::function <bool (Carte&)>& criteriu);

    bool DeleteCarteByIndex(size_t index);
    bool DeleteCarteByISBN(std::string& isbn);
    bool DeleteCarteByCriteriu(const std::function <bool (Carte&)>& criteriu);

    bool DisplayCarteByCriteriu(const std::function <bool (Carte&)>& criteriu);
    void const Display() const;

    friend std::ostream &operator<<(std::ostream &os, const Biblioteca &biblioteca);

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

    std::string nume; // Folosit pt nume fisier

    ~Biblioteca() = default;
private:
    std::list<Carte> carti;
    size_t size = 0; // In append incrementam cu 1, si in delete decrementam cu 1

    std::list<Carte> utilizator;
    size_t userSize = 0;
};

#endif
