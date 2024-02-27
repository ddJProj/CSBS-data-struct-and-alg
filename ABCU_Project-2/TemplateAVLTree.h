//
// Created by E. Johnson on 2/18/24.
//

#ifndef ABCU_PROJECT_TWO_TEMPLATEAVLTREE_H
#define ABCU_PROJECT_TWO_TEMPLATEAVLTREE_H


#include "ABCUParser.h"
#include "TemplateDataStructure.h"
#include "TemplateNode.h"
#include "Course.h"

#include "Course.h"
#include <string>


/**
 *============================================================================
 *  AVL Tree class definition that implements the template data structure
 * uses template Nodes containing template data object storage
 * the tree can use any type of data object so long as the object is declared
 * above and the appropriate operator overloads are defined < , and >.
 *============================================================================
 */

/**
 * Utilizes our template data structure class to implement an AVL tree
 * much of structure from these sources:
 * https://www.programiz.com/dsa/avl-tree
 * https://github.com/KadirEmreOto/AVL-Tree/blob/master/onefile.cpp
 * https://algs4.cs.princeton.edu/code/edu/princeton/cs/algs4/AVLTreeST.java
 *
 */
template <class T>
class AVLTree : public TemplateDataStruct<T> {
public:

    AVLTree();
    // deconstructor declaration
    virtual ~AVLTree();
    // Insert initiation declaration
    void Insert(const T &tData) override;
    // Search initiation declaration
    T *Search(const std::string &tKey) override;
    // allows use of isEmpty on the tree
    bool isTreeEmpty() const;
    // calls destructor on the tree
    void removeTree();
    // start in order traversal from root node
    void initiateInOrder();

private:
    Node<T>* root = nullptr;

    void purgeTree(Node<T>* node);
    int height(Node<T>* currentNode);
    int returnBalance(Node<T>* currentNode);
    Node<T>* rightRotate(Node<T>* parentNode);
    Node<T>* leftRotate(Node<T>* childNode);
    Node<T>* insert(Node<T>* currentNode, const T& tData);
    Node<T>* search(Node<T>* currentNode, const std::string& tKey) const;
    void inOrder(Node<T>* currentNode);

    Node<T> *createNewNode(const T &tData);
};

template<class T>
AVLTree<T>::AVLTree(): root(nullptr) {

}

/**
 * essentially the same destructor method
 * that was used for binary search tree implementation
 */
template <class T> AVLTree<T>::~AVLTree() { purgeTree(root); }






#endif //ABCU_PROJECT_TWO_TEMPLATEAVLTREE_H


