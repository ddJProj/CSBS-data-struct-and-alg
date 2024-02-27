//
// Created by E. Johnson on 2/18/24.
//

#include "ABCUParser.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include "vector"
#include <string>


using namespace std;


//============================================================================
// Utility Function Definitions:  (Input/Output/Validation)
//============================================================================



/**
 * Takes filepath and instantiates an input file data stream with the filepath for processing.
 * validates that the file has been opened safely, and then passes a reference to the file stream and a ref to the
 * data structure that is used in this application for further processing.
 *
 *@param - const string &filePath - the validated path to input file in string format
 *@param -TemplateDataStruct<Course> - the selected data structure of courses for application. in this application,
 *          this is an AVL tree, but it could be any data structure (i.e. vector, hash table etc)
 *@returns -
 */
void openFile(const std::string &filePath,
              TemplateDataStruct<Course> *courseContainer) {
    ifstream fileInputStream(filePath);
    if (!fileInputStream) {
        throw ios_base::failure("An error occurred opening your file.");
    }
    if (fileInputStream.peek() == ifstream::traits_type::eof()) {
        throw std::ios_base::failure("The file is empty");
    }
    courseInputHandler(fileInputStream, courseContainer);
    fileInputStream.close();
}

/**
 * handles the input data from the file. Does so by validating that there is data to be processed, and then calling
 * the appropriate functions to handle the various steps. Takes the first line of the file and separates it into
 * a header var before passing the remaining input data to a loop that will parse each line, then call the
 * object handler to create / return a filled object. Using the template method Insert(), the chosen templata data
 * structure is then called and the object is inserted into the correct place within.
 *
 *@param - ifstream &fileInputStream - input file data stream preopened with the correct file name
 *@param - TemplateDataStruct<Course> - the selected data structure of courses for application. in this application,
 *          this is an AVL tree, but it could be any data structure (i.e. vector, hash table etc)
 *@returns -
 */
void courseInputHandler(ifstream &fileInputStream,
                        TemplateDataStruct<Course> *courseContainer) {
    std::string headerLineInput;
    if (!std::getline(fileInputStream, headerLineInput)) {
        throw std::ios_base::failure(
                "Error reading header line. File is empty, or not in .csv format.");
    }
    std::string nextInputLine;
    while (getline(fileInputStream, nextInputLine)) {
        std::vector<std::string> courseStrings = vectorParser(nextInputLine);
        if (courseStrings.size() >= 2) {
            Course nextCourseToInsert = objectHandler(courseStrings);
            courseContainer->Insert(nextCourseToInsert);
        } else {
            throw std::ios_base::failure(
                    "Input line does not contain minimum of course ID and course title.");
        }
    }
}


/**
 * Object handler takes the parsed line of csv data, inserts the values into their respective attributes / variable
 * and then returns the populated object for insertion into data structure
 *
 *@param - vector<string> &courseData - string vector with attribute values
 *@returns -
 */
Course objectHandler(const std::vector<string> &courseData) {
    Course course;
    if (courseData.size() >= 2) {
        course.courseId = courseData[0];
        course.courseTitle = courseData[1];
        for (size_t i = 2; i < courseData.size(); i++) {
            course.prerequisiteCourses.push_back(courseData[i]);
        }
    }
    return course;
}


/**
 * Takes a raw line of input data from csv file, delimits the values by comma, and assigns each
 * of the separated values to an index position within a new string vector, in order.
 *
 *@param - string containing the full line of raw data from input file.
 *@returns -  string vector with the separated values from the file for placing into data object
 */
vector<string> vectorParser(const string &nextInputLine) {
    stringstream ss(nextInputLine);
    vector<string> courseData;
    string tempCourseValue;
    while (getline(ss, tempCourseValue, ',')) {
        courseData.push_back(tempCourseValue);
    }
    return courseData;
}
