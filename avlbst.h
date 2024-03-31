#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here

    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* current); 
    void removeFix(AVLNode<Key, Value>* current, int diff); 
    void rotateRight(AVLNode<Key, Value>* node); 
    void rotateLeft(AVLNode<Key, Value>* node); 
    int height(AVLNode<Key, Value>* node); 
    AVLNode<Key, Value>* predecessor(AVLNode<Key, Value>* current); 
};

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::predecessor(AVLNode<Key, Value>* current){
    
    AVLNode<Key, Value>* pred; 
    if (current->getLeft() != nullptr) {
        pred = current->getLeft(); 
        while (pred->getRight() != nullptr) {
            pred = pred->getRight(); 
        }
        return pred; 
    }
    else {
        pred = current; 
        while(pred->getParent() != nullptr) {
            pred = pred->getParent();
            if (pred->getParent() != nullptr && pred->getParent()->getRight() == pred) {
                return pred->getParent(); 
            }
        }
    }
    return nullptr; 
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* current) {
    //Pseudocode:
        //if curr node is null or parent node is null  
            //return
        //get grandparent node
        //if grandparent node is null
            //return
        //if parent is left child of grandparent
            //get grandparent's balance
            //set grandparent's balance to its current balance - 1
            //if grandparent's balance is 0 we just return
            //if grandparent's balance = -1
                //insertFix(parent, grandparent)
            //if grandparent's balance is -2
                //zig-zig case (current node is parent's left child so left-left-left)
                //zig-zag case (current node is parent's right child so left-left-right)
                    //if balance of curr node is -1
                        //do something
                    //if balance of curr node is 0
                        //do something
                    //if balance of curr node is 1
                        //do something
        //if parent is right child of grandparent
            //get grandparent's balance
            //set grandparent's balance to its current balance + 1
            //if grandparent's balnce is 0 we just return
            //if grandparent's balance = -1
                //insertFix(parent, grandparent)
            //if grandparent's balance is -2
                //zig-zig case (current node is parent's right child so right-right-right)
                //zig-zag case (current node is parent's left child so right-right-left)
                    //if balance of curr node is -1
                        //do something
                    //if balance of curr node is 0
                        //do something
                    //if balance of curr node is 1
                        //do something
        
        if (current == nullptr || parent == nullptr) {
            return; 
        }
        AVLNode<Key, Value>* grandparent = parent->getParent();
        
        if (grandparent == nullptr) {
            return; 
        }

        if (grandparent->getLeft() == parent) {
            grandparent->updateBalance(-1);
            //balanced so return
            if (grandparent->getBalance() == 0) {
                return; 
            }
            //balance off by -1
            if (grandparent->getBalance() == -1) {
                insertFix(grandparent, parent);
                return; 
            }
            //balance off by -2
            if (grandparent->getBalance() == -2) {
                //zig-zig case 
                if (parent->getLeft() == current) {
                    rotateRight(grandparent); 
                    parent->setBalance(0); 
                    grandparent->setBalance(0); 
                }
                //zig-zag case
                else if (parent->getRight() == current) {
                    rotateLeft(parent); 
                    rotateRight(grandparent); 
                    //how do you access balance of current?
                    if (current->getBalance() == -1) {
                        parent->setBalance(0); 
                        grandparent->setBalance(1);
                        current->setBalance(0); 
                    }
                    else if (current->getBalance() == 0) {
                        parent->setBalance(0); 
                        grandparent->setBalance(0); 
                        current->setBalance(0); 
                    }
                    else if (current->getBalance() == 1) {
                        parent->setBalance(-1); 
                        grandparent->setBalance(0); 
                        current->setBalance(0); 
                    }
                }
            }
        }
        else {
            grandparent->updateBalance(1); 
            //balanced so return 
            if (grandparent->getBalance() == 0) {
                return; 
            }
            //balalnce off by 1
            if (grandparent->getBalance() == 1) {
                insertFix(grandparent, parent); 
                return; 
            }
            //balance off by 2
            if (grandparent->getBalance() == 2) {
                //zig-zig case 
                if (parent->getRight() == current) {
                    rotateLeft(grandparent); 
                    parent->setBalance(0); 
                    grandparent->setBalance(0); 
                }
                //zig-zag case
                else if (parent->getLeft() == current) {
                    rotateRight(parent); 
                    rotateLeft(grandparent); 
                    if (current->getBalance() == 1) {
                        parent->setBalance(0); 
                        grandparent->setBalance(-1); 
                        current->setBalance(0);
                    }
                    else if (current->getBalance() == 0) {
                        parent->setBalance(0); 
                        grandparent->setBalance(0); 
                        current->setBalance(0); 
                    }
                    else if (current->getBalance() == -1) {
                        parent->setBalance(1); 
                        grandparent->setBalance(0); 
                        current->setBalance(0); 
                    }
                }
            }
        }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* current, int diff){
        //p = parent of n
        //n = current node
        //c = taller child of n
        //g = grandchild of n
        //if n is null, return
        //compute next recursive call's arguments now before altering the tree
            //let p = parent(n) and if p is not NULL let ndiff (next diff) = +1 if n is a left child and -1 otherwise
        //Assume diff = -1 and follow the remainder of this approach, mirroring if diff = +1
        //Flip for if diff == 2, flipping left/right and -1/+1
        //Case 1: b(n) + diff == -2
            //Let c = left(n), the taller of the children
            //Case 1a: b(c) = -1 //zig-zig case
                //rotateRight(n), b(n) = b(c) = 0, removeFix(p, ndiff)
            //Case 1b: b(c) == 0 //zig-zig case
                //rotateRight(n), b(n) = -1, b(c) = +1 // doesn
            //Case 1c: b(c) == +1 //zig-zag case
                //let g = right(c)
                //rotateLeft(c) then rotateRight(n)
                //If b(g) was +1 then b(n) = 0, b(c) = -1, b(g) = 0
                //If  b(g) was 0 then b(n) = 0, b(c) = 0, b(g) = 0
                //If b(g) was -1 then b(n) = +1, b(c) = 0, b(g) = 0
                //removeFix(p, ndiff)
        //Case 2: b(n) + diff == -1
            //b(n) = -1 DONE 
        //Case 3: b(n) + diff == 0
            //b(n) = 0
            //removeFix(p, ndiff)


        if (current == nullptr) {
            return; 
        }
        AVLNode<Key, Value>* parent = current->getParent(); 
        char ndiff = 0; 
        //if p is not NULL let ndiff = +1 if n is a left child and -1 otherwise.
        if (parent != nullptr) {
            //if n is a left child
            if (parent->getLeft() == current) {
                ndiff = 1;
            }
            //if n is a right child
            else if (parent->getRight() == current) {
                ndiff = -1; 
            }
        }

        //assume diff = -1 and follow the remainder of the approach
        if (diff == -1) {
            //Case 1: b(n) + diff == -2
            if (current->getBalance() + diff == -2) {
                //Case 1a: b(c) == 1, zig-zig case
                AVLNode<Key, Value>* child; 
                if (height(current->getLeft()) > height(current->getRight())) {
                    child = current->getLeft();
                }
                else {
                    child = current->getRight(); 
                }

                if (child->getBalance() == -1) {
                    rotateRight(current);
                    current->setBalance(0);
                    child->setBalance(0);
                    removeFix(parent, ndiff); 
                }
                //Case 1b
                else if (child->getBalance() == 0) {
                    rotateRight(current); 
                    current->setBalance(-1);
                    child->setBalance(1); 
                }
                //Case 1c
                else if (child->getBalance() == 1) {
                    AVLNode<Key, Value>* grandparent = child->getRight(); 
                    rotateLeft(child); 
                    rotateRight(current); 
                    if (grandparent->getBalance() == 1) {
                        current->setBalance(0);
                        child->setBalance(-1);
                        grandparent->setBalance(0);
                    }
                    else if (grandparent->getBalance() == 0) {
                        current->setBalance(0); 
                        child->setBalance(0);
                        grandparent->setBalance(0);
                    }
                    else if (grandparent->getBalance() == -1) {
                        current->setBalance(1); 
                        child->setBalance(0);
                        grandparent->setBalance(0); 
                    }
                    removeFix(parent, ndiff); 
                }
            }
            //Case 2: b(n) + diff = 1
            else if (current->getBalance() + diff == -1) {
                current->setBalance(-1);
            }
            //Case 3: b(n) + diff == 0
            else if (current->getBalance() + diff == 0) {
                current->setBalance(0); 
                removeFix(parent, ndiff); 
            }
        }
        else if (diff == 1) {
            //Case 1: b(n) + diff == 2
            if (current->getBalance() + diff == 2) {
                //let child = the taller of the children
                AVLNode<Key, Value>* child; 
                if (height(current->getLeft()) > height(current->getRight())) {
                    child = current->getLeft(); 
                }
                else {
                    child = current->getRight(); 
                }
                //Case 1a: b(c) == -1, zig-zig case
                if (child->getBalance() == 1) {
                    rotateLeft(current); 
                    current->setBalance(0);
                    child->setBalance(0);
                    removeFix(parent, ndiff); 
                }
                //Case 1b: b(c) == 0, zig-zig still
                else if (child->getBalance() == 0) {
                    rotateLeft(current); 
                    current->setBalance(1); 
                    child->setBalance(-1); 
                }
                //Case 1c: b(c) == 1, zig-zag case
                else if (child->getBalance() == -1) {
                    AVLNode<Key, Value>* grandparent = child->getLeft(); 
                    rotateRight(child);
                    rotateLeft(current);
                    if (grandparent->getBalance() == -1) {
                        current->setBalance(0); 
                        child->setBalance(1);
                        grandparent->setBalance(0);
                    }
                    else if (grandparent->getBalance() == 0) {
                        current->setBalance(0);
                        child->setBalance(0);
                        grandparent->setBalance(0);
                    }
                    else if (grandparent->getBalance() == 1) {
                        current->setBalance(-1);
                        child->setBalance(0);
                        grandparent->setBalance(0);
                    }
                    removeFix(parent, ndiff); 
                }
            }
            //Case 2: b(n) + diff == -1
            else if (current->getBalance() + diff == 1) {
                current->setBalance(1);
            }
            //Case 3: b(n) + diff == 0
            else if (current->getBalance() + diff == 0) {
                current->setBalance(0);
                removeFix(parent, ndiff);
            }
        }
}

