#ifndef SISTE_BIBLIOTECA_CPP_CARTE_H
#define SISTE_BIBLIOTECA_CPP_CARTE_H

#include <cstddef>
#include <vector>
#include <string>
#include <iostream>
#include "json.hpp"

class Carte {
public:
    std::string ISBN;
    std::string Title;
    std::vector<std::string> Authors;
    std::vector<std::string> Genres;
    double Price;
    // Puteam folosi si size_t
    unsigned int Pages;
    unsigned int Total;
    unsigned int Available;
    void const Display() const;
    friend std::ostream &operator<<(std::ostream &os, const Carte &carte);

    Carte(std::string& isbn, std::string& title, std::vector<std::string>& authors,
          std::vector<std::string>& genres, int pages, double price, int total, int available);

    explicit Carte(nlohmann::json& json);

    Carte();

    nlohmann::json GetJson();

    // Toate obiectele au destructori sau sunt primitive, deci nu avem nevoie de un destructor
    ~Carte() = default;
private:
};

#endif
