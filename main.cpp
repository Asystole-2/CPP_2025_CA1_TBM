#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <limits>
#include <map>

using namespace std;

void readfile();

void display();

void parse();

int indexOfTheme();

int indexOfName();

void displayThemeMap();

void displayLegoMatchingTheme();

void displayLegoMatchingName();

void pieceCountInformation();

void displayDescFloat();

void displayAscFloat();

void menu();

struct LegoSet {
    string setID;
    string setName;
    string theme;
    int pieceCount = 0;
    double price = 0.0;
};

void parse(const string &line, LegoSet &lego_set) {
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

void readfile(const string &filename, vector<LegoSet> &legoSets) {
    if (ifstream fin(filename); fin) {
        LegoSet legoSet;
        string line;

        while (!fin.eof()) {
            getline(fin, line);
            if (!line.empty()) {
                parse(line, legoSet);
                legoSets.push_back(legoSet);
            }
        }
        fin.close();
    } else {
        cout << "Unable to open file" << endl;
        exit(1);
    }
}

void display(const vector<LegoSet> &legoSets) {
    cout << "--------------------------------------------------------\n";
    cout << "|                   LEGO COLLECTION                    |\n";
    cout << "--------------------------------------------------------\n";

    for (const auto &set: legoSets) {
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

void displayDescFloat(vector<LegoSet> &legoSets) {
    auto func = [](LegoSet x, LegoSet y) { return x.price > y.price; };
    sort(legoSets.begin(), legoSets.end(), func);

    cout << "--------------------------------------------------------\n";
    cout << "|               HIGHEST TO LOWEST PRICE                 |\n";
    cout << "--------------------------------------------------------\n";

    for (const auto &set: legoSets) {
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

bool customComparator(const LegoSet &a, const LegoSet &b) {
    return a.price < b.price;
}

void displayAscFloat(vector<LegoSet> &legoSets) {
    sort(legoSets.begin(), legoSets.end(), customComparator);

    cout << "--------------------------------------------------------\n";
    cout << "|               LOWEST TO HIGHEST PRICE                 |\n";
    cout << "--------------------------------------------------------\n";

    for (const auto &set: legoSets) {
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


map<string, int> themeMap(const vector<LegoSet> &legoSets);

void displayThemeMap(const vector<LegoSet> &legoSets) {
    map<string, int> themes = themeMap(legoSets);

    cout << "<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>> " << endl;
    cout << "<              THEMES              >" << endl;
    cout << "<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>> " << endl;

    for (const auto &[theme,count]: themes) {
        cout << "         > " << theme << ": " << count << endl;
    }
    cout << "<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>> " << endl;
}

map<string, int> themeMap(const vector<LegoSet> &legoSets) {
    map<string, int> themeCount;
    for (const auto &set: legoSets) {
        themeCount[set.theme]++;
    }
    return themeCount;
}

int indexOfName(const vector<LegoSet> &lego_sets, const string &setName) {
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
    string legoSetName;
    cout << "* * * * * * * * * * * * * * * * * *" << endl;
    cout << "*           NAME  SEARCH          *" << endl;
    cout << "* * * * * * * * * * * * * * * * * *" << endl;
    cout << "Enter the name for the lego set you are looking for: " << endl;
    cin.ignore();
    getline(cin, legoSetName);
    int index = indexOfName(lego_sets, legoSetName);

    cout << "-------------------------------------\n";
    cout << "         Search result for: " << endl;
    cout << "         " << legoSetName << endl;
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

void pieceCountInformation(const vector<LegoSet> &lego_sets) {
    int mostPieces = 0, leastPieces = mostPieces, allPieces = 0;

    for (const auto &lego_set: lego_sets) {
        allPieces += lego_set.pieceCount;

        if (lego_set.pieceCount > mostPieces) {
            mostPieces = lego_set.pieceCount;
        }
        if (lego_set.pieceCount < mostPieces) {
            leastPieces = lego_set.pieceCount;
        }
    }
    cout << "###########################################################\n";
    cout << "##                 SET PIECE INFORMATICS                 ##" << endl;
    cout << "###########################################################\n\n";

    for (const auto &lego_set: lego_sets) {
        if (lego_set.pieceCount == leastPieces) {
            cout << "           ----------------------------------------" << endl;
            cout << "            Lego set with the lowest piece-count: " << endl;
            cout << "           ----------------------------------------" << endl;
            cout << "                  " << lego_set.setName << "\n";
            cout << "                  " << lego_set.theme << "\n";
            cout << "                  " << lego_set.price << " euro\n";
            cout << "           -----------------------------------------" << endl;
            cout << "            Contains:   * " << leastPieces << " pieces *" << endl;
            cout << "           ----------------------------------------" << endl;
        }
        if (lego_set.pieceCount == mostPieces) {
            cout << "           ----------------------------------------" << endl;
            cout << "            Lego set with the highest piece-count:" << endl;
            cout << "           ----------------------------------------" << endl;
            cout << "                " << lego_set.setName << "\n";
            cout << "                " << lego_set.theme << "\n";
            cout << "                " << lego_set.price << " euro\n";
            cout << "           ---------------------------------------" << endl;
            cout << "            Contains:   * " << mostPieces << " pieces *" << endl;
            cout << "           ----------------------------------------" << endl;
            cout << "  ...........................SPI..........................\n";
        }
    }

    const int averagePieces = allPieces / lego_sets.size();
    cout << "\n  Average piece count of all sets in the collection: " << averagePieces << "\n";
    cout << "\n###########################################################\n";
}

void menu(vector<LegoSet> &legoSets) {
    int choice;
    do {
        cout << "--------------------------------------------------\n";
        cout << " *            LEGO COLLECTION MENU              * \n";
        cout << "--------------------------------------------------\n\n";
        cout << "         1. Display all Lego sets\n";
        cout << "         2. Search for a Lego set by name\n";
        cout << "         3. Theme Map\n";
        cout << "         4. Search for a Lego set by theme\n";
        cout << "         5. Piece Count Insights\n";
        cout << "         6. Prices in ascending order\n";
        cout << "         7. Prices in descending order\n";
        cout << "         8. Exit\n";

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
                display(legoSets);
                break;
            case 2:
                displayLegoMatchingName(legoSets);
                break;
            case 3:
                displayThemeMap(legoSets);
                break;
            case 4:
                displayLegoMatchingTheme(legoSets);
                break;
            case 5:
                pieceCountInformation(legoSets);
                break;
            case 6:
                displayAscFloat(legoSets);
                break;
            case 7:
                displayDescFloat(legoSets);
                break;
            case 8:
                cout << "Exiting the program.......\n\n      bye bye :) \n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 8);
}

int main() {
    vector<LegoSet> legoSets;
    const string filename = "lego_sets_120.csv";
    readfile(filename, legoSets);
    menu(legoSets);
    return 0;
}

/*
6.	Write a function that will search through the data and return a list of all items that match or partially match a given text input.
For example, all movies that contain the text “The” in the title. Iterators must be used for this function.

*/


/*
 Total amount of pieces:252,702
  Highest: 5923
  Lowest: 830
  numbers = [
2420, 4708, 4062, 378, 2016, 143, 4535, 1969, 3347, 4726, 1186, 2935, 1050, 4911, 1949,
332, 1999, 923, 4581, 1731, 2259, 3636, 2554, 2962, 4917, 1162, 2273, 4747, 2566, 1762,
1873, 4713, 4911, 735, 3517, 3151, 4571, 2958, 170, 3606, 4050, 191, 2279, 3180, 1899,
3271, 3074, 1174, 360, 2858, 1316, 4123, 3121, 2571, 749, 2803, 347, 4241, 951, 1970,
838, 4112, 4951, 3518, 2568, 4533, 1804, 4953, 3202, 3858, 4941, 2635, 3355, 3056, 2381,
2318, 4184, 3581, 572, 54, 3036, 3200, 480, 2207, 1360, 1677, 1070, 922, 1197, 2079,
5923, 231, 2352, 3210, 878, 3120, 565, 2354, 1125, 830
]
*/

//References:    https://www.geeksforgeeks.org/sort-c-stl/
