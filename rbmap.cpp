//
// Created by CJMoo on 12/3/2023.
//

#include "rbmap.h"

rbmap::Node::Node(rbmap::Node *parent_node, bool direction_left) {
    red = true;
    left = nullptr;
    right = nullptr;
    parent = parent_node;
    parent_left = direction_left;
}

rbmap::Node::Node(rbmap::Node *parent_node, bool direction_left, std::string& new_key, std::string& new_value) {
    red = true;
    left = nullptr;
    right = nullptr;
    parent = parent_node;
    parent_left = direction_left;

    key = new_key;
    value = new_value;
}

void rbmap::balance(rbmap::Node *node) {
    if(node->parent == nullptr) {
        node->red = false;

    } else if(node->parent->red) {
        Node* parent = node->parent;
        Node* grand_parent = parent->parent;
        Node* cousin;

        if(parent->parent_left)
            cousin = grand_parent->right;
        else
            cousin = grand_parent->left;

        if(cousin != nullptr && cousin->red) {
            parent->red = false;
            cousin->red = false;
            grand_parent->red = true;
            balance(grand_parent);

        } else {
            if(node->parent_left && parent->parent_left) {
                parent->parent = grand_parent->parent;
                grand_parent->left = parent->right;
                parent->right = grand_parent;
                grand_parent->parent = parent;
                parent->parent_left = grand_parent->parent_left;
                grand_parent->parent_left = false;
                if(parent->parent != nullptr) {
                    if (parent->parent_left)
                        parent->parent->left = parent;
                    else
                        parent->parent->right = parent;
                } else {
                    head = parent;
                }

                parent->red = !parent->red;
                grand_parent->red = !grand_parent->red;
            }

            else if(!node->parent_left && parent->parent_left) {
                node->parent = grand_parent;
                node->parent_left = true;
                parent->parent = node;
                parent->right = node->left;
                node->left = parent;
                grand_parent->left = node;

                parent = node;

                parent->parent = grand_parent->parent;
                grand_parent->left = parent->right;
                parent->right = grand_parent;
                grand_parent->parent = parent;
                parent->parent_left = grand_parent->parent_left;
                grand_parent->parent_left = false;
                if(parent->parent != nullptr) {
                    if (parent->parent_left)
                        parent->parent->left = parent;
                    else
                        parent->parent->right = parent;
                } else {
                    head = parent;
                }

                parent->red = !parent->red;
                grand_parent->red = !grand_parent->red;
            }

            else if(!node->parent_left && !parent->parent_left) {
                parent->parent = grand_parent->parent;
                parent->parent_left = grand_parent->parent_left;
                grand_parent->parent = parent;
                grand_parent->parent_left = true;
                grand_parent->right = parent->left;
                parent->left = grand_parent;
                if(parent->parent != nullptr) {
                    if (parent->parent_left)
                        parent->parent->left = parent;
                    else
                        parent->parent->right = parent;
                } else {
                    head = parent;
                }

                grand_parent->red = !grand_parent->red;
                parent->red = !parent->red;
            }

            else if(node->parent_left && !parent->parent_left) {
                node->parent = grand_parent;
                node->parent_left = false;
                parent->parent = node;
                parent->left = node->right;
                node->right = parent;
                grand_parent->right = node;

                parent = node;

                parent->parent = grand_parent->parent;
                parent->parent_left = grand_parent->parent_left;
                grand_parent->parent = parent;
                grand_parent->parent_left = true;
                grand_parent->right = parent->left;
                parent->left = grand_parent;
                if(parent->parent != nullptr) {
                    if (parent->parent_left)
                        parent->parent->left = parent;
                    else
                        parent->parent->right = parent;
                } else {
                    head = parent;
                }

                grand_parent->red = !grand_parent->red;
                parent->red = !parent->red;
            }
        }
    }
}

rbmap::rbmap() {
    head = nullptr;
}

void rbmap::insert(std::string new_key, std::string new_value) {
    if(head == nullptr) {
        head = new Node(head, false, new_key, new_value);
        head->red = false;
    } else {
        Node* current_node = head;

        while(true) {
            if(new_key < current_node->key) {
                if(current_node->left == nullptr) {
                    current_node->left = new Node(current_node, true, new_key, new_value);
                    current_node = current_node->left;
                    break;

                } else {
                    current_node = current_node->left;
                }

            } else if(new_key > current_node->key) {
                if(current_node->right == nullptr) {
                    current_node->right = new Node(current_node, false, new_key, new_value);
                    current_node = current_node->right;
                    break;

                } else {
                    current_node = current_node->right;
                }

            } else {
                current_node->value = new_value;
                break;
            }
        }

        balance(current_node);
    }
}

std::string rbmap::find(std::string key) {
    if(head == nullptr) {
        return "Key not found";
    }

    Node* node = head;
    while(true) {
        if(key == node->key)
            return node->value;

        else if(key < node->key) {
            if(node->left == nullptr)
                return "Key not found";
            else
                node = node->left;
        }

        else {
            if(node->right == nullptr)
                return "Key not found";
            else
                node = node->right;
        }
    }
}

std::string rbmap::operator[](std::string key) {
    return find(key);
}
