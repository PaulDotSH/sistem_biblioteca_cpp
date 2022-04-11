#include <iostream>
#include "biblioteca/carte.h"
#include "biblioteca/biblioteca.h"

//https://github.com/nlohmann/json#serialization--deserialization
//https://www.geeksforgeeks.org/list-cpp-stl/

int main() {
//    Carte::Carte()
//
//    std::cout << "Hello, World!" << std::endl;
//    IO::TestFunc();

//    std::string& isbn, std::string& title, std::vector<std::string>& authors,
//            std::vector<std::string>& genres, int pages, double price, int total, int available

    std::string ISBN = "ISBN";
    std::string Title = "Titlu";

    std::vector<std::string> authors;
    authors.emplace_back("Autor1");
    authors.emplace_back("Autor2");
    authors.emplace_back("Autor3");

    std::vector<std::string> genres;

    genres.emplace_back("Gen1");
    genres.emplace_back("Gen2");
    genres.emplace_back("Gen3");

    int pages = 10;
    double price = 12.34;
    int total = 50;
    int available = 40;

    //Carte c;

    Carte c{ISBN,Title,authors,genres,pages,price,total,available};

    std::string nume_biblioteca = "Biblioteca 1";
    Biblioteca b(nume_biblioteca);
    b.Append(c);
    std::cout<<"test\n";

    return 0;
}
