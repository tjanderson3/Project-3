#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <map>
#include <unordered_map>
#include <algorithm>
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
    int option = 0;
    dataFile.close();
    cout << "Comparing the performance of Hashmaps and Red-Black Trees" << endl << endl;
    while(option != 3) {
        cout << "Select an option (enter 1, 2, or 3):" << endl << "1. Insert Book and ISBN #" << endl
        << "2. Find Book" << endl << "3. Exit" << endl;
        cin >> option;
        if (option == 1) {
            string insertions;
            cout << "Enter the number of books to insert:" << endl;
            cin >> insertions;
            if (insertions.length() >= 1 && all_of(insertions.begin(), insertions.end(), ::isdigit)) {
                auto start = chrono::high_resolution_clock::now();
                //insert into r-b tree/hashmap here
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration = end - start;
                cout << duration.count() << endl;
                auto start1 = chrono::high_resolution_clock::now();
                //insert into r-b tree/hashmap here
                auto end1 = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration1 = end1 - start1;
                cout << duration1.count() << endl;
            }
            else {
                cout << "Invalid input. Please enter a valid number." << endl;
            }
        }
        else if(option == 2){
            string uISBN;
            cout << "Enter the ISBN number of the book to find (10-digit number):" << endl;
            cin >> uISBN;
            if(uISBN.length() == 10 && all_of(uISBN.begin(), uISBN.end(), ::isdigit)){
                auto start = chrono::high_resolution_clock::now();
                //Search through r-b tree/hashmap here
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration = end - start;
                cout << duration.count() << endl;
                auto start1 = chrono::high_resolution_clock::now();
                //insert into r-b tree/hashmap here
                auto end1 = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration1 = end1 - start1;
                cout << duration1.count() << endl;
            }
            else{
                cout << "Invalid input. Please enter a valid ISBN number." << endl;
            }
        }
        else if(option != 3){
            cout << "Invalid input. Please enter a valid option." << endl;
        }
    }
    
    return 0;
}
