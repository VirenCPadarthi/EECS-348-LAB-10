/* Lab: Lab-10
 * Author: Viren Padarthi
 * Date creatd: 4/12/25
 *Date last modified: 4/16/2025
 * Collaborators: None 
 * Sources: Lecture Slides, Lab(8,9), Youtube, GeeksforGeeks, Replit, StackOverflow, gpt, TutorialsPoint, freecodecamp etc. 
 */




#include <iostream>
#include <fstream>
#include <vector>
#include "calculator.hpp"
using namespace std;
// This part takes the input file
int main() {
    string filename;
    cout << "Enter input file name: ";
    cin >> filename;
// If file not found
    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open the file. Please check the filename." << endl; //Error messgae to recheck the existance offile.
        return 1;
    }

    string line;
    int line_num = 1;

    // Read each line (number string) from file
    while (getline(file, line)) {
        cout << "Line " << line_num << ": " << line;

        // Check if the string is a valid double
        if (isValidDouble(line)) {
            cout << " is valid." << endl;

            // Add it to -123.456 using string math
            string result = addStrings(line, "-123.456");
            cout << line << " + (-123.456) = " << result << endl;
        } else {
            cout << " is invalid." << endl;
        }

        line_num++;
    }

    file.close();
    return 0;
}
