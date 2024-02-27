//
// Created by dd on 2/18/24.
//

#ifndef ABCU_PROJECT_TWO_ABCUPARSER_H
#define ABCU_PROJECT_TWO_ABCUPARSER_H


#include "TemplateAVLTree.h"
#include "Course.h"
#include "TemplateDataStructure.h"
#include "TemplateNode.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include "vector"
#include <string>


using namespace std;


void courseInputHandler(ifstream &fileInputStream,
                        TemplateDataStruct<Course> *courseContainer);
void printMenu();
vector<string> vectorParser(const string &nextInputLine);
void openFile(const string &filePath,
              TemplateDataStruct<Course> *courseContainer);
Course objectHandler(const vector<string> &courseData);





#endif //ABCU_PROJECT_TWO_ABCUPARSER_H
