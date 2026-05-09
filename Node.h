#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
private:
    Node *left, *right;
    std::string key;
    int data;

public:
    Node(std::string key, int data);
    ~Node();

    // Accessors
    Node *&getLeft();
    Node *&getRight();
    const std::string &getKey() const;
    int &getData();

    // Modifiers
    void setLeft(Node *node);
    void setRight(Node *node);
    void setKey(std::string key);
    void setData(int data);
};

#endif
