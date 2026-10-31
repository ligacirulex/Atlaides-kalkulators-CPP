#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Funkcija, kas pārbauda, vai teksts ir skaitlis
// Atļauj: ciparus, punktu, komatu un mīnusa zīmi tikai pirmajā pozīcijā
bool irSkaitlis(const string &txt) {
    for (int i = 0; i < txt.size(); i++) {
        char c = txt[i];

        // atļaujam mīnusa zīmi tikai kā pirmo simbolu
        if (c == '-' && i == 0)
            continue;

        // pārējie simboli drīkst būt tikai cipari, punkts vai komats
        if (!isdigit(c) && c != '.' && c != ',')
            return false;
    }
    return true;
}

int main() {

    double cena;
    double galaCena;
    double ietaupitaNauda;
    int atlaide;
    string ievadeCena;
    string ievadeAtlaide;
    string izvele;

    cout << fixed << setprecision(2); // 2 cipari aiz komata

    do {
        // ===== CENA =====
        cout << "Ievadi preces cenu (EUR): ";
        cin >> ievadeCena;

        // pārbauda, vai ievadē nav neatļautu simbolu
        if (!irSkaitlis(ievadeCena)) {
            cout << "\033[41mKļūda! Cenai jāsastāv tikai no cipariem.\033[0m" << endl;
            continue;
        }

        // aizstāj komatu ar punktu
        for (char &c : ievadeCena)
            if (c == ',') c = '.';

        cena = stod(ievadeCena); // pārvērš tekstu par skaitli(double)


        // ===== ATLAIDE =====
        cout << "Ievadi atlaidi procentos (0-100): ";
        cin >> ievadeAtlaide;

        // pārbauda, vai ievadē nav neatļautu simbolu
        if (!irSkaitlis(ievadeAtlaide)) {
            cout << "\033[41mKļūda! Atlaidei jāsastāv tikai no cipariem.\033[0m" << endl;
            continue;
        }

        // atlaidei nevajag komatus vai punktus
        for (char c : ievadeAtlaide) {
            if (c == '.' || c == ',') {
                cout << "\033[41mKļūda! Atlaidei jābūt veselam skaitlim.\033[0m" << endl;
                goto turpinat;
            }
        }

        atlaide = stoi(ievadeAtlaide);//pārvers tekstu par skaitli(int)


        // ===== KĻŪDU PĀRBAUDES =====
        if (cena < 0 || atlaide < 0) {
            cout << "\033[41mKļūda! Cena un atlaide nevar būt negatīvas.\033[0m" << endl;
        }
        else if (atlaide > 100) {
            cout << "\033[41mKļūda! Atlaide nevar būt lielāka par 100%.\033[0m" << endl;
        }
        else if (cena == 0) {
            cout << "\033[44mPrece ir dāvana, atlaide netiek piemērota.\033[0m" << endl;
        }
        else if (atlaide == 0) {
            cout << "Atlaide nav piemērota." << endl;
            cout << "Cena: " << cena << " EUR" << endl;
        }
        else {
            // ===== APRĒĶINS =====
            ietaupitaNauda = cena * atlaide / 100;
            galaCena = cena - ietaupitaNauda;

            // ===== IZVADE =====
            if (atlaide > 30) {
                cout << "\033[33m"; // dzeltena krāsa
                cout << "Cena ar atlaidi: " << galaCena << " EUR" << endl;
                cout << "Tu ietaupiji: " << ietaupitaNauda << " EUR" << endl;
                cout << "\033[0m";  // atpakaļ uz normālu krāsu
            } else {
                cout << "Cena ar atlaidi: " << galaCena << " EUR" << endl;
                cout << "Tu ietaupiji: " << ietaupitaNauda << " EUR" << endl;
            }
        }

        // ===== TURPINĀŠANA =====
        turpinat:
        cout << "Vai vēlies aprēķināt vēlreiz? (jā/nē): ";
        cin >> izvele;

    } while (izvele == "jā" || izvele == "Jā");

    cout << "Programma beigusies." << endl;
    return 0;
}

