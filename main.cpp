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
#include "rbmap.h"
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
    hashmap h;
    rbmap rb;

    cout << "Comparing the performance of Hashmaps and Red-Black Trees" << endl << endl;
    while(option != 5) {
        cout << "Select an option (enter 1, 2, 3, 4, or 5):" << endl << "1. Perform Insertions" << endl
        << "2. Perform Searches" << endl << "3. Insert Individual Book" << endl << "4. Find Individual Book" << endl << "5. Exit" << endl;
        cin >> option;
        if (option == 1) {
            string insertions;
            cout << "Enter the number of books to insert:" << endl;
            cin >> insertions;
            if (insertions.length() >= 1 && all_of(insertions.begin(), insertions.end(), ::isdigit)) {
                auto start = chrono::high_resolution_clock::now();
                for(int i = 0; i < stoi(insertions); i++){
                    rb.insert(isbns[i], books[i]);
                }
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration = end - start;
                cout << "Red-Black Tree Performance time(in ms): " << duration.count() << endl;
                auto start1 = chrono::high_resolution_clock::now();
                for(int i = 0; i < stoi(insertions); i++){
                    h.insert(isbns[i], books[i]);
                }
                auto end1 = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration1 = end1 - start1;
                cout << "Hashmap Performance time(in ms): " << duration1.count() << endl;
            }
            else {
                cout << "Invalid input. Please enter a valid number." << endl;
            }
        }
        else if(option == 2){
            string searches;
            cout << "Enter the number of books to find:" << endl;
            cin >> searches;
            if(all_of(searches.begin(), searches.end(), ::isdigit) && stoi(searches) <= 200000 && stoi(searches) > 0){
                auto start = chrono::high_resolution_clock::now();
                for(int i = 0; i < stoi(searches); i++){
                    rb.find(isbns[i]);
                }
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration = end - start;
                cout << "Red-Black Tree Performance time(in ms): " << duration.count() << endl;
                auto start1 = chrono::high_resolution_clock::now();
                for(int i = 0; i < stoi(searches); i++){
                    h.search(isbns[i]);
                }
                auto end1 = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration1 = end1 - start1;
                cout << "Hashmap Performance time(in ms): " << duration1.count() << endl;
            }
            else{
                cout << "Invalid input. Please enter a valid number of searches." << endl;
            }
        }
        else if(option == 3){
            string uISBN, title;
            cout << "Enter the 10-digit ISBN number:" << endl;
            cin >> uISBN;
            if(uISBN.length() == 10 && all_of(uISBN.begin(), uISBN.end(), ::isdigit)){
                cout << "Enter the book title:" << endl;
                cin >> title;
                auto start = chrono::high_resolution_clock::now();
                //insert into r-b tree/hashmap here
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration = end - start;
                cout << "Red-Black Tree Performance time(in ms): " << duration.count() << endl;
                auto start1 = chrono::high_resolution_clock::now();
                //insert into r-b tree/hashmap here
                auto end1 = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration1 = end1 - start1;
                cout << "Hashmap Performance time(in ms): " << duration1.count() << endl;
            }
        }
        else if(option == 4){
            string uISBN;
            cout << "Enter the 10-digit ISBN number:" << endl;
            cin >> uISBN;
            if(uISBN.length() == 10 && all_of(uISBN.begin(), uISBN.end(), ::isdigit)) {
                auto start = chrono::high_resolution_clock::now();
                //insert through r-b tree/hashmap here
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration = end - start;
                cout << "Red-Black Tree Performance time(in ms): " << duration.count() << endl;
                auto start1 = chrono::high_resolution_clock::now();
                //search through r-b tree/hashmap here
                auto end1 = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration1 = end1 - start1;
                cout << "Hashmap Performance time(in ms): " << duration1.count() << endl;
            }
        }
        else if(option != 5){
            cout << "Invalid input. Please enter a valid option." << endl;
        }
    }

    return 0;
}
