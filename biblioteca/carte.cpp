#include "carte.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Functia de display, folosind culori, afiseaza o carte in stdout
void const Carte::Display() const {

    std::cout << ANSI_COLOR_BLUE << "ISBN: " << ISBN << "\nTitlu: " << Title << "\nPagini: " << Pages << "\nPret: " << Price
              << "\nStoc: " << Available << "\nTotal: " << Total << "\nAutori: ";

    for (auto& autor : Authors) {
        std::cout<<autor<<";";
    }
    std::cout<<"\nGenuri: ";
    for (auto& gen : Genres) {
        std::cout<<gen<<";";
    }
    std::cout << ANSI_COLOR_RESET << "\n--------------\n";
}

// Constructor standard
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

#define MAX_LEN 100

//Daca nu primim parametrii, o sa citim din stdin inputul
Carte::Carte() {
    char inp[MAX_LEN];
    {
        std::cout << ANSI_COLOR_MAGENTA << "Introdu ISBN-ul cartii:\n";
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
    std::cin.get(); //de fiecare data cand dam cin la un int trb dat cin.get sau cin.ignore pentru a evita un trailing \n
    Authors.reserve(authorsNr); // alocam direct nr de elemente deoarece il stim deja
    authorsNr++;

    for (int i = 1; i < authorsNr; i++) {
        std::cout << "Introdu autorul cu numarul " << i << "\n";
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
    std::cout << ANSI_COLOR_RESET;
}

// Returnam un obiect json cu cartea
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
}

// Constructor din json
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

// Overload ostream
std::ostream &operator<<(std::ostream &os, const Carte &carte) {
    // Daca stream-ul este stdout atunci afisam cu culori
    if (os.rdbuf() == std::cout.rdbuf()) {
        carte.Display();
        return os;
    }
    os
    << "ISBN: " << carte.ISBN
    << "\nTitlu: " << carte.Title
    << "\nAutori:\n";
    for (auto& autor : carte.Authors) {
        os << autor << " ";
    }
    os << "\nGenres:\n";
    for (auto& gen : carte.Genres) {
        os << gen << " ";
    }
    os
    << "\nPagini: " << carte.Pages
    << "\nPret: " << carte.Price
    << "\nTotal: " << carte.Total
    << "\nStoc: " << carte.Available;
    return os;
}


