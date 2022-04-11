//
// Created by administrator on 4/9/22.
//

#include "biblioteca.h"
#include <functional>
#include <iostream>

Biblioteca::Biblioteca(std::string& Nume) : nume(Nume) {}

Carte* Biblioteca::FindCarteByIsbn(std::string &isbn) {
    for (auto& carte : carti)
        if (carte.ISBN == isbn) return &carte;
    return nullptr;
}


void Biblioteca::Display() {
    int index=0;
    for (auto& carte : carti) {
        //modifica ca la ambele sa fie << overloading
        std::cout<<"Index: "<<index++<<"\n";
        carte.Display();
    }
    std::cout<<"--------------\n";
}

Carte *Biblioteca::FindCarteByIndex(size_t index) {
    int _index=0;
    for (auto& carte : carti) {
        if (_index==index) return &carte;
        _index++;
    }
    return nullptr;
}

bool Biblioteca::DeleteCarteByIndex(size_t index) {
    if (index>this->size) return true;
    auto i=carti.begin();
    for (; index!=0; index--,i++) {}
    this->size--;
    carti.erase(i);
    return false;
}

bool Biblioteca::DeleteCarteByISBN(std::string &isbn) {
    for (auto i = carti.begin(); i!=carti.end(); i++) {
        if (i->ISBN == isbn) {
            carti.erase(i);
            this->size--;
            return false;
        }
    }
    return true;
}

void Biblioteca::DisplayCarteByCriteriu(bool (*criteriu)(Carte&)) {
    int index=0;
    for (auto& carte : carti) {
        //modifica ca la ambele sa fie << overloading
        std::cout<<"Index: "<<index++<<"\n";
        if (criteriu(carte))
            carte.Display();
    }
    std::cout<<"--------------\n";
}

bool Biblioteca::BorrowByISBN(std::string& ISBN) {
    for (auto& carte : carti) {
        if (carte.ISBN == ISBN && carte.Available>0) {
            carte.Available--;
            userSize++;
            utilizator.push_back(carte);
            return false;
        }
    }
    return true;
}

bool Biblioteca::BorrowByCriteriu(bool (*criteriu)(Carte &)) {
    for (auto& carte : carti) {
        if (criteriu(carte)) {
            carte.Available--;
            utilizator.push_back(carte);
            userSize++;
            return false;
        }
    }
    return true;
}

bool Biblioteca::ReturnByISBN(std::string& ISBN) {
    auto CarteUser = utilizator.begin();
    for (; CarteUser != utilizator.end(); CarteUser++) {
        if (CarteUser->ISBN == ISBN) {
            break;
        }
    }

    if (CarteUser == utilizator.end()) return true; //daca nu am gasit cartea in lista cu utilizatorul

    for (auto& carte : carti) {
        if (carte.ISBN == ISBN) {
            carte.Available++;
            userSize--;
            utilizator.erase(CarteUser);
            return false;
        }
    }

    return true;
}

void Biblioteca::Append(Carte &carte) {
    Carte c = Carte(carte);
    carti.emplace_back(c);
    this->size++;
}

Carte *Biblioteca::FindCarteByCriteriu(bool (*criteriu)(Carte &)) {
    for (auto& carte : carti)
        if (criteriu(carte)) return &carte;
    return nullptr;
}

void Biblioteca::AppendNewCarte() {
    carti.emplace_back(Carte());
    this->size++;
}