template<class Key, class Value>
int AVLTree<Key, Value>::height(AVLNode<Key, Value>* node) {
    if (node == nullptr) {
        return 0; 
    }
    int leftHeight = height(node->getLeft());
    int rightHeight = height(node->getRight());
        
    return 1 + std::max(leftHeight, rightHeight);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node){
    //6 pointer changes to implement rotations:
        // 1. parent's child
        // 2. current's parent
        // 3. current's child
        // 4. child's parent
        // 5. child's child's parent pointer
        // 6. child's child pointer
        //need to switch root pointer if the node is the root


    //declare and set parent and child nodes
    AVLNode<Key, Value>* parent = nullptr; 
    AVLNode<Key, Value>* child = nullptr; 

    //if node doesn't exist
    if(node == nullptr){
        return;
    }

    if (node->getParent() != nullptr) {
        parent = node->getParent(); 
    }
    
    //we need a left child because we are rotating right
    if(node->getLeft() != nullptr) {
        child = node->getLeft();
    }
    else {
        return;
    }

    //if node is the root
    if (node == this->root_) {
        this->root_ = child;
    }

    //1. parent's child
    //parent of node points to child of node 
    if (parent != nullptr) {
        //find out whether left child or right child is the node that we're trying to rotate
        if (parent->getLeft() == node) {
            parent->setLeft(child); 
        }
        else if (parent->getRight() == node) {
            parent->setRight(child); 
        }
    }

    //2. current's parent pointer
    //points to child 
    if (node != nullptr) {
        node->setParent(child);
    }

    //3. current's child
    // current's child should point at right child of child node and it's original child
    if (node != nullptr && child != nullptr) {
        node->setLeft(child->getRight()); 
    }

    //4. child's parent
    // should point to node's parents because it is taking node's spot now
    if (child != nullptr) {
        child->setParent(parent); 
    }

    //5. child's child's parent pointer
    //if left child, point at child so don't changes
    //if right child, point at node
    if (child->getRight() != nullptr) {
        child->getRight()->setParent(node); 
    }

    //6. child's child pointer
    // should point at node
    if (child != nullptr) {
        child->setRight(node); 
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node) {
    //6 pointer changes to implement rotations:
        //1. parent's child
        //2. current's parent
        //3. current's child
        //4. child's parent
        //5. child's child's parent pointer
        //6. child's child pointer

    //if node doesn't exist

    //declare and set parent and child nodes
    AVLNode<Key, Value>* parent = nullptr; 
    AVLNode<Key, Value>* child = nullptr; 

    if (node == nullptr) {
        return; 
    }

    if (node->getParent() != nullptr) {
        parent = node->getParent(); 
    }
    if (node->getRight() != nullptr) {
        child = node->getRight();
    }
    else {
        return;
    }

    //if node is the root
    if (node == this->root_) {
        this->root_ = child; 
    }


    //1. parent's child
    if (parent != nullptr) {
        if (parent->getLeft() == node) {
            parent->setLeft(child); 
        }
        else if (parent->getRight() == node) {
            parent->setRight(child);
        }
    }
    
    //2. current's parent
    if (node != nullptr) {
        node->setParent(child);
    }

    //3. current's child
    if (node != nullptr && child != nullptr) {
        node->setRight(child->getLeft()); 
    }

    //4. child's parent
    if (child != nullptr) {
        child->setParent(parent); 
    }

    //5. child's child's parent pointer
    if (child->getLeft() != nullptr) {
        child->getLeft()->setParent(node);
    }

    //6. child's child pointer
    if (child != nullptr) {
        child->setLeft(node);
    }

    
}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    //Pseduocode:
        //Use internal find to get node_to_insert... do you need to do this?
        //If node_to_insert is equal to null pointer ...do you need to do this?
            //return ...do you need to do this?
        //empty tree case
            //insert into the tree, steps:
                //dynamically create new node
                //setbalance equal to 0
                //make root pointer equal to new node
                //set child pointers of node possilby to node?
                    //check node class and see what variables are associated, specifically which one i need to set
        //get current node by getting the root
        //while current node is not null
            //if node_to_insert key > current key, insert right 
                //if current->getRight() is null, insert node_to_insert as current keys right child
                    //dynamically create new ndoe 
                    //setbalance of new node to 0
                    //update current's right child to new node (the dynamically created one)
                    //update the balance
                    //save the parent's current balance to a variable 
                    //if balance is -1
                        //set current node balance to 0
                        //return becuase balanced
                    //if balance is 0
                        //set current node balance to 1 (because right child )
                        //call insertFix(new node, current node)
                        //return
                //if current->getRight() is not null
                    //current = current->getRight()
            //if node_to_insert key < current key, insert left
                //if current->getLeft is null (meaning you insert node_to insert as current keys left child)
                    //dynamically create new node
                    //setbalance of new node to 0
                    //Update current's left child to new node (the dynamically created one)
                    //Update balance
                    //Save the parent's current balance to a vaariable
                    //If balance is 1
                        //Set current node balance to 0
                        //Return because balanced
                    //if balance is 0
                        //set current node balance to -1
                        //call InsertFix(new node, current node)
                        //return
                //if current->getLeft() is not null
                    //current = current->getLeft()
            //if node_to_insert key == current key  
                //override value with node to insert's value
                //return

        //pseudocode from slides
            //if empty tree => set n as root, b(n) = 0, DONE
            //else insert n (by walking the tree to a leaf, p, and inserting the new node as its child) set balance to 0, and look at its parent pair
                //if b(p) was -1, then b(p) = 0. DONE
                //if b(p) was 1, then b(p) = 0. DONE
                //if b(p) was 0, then update b(p) and call insert-fix(p,n)
    
    // std::cout << "Inserting key: " << new_item.first << " with value: " << new_item.second << std::endl;

    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*> (this->root_); 
    AVLNode<Key, Value>* parent = nullptr; 

    //empty tree case
    if (this->root_ == nullptr) {
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr); 
        static_cast<AVLNode<Key,Value>*>(this->root_)->setBalance(0); 
        return;
    }
    else {
        AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_); 
        AVLNode<Key, Value>* parent = nullptr; 
        
        
        //traverse to find spot
        while (current != nullptr) {
            parent = current; 

            //if key less than node key go left
            if (new_item.first < current->getKey()) {
                current = current->getLeft();
            }
            //if key greater than node key go right
            else if (new_item.first > current->getKey()) {
                current = current->getRight();
            }
            //if key equal to node key replace the value
            else {
                current->setValue(new_item.second);
                return;
            }
        }
        AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);
        //insert new node into location we found
        if (new_item.first < parent->getKey()) {
            parent->setLeft(newNode);
        }
        else {
            parent->setRight(newNode);  
        }
        newNode->setBalance(0); 

        if (parent->getBalance() == -1) {
            parent->setBalance(0);
        }
        else if (parent->getBalance() == 1) {
            parent->setBalance(0);
        }
        else if (parent->getBalance() == 0) {
            if (parent == nullptr){
                return;
            }
            int leftHeight = height(parent->getLeft()); 
            int rightHeight = height(parent->getRight()); 
            parent->setBalance((int8_t)(rightHeight - leftHeight));
            insertFix(parent, newNode);
        }

    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    //Pseudocode:
        //Use internalFind to find the node_to_delete
        //node_to_delete is empty 
            //return
        //if node_to_delete has two children
            //get the predecessor of node_to_delete
            //swap positions
        //if node_to_delete has one child
            //create parent node, left child, and right child of node_to_delete
            //Create the difference variable
            //if node_to_delete has no parents
                //if right is the one to exist
                    //make right child the root pointer
                    //right child parent pointer to null
                //if left is the one to exist
                    //make left child the root pointer
                    //left child parent pointer to null
            //if node_to_delete has parents
                //if parent's left child is our node_to_delete
                    //set difference = difference + 1
                    //if node_to_delete has right child
                        //parent's left child pointer points to node_to_delete's right child
                        //node_to_delete's right child parent pointer points to the left parent (grandparent node)
                    //if node_to_delete has left child
                        //parent's left child pointer points to node_to_delete's left child
                        //node_to_delete's left child parent pointer points to the left parent (grandparent node)
                //if parent's right child is our node_to_delete
                    //set difference = difference - 1
                    //If node_to_delete has right child
                        //Parent's right child pointer points to node_to_delete's right child
                        //node_to_delete's right child parent pointer points to the right parent (grandparent node)
                    //If node_to_delete has left child
                        //Parent's right child pointer points to node_to_delete's left child
                        //node_to_delete's left child's parent pointer points to right parent (grandparent node)
            //Delete node_to_delete
        //if node_to_delete has zero children
            //if node has no parent 
                //make root equal to null ptr
            //if node has parent
                //if parent is a left parent
                    //parent's left child pointer point to null
                    //set difference = difference + 1
                //if parent is a right parent
                    //parent's right child pointer points to null
                    //set difference = different - 1
        //call removeFix(parent, diff)

        // std::cout << "Deleting Key: " << key << std::endl;  

        //if tree is empty
        if (this->root_ == nullptr) {
            return;
        }

        AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_); 
        char diff = 0; 

        while (current != nullptr) {
            //check if current node is the one to be removed
            if (key == current->getKey()) {
                //Case 1: 0 child
                if (current->getLeft() == nullptr && current->getRight() == nullptr) {
                    //if node has no parents(the root), after removal make the root null
                    if (current->getParent() == nullptr) {
                        this->root_ = nullptr; 
                    }
                    //if it has parents
                    //find out whether node is a left child or a right child, set diff accordingly
                    else {
                        //left
                        if (current->getParent()->getLeft() == current){
                            diff = 1; 
                        }
                        //right
                        else if (current->getParent()->getRight() == current){
                            diff = -1; 
                        }
                        //if left child, make parent's left child null
                        if (current->getParent()->getLeft() == current) {
                            current->getParent()->setLeft(nullptr); 
                        }
                        //if right child, make parent's right child null
                        else {
                            current->getParent()->setRight(nullptr);
                        }
                    }
                    break;
                }
                //case 2: 1 left child 
                else if (current->getLeft() != nullptr && current->getRight() == nullptr) {
                    //if node to remove is the root
                    if (current->getParent() == nullptr) {
                        this->root_ = current->getLeft(); 
                    }
                    //if it has parents
                    else {
                        if (current->getParent()->getLeft() == current) {
                            diff = 1; 
                        }
                        else if (current->getParent()->getRight() == current) {
                            diff = -1; 
                        }
                        //if left child make parent's left child current's left child
                        if (current->getParent()->getLeft() == current) {
                            current->getParent()->setLeft(current->getLeft());
                        }
                        //if right child make parent's right child current's left child
                        else {
                            current->getParent()->setRight(current->getLeft());
                        }
                    }
                    //update child's parent pointer to point at grandparent
                    current->getLeft()->setParent(current->getParent());
                    break;
                }
                //case 3: 1 right child
                else if (current->getLeft() == nullptr && current->getRight() != nullptr) {
                    //if no parents, so root
                    if (current->getParent() == nullptr) {
                        this->root_ = current->getRight(); 
                    }
                    //if it has parents 
                    else {
                        if (current->getParent()->getLeft() == current) {
                            diff = 1; 
                        }
                        else if (current->getParent()->getRight() == current) {
                            diff = -1; 
                        }
                        //if left child make parent's left child current's right child
                        if (current->getParent()->getLeft() == current) {
                            current->getParent()->setLeft(current->getRight());
                        }
                        // if right child make parent's right child current's right child
                        else {
                            current->getParent()->setRight(current->getRight());
                        }
                    }
                    //update child's parent pointer to point at grandparent
                    current->getRight()->setParent(current->getParent());
                    break;
                }
                //2 child case
                else {
                    AVLNode<Key,Value>* pred = predecessor(current); 
                    nodeSwap(current, pred); 
                }
            }
            //continue looking for matching key
            else {
                if (key < current->getKey()) {
                    current = current->getLeft(); 
                }
                else {
                    current = current->getRight(); 
                }
            }
        }

        //balance tree
        if (current == nullptr) {
            return;
        }
        AVLNode<Key, Value>* parent = current->getParent();
        if (parent != nullptr) {
            removeFix(parent, diff); 
        }
        delete current; 
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
