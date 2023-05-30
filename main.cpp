#include <iostream>
#include <string>
#include "Node.h"
#include "BSTChecker.h"
using namespace std;

int main(int argc, char *argv[]) {
   // Get user input
   string userInput;
   getline(cin, userInput);
   
   // Parse into a binary ree
   Node* userRoot = Node::Parse(userInput);
   if (userRoot) {
      Node* badNode = BSTChecker::CheckBSTValidity(userRoot);
      if (badNode) {
         cout << to_string(badNode->key) << endl;
      }
      else {
         cout << "No violation" << endl;
      }
   }
   else {
      cout << "Failed to parse input tree" << endl;
   }
    
   Node::DeleteTree(userRoot);
}