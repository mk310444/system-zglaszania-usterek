#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Zgloszenie {
    int id;
    string tytul;
    string opis;
    string kategoria;
    string lokalizacja;
    string priorytet;
    string status;
};

vector<Zgloszenie> zgloszenia;
int nastepneId = 1;

void wyczyscBufor()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string wybierzKategorie()
{
    int wybor;

    cout << "\nWybierz kategorie:\n";
    cout << "1. Elektryka\n";
    cout << "2. Internet / komputer\n";
    cout << "3. Hydraulika\n";
    cout << "4. Meble\n";
    cout << "5. Drzwi / okna\n";
    cout << "6. Inne\n";
    cout << "Wybor: ";
    cin >> wybor;
    wyczyscBufor();

    switch (wybor) {
        case 1: return "Elektryka";
        case 2: return "Internet / komputer";
        case 3: return "Hydraulika";
        case 4: return "Meble";
        case 5: return "Drzwi / okna";
        case 6: return "Inne";
        default: return "Inne";
    }
}

string wybierzPriorytet()
{
    int wybor;

    cout << "\nWybierz priorytet:\n";
    cout << "1. Niski\n";
    cout << "2. Sredni\n";
    cout << "3. Wysoki\n";
    cout << "4. Pilny\n";
    cout << "Wybor: ";
    cin >> wybor;
    wyczyscBufor();

    switch (wybor) {
        case 1: return "Niski";
        case 2: return "Sredni";
        case 3: return "Wysoki";
        case 4: return "Pilny";
        default: return "Sredni";
    }
}

string wybierzStatus()
{
    int wybor;

    cout << "\nWybierz nowy status:\n";
    cout << "1. Nowe\n";
    cout << "2. Przyjete\n";
    cout << "3. W trakcie naprawy\n";
    cout << "4. Naprawione\n";
    cout << "5. Odrzucone\n";
    cout << "Wybor: ";
    cin >> wybor;
    wyczyscBufor();

    switch (wybor) {
        case 1: return "Nowe";
        case 2: return "Przyjete";
        case 3: return "W trakcie naprawy";
        case 4: return "Naprawione";
        case 5: return "Odrzucone";
        default: return "Nowe";
    }
}

void dodajZgloszenie()
{
    Zgloszenie nowe;

    nowe.id = nastepneId++;

    cout << "\n=== DODAWANIE ZGLOSZENIA ===\n";

    cout << "Podaj tytul: ";
    getline(cin, nowe.tytul);

    cout << "Podaj opis: ";
    getline(cin, nowe.opis);

    cout << "Podaj lokalizacje: ";
    getline(cin, nowe.lokalizacja);

    nowe.kategoria = wybierzKategorie();
    nowe.priorytet = wybierzPriorytet();
    nowe.status = "Nowe";

    zgloszenia.push_back(nowe);

    cout << "\nZgloszenie zostalo dodane.\n";
}

void wyswietlZgloszenie(const Zgloszenie& z)
{
    cout << "\nID: " << z.id << endl;
    cout << "Tytul: " << z.tytul << endl;
    cout << "Opis: " << z.opis << endl;
    cout << "Kategoria: " << z.kategoria << endl;
    cout << "Lokalizacja: " << z.lokalizacja << endl;
    cout << "Priorytet: " << z.priorytet << endl;
    cout << "Status: " << z.status << endl;
}

void wyswietlWszystkieZgloszenia()
{
    cout << "\n=== LISTA ZGLOSZEN ===\n";

    if (zgloszenia.empty()) {
        cout << "Brak zgloszen.\n";
        return;
    }

    for (const Zgloszenie& z : zgloszenia) {
        cout << "\nID: " << z.id
             << " | " << z.tytul
             << " | " << z.kategoria
             << " | " << z.lokalizacja
             << " | " << z.priorytet
             << " | " << z.status;
    }

    cout << endl;
}

