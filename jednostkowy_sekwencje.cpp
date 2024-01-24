#include "pch.h" // W tym miejscu dodaj odpowiedni plik nag³ówkowy dla Twojego œrodowiska
#include "CppUnitTest.h"
#include <sstream>
#include <C:\Users\Admin\source\repos\sekwencje\sekwencje\sekw.cpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    TEST_CLASS(ZarzadzanieTerminamiTests)
    {
    public:
        TEST_METHOD(TestOdczytajZBazyDanych)
        {
            ZarzadzanieTerminami zarzadzanieTerminami;
            zarzadzanieTerminami.sprawdzListeTerminow();

            const string* listaTerminow = zarzadzanieTerminami.bazaDanych.listaTerminow;
            int liczbaTerminow = zarzadzanieTerminami.bazaDanych.liczbaTerminow;

            Assert::AreEqual(3, liczbaTerminow);
            Assert::AreEqual(string("Termin1"), listaTerminow[0]);
            Assert::AreEqual(string("Termin2"), listaTerminow[1]);
            Assert::AreEqual(string("Termin3"), listaTerminow[2]);
        }

        TEST_METHOD(TestWprowadzZmiany)
        {
            ZarzadzanieTerminami zarzadzanieTerminami;

            string* nowaListaTerminow = nullptr;
            int nowaLiczbaTerminow = 0;

            // Symulacja wejœcia u¿ytkownika
            istringstream input("NowyTermin1\nNowyTermin2\nkoniec");

            // Przekazanie strumienia wejœciowego jako argument
            bool zmianyWprowadzone = zarzadzanieTerminami.wprowadzZmiany(input, nowaListaTerminow, nowaLiczbaTerminow);

            Assert::IsTrue(zmianyWprowadzone);
            Assert::AreEqual(2, nowaLiczbaTerminow);
            Assert::AreEqual(string("NowyTermin1"), nowaListaTerminow[0]);
            Assert::AreEqual(string("NowyTermin2"), nowaListaTerminow[1]);

            delete[] nowaListaTerminow;
        }

        TEST_METHOD(TestAktualizujBazeDanych)
        {
            ZarzadzanieTerminami zarzadzanieTerminami;

            string* nowaListaTerminow = new string[2]{ "NowyTermin1", "NowyTermin2" };
            int nowaLiczbaTerminow = 2;

            zarzadzanieTerminami.aktualizujBazeDanych(nowaListaTerminow, nowaLiczbaTerminow);

            const string* listaTerminow = zarzadzanieTerminami.bazaDanych.listaTerminow;
            int liczbaTerminow = zarzadzanieTerminami.bazaDanych.liczbaTerminow;

            Assert::AreEqual(2, liczbaTerminow);
            Assert::AreEqual(string("NowyTermin1"), listaTerminow[0]);
            Assert::AreEqual(string("NowyTermin2"), listaTerminow[1]);

            delete[] nowaListaTerminow;
        }
    };
}
