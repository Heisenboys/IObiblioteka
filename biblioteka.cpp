#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

class Baza_danych {
    string baza_kont = "baza_kont.txt";
    string baza_ksiazek = "baza_ksiazek.txt";
public:

    void katalog() {
        ifstream plik;
        string linia, reszta;
        plik.open(baza_ksiazek);
        while (!plik.eof()) {
            getline(plik, linia, ';');
            getline(plik, reszta);
            cout << linia << endl;
        }
        return;
    }

    bool znajdzkonto(string login, string haslo)
    {
        ifstream plik;
        plik.open(baza_kont);
        string l, h, buf;
        while (plik >> l) {
            plik >> h;
            if (l == login && h == haslo) {
                return true;
            }
            else if (l == login && h != haslo) {
                return false;
            }
        }
        return false;
    }

    bool znajdzlogin(string login) {
        ifstream plik;
        plik.open(baza_kont);
        string l, h;
        while (plik >> l) {
            plik >> h;
            if (login == l)
            {
                plik.close();
                return true;
            }
        }
        plik.close();
        return false;
    }

    void dodajkonto(string login, string haslo) {
        ofstream plik;
        plik.open(baza_kont, ios::app);
        plik << login << " " << haslo << endl;
        plik.close();
        return;
    }

    void zmianadostepnosci(string autor, string tytul, int plusminus) {
        ofstream plik;
        ifstream plik2;
        string linia;
        plik2.open(baza_ksiazek);
        plik.open("temporary.txt", ios::app);
        int i = 0;
        while (getline(plik2, linia)) {

            if (i)
                plik << endl;
            i++;
            if (linia.find(autor) != string::npos && linia.find(tytul) != string::npos) {
                string::iterator i = linia.end() - 1;
                (*i) += plusminus;
                plik <<linia;
            }
            else
                plik <<linia;
        }
            plik.close();
            plik2.close();
            remove("baza_ksiazek.txt");
            rename("temporary.txt", "baza_ksiazek.txt");
    }

    void zmianaflagilisty(string autor, string tytul) {
        ofstream plik;
        ifstream plik2;
        string linia;
        int i = 0;
        plik2.open(baza_ksiazek);
        plik.open("temporary.txt", ios::app);
        while (getline(plik2, linia)) {
            if (i)
                plik << endl;
            i++;
            if (linia.find(autor) != string::npos && linia.find(tytul) != string::npos) {
                string::iterator i = linia.end() - 3;
                (*i) = '1';
                plik << linia;
            }
            else {
                plik << linia;
            }
        }
            plik.close();
            plik2.close();
            remove("baza_ksiazek.txt");
            rename("temporary.txt", "baza_ksiazek.txt");
    }

    bool czyksiazkajestwkatalogu(string autor, string tytul) {
        ifstream plik;
        string autorp, tytulp, reszta;
        plik.open(baza_ksiazek);
        while (!plik.eof()) {
            getline(plik, autorp, ',');
            getline(plik, tytulp, ';');
            getline(plik, reszta);
            if (autor == autorp && " " + tytul == tytulp)
                return true;
        }
        return false;
    }

