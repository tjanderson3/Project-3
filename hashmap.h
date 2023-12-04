//
// Created by hunor on 11/29/2023.
//

#ifndef HASH_HASHMAP_H
#define HASH_HASHMAP_H

#include <string>
#include <iostream>
#include <vector>
#include <utility>


class hashmap
{
private:
    //things to store
    std::vector<std::pair<std::string, std::string>> table;
    int size;
    double loadFactor;
    int resizeThreshold;

    //private functions :3
    unsigned int hashFunction(const std::string& key, int table_size);
    unsigned int findNextEmptySlot(unsigned int index);
    void resize();
    void checkResize();

public:
    explicit hashmap(int initialSize = 100, double initialLoadFactor = 0.7)
            : table(initialSize, std::make_pair("","")), size(0), loadFactor(initialLoadFactor),
              resizeThreshold(static_cast<int>(initialLoadFactor * initialSize)) {}
    void insert(const std::string& key, const std::string& value);
    std::string search(const std::string& key);
    void remove(const std::string& key);
};

unsigned int hashmap::hashFunction(const std::string &key, int table_size)
{
    unsigned int hash = 0;
    for (char ch : key) {
        hash = (hash * 11 + ch) % table_size;
    }
    return hash;
}

unsigned int hashmap::findNextEmptySlot(unsigned int index)
{
    //Checks if current index isnt used or deleted and if used, +1
    while (!table[index].first.empty()) {
        index = (index + 1) % table.size();
    }
    return index;
}

void hashmap::resize()
{
    //new vector of 2*size (empty)
    int newSize = table.size() * 2;
    std::vector<std::pair<std::string, std::string>> newTable(newSize, std::make_pair("", ""));

    //goes through prev table and rehashes
    for (const auto& node : table) {
        if (!node.first.empty()) {
            unsigned int index = hashFunction(node.first, newSize);
            while (!newTable[index].first.empty()) {
                index = (index + 1) % newTable.size();
            }
            newTable[index].first = node.first;
            newTable[index].second = node.second;
        }
    }

    //cppreference told me to use
    table = std::move(newTable);
    resizeThreshold = static_cast<int>(loadFactor * table.size());
}

void hashmap::checkResize()
{
    //wrapper for resize()
    //adds check
    if (size >= resizeThreshold) {
        resize();
    }
}

void hashmap::insert(const std::string &key, const std::string &value)
{
    checkResize();

    unsigned int index = hashFunction(key, table.size());
    index = findNextEmptySlot(index);
    table[index].first = key;
    table[index].second = value;
    size++;
}

std::string hashmap::search(const std::string &key)
{
    unsigned int index = hashFunction(key, table.size());
    while (!table[index].first.empty()) {
        if (table[index].first == key) {
            return table[index].second;
        }
        index = (index + 1) % table.size();
    }
    return "Key not found";
}

void hashmap::remove(const std::string &key)
{
    unsigned int index = hashFunction(key, table.size());
    while (!table[index].first.empty()) {
        if (table[index].first == key) {
            table[index].first = "";
            table[index].second = "";
            size--;
            return;
        }
        index = (index + 1) % table.size();
    }
}


#endif //HASH_HASHMAP_H
