//
// Created by administrator on 4/9/22.
//

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
    unsigned int Pages;
    double Price;
    unsigned int Total;
    unsigned int Available;

    //Constructor
    Carte(std::string& isbn, std::string& title, std::vector<std::string>& authors,
          std::vector<std::string>& genres, int pages, double price, int total, int available);

    Carte(nlohmann::json& json);

    Carte();

    void Display();

    nlohmann::json GetJson();

//    inline void to_json(nlohmann::json& j, const Carte& carte);
//    inline void from_json(const nlohmann::json& j, Carte& carte);

    //Carte() = delete;

    ~Carte();
private:
};


#endif //SISTE_BIBLIOTECA_CPP_CARTE_H
