#include "menu.h"

#define NUME_DB "db.json"

int main() {
    menu::GetInstance().biblioteca.nume = NUME_DB;
    menu::GetInstance().biblioteca.ReadCarti();
    menu::GetInstance().DisplayHelpMessage();
    menu::GetInstance().StartLoop();

    return 0;
}
