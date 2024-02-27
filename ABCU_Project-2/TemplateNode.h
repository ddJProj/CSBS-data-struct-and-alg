//
// Created by E. Johnson on 2/18/24.
//

#ifndef ABCU_PROJECT_TWO_TEMPLATENODE_H
#define ABCU_PROJECT_TWO_TEMPLATENODE_H



#include "ABCUParser.h"
#include "TemplateAVLTree.h"
#include "Course.h"
#include "TemplateDataStructure.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include "vector"
#include <string>

using namespace std;




/**
 *============================================================================
 *  Template Node structure definition for reusability
 *============================================================================
 */

/**
 * template Node object definition. Can be used with TemplateDataStruture
 * if you are using a tree based data structure. by modifying the struture
 * slightly can work with a linked list for vector / hashmap with chaining to
 * use for those just remove the unnecessary pointer / height value designed in
 * a way so that the data that the node holds can be whatever is needed to be
 * stored. In this application tData for a node will be an individual Course
 * struct
 */
template <class T>
struct Node {

    // this is where we put our data
    // in this project it will be the Course struct
    T tData;
    Node<T>* left;
    Node<T>* right;
    int height;


    /**
   *  default node constructor. Values are initialized in createANode helper function
   */
    Node() = default;

};

#endif //ABCU_PROJECT_TWO_TEMPLATENODE_H
