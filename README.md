# bst-validity-checker
Given a tree (of nodes), this program checks if it is a valid Binary Search Tree (BST). If it is not, it finds the violating node of the tree (defined in BSTChecker.h).

The solution implements a BSTChecker class with a CheckBSTValidity() function that takes the root node of a binary search tree as input. It checks the validity of the BST by recursively traversing the tree in an in-order fashion, keeping track of the previously visited node, any node that violates BST requirements, and any node that points to an ancestor.

The function uses a helper function, check_BST_helper(), to perform the recursive traversal. During the traversal, it checks if the current node violates the BST requirements by comparing it with the previously visited node. If a violation is found, the function sets the violating node and returns false.

Additionally, the function checks if the current node has a left or right child that points to an ancestor node. If such a violation is found, the function sets the node_to_ancestor variable and returns false.

At the end of the traversal, the function checks if the tree is a valid BST based on the values of the previously visited node, the violating node, and the node_to_ancestor. If the tree is valid, it returns nullptr. Otherwise, it determines the invalid node to be returned based on specific conditions and returns the corresponding pointer.