int znajdzIndeksPoId(int id)
{
    for (int i = 0; i < static_cast<int>(zgloszenia.size()); i++) {
        if (zgloszenia[i].id == id) {
            return i;
        }
    }

    return -1;
}

void wyszukajZgloszeniePoId()
{
    int id;

    cout << "\nPodaj ID zgloszenia: ";
    cin >> id;
    wyczyscBufor();

    int indeks = znajdzIndeksPoId(id);

    if (indeks == -1) {
        cout << "Nie znaleziono zgloszenia o podanym ID.\n";
        return;
    }

    wyswietlZgloszenie(zgloszenia[indeks]);
}

void zmienStatusZgloszenia()
{
    int id;

    cout << "\nPodaj ID zgloszenia, ktoremu chcesz zmienic status: ";
    cin >> id;
    wyczyscBufor();

    int indeks = znajdzIndeksPoId(id);

    if (indeks == -1) {
        cout << "Nie znaleziono zgloszenia o podanym ID.\n";
        return;
    }

    cout << "\nAktualny status: " << zgloszenia[indeks].status << endl;
    zgloszenia[indeks].status = wybierzStatus();

    cout << "Status zostal zmieniony.\n";
}

void usunZgloszenie()
{
    int id;

    cout << "\nPodaj ID zgloszenia do usuniecia: ";
    cin >> id;
    wyczyscBufor();

    int indeks = znajdzIndeksPoId(id);

    if (indeks == -1) {
        cout << "Nie znaleziono zgloszenia o podanym ID.\n";
        return;
    }

    zgloszenia.erase(zgloszenia.begin() + indeks);

    cout << "Zgloszenie zostalo usuniete.\n";
}

void pokazStatystyki()
{
    int nowe = 0;
    int przyjete = 0;
    int wTrakcie = 0;
    int naprawione = 0;
    int odrzucone = 0;

    for (const Zgloszenie& z : zgloszenia) {
        if (z.status == "Nowe") nowe++;
        else if (z.status == "Przyjete") przyjete++;
        else if (z.status == "W trakcie naprawy") wTrakcie++;
        else if (z.status == "Naprawione") naprawione++;
        else if (z.status == "Odrzucone") odrzucone++;
    }

    cout << "\n=== STATYSTYKI ===\n";
    cout << "Wszystkie zgloszenia: " << zgloszenia.size() << endl;
    cout << "Nowe: " << nowe << endl;
    cout << "Przyjete: " << przyjete << endl;
    cout << "W trakcie naprawy: " << wTrakcie << endl;
    cout << "Naprawione: " << naprawione << endl;
    cout << "Odrzucone: " << odrzucone << endl;
}

void pokazMenu()
{
    cout << "\n\n=== SYSTEM ZGLASZANIA USTEREK ===\n";
    cout << "1. Dodaj zgloszenie\n";
    cout << "2. Wyswietl wszystkie zgloszenia\n";
    cout << "3. Wyszukaj zgloszenie po ID\n";
    cout << "4. Zmien status zgloszenia\n";
    cout << "5. Usun zgloszenie\n";
    cout << "6. Pokaz statystyki\n";
    cout << "0. Zakoncz program\n";
    cout << "Wybor: ";
}

int main()
{
    int wybor;

    do {
        pokazMenu();
        cin >> wybor;
        wyczyscBufor();

        switch (wybor) {
            case 1:
                dodajZgloszenie();
                break;
            case 2:
                wyswietlWszystkieZgloszenia();
                break;
            case 3:
                wyszukajZgloszeniePoId();
                break;
            case 4:
                zmienStatusZgloszenia();
                break;
            case 5:
                usunZgloszenie();
                break;
            case 6:
                pokazStatystyki();
                break;
            case 0:
                cout << "Zamykanie programu...\n";
                break;
            default:
                cout << "Niepoprawny wybor.\n";
        }

    } while (wybor != 0);

    return 0;
}