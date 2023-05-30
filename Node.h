#ifndef NODE_H
#define NODE_H

#include <cctype>
#include <string>
#include <vector>

class Node {
private:
   static std::string RemoveLeadingWhitespace(std::string str) {
      int i = 0;
      while (i < (int) str.length()) {
         // If the character at index i is not whitespace, then return the
         // substring that starts at i
         if (!std::isspace(str[i])) {
            return str.substr(i);
         }
         
         i++;
      }
      
      // Completing the loop means the entire string is whitespace
      return std::string();
   }
public:
   int key;
   Node* left;
   Node* right;
   
   Node(int nodeKey, Node* leftChild = nullptr, Node* rightChild = nullptr) {
      key = nodeKey;
      left = leftChild;
      right = rightChild;
   }
   
   virtual ~Node() {
   }

   // Counts the number of nodes in this tree
   virtual int Count() {
      int leftCount = 0;
      if (left) {
         leftCount = left->Count();
      }
      int rightCount = 0;
      if (right) {
         rightCount = right->Count();
      }
      return 1 + leftCount + rightCount;
   }
   
   static void DeleteTree(Node* root) {
      if (root) {
         DeleteTree(root->left);
         DeleteTree(root->right);
         delete root;
      }
   }
   
   // Inserts the new node into the tree.
   virtual void Insert(Node* node) {
      Node* currentNode = this;
      while (currentNode) {
         if (node->key < currentNode->key) {
            if (currentNode->left) {
               currentNode = currentNode->left;
            }
            else {
               currentNode->left = node;
               currentNode = nullptr;
            }
         }
         else {
            if (currentNode->right) {
               currentNode = currentNode->right;
            }
            else {
               currentNode->right = node;
               currentNode = nullptr;
            }
         }
      }
   }
   
   virtual void InsertAll(const std::vector<int>& keys) {
      for (int key : keys) {
         Insert(new Node(key));
      }
   }
   
   static Node* Parse(std::string treeString) {
      // # A node is enclosed in parentheses with a either just a key: (key),
      // or a key, left child, and right child triplet: (key, left, right). The
      // left and right children, if present, can be either a nested node or
      // "null".
      
      // Remove leading whitespace first
      treeString = Node::RemoveLeadingWhitespace(treeString);
      
      // The string must be non-empty, start with "(", and end with ")"
      if (0 == treeString.length() || treeString[0] != '(' ||
         treeString[treeString.length() - 1] != ')') {
         return nullptr;
      }
      
      // Parse between parentheses
      treeString = treeString.substr(1, treeString.length() - 2);
      
      // Find non-nested commas
      std::vector<int> commaIndices;
      int parenCounter = 0;
      for (int i = 0 ; i < (int)treeString.length(); i++) {
         char character = treeString[i];
         if ('(' == character) {
            parenCounter++;
         }
         else if (')' == character) {
            parenCounter--;
         }
         else if (',' == character && 0 == parenCounter) {
            commaIndices.push_back(i);
         }
      }
      
      // If no commas, treeString is expected to be just the node's key
      if (0 == commaIndices.size()) {
         return new Node(std::stoi(treeString));
      }
      
      // If number of commas is not 2, then the string's format is invalid
      if (2 != commaIndices.size()) {
         return nullptr;
      }

      // "Split" on comma
      int i1 = commaIndices[0];
      int i2 = commaIndices[1];
      std::string piece1 = treeString.substr(0, i1);
      std::string piece2 = treeString.substr(i1 + 1, i2 - i1 - 1);
      std::string piece3 = treeString.substr(i2 + 1);

      // Make the node with just the key
      Node* nodeToReturn = new Node(stoi(piece1));
      
      // Recursively parse children
      nodeToReturn->left = Node::Parse(piece2);
      nodeToReturn->right = Node::Parse(piece3);
      return nodeToReturn;
   }
};

#endif