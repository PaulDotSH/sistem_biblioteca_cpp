#ifndef SISTEM_BIBLIOTECA_CPP_MENU_H
#define SISTEM_BIBLIOTECA_CPP_MENU_H
#include "string"
#include "biblioteca/biblioteca.h"

class menu {
public:
    // Stocam comenzile posibile intr-un enum pentru a face codul mai citibil
    // ret -> return, dar return e un reserved keyword, la fel si del -> delete
    enum command {NaC,add,del,list,search,ret,borrow,save,quit,help,clear,load};

    command ParseCommand(std::string cmd);
    command ParseCommand(const char* cmd);

    void DisplayHelpMessage();
    command GetUserCommand();

    void AfisareDeleteOptiuni();

    void AfisareSearchOptiuni();

    void AfisareBorrowOptiuni();

    void AfisareReturnOptiuni();

    void StartLoop();

    // Meniul este un singleton, adica doar o singura instata a acestuia poate exista
    static menu& GetInstance() {
        static menu* singleton = new menu(); // Instanta este initializata doar cand avem nevoie de un meniu cel putin o data
        return *singleton;
    }

    void ClearScreen();

    Biblioteca biblioteca;
private:
    menu() = default;

    // Blocam accessul la copy si move operators pentru a mentine proprietatea de singleton
    menu(const menu&) = delete;
    menu& operator=(const menu&) = delete;
    menu(menu&&) = delete;
    menu& operator=(menu&&) = delete;
};


#endif
