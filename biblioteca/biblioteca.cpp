#include "biblioteca.h"
#include <functional>
#include <iostream>
#include "fstream"

Biblioteca::Biblioteca(std::string& Nume) : nume(Nume) {}

// Functiile de tip "FindCarteBy" vor returna o referinta la o carte din biblioteca in functie de o conditie
Carte* Biblioteca::FindCarteByIsbn(std::string &isbn) {
    for (auto& carte : carti)
        if (carte.ISBN == isbn) return &carte;
    return nullptr;
}

// Functia display afiseaza si culori, folosim Display pentru a afisa o "biblioteca" in stdout
void const Biblioteca::Display() const {
    int index=0;
    for (auto& carte : carti) {
        std::cout<<"Index: "<<index++<<"\n";
        carte.Display();
    }
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

bool Biblioteca::DisplayCarteByCriteriu(const std::function <bool (Carte&)>& criteriu) {
    int index=0;
    bool ok = false;
    for (auto& carte : carti) {
        if (criteriu(carte))
        {
            std::cout<<"Index: "<<index<<"\n";
            ok=true;
            carte.Display();
        }
        index++;
    }
    return ok;
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

// Functiile de tip "ByCriteriu" primesc o functie care primeste ca parametru o referinta la o carte
// care este cartea prin care se itereaza, si fac o actiune depinzand de bool-ul returnat
// de exemplu in acest caz, o carte este imprumutata daca criteriul este valid
bool Biblioteca::BorrowByCriteriu(const std::function <bool (Carte&)>& criteriu) {
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

    if (CarteUser == utilizator.end()) return true; // Daca nu am gasit cartea in lista cu utilizatorul

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

// Returnam o carte cu un pointer deoarece putem returna nullptr in cazul in care o carte nu este gasita
Carte* Biblioteca::FindCarteByCriteriu(const std::function <bool (Carte&)>& criteriu) {
    for (auto& carte : carti)
        if (criteriu(carte)) return &carte;
    return nullptr;
}

// Citeste o carte noua din stdin
void Biblioteca::Append() {
    carti.emplace_back(Carte());
    this->size++;
}

// Parsam clasa biblioteca intr-un json si il tirmite in stream-ul primit
void Biblioteca::SaveCarti(std::ostream& stream) {
    nlohmann::json json;
    for (Carte& carte : carti) {
        json["Carti"].push_back(carte.GetJson());
    }
    json["size"] = this->size;

    for (Carte& carte : utilizator) {
        json["User"].push_back(carte.GetJson());
    }
    json["userSize"] = this->userSize;

    stream<<json;
}

void Biblioteca::SaveCarti(const char* file) {
    std::fstream stream;
    stream.open(file, std::fstream::out);
    SaveCarti(stream);
}

void Biblioteca::SaveCarti(const std::string& file) {
    std::fstream stream;
    stream.open(file, std::fstream::out);
    SaveCarti(stream);
}

// Dam parse din json in clasa biblioteca dintr-un stream
void Biblioteca::ReadCarti(std::istream& stream) {
    nlohmann::json json;
    stream >> json;

    nlohmann::json outJson;
    for (auto& it : json["Carti"]) {
        outJson = nlohmann::json::parse(it.dump());
        carti.emplace_back(outJson);
    }

    for (auto& it : json["User"]) {
        outJson = nlohmann::json::parse(it.dump());
        utilizator.emplace_back(outJson);
    }

    this->size = json["size"];
    this->userSize = json["userSize"];
}

void Biblioteca::ReadCarti(const std::string& file) {
    std::fstream stream;
    stream.open(file, std::fstream::in);
    if (stream.fail()) return;
    ReadCarti(stream);
}

void Biblioteca::ReadCarti(const char* file) {
    std::fstream stream;
    stream.open(file, std::fstream::in);
    if (stream.fail()) return;
    ReadCarti(stream);
}

Biblioteca::Biblioteca(const char* Nume) : nume(Nume) {}

void Biblioteca::ReadCarti() {
    ReadCarti(this->nume);
}

void Biblioteca::SaveCarti() {
    SaveCarti(this->nume);
}

bool Biblioteca::DeleteCarteByCriteriu(const std::function <bool (Carte&)>& criteriu) {
    auto i=carti.begin();
    for (auto& carte : carti) {
        if (criteriu(carte)) {
            carti.erase(i);
            this->size--;
            return false;
        }
        i++;
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const Biblioteca &biblioteca) {
    // Daca stream-ul este stdout atunci afisam cu culori
    if (os.rdbuf() == std::cout.rdbuf()) {
        biblioteca.Display();
        return os;
    }
    for (auto& carte : biblioteca.carti) {
        os << carte << "\n";
    }
    return os;
}

Biblioteca::Biblioteca() = default;




