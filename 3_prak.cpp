#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct menuItemType {
    string menuItem;
    double menuPrice;
};

const int PATIEKALU_KIEKIS = 8;

// nuskaito meniu su tarpais 
void getData(menuItemType meniuSarasas[]) {
    ifstream fin("menu.txt");
    if (!fin) {
        cout << "Klaida: nepavyko atidaryti menu.txt" << endl;
    }

    for (int i = 0; i < PATIEKALU_KIEKIS; i++) {
        string eilute;
        getline(fin, eilute);

        int pos = eilute.find_last_of(' ');
        meniuSarasas[i].menuItem = eilute.substr(0, pos);
        meniuSarasas[i].menuPrice = stod(eilute.substr(pos + 1));
    }

    fin.close();
}

// rodo meniu
void showMenu(menuItemType meniuSarasas[]) {
    cout << "Sveiki atvykę į restoraną!\n\n";
    cout << "Pusryčių meniu:\n";

    for (int i = 0; i < PATIEKALU_KIEKIS; i++) {
        cout << i + 1 << ". " << meniuSarasas[i].menuItem << " - "
             << fixed << setprecision(2) << meniuSarasas[i].menuPrice << "€" << endl;
    }

    cout << "\nPasirinkite patiekalus (0 - baigti):\n";
}

// spausdina sąskaitą 
void printCheck(menuItemType meniuSarasas[], int kiekiai[]) {
    ofstream fout("receipt.txt");

    double tarpineSuma = 0.0;

    cout << "\n--- Jūsų užsakymas ---\n\n";
    fout << "Jūsų užsakymas:\n\n";

    for (int i = 0; i < PATIEKALU_KIEKIS; i++) {
        if (kiekiai[i] > 0) {
            double suma = meniuSarasas[i].menuPrice * kiekiai[i];
            tarpineSuma += suma;

            cout << kiekiai[i] << "  " << meniuSarasas[i].menuItem << "  "
                 << fixed << setprecision(2) << suma << "€\n";

            fout << kiekiai[i] << "  " << meniuSarasas[i].menuItem << "  "
                 << fixed << setprecision(2) << suma << "€\n";
        }
    }

    double pvm = tarpineSuma * 0.21;
    double galutine = tarpineSuma + pvm;

    cout << "\nMokesčiai (21%): " << fixed << setprecision(2) << pvm << "€\n";
    cout << "Galutinė suma: " << fixed << setprecision(2) << galutine << "€\n";

    fout << "\nMokesčiai (21%): " << fixed << setprecision(2) << pvm << "€\n";
    fout << "Galutinė suma: " << fixed << setprecision(2) << galutine << "€\n";

    fout.close();
}

int main() {
    menuItemType meniuSarasas[PATIEKALU_KIEKIS];

    // programa veikia be sustojimo 
    while (true) {
        int kiekiai[PATIEKALU_KIEKIS] = {0};

        getData(meniuSarasas);
        showMenu(meniuSarasas);

        while (true) {
            int pasirinkimas;
            cout << "Pasirinkite patiekalo numerį: ";
            cin >> pasirinkimas;

            if (pasirinkimas == 0) break;
            if (pasirinkimas < 1 || pasirinkimas > PATIEKALU_KIEKIS) {
                cout << "Neteisingas pasirinkimas.\n";
                continue;
            }

            int porcijos;
            cout << "Įveskite porcijų kiekį: ";
            cin >> porcijos;

            if (porcijos > 0)
                kiekiai[pasirinkimas - 1] += porcijos;
        }

        printCheck(meniuSarasas, kiekiai);

        cout << "\nSąskaita įrašyta į receipt.txt\n";
        cout << "\nNorite atlikti naują užsakymą? (1 - taip, 0 - išeiti): ";

        int testi;
        cin >> testi;

        if (testi == 0) {
            cout << "Programa baigta.\n";
            break;
        }

        cout << "\n--- Naujas užsakymas ---\n\n";
    }

    return 0;
}
