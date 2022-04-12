//
// Created by administrator on 4/9/22.
//

#include "carte.h"

void Carte::Display()  {
    std::cout << "ISBN: " << ISBN << "\nTitlu: " << Title << "\nPagini: " << Pages << "\nPret: " << Price
              << "\nStoc: " << Available << "\nTotal: " << Total << "\nAutori: ";

    for (auto& autor : Authors) {
        std::cout<<autor<<";";
    }
    std::cout<<"\nGenuri: ";
    for (auto& gen : Genres) {
        std::cout<<gen<<";";
    }
    std::cout<<"\n";
}

Carte::Carte(std::string &isbn, std::string &title, std::vector<std::string> &authors, std::vector<std::string> &genres,
             int pages, double price, int total, int available) : Pages(pages), Price(price), Total(total), Available(available)
{
    ISBN = isbn;
    Title = title;
    for (const auto& str : authors) {
        Authors.emplace_back(str);
    }

    for (const auto& str : genres) {
        Genres.emplace_back(str);
    }
}

Carte::~Carte() {

}

#define MAX_LEN 100

//Daca nu primim parametrii, o sa citim de la tastatura inputul
Carte::Carte() {
    char inp[MAX_LEN];
    {
        std::cout << "Introdu ISBN-ul cartii:\n";
        std::cin.getline(inp,MAX_LEN);
        this->ISBN = inp;
    }
    {
        std::cout << "Introdu titlul cartii:\n";
        std::cin.getline(inp,MAX_LEN);
        this->Title = inp;
    }
    int authorsNr,genresNr;

    std::cout << "Introdu numarul de autori\n";
    std::cin >> authorsNr;
    std::cin.get(); //de fiecare data cand dam cin la un int trb dat cin.get sau cin.ignore ca altfel o sa ne ia un empty string
    Authors.reserve(authorsNr); //alocam direct nr de elemente deoarece il stim deja
    authorsNr++;

    for (int i = 1; i < authorsNr; i++) {
        std::cout << "Introdu genul cu numarul " << i << "\n";
        std::cin.getline(inp,MAX_LEN);
        this->Authors.emplace_back(inp);
    }

    std::cout << "Introdu numarul de genuri\n";
    std::cin >> genresNr;
    std::cin.get();
    Genres.reserve(genresNr);
    genresNr++;

    for (int i = 1; i < genresNr; i++) {
        std::cout << "Introdu genul cu numarul " << i << "\n";
        std::cin.getline(inp,MAX_LEN);
        this->Genres.emplace_back(inp);
    }

    std::cout << "Introdu numarul de pagini\n";
    std::cin >> this->Pages;

    std::cout << "Introdu pretul\n";
    std::cin >> this->Price;

    std::cout << "Introdu numarul de carti totale\n";
    std::cin >> this->Total;

    std::cout << "Introdu numarul de carti in stoc\n";
    std::cin >> this->Available;
    std::cin.get();
}

nlohmann::json Carte::GetJson() {
    nlohmann::json json;
    json["isbn"] = ISBN;
    json["title"] = Title;
    json["authors"] = Authors;
    json["genres"] = Genres;
    json["pages"] = Pages;
    json["price"] = Price;
    json["available"] = Available;
    json["Total"] = Total;
    return json;
};

Carte::Carte(nlohmann::json& json) {
    ISBN = json["isbn"];
    Title = json["title"];
    for (auto& it : json["authors"]) {
        Authors.push_back(it.get<std::string>());
    }
    for (auto& it : json["genres"]) {
        Genres.push_back(it.get<std::string>());
    }
    Pages = json["pages"];
    Price = json["price"];
    Available = json["available"];
    Total = json["Total"];
}


