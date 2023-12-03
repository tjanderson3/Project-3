#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "hashmap.h"
using namespace std;

int main() {
    ifstream dataFile("../Books_isbn.txt");
    string line;
    vector<string> books;
    vector<string> isbns;
    string book, isbn, header;
    getline(dataFile, header);
    while(getline(dataFile, line)){
        istringstream iss(line);
        iss >> isbn;
        getline(iss >> ws, book);
        isbns.push_back(isbn);
        books.push_back(book);
    }
    int option;
    dataFile.close();
    //cout << "Select an option (enter 1, 2, or 3):" << endl << "1. Insert Book and ISBN #" << endl << "2. Remove Book and ISBN #" << endl << "3. Find Book" << endl;
    //cin >> option;
    hashmap test;
    for(int i = 0; i < 100; i++){
        test.insert(isbns[i], books[i]);
    }
    for(int j = 0; j < 100; j++){
        cout << test.search(isbns[j]) << endl;
    }
    return 0;
}
