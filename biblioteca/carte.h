//
// Created by administrator on 4/9/22.
//

#ifndef SISTE_BIBLIOTECA_CPP_CARTE_H
#define SISTE_BIBLIOTECA_CPP_CARTE_H

#include <cstddef>
#include <vector>
#include <string>
#include <iostream>

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

    Carte();

    void Display();

    //Carte() = delete;

    ~Carte();
private:
};


#endif //SISTE_BIBLIOTECA_CPP_CARTE_H
