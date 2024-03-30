#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void clearHelper(Node<Key, Value>* node); 
    int balanceHelper(Node<Key, Value>* node) const; 



protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr; 
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = nullptr; 
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ == rhs.current_; 
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ != rhs.current_; 

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO

    //if iterator reached the end
    if (current_ == nullptr) {
      return *this; 
    }
    //if the current node has a right child, the next node to iterate to is the left most node of the right subtree
    if (current_->getRight() != nullptr) {
      current_ = current_->getRight(); 
      //go to leftmost child
      while (current_->getLeft() != nullptr) {
        current_ = current_->getLeft(); 
      }
    }
    //if no right child, we go to parent that we haven't vistited yet
    else{
      Node<Key, Value>* parent = current_->getParent(); 
      while (parent != nullptr && current_ == parent->getRight()) {
        current_ = parent; 
        parent = parent->getParent(); 
      }
      current_ = parent; 
    }
  return *this; 
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = nullptr; 
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear(); 
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    //what to do if our tree is empty?
      //create new root for a new tree
    //begin traversal at the root and keep traversing until you reach NULL
      //compare keys of your current node and the node you are trying to insert
        //go into left subtree if new node's key is < parent
        //go into right subtree if new node's key is > parent
        //if keys are the same, update the value
    //when you end your traversal, you have found the location to insert your new node
      //dynamically create a new node and correctly set the node's parent pointer
      //don't forget to update the parent node's left and right child pointers

    //if tree is empty, create new root for a new tree
    if (root_ == nullptr) {
      root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
      return; 
    }

    //if not empty, traverse the tree to find where to insert the new node
    Node<Key, Value>* current = root_; 
    //need parent node to see where to insert later
    Node<Key, Value>* parent = nullptr; 
    //start the traversal that ends until you find a location
    while (current != nullptr) {
      parent = current;
      //if new node's key is less than current key, then go left subtree
      if (keyValuePair.first < current->getKey()) {
        current = current->getLeft(); 
      }
      //if new node's key is greater than current key, then go to right subtree
      else if (keyValuePair.first > current->getKey()){
        current = current->getRight(); 
      }
      //if new node's key is equal to current key, we've found the location 
      else {
        current->setValue(keyValuePair.second);
        return; 
      }
    }
    //after finding the location to insert in the tree, we dynamically create a new node
    Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
    //determine whether on parent node's left side or right side
    if (keyValuePair.first < parent->getKey()) {
      parent->setLeft(newNode); 
    }
    else {
      parent->setRight(newNode); 
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    //Find the node with the given key using internalFind
    //Once you find the node, it can fall under 3 cases:
      //0 children: simply delete the node
      //1 child: Promote the child into the node's location, then delete the node
      //2 children: swap the node with its predecessor, then it will fall under the 0 or 1 child cases

    //pseudocode:
    //2 child case: 
      //find predecessor using the helper function 
      //if it is not nullptr, swap with the nodeToDelete

    //1 child case: 
      //if node to delete has no parent (root node)
        //if right child is the one to exist
          //set right child to root node
          //right child's parent to nullptr
          //root node to point to right child
          //nothing points to nodeToDelete now, so it is safe to delete
        //if left child is the one to exist
          //set left child to root node
          //left child's parent to nullptr
          //root node to point to left child
          //nothing points to nodeToDelete now, so it is safe to delete
      //if node to delete has parents
        //if parent is left parent
          //if nodeToDelete has right child
            //right child's parent now points to nodeToDelete's parent (the grandparent)
            //grandparent's left child is now right child
          //if nodeToDelete has left child
            //left childs parent is now grandparent node
            //grandparent's left child is now left child
        //if parent is right parent
          //if nodeToDelete has right child
            //right child's parent is now grandparent node
            //grandparent child pointer points at nodeToDelete's right child
          //if nodeToDelete has left child
            //left childs parent is now grandparent node
            //grandparent child pointer points to nodeToDelete's left child
    
    //0 child case
      //if no parent
        //make root equal to nullptr
      //if there is parent
        //if left parent
          //parent's left child point to nullptr
        //if right parent
          //parent's right child point to nullptr

    //at the end, delete the node safely

    Node<Key, Value>* nodeToDelete = internalFind(key); 
    //if nodeToDelete not found, exist
    if (nodeToDelete == nullptr) {
      return; 
    }

    //2 child case
    if (nodeToDelete->getLeft() != nullptr && nodeToDelete->getRight() != nullptr) {
      //find predecessor using helper function
      Node<Key,Value>* pred = predecessor(nodeToDelete);
      //if exists, swap with nodeToDelete
      if (pred != nullptr) {
        nodeSwap(nodeToDelete, pred); 
      }
    }

    //1 child case
    Node<Key, Value>* child = nullptr; 
    //determine if child is right or left child
    if (nodeToDelete->getLeft() != nullptr) {
      child = nodeToDelete->getLeft(); 
    }
    else if (nodeToDelete->getRight() != nullptr) {
      child = nodeToDelete->getRight(); 
    }

    if (child != nullptr) {
      //if nodeToDelete has no parents = is root
      if (nodeToDelete == root_) {
        //make the child the new root
        root_ = child; 
        //set parent of child to nullptr because child has no parents now
        child->setParent(nullptr); 
      }
      //if has parents
      else {
        Node<Key, Value>* Parent = nodeToDelete->getParent(); 
        //set child's parent to grandparent, update grandparent's child pointer to grandchild
        //so nothing is pointing at nodeToDelete now, so can safely delete.
        child->setParent(Parent); 
        //if grandparent is left grandparent
        if (Parent->getLeft() == nodeToDelete) {
          Parent->setLeft(child); 
        }
        //if grandparent is right grandparent
        else {
          Parent->setRight(child); 
        }
      }
    }

    //0 child case
    //if child is nullptr
    else {
      //if no parents, it means it is the root
      if (nodeToDelete == root_) {
        root_ = nullptr; 
      }
      //not the root, has parents
      else {
        Node<Key, Value>* parent = nodeToDelete->getParent();
        //check if left or right parent
        if (parent->getLeft() == nodeToDelete) {
          parent->setLeft(nullptr); 
        }
        else {
          parent->setRight(nullptr); 
        }
      }
    }
    //after making sure all pointers are pointing in correct place, delete the node
    delete nodeToDelete; 
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    //Case 1: If there is a left child 
      //Go all the way to the right of that chain
    //Case 2: If there is no left child
      //Starting with our node, traverse the parent chain until we find a right child pointer
      //that pointer is the predecessor

      //if current doesn't exist
      if (current == nullptr) {
        return nullptr;
      }

      //Case 1: if there is a left child
      if (current->getLeft() != nullptr) {
        //start from left child and go all the way right
        Node<Key, Value>* pred = current->getLeft(); 
        while (pred->getRight() != nullptr) {
          pred = pred->getRight(); 
        }
        return pred; 
      }

      //case 2: if there is no left child the pred is up in the tree
      if (current->getLeft() == nullptr) {
        //traverse the parent chain until we find a right child pointer
        Node<Key, Value>* parent = current; 
        while (parent != nullptr && current == parent->getLeft()) {
          //move to the parent
          current = parent;
          //update parent to the grandparent 
          parent = parent->getParent(); 
        }
        //the parent node is the predecessor
        return parent; 
      }
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    //need to use this->root to use root, can't use root_ because no arguments passed
    //remove all nodes in the tree
      //since the children nodes need their parent pointers, we will delete the children before deleting the parent
      //Update the root node
    clearHelper(this->root_); 
    this->root_ = nullptr; 

}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* node) {
    //if empty already
    if (node == nullptr){
      return; 
    }
    //traverse to end of left subtree and start deleting
    clearHelper(node->getLeft()); 
    //traverse to end of right subtre and start deleting
    clearHelper(node->getRight());

    delete node; 
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    //Returns a pointer to the node with the smallest key, which is on the very left
    
    Node<Key, Value>* current = root_; 
    
    //keep going left in the left subtree until we reach a nullptr
    //when the getLeft() is equal to nullptr, it shows it is a leaf node
    while(current != nullptr && current->getLeft() != nullptr) {
      current = current->getLeft(); 
    }
    return current; 
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    //start at root
    //compare keys and choose between right and left subtrees based on the key
    //return the node if keys match
    //return nullptr if node is not found after reaching bottom of tree

    //start at the root
    Node<Key, Value>* current = root_; 

    //iterate through the tree, comparing keys of current and the given key
    while (current != nullptr) {
      //if key given is greater than the current node key, go right
      if (current->getKey() < key) {
        current = current->getRight(); 
      }
      //if key given is less than the current node key, go left
      else if (current->getKey() > key) {
        current = current->getLeft(); 
      }
      //if key given is equal to the current node key, return the node
      else {
        return current; 
      }
    }
  return nullptr; 
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    //to check if a node is balanced, we need to compare heights of its subtrees
      //to get the heights we need to start traversing from bottom of the tree
    //find the heights of the left and right subtree
      //if the heights differ by >1, tree is not balanced -> return (and propagate) false to top of recursive call
      //if heights differ by <=1, then continue comparing heights upwards
        //height of the current node will now be 1 + the max height of the two subtrees

    return balanceHelper(this->root_) != -1; 
      

}

template<typename Key, typename Value> 
int BinarySearchTree<Key, Value>::balanceHelper(Node<Key, Value>* node) const {
  //empty but it means it is balanced
  if (node == nullptr) {
    return 0; 
  }

  //check left subtree for the height and the balanced
  int leftHeight = balanceHelper(node->getLeft()); 
  if (leftHeight == -1) {
    return -1; 
  }

  //check right subtree for the height and the balance
  int rightHeight = balanceHelper(node->getRight()); 
  if (rightHeight == -1) {
    return -1; 
  }

  //if heights differ by 1, tree is not balanced -> return and propagate false to top recursive call
  if (abs(leftHeight - rightHeight) != 0) {
    return -1; 
  }

  //height of the current node will be 1 + max height of the two subtrees
  return 1 + std::max(leftHeight, rightHeight);

}




template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
