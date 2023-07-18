/*
 * Name             student.cpp
 * Author           Krystal Hong
 * Date             9 September 2021
 * Description      Learning C++ classes
 * Pledge           I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>


using namespace std;


/**
* Allows the user to enter information for multiple students, then
* find those students whose GPA is below 1.0 and prints them to the
* screen.
*/

class Student {

private:
	string first_, last_;
	float gpa_;
	int id_;


   public:
    Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} {}

    string full_name() const {
        return first_ + " " + last_;
    }



    int id() const {
        return id_;
    }

    float gpa() const {
        return gpa_;
    }


    void print_info() const {
        cout << full_name() << ", GPA: " << fixed << setprecision(2) << gpa() << ", ID: " << id() << endl;
    }



    // print_info() should print in the format (GPA has 2 decimal places):
    // Bob Smith, GPA: 3.50, ID: 20146
};
/**
*Takes a vector of Student objects,and returns a new vector
*withallStudentswhoseGPAis<1.0.
*/



vector<Student> find_failing_students(const vector<Student> &students) {
    vector<Student> failing_students;
    //Iterates through the students vector,appending each student whose gpa is
    //less than 1.0 to the failing_students vector.
    for (auto it = students.cbegin(); it != students.cend(); ++it) {
        if (it->gpa() < 1.0) {
            failing_students.push_back(*it);
        }

    }


    return failing_students;
}
/**
*Takes
a vector of Student objects and prints them to the screen.
*/


void print_students(const vector<Student> &students) {
	 //Iterates through the students vector,calling print_info() for each student.

    for (auto it = students.cbegin(); it != students.cend(); ++it) {
        it->print_info();
    }

}

int main() {
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;
    do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while (gpa < 0 || gpa > 4) {
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');
    cout << endl << "All students:" << endl;
    print_students(students);
    cout << endl << "Failing students:";

    // TODO
    // Print a space and the word 'None' on the same line if no students are
    // failing.
    // Otherwise, print each failing student on a separate line.


    vector<Student> fail = find_failing_students(students);
    if (fail.empty()) {
        cout << " None";
    } else {
        cout << endl;
        print_students(fail);
    }


    return 0;
}
