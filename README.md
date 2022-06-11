# Sistem de management al unei biblioteci

Programul este similar cu un shell cu niste comenzi, pentru a face management unei biblioteci.
Entry point-ul este in fisierul main.cpp, care porneste un loop in care utizatorul trebuie sa introduca comenzi, care vor fi executate de program.

## Structuri de date
#### 1. Clasa Carte
Clasa carte este similara un "struct", care are field-urile ISBN, Title, Authors, Genres, Price, Pages, Total și Available. Toate aceste field-uri sunt publice, acestea doar stocând niște date care nu modifică "state-ul" obiectului, nu avea sens sa folosim getters și setters.
Aceasta clasa are ca field-uri doar Display, GetJson, constructori si overload la operatorul de citire. Această clasă nu are un destructor, folosind doar obiecte care deja au destructori sau primitive.
Constructorul cu parametru **``nlohmann::json``** și functia **``GetJson()``** sunt folosite pentru parse-ul din și în json. Iar funcțiile Display și overload-ul la operatorul **`<<`** sunt folosite pentru afisarea acestui obiect, funcția Display este folosita pentru output-ul în stdout deoarece acesta va afișa textul cu culori, folosindu-use de codurile ANSI, acestea fiind suportate pe majoritatea shell-urilor.
#### 2. Clasa Biblioteca
Clasa bibliotecă conține două liste de cărți, una pentru utilizator și una pentru bibliotecă, dar și dimensiunile acestora, aceasta are funcționalități de Read și Save pentru a citi și salva datele prezente în bibliotecă, acestea pot fi salvate in orice tip derivat din **`std::ostream`**.
Pe lângă acestea, putem afișa, găsi, șterge, împrumuta și returna cărți, după orice criteriu, acesta fiind o funcție care primește datele despre o carte și returneaya un bool, marcând dacă acțiunea trebuie efectuată sau nu.
La fel ca și clasa carte, aceasta are overloaded operatorul **`<<`**, și funcția Display, biblioteca fiind afișată cu culori in cazul in care stream-ul este stdout, iar fara în celelalte cazuri.
Nici această clasă nu are un destructor deoarece field-urile din aceasta sunt distruse automat de destructorii lor.
#### 3. Clasa Menu
Clasa meniu este o clasă de tip **singleton**, adica cu o singură instanță posibilă. Aceasta conține funcția **`StartLoop()`**. Care pornește loop-ul cu "shell"-ul, în care aplicația continuă să parseze input-ul de la utilizator, iar în cazul în care o comanda este introdusă, submeniul corespunzător este afișat sau comanda corespunzătoare este rulată, iar în caz contrariu un mesaj este afișat.
## Structura fișierelor și modul de salvare
Toate datele din bibliotecă sunt salvate într-un fișier in format json, acesta fiind by default numit "db.json". Schimbările sunt salvate in momentul in care utilizatorul folosește comanda **`save`**.  Parsing-ul se face folosindu-ne de libraria `nlohmann json`.

## Meniul aplicației
La pornirea aplicației, aceasta informează utilizatorul să "Scrie o comanda pentru a interactiona cu programul", si care sunt comenzile prezente si alias-urile lor.
Comenzile pe care le poate introduce utilizatorul sunt: `add, delete/del, list, search, borrow, return, load, save/s, quit/q, help`. Fiecare dintre această comanda afișează un submeniu, din clasa meniu, excepție fiind `add, list, load, save, quit și help`.
- add
Apelează constructorul de la clasa Carte, fară parametrii, care face programul să citească o carte din stdin, pe care o adauga in lista cărților din clasa bibliotecă.
- delete
Apelează un submeniu care lasă utilizatorul să șteargă o carte după index, isbn sau autor.
- list
Afisează clasa bibliotecă, adică toate carțile din aceasta.
- search
Apelează un submeniu care îi permite utilizatorului să afișeze cărțiile care îndeplinesc o condiție. Acesta poate să caute după `index, isbn, autor, gen, pret, număr de pagini și disponibilitate`.
- borrow
Îi permite utilizatorului să împrumute o carte după ISBN-ul acesteia.
- return
Îi permite utilizatorului să returneze o carte după ISBN-ul acesteia.
- load
Reîncarcă datele din fișier.
- save
Salvează datele în fișier.
- quit
Iese din program.
- help
Afișează mesajul de ajutor.
- clear
Șterge output-ul terminalului daca îi este permis, funcționând pe unix based systems dar și Windows.

