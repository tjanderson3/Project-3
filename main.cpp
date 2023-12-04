#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include "hashmap.h"
#include "rbmap.h"
using namespace std;

int main() {
    ifstream dataFile("../Books_isbn.txt");//open our dataset--> over 270 thousand entries
    string line;
    vector<string> books;
    vector<string> isbns;
    string book, isbn, header;
    getline(dataFile, header); //skip first line (header)
    while(getline(dataFile, line)){
        istringstream iss(line);
        iss >> isbn;
        getline(iss >> ws, book);
        isbns.push_back(isbn);
        books.push_back(book);
    }//add data set to vectors
    int option = 0;
    dataFile.close();
    hashmap h;
    rbmap rb;//instantiate rb tree and hashmap
    for(int i = 0; i < isbns.size(); i++){
        h.insert(isbns[i], books[i]);
        rb.insert(isbns[i], books[i]);
    }//create a preset rb tree and hashmap with all of our data points

    cout << "Comparing the performance of Hashmaps and Red-Black Trees" << endl << endl;
    while(option != 5) {//main function loop
        cout << "Select an option (enter 1, 2, 3, 4, or 5):" << endl << "1. Perform Insertions" << endl
        << "2. Perform Searches" << endl << "3. Insert Individual Book" << endl << "4. Find Individual Book" << endl << "5. Exit" << endl;
        cin >> option;
        if (option == 1) {
            string insertions;
            double loadFactor;
            int size;//load factor and size for hashmap
            cout << "Enter the number of books to insert:" << endl;
            cin >> insertions;
            if (insertions.length() >= 1 && all_of(insertions.begin(), insertions.end(), ::isdigit)) {//validate input
                cout << "Enter the desired load factor for the hash table(# between 0 and 1):" << endl;
                cin >> loadFactor;
                cout << "Enter the desired initial size for the hash table(# greater than or equal to 1):" << endl;
                cin >> size;
                rbmap rb1;//instantiates a new rb tree and hashmap so we dont insert twice
                hashmap h1(size, loadFactor);
                auto start = chrono::high_resolution_clock::now();
                for(int i = 0; i < stoi(insertions); i++){
                    rb1.insert(isbns[i], books[i]);
                }//timers on both rb and hash
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration = end - start;
                cout << "Red-Black Tree Performance time(in ms): " << duration.count() << endl;
                auto start1 = chrono::high_resolution_clock::now();
                for(int i = 0; i < stoi(insertions); i++){
                    h1.insert(isbns[i], books[i]);
                }
                auto end1 = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration1 = end1 - start1;
                cout << "Hashmap Performance time with load factor " << loadFactor << " and initial size " << size << "(in ms): " << duration1.count() << endl;
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
                }//uses preset hashmap and rb tree
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
        else if(option == 3){//3 and 4 for individual insertion and searches, adds it or finds it from preset list
            string uISBN, title;
            cout << "Enter the 10-digit ISBN number:" << endl;
            cin >> uISBN;
            if(uISBN.length() == 10 && all_of(uISBN.begin(), uISBN.end(), ::isdigit)){
                cout << "Enter the book title:" << endl;
                cin >> title;
                auto start = chrono::high_resolution_clock::now();
                rb.insert(uISBN, title);
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration = end - start;
                cout << "Red-Black Tree Performance time(in ms): " << duration.count() << endl;
                auto start1 = chrono::high_resolution_clock::now();
                h.insert(uISBN, title);
                auto end1 = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration1 = end1 - start1;
                cout << "Hashmap Performance time(in ms): " << duration1.count() << endl;
            }
        }
        else if(option == 4){
            string uISBN;
            string title, title1;
            cout << "Enter the 10-digit ISBN number:" << endl;
            cin >> uISBN;
            if(uISBN.length() == 10 && all_of(uISBN.begin(), uISBN.end(), ::isdigit)) {
                auto start = chrono::high_resolution_clock::now();
                title = rb.find(uISBN);
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration = end - start;
                cout << "Book title: " << title << endl;
                cout << "Red-Black Tree Performance time(in ms): " << duration.count() << endl;
                auto start1 = chrono::high_resolution_clock::now();
                title1 = h.search(uISBN);
                auto end1 = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration1 = end1 - start1;
                cout << "Book title: " << title1 << endl;
                cout << "Hashmap Performance time(in ms): " << duration1.count() << endl;
            }
        }
        else if(option != 5){
            cout << "Invalid input. Please enter a valid option." << endl;
        }
    }

    return 0;
}

