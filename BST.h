#ifndef BST_H
#define BST_H

#include "Node.h"
#include <iostream>
#include <fstream>

class BST {
private:
    Node *root;

    void insert(Node *&node, std::string key, int data);
    void print(Node *node) const;
    void destroy(Node *node);
    Node *findHelper(Node *node, std::string key) const;
    void saveToFile(Node *node, std::ofstream &file) const;
    Node *min(Node *node) const;
    Node *max(Node *node) const;
    void deleteNode(Node *&node, std::string key);

public:
    BST();
    ~BST();

    void set(std::string key, int data);
    int find(std::string key) const;
    void print() const;
    bool readFromFile(std::string filename);
    void saveToFile(std::string filename) const;
    void min() const;
    void max() const;
    void remove(std::string key);

    int &operator[](std::string key);
    int operator[](std::string key) const;

    Node *getRoot() const;
};

#endif
