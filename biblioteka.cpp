#include <iostream>
#include <fstream>
 using namespace std;

class Baza_danych{
    string baza_kont="baza_kont.txt";
    public:

    bool znajdzkonto(string login, string haslo)
	{
		ifstream plik;
		plik.open(baza_kont);
		string l,h, buf;
		while (!plik.eof()||l!=login){
            plik>>l >> h;
            cout<<"\n"<<l<<endl;
            }
            if(l==login && h==haslo){
                return true;
            }
            if(l==login && h!=haslo){
                return false;
            }
            return false;
    }

//         bool znajdzlogin(string login) {
//     ifstream plik;
//     plik.open(baza_kont);
//     string l, haslo; // Dodaj zmienną haslo
//     bool znaleziono = false;

//     while (plik >> l >> haslo) {
//         if (l == login) {
//             znaleziono = true;
//             break; // Jeśli znaleziono login, nie ma potrzeby kontynuowania pętli
//         }
//     }

//     plik.close();
//     return znaleziono;
// }

        bool znajdzlogin(string login){
            ifstream plik;
            plik.open(baza_kont);
            string l,h;
            while(!plik.eof()){
                while(l!=login){
                    plik>>l>>h;
                }
            plik.close();
            return true;
            }
        plik.close();
        return false;
        }            
        
        void dodajkonto(string login, string haslo){
            ofstream plik;
            plik.open(baza_kont, ios::app);
            plik<<login<<" "<<haslo<<endl;
            plik.close();
            return;
        }
	};

class Kontroler{
    Baza_danych baza_danych;
    public:
    bool logowanie(string login, string haslo){
        if(baza_danych.znajdzkonto(login, haslo)){
            return true;
        }
        else{
            return false;
        }
    }

    bool rejestracja(string login, string haslo){
        if(!baza_danych.znajdzlogin(login)){
            baza_danych.dodajkonto(login, haslo);
            cout<<"Zarejestrowano";
            return true;
        }
        else{
            return false;
        }
    }
    
};

class Interface{
    Kontroler kontroler;
    public:
    void logowanie(){
        string login,haslo;
        cout<<"Login:";
        cin>>login;
        cout<<"\nHaslo:";
        cin>>haslo;
        if(!kontroler.logowanie(login,haslo)){
            cout<<"Zle dane. Wprowadz login i haslo ponownie"<<endl;
            cout<<"Login:";
            cin>>login;
            cout<<"\nHaslo:";
            cin>>haslo;
            kontroler.logowanie(login, haslo);
        }
        else{
            cout<<"Zalogowano"<<endl;
        }
        return;
    }
    
    void rejestracja(){
        string login,haslo,haslo2;
        cout<<"Login:";
        cin>>login;
        cout<<"\nHaslo:";
        cin>>haslo;
        while(haslo!=haslo2){
        cout<<"\nHaslo powtornie:";
        cin>>haslo2;
    }
        while(!kontroler.rejestracja(login, haslo)){
            cout<<"Login zajety"<<endl;
            cout<<"Login:";
            cin>>login;
            cout<<"\nHaslo:";
            cin>>haslo;
            while(haslo!=haslo2){
            cout<<"\nHaslo powtornie:";
            cin>>haslo2;
            kontroler.rejestracja(login, haslo);
        };
    };
    }
};

 void ClientCode(Interface interface){
    int pom;
    cout<<"1.Logowanie\t2.Rejestracja"<<endl;
    while(1){
        cin>>pom;
    if(pom==1 || pom==2){
        break;
    }
    else{
       cout<<"Podano zla opcje. Wybierz jeszcze raz"<<endl;
    }
    }
    switch (pom){
        case 1:
            interface.logowanie();
            break;
        case 2:
            interface.rejestracja();
            break;
    }

 }

 int main() {
    Interface interface;
    ClientCode(interface);

    return 0;
}
