#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <openssl/aes.h>
#include <openssl/rand.h>

using namespace std;

// Simple XOR encryption for demonstration
string encryptDecrypt(string data, string key) {
    string result = data;
    for (size_t i = 0; i < data.size(); i++) {
        result[i] = data[i] ^ key[i % key.size()];
    }
    return result;
}

// Save password to file (encrypted)
void savePassword(const string& site, const string& username, const string& password, const string& filename, const string& key) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string encrypted_password = encryptDecrypt(password, key);
    file << site << " " << username << " " << encrypted_password << endl;
    file.close();
    cout << "Password saved successfully!" << endl;
}

// Retrieve password for a specific site
void retrievePassword(const string& site, const string& filename, const string& key) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line, s, u, p;
    while (getline(file, line)) {
        stringstream ss(line);
        ss >> s >> u >> p;

        if (s == site) {
            string decrypted_password = encryptDecrypt(p, key);
            cout << "Username: " << u << ", Password: " << decrypted_password << endl;
            file.close();
            return;
        }
    }

    cout << "No password found for site: " << site << endl;
    file.close();
}

// Delete a password for a specific site
void deletePassword(const string& site, const string& filename) {
    ifstream file(filename);
    ofstream tempFile("temp.txt");

    if (!file.is_open() || !tempFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line, s;
    while (getline(file, line)) {
        stringstream ss(line);
        ss >> s;
        if (s != site) {
            tempFile << line << endl;
        }
    }

    file.close();
    tempFile.close();
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    cout << "Password for site " << site << " deleted successfully!" << endl;
}

int main() {
    string filename = "passwords.txt";
    string key = "mysecretkey";  // Simple key for encryption

    int choice;
    while (true) {
        cout << "\nPassword Manager Menu:" << endl;
        cout << "1. Save Password" << endl;
        cout << "2. Retrieve Password" << endl;
        cout << "3. Delete Password" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore the newline character after reading choice

        if (choice == 1) {
            string site, username, password;
            cout << "Enter site name: ";
            getline(cin, site);
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            savePassword(site, username, password, filename, key);
        }
        else if (choice == 2) {
            string site;
            cout << "Enter site name: ";
            getline(cin, site);
            retrievePassword(site, filename, key);
        }
        else if (choice == 3) {
            string site;
            cout << "Enter site name: ";
            getline(cin, site);
            deletePassword(site, filename);
        }
        else if (choice == 4) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
