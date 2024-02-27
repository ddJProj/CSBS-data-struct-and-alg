//
// Created by E. Johnson on 2/18/24.
//



#include "TemplateAVLTree.h"

#include "vector"
#include <string>


using namespace std;

/**
 * Node creation helper method. Created because I was having issues with my Course data not
 * being stored properly.
 *
 * @param tData object containing data to store in the tree
 * @return Node<T> *ptr - pointer to the new node containing our data
 */
template<class T>
Node<T> *AVLTree<T>::createNewNode(const T &tData) {
    Node<T> *newNode = new Node<T>();
    newNode->tData = tData;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    return newNode;

}


/**
 * destructor helper method to traverse the tree recursively
 * calls delete on each node within
 *@param - pointer to a Node of type template T
 */
template<class T>
void AVLTree<T>::purgeTree(Node<T> *node) {
    if (node != nullptr) {
        // call this method with the left child node
        purgeTree(node->left);
        // call this method with the right child node
        purgeTree(node->right);
        // delete the node that this method was called with
        delete node;
    }
}

/**
 * calls the destructor helper method to traverse the tree recursively
 * calls delete on each node within. Method is designed to allow partial
 * or faulty trees to be deleted
 */
template<class T>
void AVLTree<T>::removeTree() {
    purgeTree(root);
    root = nullptr;
}

/**
 *allows the use of isEmpty() check on AVLTree
 * isEmpty() method found from the following link:
 * https://algs4.cs.princeton.edu/code/edu/princeton/cs/algs4/AVLTreeST.java
 *
 *@returns - boolean value indicating if tree is empty (true) or not (false)
 */
template<class T>
bool AVLTree<T>::isTreeEmpty() const {
    return root == nullptr;
}


/**
 * So long as the tree isnt empty / root isnt null, Calls in order traversal on
 * the root node of the tree via inOrder method
 */
template<class T>
void AVLTree<T>::initiateInOrder() {
    // if the tree is empty, return without attempting to traverse
    if (root == nullptr) {
        return;
    }
    inOrder(root); // if root is not nullptr call traversal method
}

/**
 * Begins traversing the tree in sorted order, as well as adding output / print calls
 * to the stack. Calls the lowest value (left child), adds current node print call to the stack,
 * then calls the next node that is greater than current node.
 *
 *@param - pointer to a Node<template T> "currentNode"
 *
 */
template<class T>
void AVLTree<T>::inOrder(Node<T> *currentNode) {
    if (currentNode != nullptr) {
        inOrder(currentNode->left);
        printANode(currentNode);
        inOrder(currentNode->right);
    }
}


/**
 * returns the height value that is stored in a given node.
 * This is the height of that node in the tree
 *
 *@param - pointer to a Node of type template T "currentNode"
 *@returns - integer height value of the current node
 */
template<class T>
int AVLTree<T>::height(Node<T> *currentNode) {
    // nNodes =
    if (currentNode == nullptr) {
        return 0;
    }
    return currentNode->height;
}



/**
 * Finds / calculates the balance of a current node using
 * the height values of it's child nodes. This is the value that tells the tree
 * when a sub-tree needs to be rebalanced because one side is heavier
 *
 *@param - pointer to a Node of type template T "currentNode"
 *@returns - integer value of tree's balance
 */
template<class T>
int AVLTree<T>::returnBalance(Node<T> *currentNode) {
    if (currentNode == nullptr) {
        return 0;
    }
    return (height(currentNode->left) - height(currentNode->right));
}


/**
 * The method responsible for our left rotations / rebalance movements in the tree
 *
 *@param - pointer to a Node of type template T "childNode"
 *@returns - pointer to a Node of type template T
 */
template<class T>
Node<T> *AVLTree<T>::leftRotate(Node<T> *childNode) {

    Node<T> *parentNode = childNode->right;
    // holds ptr to the subtree while we rotate for proper reattachment after
    Node<T> *tempSubtree = parentNode->left;

    // this is our rotation for left tree
    parentNode->left = childNode;
    childNode->right = tempSubtree;


    // now we update the height of the tree after the rotation
    childNode->height =
            max(height(childNode->left), height(childNode->right)) + 1;
    parentNode->height =
            max(height(parentNode->left), height(parentNode->right)) + 1;

    // this is our new root node
    return parentNode;
}


/**
 * The method responsible for our right rotations / rebalance movements in the tree
 *
 *@param - pointer to a Node of type template T "parentNode"
 *@returns - pointer to a Node of type template T
 */
