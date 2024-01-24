#include <iostream>
#include <string>
#include <sstream>

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
        listaTerminow = new string[3]{ "Termin1", "Termin2", "Termin3" };
        liczbaTerminow = 3;
        cout << "Odczyt z bazy danych zako�czony\n";
    }

    void aktualizujBazeDanych(const string* nowaListaTerminow, int nowaLiczbaTerminow) {
        delete[] listaTerminow;
        listaTerminow = new string[nowaLiczbaTerminow];
        for (int i = 0; i < nowaLiczbaTerminow; ++i) {
            listaTerminow[i] = nowaListaTerminow[i];
        }
        liczbaTerminow = nowaLiczbaTerminow;
        cout << "Aktualizacja bazy danych zako�czona\n";
    }
};

class ZarzadzanieTerminami {
public:
    Database bazaDanych;

    void sprawdzListeTerminow(istream& input = cin, ostream& output = cout) {
        bazaDanych.odczytajZBazyDanych();
    }

    void wyswietlInformacje(const string* listaTerminow, int liczbaTerminow, ostream& output = cout) {
        output << "Terminy w bazie danych:\n";
        for (int i = 0; i < liczbaTerminow; ++i) {
            output << listaTerminow[i] << "\n";
        }
    }

    bool wprowadzZmiany(istream& input, string*& nowaListaTerminow, int& nowaLiczbaTerminow, ostream& output = cout) {
        output << "Wprowad� nowe terminy (ka�dy termin w nowej linii, zako�cz wprowadzanie 'koniec'):\n";
        string nowyTermin;
        while (getline(input, nowyTermin) && nowyTermin != "koniec") {
            ++nowaLiczbaTerminow;
        }

        nowaListaTerminow = new string[nowaLiczbaTerminow];
        input.clear();  // Wyczy�� flagi b��d�w
        input.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignoruj znaki do ko�ca linii, aby pozby� si� reszty poprzedniego strumienia
        input.seekg(0, ios::beg);  // Przejd� na pocz�tek strumienia

        for (int i = 0; i < nowaLiczbaTerminow; ++i) {
            getline(input, nowaListaTerminow[i]);
        }

        // Zwr�� true, je�li lista termin�w zosta�a zmieniona
        return nowaLiczbaTerminow > 0;
    }



    void aktualizujBazeDanych(string* nowaListaTerminow, int nowaLiczbaTerminow) {
        bazaDanych.aktualizujBazeDanych(nowaListaTerminow, nowaLiczbaTerminow);
    }

    void wyswietlWynik(bool powodzenie, ostream& output = cout) {
        if (powodzenie) {
            output << "Operacja zako�czona powodzeniem\n";
        }
        else {
            output << "Operacja zako�czona niepowodzeniem\n";
        }
    }
};

int main() {
    ZarzadzanieTerminami zarzadzanieTerminami;
    istringstream input("NowyTermin1\nNowyTermin2\nkoniec");
    ostringstream output;

    zarzadzanieTerminami.sprawdzListeTerminow(input, output);

    const string* listaTerminow = zarzadzanieTerminami.bazaDanych.listaTerminow;
    int liczbaTerminow = zarzadzanieTerminami.bazaDanych.liczbaTerminow;

    zarzadzanieTerminami.wyswietlInformacje(listaTerminow, liczbaTerminow, output);

    string* nowaListaTerminow = nullptr;
    int nowaLiczbaTerminow = 0;

    bool zmianyWprowadzone = zarzadzanieTerminami.wprowadzZmiany(input, nowaListaTerminow, nowaLiczbaTerminow, output);

    if (zmianyWprowadzone) {
        zarzadzanieTerminami.aktualizujBazeDanych(nowaListaTerminow, nowaLiczbaTerminow);
        delete[] nowaListaTerminow;
    }

    zarzadzanieTerminami.wyswietlWynik(zmianyWprowadzone, output);

    return 0;
}
