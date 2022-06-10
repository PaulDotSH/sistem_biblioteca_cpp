//
// Created by administrator on 4/12/22.
//

#include <cstring>
#include <iostream>
#include "menu.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Comanda cls functioneaza pentru windows iar clear pentru sistemele "unix-like"
void menu::ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Support pentru std::string dar si pentru cstrings
menu::command menu::ParseCommand(std::string cmd) {
    return ParseCommand(cmd.c_str());
}

// Folosindu-ne de enums facem codul mai readable
menu::command menu::ParseCommand(const char *cmd) {
    if (strcmp(cmd,"add")==0)
        return add;
    if (strcmp(cmd,"delete")==0 || strcmp(cmd,"del")==0) // del functioneaza ca un alias pentru delete
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

// Dimensiune buffer
#define MAX_STR_LEN 100

// Citeste urmatoarea comanda a utiliozatorului si returneaza un enum cu comanda
menu::command menu::GetUserCommand() {
    char inp[MAX_STR_LEN];
    std::cout << ANSI_COLOR_RED << "Introdu comanda ta\n" << ANSI_COLOR_RESET;
    std::cin.getline(inp,MAX_STR_LEN);
    return ParseCommand(inp);
}

inline void menu::DisplayHelpMessage() {
    std::cout << ANSI_COLOR_RED << "Scrie o comanda pentru a interactiona cu programul\n" << ANSI_COLOR_BLUE
    "Comenziile prezente momentan sunt:\n" << ANSI_COLOR_GREEN
    "add, delete/del, list, search, borrow, return, load, save/s, quit/q, help\n" << ANSI_COLOR_RESET;
}

// Submeniul pentru comanda delete
void menu::AfisareDeleteOptiuni() {
    int optiune;
    do {
        std::cout << ANSI_COLOR_YELLOW << "0. Back\n" <<
        "1. Delete dupa index\n" <<
        "2. Delete dupa ISBN\n" <<
        "3. Delete dupa Autor\n" << ANSI_COLOR_RESET;
        std::cin >> optiune;
        std::cin.ignore();
    } while(optiune < 0 || optiune > 3);

    // Folosim un stil similar cu cel din go in care returnam o "eroare" in caz ca o comanda nu s-a executat
    // cu success
    bool ret;
    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            int index;
            std::cin >> index;
            std::cin.ignore(); // Altfel ramane un trailing \n care da break la orice fgets() sau std::cin.getline()
            ret = biblioteca.DeleteCarteByIndex(index);
        }
            break;
        case 2:
        {
            std::string isbn;
            getline(std::cin,isbn);
            ret = biblioteca.DeleteCarteByISBN(isbn);
        }
            break;
        case 3:
        {
            // Alocam buffer-ul pe stack
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

    // De asemenea acest "error handling" se putea face cu un size_t care sa specifice cate carti au satsifacut conditia
    ret ? std::cout << ANSI_COLOR_RED << "Nu au fost gasite carti care sa satisfaca conditia\n" << ANSI_COLOR_RESET : std::cout << ANSI_COLOR_GREEN "Carte stearsa / carti sterse cu succes\n" << ANSI_COLOR_RESET;
}

// Submeniul pentru comanda search
void menu::AfisareSearchOptiuni() {
    int optiune;
    do {
        std::cout << ANSI_COLOR_YELLOW << "0. Back\n" <<
                  "1. Search dupa index\n" <<
                  "2. Search dupa ISBN\n" <<
                  "3. Search dupa Autor\n" <<
                  "4. Search dupa Gen\n" <<
                  "5. Search dupa Pret\n" <<
                  "6. Search dupa Numarul de pagini\n" <<
                  "7. Search dupa disponibilitate\n" << ANSI_COLOR_RESET;
        std::cin >> optiune;
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
            getline(std::cin,isbn);
            biblioteca.DisplayCarteByCriteriu([&isbn](Carte& carte){
                return carte.ISBN == isbn;
            });
        }
            break;
        case 3:
        {
            std::string tmp;
            getline(std::cin,tmp);
            biblioteca.DisplayCarteByCriteriu([&tmp](Carte& carte){
                for (auto& autor : carte.Authors)
                    if (autor==tmp) return true;
                return false;
            });
        }
            break;
        case 4:
        {
            std::string tmp;
            getline(std::cin,tmp); // .
            biblioteca.DisplayCarteByCriteriu([&tmp](Carte& carte){
                for (auto& gen : carte.Genres)
                    if (gen==tmp) {
                        std::cout << gen << "\n";
                        return true;

                    }
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
               return carte.Pages == NrPagini;
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
}

// Submeniul pentru comanda borrow
void menu::AfisareBorrowOptiuni() {
    int optiune;
    do {
        std::cout << ANSI_COLOR_YELLOW << "0. Back\n" <<
                  "1. Imprumuta dupa ISBN\n" << ANSI_COLOR_RESET;
        std::cin >> optiune;
        std::cin.ignore();
    } while(optiune < 0 || optiune > 1);

    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            std::string isbn;
            getline(std::cin,isbn);
            biblioteca.BorrowByISBN(isbn) ? std::cout << ANSI_COLOR_RED "Cartea nu a fost gasita sau nu este in stoc\n" << ANSI_COLOR_RESET
            : std :: cout << ANSI_COLOR_GREEN << "Ai imprumutat cartea cu succes\n" << ANSI_COLOR_RESET;
        }
    }
}

// Submeniul pentru comanda return
void menu::AfisareReturnOptiuni() {
    int optiune;
    do {
        std::cout << ANSI_COLOR_YELLOW "0. Back\n" <<
                  "1. Returneaza dupa ISBN\n" << ANSI_COLOR_RESET;
        std::cin >> optiune;
        std::cin.ignore();
    } while(optiune < 0 || optiune > 1);

    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            std::string isbn;
            getline(std::cin,isbn);
            biblioteca.ReturnByISBN(isbn) ? std::cout << ANSI_COLOR_RED << "Nu ai aceasta carte!\n" << ANSI_COLOR_RESET
            : std::cout << ANSI_COLOR_GREEN "Carte returnata cu succes\n" << ANSI_COLOR_RESET;
            return;
        }
    }
}

// Porneste loop-ul meniului, care actioneaza ca un fel de shell
void menu::StartLoop() {
    while (true) {
        // luam comanda de la utilizator si actionam corespunzator
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
                break;
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
                std::cout << ANSI_COLOR_RED << "Comanda inexistenta\n" << ANSI_COLOR_RESET;
                break;
        }
    }
}





