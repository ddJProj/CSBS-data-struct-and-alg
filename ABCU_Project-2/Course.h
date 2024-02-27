//
// Created by E. Johnson on 2/18/24.
//

#ifndef ABCU_PROJECT_TWO_COURSE_H
#define ABCU_PROJECT_TWO_COURSE_H


#include "ABCUParser.h"
#include "TemplateAVLTree.h"
#include "TemplateDataStructure.h"
#include "TemplateNode.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include "vector"
#include <string>


using namespace std;

#include <string>
#include <vector>


/**============================================================================
 *  Course structure object definition
 *=============================================================================
 */

/**
 * Holds the values from a single line of our input file
 */
struct Course {
    std::string courseId;
    std::string courseTitle;
    std::vector<std::string> prerequisiteCourses;

    Course() = default;

    // if we want to call the constructor with values to create a struct instead
    // of starting with an empty Course struct and assigning values
    Course(const std::string& id, const std::string& title,
           const std::vector<std::string>& prerequisites = {})
            : courseId(id), courseTitle(title), prerequisiteCourses(prerequisites) {}

    // to add prerequisiteCourses easier to the vector after creation

    void addPrerequisiteCourse(const std::string& prerequisite) {
        prerequisiteCourses.push_back(prerequisite);
    }

    /**
     * https://brevzin.github.io/c++/2019/07/28/comparisons-cpp20/
     * overload for less than operator to allow template comparison of
     * two string courseId values we compare two Course objects that are
     * contained within the T node tData template. define that we are
     * the string values of the two objects courseId's
     */
    bool operator<(const Course& otherCourseObj) const {
        return courseId < otherCourseObj.courseId;
    }
    /**
     * overload for greater than operator to allow template comparison of
     * two string courseId values
     */
    bool operator>(const Course& otherCourseObj) const {
        return courseId > otherCourseObj.courseId;
    }
};

#endif //ABCU_PROJECT_TWO_COURSE_H