template<class T>
Node<T> *AVLTree<T>::rightRotate(Node<T> *parentNode) {

    Node<T> *childNode = parentNode->left;
    // holds ptr to the subtree while we rotate for proper reattachment after
    Node<T> *tempSubtree = childNode->right;

    // this is our rotation for right tree
    childNode->right = parentNode;
    parentNode->left = tempSubtree;

    // now we update the height of the tree after the rotation
    parentNode->height =
            max(height(parentNode->left), height(parentNode->right)) + 1;
    childNode->height =
            max(height(childNode->left), height(childNode->right)) + 1;

    // this is our new root node of this subtree
    return childNode;
}

/**
 * Search override method from template data structure.
 * Must be implemented in whatever structure you use.
 * Calls the search() method on the template string tkey to search the
 * data structure for match.
 *
 *@param -string &tKey - search value to compare against objects within nodes
 *@returns - pointer to a Node of type template T
 */
template<class T>
T *AVLTree<T>::Search(const string &tKey) {
    // call the recursive search fnc to traverse the tree
    Node<T> *node = search(root, tKey);
    // when we find treeKey match, return a ptr to it
    if (node != nullptr) {
        return &(node->tData);
    }
    return nullptr; // if nothing is found return nullptr
}




/**
 *method defined as const as it does not modify data in the tree
 *
 *@param - pointer to a Node of type template T "currentNode"
 *@param -string &tKey - search value to compare against objects within nodes
 *@returns - pointer to a Node of type template T
 */
template<class T>
Node<T> *AVLTree<T>::search(Node<T> *currentNode, const string &tKey) const {
    // base case, if our node not found
    if (currentNode == nullptr) {
        return nullptr;
    }
    // the key (courseId) is less than the current Node courseId
    // we traverse left
    if (tKey < currentNode->tData.courseId) {
        return search(currentNode->left, tKey);
    }
        // the key (courseId) is greater than the current Node courseId
        // we traverse right
    else if (tKey > currentNode->tData.courseId) {
        return search(currentNode->right, tKey);
    } else { // we found the node we are looking for!
        return currentNode;
    }
}




/**
 * Search override method from template data structure.
 * Must be implemented in whatever structure you use.
 * Calls the insert() method with the data object that will be stored
 * within a template Node. In this applicatioin the tData object
 * is a Course struct object
 *
 *@param - const T &tData - Template data object to be contained in a Node<T>
 */
template<class T>
void AVLTree<T>::Insert(const T &tData) {

    root = insert(root, tData);
}



/**
 * This is the core insertion logic for the AVL tree. The tree checks various conditions to ensure that the node and
 * node data are ready, finds the sorted position for the node, and then ensures that the tree recalculates
 * and rebalances itself if one subtreee has become heavier
 *
 *@param - const &tData of template type T - the data object (course object in this case)
 *@param - pointer to a Node of type template T "currentNode"
 *@returns - pointer to a Node of type template T
 */
template<class T>
Node<T> *AVLTree<T>::insert(Node<T> *currentNode, const T &tData) {
    if (currentNode == nullptr) {
        return createNewNode(tData);
    }

    // perform our insertion recursion calls
    //
    // if courseId to insert is less than course to insert
    if (tData < currentNode->tData) {
        // need to go to lower values recursively call insert with the left child
        // of current node
        currentNode->left = insert(currentNode->left, tData);
    }
        // need to go to higher values, recursively call insert with the right child
        // of current node
    else if (tData > currentNode->tData) {
        currentNode->right = insert(currentNode->right, tData);
    }
        // this tree does not allow duplicate courseId's so return
    else {
        return currentNode;
    }

    // update the value of height for parent node
    currentNode->height =
            1 + max(height(currentNode->left), height(currentNode->right));

    // find / calc the balance factor of tree to see if this causes us to be
    // unbalanced
    int balance = returnBalance(currentNode);

    // take recourse for rebalancing the tree if we are now unbalanced

    // left left most case
    if (balance > 1 && tData < currentNode->left->tData) {
        return rightRotate(currentNode);
    }

    // right rightmost case
    if (balance < -1 && tData > currentNode->right->tData) {
        return leftRotate(currentNode);
    }

    // left rightmost case
    if (balance > 1 && tData > currentNode->left->tData) {
        currentNode->left = leftRotate(currentNode->left);
        return rightRotate(currentNode);
    }
    // right leftmost case
    if (balance < -1 && tData < currentNode->right->tData) {
        currentNode->right = rightRotate(currentNode->right);
        return leftRotate(currentNode);
    }

    return currentNode;
}
