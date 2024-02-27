
//
// Created by E. Johnson on 2/18/24.
//

#include "ABCUParser.h"
#include "TemplateDataStructure.h"
#include "TemplateAVLTree.h"
#include "Course.h"
#include "TemplateNode.h"
#include "TemplateAVLTree.cpp"

#include "vector"
#include <string>
#include <iostream>
#include <limits>

using namespace std;




//============================================================================
// Global definitions visible to all methods and classes
//============================================================================



const unsigned int STRING_INPUT_COURSEID = 13;
const unsigned int STRING_INPUT_FILENAME = 21;


/**
 * output function to handle printing the template tData object for this application
 * as this is a Course struct object, this method involves the process of printing the
 * values contained in the individual Course struct
 *
 *@param - Course *courseToPrint - pointer to the course object being printed
 *@returns -
 */
void printACourse(Course* course) {
	// if the node is somehow empty / nullptr
	if (course == nullptr) {
		return;
	}


	vector <string> prereqs = course->prerequisiteCourses;
	std::cout << "Course ID: " << course->courseId << " | ";
	std::cout << "Course Title: " << course->courseTitle << " | ";
	std::cout << "Prerequisite Courses: ";

	if (!course->prerequisiteCourses.empty()) {
		for (size_t i = 0; i < course->prerequisiteCourses.size(); i++) {
			if (i == course->prerequisiteCourses.size() - 1) {
				std::cout << course->prerequisiteCourses[i] << endl;
			}
			else {
				std::cout << course->prerequisiteCourses[i] << ", ";
			}
		}
		std::cout << endl;
	}
	else {
		std::cout << "None\n" << endl;
	}
}

/**
 * using the print node method to route output to print a course
 * done this way to increase modularity of the AVL tree logic
 * and reduce any definition of object types within the tree
 *
 *@param - node<t> *nodetoprint - template node containing template data object
 */
template <class T> void printANode(Node<T>* nodeToPrint) {
	// if the node is somehow empty / nullptr
	if (nodeToPrint == nullptr) {
		return;
	}

	printACourse(&nodeToPrint->tData);

}


 /**
  * Main menu print function
  */
void printMenu() {
	std::cout << "\nOption 1 = Import Course catalog from file path" << endl;
	std::cout << "Option 2 = Print Course catalog (Sorted by ID)" << endl;
	std::cout << "Option 3 = Print a Course by course ID" << endl;
	std::cout << "Option 4 = Exit program" << endl;
}



/**
 * user string input validation function for menu navigation / action
 * selection
 *
 * @param const int inputType
 * @return string input - validated string input
 */
string stringInputValidation(unsigned int inputType) {
	// variable to hold user input
	string input;
	// loop control variable, loops while input not valid
	bool inputValid = false;
	do {
		try {

			getline(cin >> ws, input);

			if (cin.fail() || input.empty()) {
				throw ios_base::failure("Text input attempt failed.");

			}
      // when course ID input selected, input not empty, 
      // and input isnt in correct format 4 letter, 3 numbers
			else if (inputType == STRING_INPUT_COURSEID && !input.empty() &&
				input.length() != 7) {
				if (!(std::isalpha(input[0])) || !(std::isalpha(input[1])) ||
					!(std::isalpha(input[2])) || !(std::isalpha(input[3])) ||
					!(std::isdigit(input[4])) || !(std::isdigit(input[5])) ||
					!(std::isdigit(input[6]))) {
					throw ios_base::failure(
						"Text input invalid. Expected string in format ABCD123");
				}
			}
			// if input is not empty, and does not contain the sub string ".csv"
			else if (inputType == STRING_INPUT_FILENAME && !input.empty() &&
				input.find(".csv") == std::string::npos) {
				throw ios_base::failure(
					"Text input invalid. Expected valid .csv file.");
			}

			else {
				inputValid = true;
			}
		}
		catch (const ios_base::failure& except) {

			cout << "Enter a valid text input, or enter exit to return to menu." << endl;
		}
	} while (!inputValid && !(input.compare("exit") == 0));

	return input;
}



/**
 * user integer input validation function for menu navigation / action
 * selection
 *
 * @param const unsigned int menuSelection - the menu to validate input for
 * @return validated integer input
 */
int userIntegerValidation() {

	int input{};

	bool inputValid = false;
	do {
		try {

			std::cout << "Enter a valid integer input to proceed." << endl;
			cin >> input;
			cin.ignore();

			// if input is not a valid menu option or an integer
			// such as is not between 1 and 4 or equal to 9
			if (cin.fail() || !(input >= 1 && input <= 4 || input == 9)) {

				throw ios_base::failure("Invalid integer input. Expected 1-4 or 9.");
			}
			else {
				inputValid = true;
			}
		}
		catch (const ios_base::failure& except) // catch input output exception
		{
			cin.clear(); // clear the error / exception
			cin.ignore(numeric_limits<streamsize>::max(),
				'\n'); // ignore remaining exceptions related to this io stream
			std::cerr << except.what() << endl;
		}
	} while (!inputValid);

	return input;
}