    bool czyksiazkajestdostepna(string autor, string tytul) {
        ifstream plik;
        string autorp, tytulp,buf;
        int syf,syf2,syf3;
        int iloscdostepnych;
        plik.open(baza_ksiazek);
        while (!plik.eof()) {
            getline(plik, autorp, ',');
            getline(plik, tytulp, ';');
            plik >> syf >> syf2 >> iloscdostepnych;
            getline(plik, buf);
            if (autor == autorp && " " + tytul == tytulp) {
                if (iloscdostepnych > 0) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
        return false;
    }

    void zapisznaliste(string autor, string tytul, string login) {
        string nazwa = autor + " " + tytul+".txt";
        ofstream plik;
        plik.open(nazwa, ios::app);
        plik << login << endl;
        plik.close();
    }

    bool czyksiazkabylawypozyczona(string autor, string tytul) {
        ifstream plik;
        string autorp, tytulp, buf;
        int syf;
        int pierwotna, zmienna; //pierwotna to ile kopii bylo oryginalnie w bibliotece, zmienna to terazniejsza ilosc kopii
        plik.open(baza_ksiazek);
        while (!plik.eof()) {
            getline(plik, autorp, ',');
            getline(plik, tytulp, ';');
            plik >> pierwotna >> syf >> zmienna;
            getline(plik, buf);
            if (autor == autorp && " " + tytul == tytulp) {
                if (pierwotna == zmienna) {
                    return false;
                }
                else {
                    return true;
                }
            }
        }
    }

    void powiadomienia(string autor, string tytul){
        ifstream plik;
        string nazwa = autor + " " + tytul+".txt";
        string linia;
        plik.open(nazwa);
        if(!plik.is_open()){
            return;
        }
        cout<<"Wysylam powiadomienia do tych uzytkownikow"<<endl;
        while(getline(plik, linia)){
            cout<<linia<<endl;
        }
        plik.close();
        char* xd = new char[nazwa.length()+1];
        // strcpy_s(xd, nazwa.length()+1, nazwa.c_str());
        strcpy(xd, nazwa.c_str());
        remove(xd);
        return;
    }

};

class Kontroler {
    Baza_danych baza_danych;
public:
    bool logowanie(string login, string haslo) {
        return(baza_danych.znajdzkonto(login, haslo));
    }

    bool rejestracja(string login, string haslo) {
        if (!baza_danych.znajdzlogin(login)) {
            baza_danych.dodajkonto(login, haslo);
            return true;
        }
        else {
            return false;
        }
    }

    void katalog() {
        baza_danych.katalog();
        return;
    }

    bool czyksiazkajestwkatalogu(string autor, string tytul) {
        return baza_danych.czyksiazkajestwkatalogu(autor, tytul);
    }

    bool czyksiazkajestdostepna(string autor, string tytul) {
        int pos, iloscdostepnych;
        if (baza_danych.czyksiazkajestdostepna(autor, tytul)) {
            baza_danych.zmianadostepnosci(autor, tytul, -1);
            return true;
        }
        else {
            return false;
        }
    }

    void zapisznaliste(string autor, string tytul, string login) {
        baza_danych.zapisznaliste(autor, tytul, login);
        baza_danych.zmianaflagilisty(autor, tytul);
        return;
    }

    bool czyksiazkabylawypozyczona(string autor, string tytul) {
        return baza_danych.czyksiazkabylawypozyczona(autor, tytul);
    }

    void zwrot(string autor, string tytul) {
        baza_danych.zmianadostepnosci(autor, tytul, 1);
        baza_danych.powiadomienia(autor, tytul);
        return;
    }

};

class Interface {
    Kontroler kontroler;
public:
    void logowanie(bool& x, string& login) {
        string haslo;
        cout << "Login:";
        cin >> login;
        cout << "\nHaslo:";
        cin >> haslo;
        if (kontroler.logowanie(login, haslo)) {
            cout << "Zalogowano" << endl;
            x = false;
        }
        else {
            cout << "Zle dane" << endl;
        }
        return;
    }

    void rejestracja(bool& x, string& login) {
        string haslo, haslo2;
        cout << "Login:";
        cin >> login;
        cout << "\nHaslo:";
        cin >> haslo;
        while (haslo != haslo2) {
            cout << "\nHaslo powtornie:";
            cin >> haslo2;
        }
        if (kontroler.rejestracja(login, haslo)) {
            cout << "Zarejestrowano" << endl;
            x = false;
            return;
        }
        else {
            cout << "Login zajety" << endl;
            return;
        }
    }

    void katalog() {
        cout << "Oto biblioteczny katalog" << endl;
        kontroler.katalog();
        return;
    }

    void wypozycz(string login) {
        string autor, tytul;
        while (getchar() != '\n') {
            ;
        }
        cout << "Podaj autora i tytul ksiazki ktora chcesz wypozyczyc" << endl;
        cout << "Autor:";
        getline(cin, autor);
        cout << "\nTytul:";
        getline(cin, tytul);
        if (!kontroler.czyksiazkajestwkatalogu(autor, tytul)) {
            cout << "Nie ma takiej ksiazki w katalogu" << endl;
            return;
        }
        else {
            if (kontroler.czyksiazkajestdostepna(autor, tytul)) {
                cout << "Milego czytania" << endl;
                return;
            }
            else {
                cout << "Ksiazka nie jest teraz dostepna. Czy chcesz zapisac sie na liste oczekujacych(0/1)?" << endl;
                int pom;
                cin >> pom;
                if (pom == 0) {
                    return;
                }
                else {
                    kontroler.zapisznaliste(autor, tytul, login);
                    return;
                }
            }
        }
    }

    void zwroc() {
        string autor, tytul;
        while (getchar() != '\n') {
            ;
        }
        cout << "Wypisz autora i tytul ksiazki ktora chcesz zwrocic" << endl;
        cout << "Autor:";
        getline(cin, autor);
        cout << "\nTytul:";
        getline(cin, tytul);
        if (!kontroler.czyksiazkajestwkatalogu(autor, tytul)) {
            cout << "Nie ma takiej ksiazki w katalogu" << endl;
            return;
        }
        else {
            if (!kontroler.czyksiazkabylawypozyczona(autor, tytul)) {
                cout << "Ta ksiazka nie byla wypozyczona" << endl;
                return;
            }
            else {
                kontroler.zwrot(autor, tytul);
                cout << "Dziekujemy za zwrot" << endl;
                return;
            }
        }
    }
};

void ClientCode(Interface& interface) {
    int pom;
    bool x = 1;
    string login;

    while (x) {
        while (true) {
            cout << "1.Logowanie\t2.Rejestracja" << endl;
            cin >> pom;
            if (pom == 1 || pom == 2) {
                break;
            }
            else {
                cout << "Podano zla opcje. Wybierz jeszcze raz" << endl;
            }
        }

        switch (pom) {
        case 1:
            interface.logowanie(x, login);
            break;
        case 2:
            interface.rejestracja(x, login);
            break;
        }
    }
    x = 1;
    while (x) {
        while (true) {
            cout << "1.Wyswietl katalog\t2.Wypozycz ksiazke\t3.Zwroc ksiazke" << endl;
            cin >> pom;
            if (pom == 1 || pom == 2 || pom == 3) {
                break;
            }
            else {
                cout << "Podano zla opcje. Wybierz jeszcze raz" << endl;
            }
        }

        switch (pom) {
        case 1:
            interface.katalog();
            break;
        case 2:
            interface.wypozycz(login);
            break;
        case 3:
            interface.zwroc();
            break;
        }
        cout << "Kliknij 0 zeby zakonczyc" << endl;
        cin >> x;
    }
}

int main() {
    Interface interface;
    ClientCode(interface);

    return 0;
}