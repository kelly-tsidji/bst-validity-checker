/***********************************************************************************
 *
 *                     BSTChecker.h
 *
 *     Assignment: Project 1
 *     Author:     Kelly Tsidji
 *     Date:       02/20/2023
 *
 *     This programs checks if a given tree is a valid Binary Search Tree.
 *     If it is not, it finds the violating node of the tree.
 *     A violating node will be one of three things:
 *       - A node in the left subtree of an ancestor with a lesser key
 *       - A node in the right subtree of an ancestor with a greater key
 *       - A node with the left or right member variable pointing to an ancestor.
 *
 **********************************************************************************/
 
#ifndef BSTCHECKER_H
#define BSTCHECKER_H

#include "Node.h"
#include <vector>
#include <iostream>
using namespace std;


class BSTChecker {
   
   
public:
   /* CheckBSTValidity
    *
    * Checks if a given tree is a valid BST.
    * Inputs:
    *    Node *rootNode: pointer that points to the root of the tree.
    * Return: a pointer to the node that violates BST requirements, or nullptr if the tree is a valid BST.
    * Notes:
    *		If an empty tree is provided, then it passes BST requirements, and the function returns nullptr.
    */
   static Node* CheckBSTValidity(Node* rootNode) {
      Node* prev = NULL;
   	Node *bad_node = NULL;
   	vector<Node* > node_addresses;   
   	Node* node_to_ancestor = NULL;  
   	
   	bool is_bst = check_BST_helper(rootNode, prev, bad_node, node_addresses, node_to_ancestor);
	
	   // if there is a node that points to its ancestor in the tree, return it
   	if(node_to_ancestor) {
   	   return node_to_ancestor;
   	}

      // if the tree is a valid BST, return nullptr
   	if(is_bst) {
   	   return nullptr;
   	}
   	// in the case the tree is not a valid BST, the violating node will be stored in either prev or bad_node.
   	// determine which one should be returned as the invalid node
   	else {
         int root_data;
   	   int bad_node_data;
   	   int prev_data;
   	    
         if((rootNode != NULL) && (bad_node != NULL) & (prev != NULL)) {
            root_data = rootNode->key;
            bad_node_data = bad_node->key;
            prev_data = prev->key;
           
            if (root_data < bad_node_data && bad_node_data < prev_data) {
               int root_right_data;
               
               if(rootNode->right->key) {
                  root_right_data = rootNode->right->key;
                   
                  if(root_right_data == bad_node_data) {
                    return prev;
                  }
                   
                  if(root_right_data == prev_data){
                   return bad_node;
                  }
               }
            
            }
            
            if (bad_node_data < prev_data && bad_node_data < root_data && root_data <= prev_data) {
               return bad_node;
            }
         }
   	    
         return prev;
   	}
    
   }
   

private:
   
   /* check_BST_helper
    *
    * Checks if a given tree is a valid BST
    * Inputs:
    *		struct Node *root: pointer that points to the root of the tree.
    *    Node *& prev: pointer that tracks the previously visited node.
    *    Node *& bad_node: pointer that keeps track of any node that breaks the 1st two BST requirements.
    *    vector<Node* >& node_addresses: vector that keeps track of the addresses of nodes that have been visited.
    *    Node *& node_to_ancestor: pointer that keeps track of any node that breaks the 3rd BST requirement.
    * Return: true if the given tree is a valid BST, false if not.
    */
   static bool check_BST_helper(struct Node* root, Node*& prev, Node *& bad_node, vector<Node* >& node_addresses, 
                         Node*& node_to_ancestor)
   {
      // traverse the tree in inorder fashion and keep track of prev, bad_node, and node_to_ancestor nodes
      if (root) {
         
         // add the address of the current node to the vector node_addresses
         Node *curr_node = root;
         node_addresses.push_back(curr_node);
         
         // if the current node points to an ancestor (an address in node_addresses), 
         // save that  node as node_to_ancestor
         for(unsigned int i = 0; i < node_addresses.size(); i++) {
            
            if( curr_node->left == node_addresses.at(i) || curr_node->right == node_addresses.at(i)) {
               node_to_ancestor = curr_node;
               return false;
            }
            
         }
         
         // recurse into the left child of the current node
      	if (!check_BST_helper(root->left, prev, bad_node, node_addresses, node_to_ancestor)) {
      	   return false;
      	}
      
      	if (prev != NULL && root->key < prev->key) {
      	   bad_node = root;
      	   return false;
      	}
      
      	prev = root;
      
         // recurse into the right child of the current node
      	return check_BST_helper(root->right, prev, bad_node, node_addresses, node_to_ancestor);
      }

	   return true;
   }
   
   
};


#endif
