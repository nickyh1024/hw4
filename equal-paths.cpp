#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int equalPathsHelper(Node* node); 
int max(int a, int b); 

int max(int a, int b) {
    if (a > b) {
        return a; 
    }
    if (b > a) {
        return b; 
    }
}

bool equalPaths(Node* root)
{
    // Add your code below

    //to verify if all paths are equal length, we need to know the length of a path as we visit it 
        //each recursive call represents a path from the current node to the leaf node
        //You need to compare the lengths of the path from a node's left child to leaf node vs the path from a node's right child to leaf node
            //What to return if the path lengths are equal?
            //What to return if the path lengths are not equal?
            //What to do if a node does not have a left/right child?
        //base case:what to return when you reach a NULL node?
    
    return equalPathsHelper(root) != -1; 
    

}

int equalPathsHelper(Node* node){
    //path ends when we hit nullptr
    if (node == nullptr) {
      return 0; 
    }
    //check depths of left and right subtree recursively
    int leftDepth = equalPathsHelper(node->left);
    int rightDepth = equalPathsHelper(node->right);

    //if either subtree path height is -1 it is unequal
    if (leftDepth == -1 || rightDepth == -1) {
      return -1; 
    }

    //compare path of node's left child to leaf node vs path of node's right child to leaf node
    if (node->left != nullptr && node->right != nullptr && leftDepth != rightDepth) {
      return -1; 
    }
    
    //return the depth of the path, which is the max depth subtree + 1 for the current node
    return max(leftDepth, rightDepth) + 1; 
}
