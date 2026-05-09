#include "Node.h"

Node::Node(std::string key, int data)
    : left(nullptr), right(nullptr), key(key), data(data) {}

Node::~Node() {}

// Accessors
Node *&Node::getLeft() {
    return left;
}

Node *&Node::getRight() {
    return right;
}

const std::string &Node::getKey() const {
    return key;
}

int &Node::getData() {
    return data;
}

// Modifiers
void Node::setLeft(Node *node) {
    left = node;
}

void Node::setRight(Node *node) {
    right = node;
}

void Node::setKey(std::string key) {
    this->key = key;
}

void Node::setData(int data) {
    this->data = data;
}
