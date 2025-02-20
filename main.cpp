#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <set>
using namespace std;

void readfile();

void legosets();

void display();

void parse();

int indexofvalue();

void displayLegomatchingSet_ID();

/*
 Formate: Set_ID,Set_Name,Theme,Piece_Count,Price

Themes: Ninjago
Marvel   Star Wars   Minecraft   Creator   City    Friends   Harry Potter
Technic   Architecture   DC   Ideas   Super Mario   Disney   Jurassic World
*/
//std::vector<std::tuple <int, std::string> > myArr;

/*2.	Write a function that will accept two parameters: the vector of structs and a value for a particular field (of your choosing).  The function will search through the vector elements for the value (in a particular field) and will return the index (int) of the located element,
or -1 if no match is found.  Use the returned index to access and display the contents of the struct, otherwise, display a not found message.

3.	Write a function that will accept the vector of structs,
iterate through the data loaded in stage 2 and accumulate a count of the number of rows that are a match for each of the unique values in a chosen column.
For example, if you chose movie data then this function could return the number of movies of each genre (comedy, thriller, drama, etc.).
This function should return a map containing all information.
*/

int main() {
    legosets();
    return 0;
}

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
    cout << "                   Lego Collection  \n";
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
int indexofvalue(vector<LegoSet> &lego_sets, string &Set_ID) {
    int index = -1;

    if (!lego_sets.empty()) {
        for (int i = 0; i < lego_sets.size(); i++) {
            if (lego_sets[i].setID == Set_ID) {
                index = i;
            }
        }
    } else {
        cout << " The vector is empty " << endl;
    }

    return index;
}

void displayLegomatchingSet_ID(vector<LegoSet> &lego_sets) {
    string legoSet_ID;
    cout << "Enter the ID for the lego set you are looking for: " << endl;
    cin >> legoSet_ID;
    int index = indexofvalue(lego_sets, legoSet_ID);

    cout << "--------------------------------------------------------\n";
    cout << "            Search result for: " << legoSet_ID << endl;
    cout << "--------------------------------------------------------\n";

    if (index > -1 && index <= lego_sets.size()) {
        if (!lego_sets.empty()) {
            cout << " Name: " << lego_sets[index].setName << "\n";
            cout << " Theme: " << lego_sets[index].theme << "\n";
            cout << " Piece count: " <<lego_sets[index].pieceCount << "\n";
            cout << " Price: " << lego_sets[index].price << " euro\n";
            cout << "--------------------------------------------------------\n";
        }
        else {
            cout << " The vector is empty " << endl;
        }
    } else {
        cout << "Invalid set ID [index: " << index <<"]" << endl;
    }

}

void legosets() {
    vector<LegoSet> legosets;
    string filename = "lego_sets_120.csv";
    readfile(filename, legosets);
    // display(legosets);
    displayLegomatchingSet_ID(legosets);
}


