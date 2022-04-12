//
// Created by administrator on 4/12/22.
//

#ifndef SISTEM_BIBLIOTECA_CPP_MENU_H
#define SISTEM_BIBLIOTECA_CPP_MENU_H
#include "string"
#include "biblioteca/biblioteca.h"

//namespace menu {
//    enum command {NaC,add,del,list,search,ret,borrow,save,quit,help,clear};
//}

class menu {
public:
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

    static menu& GetInstance() {
        // Allocate with `new` in case IO is not trivially destructible.
        static menu* singleton = new menu();
        return *singleton;
    }

    void ClearScreen();

    Biblioteca biblioteca;
private:
    menu() = default;

    // Delete copy/move so extra instances can't be created/moved.
    menu(const menu&) = delete;
    menu& operator=(const menu&) = delete;
    menu(menu&&) = delete;
    menu& operator=(menu&&) = delete;
};


#endif //SISTEM_BIBLIOTECA_CPP_MENU_H
