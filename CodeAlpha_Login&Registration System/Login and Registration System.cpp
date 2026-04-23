#include <iostream>
#include <fstream>
#include <string>

using namespace std;


// -------------------------------
// Helper: Validate Input
// -------------------------------
bool validateInput(string username, string password, string &message) {
    if (username.empty() || password.empty()) {
        message = "Username and password cannot be empty.";
        return false;
    }

    if (username.length() < 3) {
        message = "Username must be at least 3 characters.";
        return false;
    }

    if (password.length() < 5) {
        message = "Password must be at least 5 characters.";
        return false;
    }

    return true;
}


// -------------------------------
// Check if User Exists
// -------------------------------
bool userExists(string username) {
    string filename = username + ".txt";
    ifstream file(filename.c_str());  // ? check file existence

    if (file) {
        file.close();
        return true;
    }

    return false;
}


// -------------------------------
// Register User
// -------------------------------
void registerUser() {
    string username, password, message;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    // Validate
    if (!validateInput(username, password, message)) {
        cout << "? Registration Failed: " << message << endl;
        return;
    }

    // Check duplicate
    if (userExists(username)) {
        cout << "? Registration Failed: Username already exists.\n";
        return;
    }

    // Create file for user
    string filename = username + ".txt";
    ofstream file(filename.c_str());

    file << password;  // store password
    file.close();

    cout << "? Registration Successful!\n";
}


// -------------------------------
// Login User
// -------------------------------
void loginUser() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    string filename = username + ".txt";
    ifstream file(filename.c_str());

    if (!file) {
        cout << "? Login Failed: Username not found.\n";
        return;
    }

    string storedPassword;
    file >> storedPassword;

    if (storedPassword == password) {
        cout << "? Login Successful!\n";
    } else {
        cout << "? Login Failed: Incorrect password.\n";
    }

    file.close();
}


// -------------------------------
// Main Menu
// -------------------------------
int main() {
    int choice;

    while (true) {
        cout << "\n--- Login & Registration System ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "? Invalid choice. Try again.\n";
        }
    }
}
