#include <iostream>
#include "fstream"
#include "biblioteca/carte.h"
#include "biblioteca/biblioteca.h"
#include "biblioteca/json.hpp"
#include "menu.h"

//https://github.com/nlohmann/json#serialization--deserialization
//https://www.geeksforgeeks.org/list-cpp-stl/

//void foo() {
//    std::string ISBN = "ISBN";
//    std::string Title = "Titlu";
//
//    std::vector<std::string> authors;
//    authors.emplace_back("Autor1");
//    authors.emplace_back("Autor2");
//    authors.emplace_back("Autor3");
//
//    std::vector<std::string> genres;
//
//    genres.emplace_back("Gen1");
//    genres.emplace_back("Gen2");
//    genres.emplace_back("Gen3");
//
//    int pages = 10;
//    double price = 12.34;
//    int total = 50;
//    int available = 40;
//
//
//    Carte c{ISBN,Title,authors,genres,pages,price,total,available};
//
//    std::string nume_biblioteca = "Biblioteca 1";
//    Biblioteca b(nume_biblioteca);
//    b.Append(c);
//
//    b.BorrowByISBN(c.ISBN);
////    b.ReturnByISBN(c.ISBN);
//
//
//    b.SaveCarti("ceva.txt");
//
//    std::fstream stream;
//    stream.open("ceva.txt", std::fstream::in);
//
//    std::string nume = "test";
//    Biblioteca b2(nume);
//    b2.ReadCarti(stream);
//}

#define NUME_DB "db.json"

int main() {
    menu::GetInstance().biblioteca.nume = NUME_DB;
    menu::GetInstance().biblioteca.ReadCarti();
    menu::GetInstance().DisplayHelpMessage();
    menu::GetInstance().StartLoop();

    return 0;
}