/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {


	/*
	// process command line arguments
	string csvPath, courseKey;
	switch (argc) {
		case 2:
			csvPath = argv[1];
			courseKey = "98109";
			break;
		case 3:
			csvPath = argv[1];
			courseKey = argv[2];
			break;
		default:
			csvPath = "hard code filePath here";
			courseKey = "CSCI350";
	}
	*/



	// Define a timer variable
	clock_t ticks;

	// declare variable to hold path to input .csv file
	string csvPath;

	// Define an AVL tree to hold course inputs
	auto* courseAVLTree = new AVLTree<Course>();

	// create course pointer to hold return location values to
	Course* course;
	// declare variable to check if input has successfully loaded the tree
	bool isFileLoaded = false;

	// menu choice selected storage variable
	int choice = 0;

	while (choice != 4) {

		// print main menu
		printMenu();

		// get menu choice selection, and validate it
		choice = userIntegerValidation();

		if (choice == 9) {
			continue;
		}
		// take action on the selected menu choice
		switch (choice) {

		case 1:
			try {
				std::cout << "\nEnter path to .csv file. " << endl;
				// validate and get the filepath to .csv input file from user

				// COMMENT OUT csvPath here to use switchbased fixed input at beginning of main()
				csvPath = stringInputValidation(STRING_INPUT_FILENAME);

				// if user entered exit to return to menu, return to menu.
				if (csvPath.compare("exit") == 0) {
					break;
				}


				// check if tree is empty, if tree not empty, delete any existing nodes
				if (!courseAVLTree->isTreeEmpty()) {
					// calls removal method which calls destructor helper / triggers destructor
					courseAVLTree->removeTree();
					isFileLoaded = false;
					cout << "\nData container was not empty, removing existing data now... Please try again." << endl;
					break;

				}
				else { // tree is empty, proceed to add input

					// Initialize a timer variable before loading bids
					ticks = clock();
					// Complete the method call to load the bids
					openFile(csvPath, courseAVLTree);
					// cout << courseAVLTree->Size() << " courses read" << endl;

					// Calculate elapsed time, current clock ticks minus starting clock ticks
					ticks = clock() - ticks; 
				}

			}
			catch (std::exception& except) {
				std::cerr << "The courses have failed to load: " << except.what()
					<< endl;
				// reassign check as false
				isFileLoaded = false;
				break;
			}
			// output the time taken to load courses if no exception occurs
			std::cout << "\nTime taken: " << ticks << " clock ticks";
			std::cout << " or: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds"
				<< endl;
			// assign isFileLoaded to be true
			isFileLoaded = true;

			break;

		case 2:

			// if no file has been loaded yet, work cant be done!
			if (!isFileLoaded || courseAVLTree->isTreeEmpty()) {
				std::cout << "You must load a file before attempting to do work!"
					<< endl;
				break; // exit the case if input not yet loaded
			}
			else {

				// Initialize a timer variable before printing course in order
				ticks = clock();

				// begin traversal of tree in order by courseId, outputting/ printing each
				courseAVLTree->initiateInOrder();

				// Calculate elapsed time, current clock ticks minus starting clock ticks
				ticks = clock() - ticks;
			}
			// output the time taken to search for the course
			std::cout << "Time taken: " << ticks << " clock ticks";
			std::cout << " or: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds"
				<< endl;
			break;

		case 3:
			// if no file has been loaded yet, work cant be done!
			if (!isFileLoaded || courseAVLTree->isTreeEmpty()) {
				std::cout << "You must load a file before attempting to do work!"
					<< endl;
				break; // exit the case if input not yet loaded

			}
			else {

				std::cout << "\nEnter Course ID: " << endl;


				// COMMENT OUT courseID here to use switchbased fixed input at beginning of main()

				// get course Id / key from user input to search for
				string courseKey = stringInputValidation(STRING_INPUT_COURSEID);

				// Initialize a timer variable before printing finding and printing the course
				ticks = clock();

				// return pointer to the course (or null if no course found)
				course = courseAVLTree->Search(courseKey);

				// Calculate elapsed time, current clock ticks minus starting clock ticks
				ticks = clock() - ticks;


				// if a valid Course object was found
				if (course != nullptr && !course->courseId.empty()) {
					// output the values of that course

					std::cout << "\nCourse ID: " << courseKey << " was found." << endl;

					printACourse(course);

				}
				else { // a valid course not found
					std::cout << "\nCourse ID: " << courseKey << " not found." << endl;
				}
				// output the time taken to search for the course
				std::cout << "Time taken: " << ticks << " clock ticks";
				std::cout << " or: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds"
					<< endl;
				break;
			}
		default:
			break;
		}

	}

	std::cout << "Good bye." << endl;

	delete courseAVLTree;

	return 0;
}
