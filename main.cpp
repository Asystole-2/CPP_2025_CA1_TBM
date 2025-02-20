#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

void readfile();

void legosets();

void display();

void parse();

/*
 Formate: Set_ID,Set_Name,Theme,Piece_Count,Price

Themes: Ninjago
Marvel   Star Wars   Minecraft   Creator   City    Friends   Harry Potter
Technic   Architecture   DC   Ideas   Super Mario   Disney   Jurassic World
*/
//std::vector<std::tuple <int, std::string> > myArr;
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
            if (line!="") {
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

    for (const auto &set : legosets) {
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

void legosets() {
    vector<LegoSet> legosets;
    string filename = "lego_sets_120.csv";
    readfile(filename, legosets);
    display(legosets);
}
