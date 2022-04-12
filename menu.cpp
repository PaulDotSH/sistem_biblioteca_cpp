//
// Created by administrator on 4/12/22.
//

#include <cstring>
#include <iostream>
#include "menu.h"

void menu::ClearScreen() {
#ifdef WINDOWS
    system("cls");
#else
    system("clear");
#endif
}

menu::command menu::ParseCommand(std::string cmd) {
    return ParseCommand(cmd.c_str());
}

menu::command menu::ParseCommand(const char *cmd) {
    if (strcmp(cmd,"add")==0)
        return add;
    if (strcmp(cmd,"delete")==0 || strcmp(cmd,"del")==0)
        return del;
    if (strcmp(cmd,"list")==0)
        return list;
    if (strcmp(cmd,"search")==0)
        return search;
    if (strcmp(cmd,"borrow")==0)
        return borrow;
    if (strcmp(cmd,"save")==0 || strcmp(cmd,"s")==0)
        return save;
    if (strcmp(cmd,"quit")==0 || strcmp(cmd,"q")==0)
        return quit;
    if (strcmp(cmd,"clear")==0)
        return clear;
    if (strcmp(cmd,"load")==0)
        return load;
    if (strcmp(cmd,"ret")==0 || strcmp(cmd,"return")==0)
        return ret;
    if (strcmp(cmd,"help")==0)
        return help;
    return NaC;
}

#define MAX_STR_LEN 100

menu::command menu::GetUserCommand() {
    char inp[MAX_STR_LEN];
    std::cout<<"Introdu comanda ta\n";
    std::cin.getline(inp,MAX_STR_LEN);
    return ParseCommand(inp);
}

void menu::DisplayHelpMessage() {
    std::cout << "Scrie o comanda pentru a interactiona cu programul\n" <<
    "Comenziile prezente momentan sunt:\n" <<
    "add, delete/del, list, search, borrow, return, load, save/s, quit/q, help\n";
}

void menu::AfisareDeleteOptiuni() {
    int optiune;
    do {
        std::cout << "0. Back\n" <<
        "1. Delete dupa index\n" <<
        "2. Delete dupa ISBN\n" <<
        "3. Delete dupa Autor\n";
        std::cin >> optiune;
        ClearScreen();
        std::cin.ignore();
    } while(optiune < 0 || optiune > 3);

    bool ret;
    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            int index;
            std::cin >> index;
            std::cin.ignore();
            ret = biblioteca.DeleteCarteByIndex(index);
        }
            break;
        case 2:
        {
            std::string isbn;
            std::cin >> isbn;
            ret = biblioteca.DeleteCarteByISBN(isbn);
        }
            break;
        case 3:
        {
            char inp[MAX_STR_LEN];
            std::cin.getline(inp,MAX_STR_LEN);
            std::string tmp = inp;
            ret = biblioteca.DeleteCarteByCriteriu([&tmp](Carte& carte){
                for (auto& autor: carte.Authors)
                    if (autor == tmp) return true;
                return false;
            });
        }
    }

    ret ? std::cout << "Nu au fost gasite carti care sa satisfaca conditia\n" : std::cout<<"Carti sterse cu succes\n";
    //TODO: delete dupa ce a selectat userul
}

void menu::AfisareSearchOptiuni() {
    int optiune;
    do {
        std::cout << "0. Back\n" <<
                  "1. Search dupa index\n" <<
                  "2. Search dupa ISBN\n" <<
                  "3. Search dupa Autor\n" <<
                  "4. Search dupa Gen\n" <<
                  "5. Search dupa Pret\n" <<
                  "6. Search dupa Numarul de pagini\n" <<
                  "7. Search dupa disponibilitate\n";
        std::cin >> optiune;
        ClearScreen();
        std::cin.ignore();
    } while(optiune < 0 || optiune > 7);

    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            int index;
            std::cin>>index;
            std::cin.ignore();
            biblioteca.DisplayCarteByCriteriu([&index](Carte& carte){
                if (index--==0) return true;
                return false;
            });
        }
            break;
        case 2:
        {
            std::string isbn;
            std::cin >> isbn;
            biblioteca.DisplayCarteByCriteriu([&isbn](Carte& carte){
                return carte.ISBN == isbn;
            });
        }
            break;
        case 3:
        {
            char inp[MAX_STR_LEN];
            std::cin.getline(inp,MAX_STR_LEN);
            std::string tmp = inp;
            biblioteca.DisplayCarteByCriteriu([&tmp](Carte& carte){
                for (auto& autor : carte.Authors)
                    if (autor==tmp) return true;
                return false;
            });
        }
            break;
        case 4:
        {
            char inp[MAX_STR_LEN];
            std::cin.getline(inp,MAX_STR_LEN);
            std::string tmp = inp;
            biblioteca.DisplayCarteByCriteriu([&tmp](Carte& carte){
                for (auto& gen : carte.Genres)
                    if (gen==tmp) return true;
                return false;
            });
        }
            break;
        case 5:
        {
            double pret;
            std::cin>>pret;
            std::cin.ignore();
            biblioteca.DisplayCarteByCriteriu([&pret](Carte& carte){
                return carte.Price == pret;
            });
        }
            break;
        case 6:
        {
            unsigned int NrPagini;
            std::cin>>NrPagini;
            std::cin.ignore();
            biblioteca.DisplayCarteByCriteriu([&NrPagini](Carte& carte){
               return carte.Pages = NrPagini;
            });
        }
            break;
        case 7:
        {
            biblioteca.DisplayCarteByCriteriu([](Carte& carte){
               return carte.Available != 0;
            });
        }
            break;
    }

    //TODO: search dupa ce a selectat userul
}

void menu::AfisareBorrowOptiuni() {
    int optiune;
    do {
        std::cout << "0. Back\n" <<
                  "1. Imprumuta dupa ISBN\n";
        std::cin >> optiune;
        ClearScreen();
        std::cin.ignore();
    } while(optiune < 0 || optiune > 1);

    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            std::string isbn;
            std::cin >> isbn;
            biblioteca.BorrowByISBN(isbn) ? std::cout << "Cartea nu a fost gasita sau nu este in stoc\n"
            : std :: cout << "Ai imprumutat cartea cu succes\n";
        }
    }
}

void menu::AfisareReturnOptiuni() {
    int optiune;
    do {
        std::cout << "0. Back\n" <<
                  "1. Returneaza dupa ISBN\n";
        std::cin >> optiune;
        ClearScreen();
        std::cin.ignore();
    } while(optiune < 0 || optiune > 1);

    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            std::string isbn;
            std::cin >> isbn;
            biblioteca.ReturnByISBN(isbn) ? std::cout << "Nu ai aceasta carte!\n" : std::cout << "Carte returnata cu succes\n";
        }
    }
}

void menu::StartLoop() {
    while (true) {
        auto cmd = GetUserCommand();
        switch (cmd) {
            case list:
                biblioteca.Display();
                break;
            case clear:
                ClearScreen();
                break;
            case help:
                DisplayHelpMessage();
                break;
            case add:
                biblioteca.Append();
                break;
            case save:
                biblioteca.SaveCarti();
                break;
            case load:
                biblioteca.ReadCarti();
            case quit:
                return;
            case del:
                AfisareDeleteOptiuni();
                break;
            case search:
                AfisareSearchOptiuni();
                break;
            case ret:
                AfisareReturnOptiuni();
            case borrow:
                AfisareBorrowOptiuni();
            default:
                break;
        }
    }
}





