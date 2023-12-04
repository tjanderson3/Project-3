//
// Created by CJMoo on 12/3/2023.
//

#ifndef PROJECT3_RBMAP_H
#define PROJECT3_RBMAP_H

#include <string>
#include <utility>


class rbmap {
    struct Node {
        std::string key;
        std::string value;

        // Color boolean, black = false
        bool red;
        // Whether or not node is the left child of its parent, right = false
        bool parent_left;
        Node* left;
        Node* right;
        Node* parent;

        Node(Node* parent_node, bool direction_left);
        Node(Node* parent_node, bool direction_left, std::string& new_key, std::string& new_value);
    };

    Node* head;

    void balance(Node* node);

public:

    rbmap();
    void insert(std::string new_key, std::string new_value);
    std::string find(std::string key);

    std::string operator[](std::string key);
};


#endif //PROJECT3_RBMAP_H
