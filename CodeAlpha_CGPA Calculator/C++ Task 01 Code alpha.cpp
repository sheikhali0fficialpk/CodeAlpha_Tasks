#include <iostream>
using namespace std;

// Convert grade to grade points

float getGradePoint(string grade) {
    if (grade == "A"  || grade == "A+") return 4.0;
    if (grade == "A-") return 3.7;
    if (grade == "B+") return 3.3;
    if (grade == "B")  return 3.0;
    if (grade == "B-") return 2.7;
    if (grade == "C+") return 2.3;
    if (grade == "C")  return 2.0;
    if (grade == "C-") return 1.7;
    if (grade == "D")  return 1.0;
    if (grade == "F")  return 0.0;

    return -1.0; // invalid
}

// Input code data portion 

void inputCourses(int n, string names[], string grades[], float credits[]) {
    for (int i = 0; i < n; i++) {
        
		cout << "\nCourse " << i + 1 << endl;

        cout << "Enter course name: ";
        cin >> names[i];

        // Grade validation
        
		while (true) {
            cout << "Enter grade (A, B+, etc): ";
            cin >> grades[i];

            if (getGradePoint(grades[i]) != -1)
                break;

            cout << "Invalid grade! Try again.\n";
        }

        // Credit validation
        
		while (true) {
            cout << "Enter credit hours: ";
            cin >> credits[i];

            if (credits[i] > 0)
                break;

            cout << "Invalid credits! Must be > 0.\n";
        }
    }
}

// Calculate CGPA fORMULA

float calculateCGPA(int n, string grades[], float credits[], float &totalCredits, float &totalPoints) {

    totalCredits = 0;
    totalPoints = 0;

    for (int i = 0; i < n; i++) {
        float gp = getGradePoint(grades[i]);
        totalCredits += credits[i];
        totalPoints += gp * credits[i];
    }

    return totalPoints / totalCredits;
}

// Display results

	void displayResult(int n, string names[], string grades[], float credits[]) {
    	float totalCredits, totalPoints;
    	float cgpa = calculateCGPA(n, grades, credits, totalCredits, totalPoints);

    	cout << "\n\n===== RESULT =====\n";

    	cout << "Course\tGrade\tCredits\tPoints\n";

    	for (int i = 0; i < n; i++) {
        	float gp = getGradePoint(grades[i]);
        	float points = gp * credits[i];

        	cout << names[i] << "\t" << grades[i] << "\t"<< credits[i] << "\t" << points << endl;
    }

    cout << "\nTotal Credits: " << totalCredits << endl;
    cout << "Total Grade Points: " << totalPoints << endl;
    cout << "Final CGPA: " << cgpa << endl;
}

int main() {
    int n;

    cout << "===== CGPA CALCULATOR =====\n";
    cout << "Enter number of courses: ";
    cin >> n;

    string names[n];
    string grades[n];
    float credits[n];

    inputCourses(n, names, grades, credits);
    displayResult(n, names, grades, credits);

    return 0;
}
