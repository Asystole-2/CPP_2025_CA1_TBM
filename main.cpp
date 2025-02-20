#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <set>
using namespace std;

void readfile();

void display();

void parse();

int indexOfTheme();

int indexOfName();

void displayLegoMatchingTheme();

void displayLegoMatchingName();

void menu();

/*
 Formate: Set_ID,Set_Name,Theme,Piece_Count,Price

Themes: Ninjago
Marvel   Star Wars   Minecraft   Creator   City    Friends   Harry Potter
Technic   Architecture   DC   Ideas   Super Mario   Disney   Jurassic World
*/
//std::vector<std::tuple <int, std::string> > myArr;
/*
3.	Write a function that will accept the vector of structs,
iterate through the data loaded in stage 2 and accumulate a count of the number of rows that are a match for each of the unique values in a chosen column.
For example, if you chose movie data then this function could return the number of movies of each genre (comedy, thriller, drama, etc.).
This function should return a map containing all information.
*/

struct LegoSet {
    string setID;
    string setName;
    string theme;
    int pieceCount;
    double price;
};

void parse(string line, LegoSet &lego_set) {
    stringstream ss(line);
    string temp;

    getline(ss, temp, ',');
    lego_set.setID = temp;

    getline(ss, temp, ',');
    lego_set.setName = temp;

    getline(ss, temp, ',');
    lego_set.theme = temp;

    getline(ss, temp, ',');
    lego_set.pieceCount = stoi(temp);

    getline(ss, temp, ',');
    lego_set.price = stod(temp);
}

void readfile(string filename, vector<LegoSet> &legosets) {
    LegoSet legoset;
    ifstream fin(filename);
    if (fin) {
        string line;

        while (!fin.eof()) {
            getline(fin, line);
            if (line != "") {
                parse(line, legoset);
                legosets.push_back(legoset);
            }
        }
        fin.close();
    } else {
        cout << "Unable to open file" << endl;
        exit(1);
    }
}

void display(const vector<LegoSet> &legosets) {
    cout << "--------------------------------------------------------\n";
    cout << "|                   LEGO COLLECTION                    |\n";
    cout << "--------------------------------------------------------\n";

    for (const auto &set: legosets) {
        cout << " ID: " << set.setID << "\n";
        cout << " Name: " << set.setName << "\n";
        cout << " Theme: " << set.theme << "\n";
        cout << " Pieces: " << set.pieceCount << "\n";
        cout << fixed << std::setprecision(2);
        cout << " Price: " << set.price << "\n";
        cout << "--------------------------------------------------------\n";
    }
    cout << " End of Collection \n";
}

int indexOfTheme(vector<LegoSet> &lego_sets, string &theme) {
    int index = -1;

    if (!lego_sets.empty()) {
        for (int i = 0; i < lego_sets.size(); i++) {
            if (lego_sets[i].theme == theme) {
                index = i;
            }
        }
    } else {
        cout << " The vector is empty " << endl;
    }

    return index;
}
int indexOfName(vector<LegoSet> &lego_sets, string &setName) {
    int index = -1;

    if (!lego_sets.empty()) {
        for (int i = 0; i < lego_sets.size(); i++) {
            if (lego_sets[i].setName == setName) {
                index = i;
            }
        }
    } else {
        cout << " The vector is empty " << endl;
    }

    return index;
}

void displayLegoMatchingTheme(vector<LegoSet> &lego_sets) {
    string legoTheme;
    cout << "* * * * * * * * * * * * * * * * * * *" << endl;
    cout << "*            THEME SEARCH           *"  << endl;
    cout << "* * * * * * * * * * * * * * * * * * *" << endl;
    cout << "Enter the theme for the lego set you are looking for: " << endl;
    cin.ignore();
    getline(cin,legoTheme);
    int index = indexOfTheme(lego_sets, legoTheme);

    cout << "---------------------------------------------\n";
    cout << "         Search result for: "<< legoTheme << endl;
    cout << "---------------------------------------------\n";

    if (index > -1 && index <= lego_sets.size()) {
        if (!lego_sets.empty()) {
            cout << " Name: " << lego_sets[index].setName << "\n";
            cout << " Theme: " << lego_sets[index].theme << "\n";
            cout << " Piece count: " <<lego_sets[index].pieceCount << "\n";
            cout << " Price: " << lego_sets[index].price << " euro\n";
            cout << "-----------------------------\n";
        }
        else {
            cout << " The vector is empty " << endl;
        }
    } else {
        cout << "Invalid theme [index: " << index <<"]" << endl;
    }

}

void displayLegoMatchingName(vector<LegoSet> &lego_sets) {
    string legoSetname;
    cout << "* * * * * * * * * * * * * * * * * *" << endl;
    cout << "*           NAME  SEARCH          *"  << endl;
    cout << "* * * * * * * * * * * * * * * * * *" << endl;
    cout << "Enter the name for the lego set you are looking for: " << endl;
    cin.ignore();
    getline(cin,legoSetname);
    int index = indexOfName(lego_sets, legoSetname);

    cout << "-------------------------------------\n";
    cout << "         Search result for: " <<  endl;
    cout << "         "<< legoSetname << endl;
    cout << "-------------------------------------\n";

    if (index > -1 && index <= lego_sets.size()) {
        if (!lego_sets.empty()) {
            cout << " Name: " << lego_sets[index].setName << "\n";
            cout << " Theme: " << lego_sets[index].theme << "\n";
            cout << " Piece count: " <<lego_sets[index].pieceCount << "\n";
            cout << " Price: " << lego_sets[index].price << " euro\n";
            cout << "-----------------------------\n";
        }
        else {
            cout << " The vector is empty " << endl;
        }
    } else {
        cout << "Invalid set name [index: " << index <<"]" << endl;
    }

}

void menu(vector<LegoSet> &legosets) {
    int choice;
    do {
        cout << "--------------------------------------------------\n";
        cout << " *            LEGO COLLECTION MENU              * \n";
        cout << "--------------------------------------------------\n";
        cout << "         1. Display all Lego sets\n";
        cout << "         2. Search for a Lego set by name\n";
        cout << "         3. Search for a Lego set by theme\n";
        cout << "         4. Exit\n";
        cout << " Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                display(legosets);
            break;
            case 2:
                displayLegoMatchingName(legosets);
            break;
            case 3:
                displayLegoMatchingTheme(legosets);
            break;
            case 4:
                cout << "Exiting the program.\n";
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

int main() {
    vector<LegoSet> legosets;
    string filename = "lego_sets_120.csv";
    readfile(filename, legosets);
    menu(legosets);
    return 0;
}


