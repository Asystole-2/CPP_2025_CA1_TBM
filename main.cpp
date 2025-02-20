#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <limits>
#include <map>
#include <set>
using namespace std;

void readfile();

void display();

void parse();

int indexOfTheme();

int indexOfName();

void displayThemeMap();

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

map<string, int> themeMap(const vector<LegoSet> & legosets);

void displayThemeMap(const vector<LegoSet> &legosets){
    map <string, int> themes = themeMap(legosets);

    cout << "<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>> "<< endl;
    cout << "<              THEMES              >" << endl;
    cout << "<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>> "<< endl;

    for (const auto &[theme,count] : themes) {
        cout <<"         > "<< theme <<": "<< count<< endl;
    }
    cout << "<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>> "<< endl;

}
 map<string,int> themeMap(const vector<LegoSet> &legosets) {
    map<string,int > themeCount;
    for (const auto &set: legosets) {
        themeCount[set.theme]++;
    }
    return themeCount;
}

int indexOfName(const vector<LegoSet> &lego_sets, string &setName) {
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

void displayLegoMatchingTheme(const vector<LegoSet> &lego_sets) {
    string legoTheme;
    int count = 0;
    cout << "* * * * * * * * * * * * * * * * * * *" << endl;
    cout << "*            THEME SEARCH           *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * *" << endl;
    cout << "Enter the theme for the lego set you are looking for: " << endl;
    cin.ignore();
    getline(cin, legoTheme);
    cout << "---------------------------------------------\n";
    cout << "         Search result for: " << legoTheme << endl;
    cout << "---------------------------------------------\n";

    for (int i = 0; i < lego_sets.size(); i++) {
        if (lego_sets[i].theme == legoTheme) {
            count++;
            if (!lego_sets.empty()) {
                cout << " ID: " << lego_sets[i].setID << endl;
                cout << " Name: " << lego_sets[i].setName << "\n";
                cout << " Piece count: " << lego_sets[i].pieceCount << "\n";
                cout << " Price: " << lego_sets[i].price << " euro\n";
                cout << "---------------------------------------------\n";
            } else {
                cout << " The vector is empty " << endl;
            }
        }
    }
    cout << "         " << count << " lego sets found" << endl;
    cout << "---------------------------------------------\n";
}

void displayLegoMatchingName(const vector<LegoSet> &lego_sets) {
    string legoSetname;
    cout << "* * * * * * * * * * * * * * * * * *" << endl;
    cout << "*           NAME  SEARCH          *" << endl;
    cout << "* * * * * * * * * * * * * * * * * *" << endl;
    cout << "Enter the name for the lego set you are looking for: " << endl;
    cin.ignore();
    getline(cin, legoSetname);
    int index = indexOfName(lego_sets, legoSetname);

    cout << "-------------------------------------\n";
    cout << "         Search result for: " << endl;
    cout << "         " << legoSetname << endl;
    cout << "-------------------------------------\n";

    if (index > -1 && index <= lego_sets.size()) {
        if (!lego_sets.empty()) {
            cout << " ID: " << lego_sets[index].setID << endl;
            cout << " Theme: " << lego_sets[index].theme << "\n";
            cout << " Piece count: " << lego_sets[index].pieceCount << "\n";
            cout << " Price: " << lego_sets[index].price << " euro\n";
            cout << "-----------------------------\n";
        } else {
            cout << " The vector is empty " << endl;
        }
    } else {
        cout << "Invalid set name [index: " << index << "]" << endl;
    }
}

void menu(const vector<LegoSet> &legosets) {
    int choice;
    do {
        cout << "--------------------------------------------------\n";
        cout << " *            LEGO COLLECTION MENU              * \n";
        cout << "--------------------------------------------------\n";
        cout << "         1. Display all Lego sets\n";
        cout << "         2. Search for a Lego set by name\n";
        cout << "         3. Theme Map\n";
        cout << "         4. Search for a Lego set by theme\n";
        cout << "         5. Exit\n";
        cout << " Enter your choice: ";

        cin.clear();

        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                display(legosets);
                break;
            case 2:
                displayLegoMatchingName(legosets);
                break;
            case 3:
                displayThemeMap(legosets);
            break;
            case 4:
                displayLegoMatchingTheme(legosets);
                break;
            case 5:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 5);
}

int main() {
    vector<LegoSet> legosets;
    string filename = "lego_sets_120.csv";
    readfile(filename, legosets);
    menu(legosets);
    return 0;
}
