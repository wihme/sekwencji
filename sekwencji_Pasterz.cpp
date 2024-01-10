#include <iostream>
#include <string>

using namespace std;

class Database {
public:
    string* listaTerminow;
    int liczbaTerminow;

    Database() : listaTerminow(nullptr), liczbaTerminow(0) {}

    ~Database() {
        delete[] listaTerminow;
    }

    void odczytajZBazyDanych() {
        listaTerminow = new string[3]{"Termin1", "Termin2", "Termin3"};
        liczbaTerminow = 3;
        cout << "Odczyt z bazy danych zakończony\n";
    }

    void aktualizujBazeDanych(const string* nowaListaTerminow, int nowaLiczbaTerminow) {
        delete[] listaTerminow;
        listaTerminow = new string[nowaLiczbaTerminow];
        for (int i = 0; i < nowaLiczbaTerminow; ++i) {
            listaTerminow[i] = nowaListaTerminow[i];
        }
        liczbaTerminow = nowaLiczbaTerminow;
        cout << "Aktualizacja bazy danych zakończona\n";
    }
};

class ZarzadzanieTerminami {
public:
    Database bazaDanych;

    void sprawdzListeTerminow() {
        bazaDanych.odczytajZBazyDanych();
    }

    void wyswietlInformacje(const string* listaTerminow, int liczbaTerminow) {
        cout << "Terminy w bazie danych:\n";
        for (int i = 0; i < liczbaTerminow; ++i) {
            cout << listaTerminow[i] << "\n";
        }
    }

    bool wprowadzZmiany(string*& nowaListaTerminow, int& nowaLiczbaTerminow) {
        cout << "Wprowadź nowe terminy (każdy termin w nowej linii, zakończ wprowadzanie 'koniec'):\n";
        string nowyTermin;
        while (cin >> nowyTermin && nowyTermin != "koniec") {
            ++nowaLiczbaTerminow;
        }

        nowaListaTerminow = new string[nowaLiczbaTerminow];
        for (int i = 0; i < nowaLiczbaTerminow; ++i) {
            cin >> nowaListaTerminow[i];
        }

        // Zwróć true, jeśli lista terminów została zmieniona
        return nowaLiczbaTerminow > 0;
    }

    void aktualizujBazeDanych(string* nowaListaTerminow, int nowaLiczbaTerminow) {
        bazaDanych.aktualizujBazeDanych(nowaListaTerminow, nowaLiczbaTerminow);
    }

    void wyswietlWynik(bool powodzenie) {
        if (powodzenie) {
            cout << "Operacja zakończona powodzeniem\n";
        } else {
            cout << "Operacja zakończona niepowodzeniem\n";
        }
    }
};

int main() {
    ZarzadzanieTerminami zarzadzanieTerminami;
    zarzadzanieTerminami.sprawdzListeTerminow();

    const string* listaTerminow = zarzadzanieTerminami.bazaDanych.listaTerminow;
    int liczbaTerminow = zarzadzanieTerminami.bazaDanych.liczbaTerminow;

    zarzadzanieTerminami.wyswietlInformacje(listaTerminow, liczbaTerminow);

    string* nowaListaTerminow = nullptr;
    int nowaLiczbaTerminow = 0;

    bool zmianyWprowadzone = zarzadzanieTerminami.wprowadzZmiany(nowaListaTerminow, nowaLiczbaTerminow);

    if (zmianyWprowadzone) {
        zarzadzanieTerminami.aktualizujBazeDanych(nowaListaTerminow, nowaLiczbaTerminow);
        delete[] nowaListaTerminow;
    }

    zarzadzanieTerminami.wyswietlWynik(zmianyWprowadzone);

    return 0;
}
