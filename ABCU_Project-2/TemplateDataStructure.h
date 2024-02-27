//
// Created by E. Johnson on 2/18/24.
//

#ifndef ABCU_PROJECT_TWO_TEMPLATEDATASTRUCTURE_H
#define ABCU_PROJECT_TWO_TEMPLATEDATASTRUCTURE_H



#include "ABCUParser.h"
#include "TemplateAVLTree.h"
#include "Course.h"
#include "TemplateNode.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include "vector"
#include <string>


using namespace std;

#include <string>


/**
 *============================================================================
 *  Template data structure class. Utilizes common insert / search method
 *  for reusability accross multiple types of data structures
 *============================================================================
 */



/**
 * Data structure template. Can be readily used for hash map, vector,
 * or tree implementations
 * In this application, the template data "tData" object will contain
 * the Course object, and "tkey" will be the courseId
 */
template <class T>
class TemplateDataStruct {
public:
    // uses fully virtual methods that will need to be overriden when implemented
    // insert template data object into chosen data structure
    virtual void Insert(const T &tData) = 0;

    // uses parameter template key for searching for matching tData object
    virtual T *Search(const std::string &tKey) = 0;

    // the destructor for the template data structure that will be implemented
    virtual ~TemplateDataStruct() {}
};


#endif //ABCU_PROJECT_TWO_TEMPLATEDATASTRUCTURE_H
