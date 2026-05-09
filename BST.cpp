#include "BST.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// ── Private helpers ──────────────────────────────────────────────────────────

void BST::insert(Node *&node, string key, int data) {
    if (node == nullptr) {
        node = new Node(key, data);
    } else if (key < node->getKey()) {
        insert(node->getLeft(), key, data);
    } else if (key > node->getKey()) {
        insert(node->getRight(), key, data);
    } else {
        node->setData(data);
    }
}

void BST::destroy(Node *node) {
    if (node) {
        destroy(node->getLeft());
        destroy(node->getRight());
        delete node;
    }
}

void BST::print(Node *node) const {
    if (node != nullptr) {
        print(node->getLeft());
        cout << "(" << node->getKey() << ", " << node->getData() << ") ";
        print(node->getRight());
    }
}

void BST::saveToFile(Node *node, ofstream &file) const {
    if (node != nullptr) {
        saveToFile(node->getLeft(), file);
        file << node->getKey() << " " << node->getData() << "\n";
        saveToFile(node->getRight(), file);
    }
}

Node *BST::findHelper(Node *node, string key) const {
    if (node == nullptr || key == node->getKey()) {
        return node;
    }
    if (key < node->getKey()) {
        return findHelper(node->getLeft(), key);
    }
    return findHelper(node->getRight(), key);
}

Node *BST::min(Node *node) const {
    if (node == nullptr) return nullptr;
    while (node->getLeft() != nullptr) {
        node = node->getLeft();
    }
    return node;
}

Node *BST::max(Node *node) const {
    if (node == nullptr) return nullptr;
    while (node->getRight() != nullptr) {
        node = node->getRight();
    }
    return node;
}

void BST::deleteNode(Node *&node, string key) {
    if (node == nullptr) return;

    if (key < node->getKey()) {
        deleteNode(node->getLeft(), key);
    } else if (key > node->getKey()) {
        deleteNode(node->getRight(), key);
    } else {
        if (node->getLeft() == nullptr) {
            Node *temp = node->getRight();
            delete node;
            node = temp;
        } else if (node->getRight() == nullptr) {
            Node *temp = node->getLeft();
            delete node;
            node = temp;
        } else {
            Node *temp = min(node->getRight());
            node->setKey(temp->getKey());
            node->setData(temp->getData());
            deleteNode(node->getRight(), temp->getKey());
        }
    }
}

// ── Constructor / Destructor ─────────────────────────────────────────────────

BST::BST() : root(nullptr) {}

BST::~BST() {
    destroy(root);
}

// ── Public interface ─────────────────────────────────────────────────────────

void BST::set(string key, int data) {
    insert(root, key, data);
}

int BST::find(string key) const {
    Node *result = findHelper(root, key);
    return result ? result->getData() : 0;
}

void BST::print() const {
    print(root);
    cout << "\n";
}

bool BST::readFromFile(string filename) {
    // Accepts filename with or without .txt extension
    if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt") {
        filename += ".txt";
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open \"" << filename << "\"\n";
        return false;
    }

    string word;
    while (file >> word) {
        // Strip punctuation, keeping apostrophes (contractions)
        word.erase(remove_if(word.begin(), word.end(), [](char c) {
            return ispunct(static_cast<unsigned char>(c)) && c != '\'';
        }), word.end());

        // Lowercase
        transform(word.begin(), word.end(), word.begin(),
                  [](unsigned char c) { return tolower(c); });

        if (!word.empty()) {
            set(word, find(word) + 1);
        }
    }
    file.close();
    return true;
}

void BST::saveToFile(string filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open \"" << filename << "\"\n";
        return;
    }
    saveToFile(root, file);
    file.close();
}

void BST::min() const {
    Node *result = min(root);
    if (result) {
        cout << "Min: \"" << result->getKey() << "\" (" << result->getData() << ")\n";
    } else {
        cout << "Tree is empty.\n";
    }
}

void BST::max() const {
    Node *result = max(root);
    if (result) {
        cout << "Max: \"" << result->getKey() << "\" (" << result->getData() << ")\n";
    } else {
        cout << "Tree is empty.\n";
    }
}

void BST::remove(string key) {
    deleteNode(root, key);
}

// ── operator[] ───────────────────────────────────────────────────────────────

// Read-only: returns 0 if key not found
int BST::operator[](string key) const {
    Node *current = root;
    while (current != nullptr) {
        if (key < current->getKey())       current = current->getLeft();
        else if (key > current->getKey())  current = current->getRight();
        else                               return current->getData();
    }
    return 0;
}

// Read-write: inserts key with value 0 if not found, returns reference to data
int &BST::operator[](string key) {
    Node *current = root;
    while (current != nullptr) {
        if (key < current->getKey())       current = current->getLeft();
        else if (key > current->getKey())  current = current->getRight();
        else                               return current->getData();
    }
    // Key not present — insert it, then find and return the new node's data
    insert(root, key, 0);
    return findHelper(root, key)->getData();
}

Node *BST::getRoot() const {
    return root;
}
