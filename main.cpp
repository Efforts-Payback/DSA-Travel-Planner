#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>
#include <windows.h>
#include "travelplanner.cpp"
#include "travelplanner.hpp"
using namespace std;

void adminLogin();
void customerLogin();
void login();
void signUp();
void adminPanel();
void customerPanel();
void startTravelPlanner();
void askForServices();

int main() {
    system("cls");
    char ch;
    cout << "----------Login----------" << endl;
    cout << "1. Admin Login" << endl;
    cout << "2. Customer Login/Sign Up" << endl;
    cin >> ch;
    switch (ch) {
        case '1':
            adminLogin();
            break;
        case '2':
            customerLogin();
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
            Sleep(2000);
            main();
            break;
    }
    return 0;
}

void adminLogin() {
    string adminUser = "admin", adminPass = "admin123";
    string user, pass;

    cout << "Admin Login" << endl;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    if (user == adminUser && pass == adminPass) {
        cout << "Welcome Admin!" << endl;
        adminPanel();
    } else {
        cout << "Invalid credentials!" << endl;
        Sleep(2000);
        main();
    }
}

void customerLogin() {
    char choice;
    cout << "Are you an old customer or a new customer? (O/N): ";
    cin >> choice;

    if (choice == 'O' || choice == 'o') {
        login();
    } else if (choice == 'N' || choice == 'n') {
        signUp();
    } else {
        cout << "Invalid choice! Please try again." << endl;
        Sleep(2000);
        customerLogin();
    }
}

void signUp() {
    string name, pass;
    cout << "Enter your details to sign up: " << endl;
    cout << "Username: ";
    cin >> name;
    cout << "Password: ";
    cin >> pass;

    fstream fout;
    fout.open("customers.txt", ios::app); 
    fout << name << " " << pass << endl;
    fout.close();

    cout << "You have successfully signed up!" << endl;
    Sleep(2000);
    customerPanel(); 
}

void login() {
    int flag = 0;
    string name, pass, name1, pass1;
    cout << "Enter your details: " << endl;
    cout << "Username: ";
    cin >> name;
    cout << "Password: ";
    cin >> pass;

    ifstream fin;
    fin.open("customers.txt", ios::in);
    while (fin >> name1 >> pass1) {
        if (name == name1 && pass == pass1) {
            flag = 1;
            break;
        }
    }
    fin.close();

    if (flag == 1) {
        cout << "Login successful! Welcome, " << name << "." << endl;
        Sleep(2000);
        customerPanel();
    } else {
        cout << "Invalid login details. Please try again." << endl;
        Sleep(2000);
        customerLogin(); 
    }
}

void adminPanel() {
    system("cls"); 
    cout << "====== Admin Panel ======" << endl;
    
    char choice;
    cout << "1. Add Customers" << endl;
    cout << "2. Remove Customers" << endl;
    cout << "3. Return to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == '1') {
        int numCustomers;
        cout << "How many customers do you want to add? ";
        cin >> numCustomers;

        fstream fout;
        fout.open("customers.txt", ios::app); 

        if (!fout) {
            cerr << "Error opening file. Please check permissions." << endl;
            return;
        }

        for (int i = 1; i <= numCustomers; ++i) {
            string name, pass;
            cout << "Enter details for customer " << i << ":" << endl;

            cout << "Username: ";
            cin >> name;
            cout << "Password: ";
            cin >> pass;

            fout << name << " " << pass << endl;
            cout << "Successfully added " << name << " with password: " << pass << endl;
        }

        fout.close();
        cout << "\nAll customers have been successfully added." << endl;
        cout << "Returning to main menu..." << endl;
        Sleep(2000); 
        main();

    } else if (choice == '2') {
        string customerToRemove, line;
        cout << "Enter the username of the customer to remove: ";
        cin >> customerToRemove;

        ifstream fin("customers.txt");
        ofstream temp("temp.txt");

        if (!fin || !temp) {
            cerr << "Error opening files." << endl;
            return;
        }

        bool found = false;
        while (getline(fin, line)) {
            if (line.find(customerToRemove + " ") != 0) { 
                temp << line << endl;
            } else {
                found = true;
            }
        }
        fin.close();
        temp.close();

        if (found) {
            remove("customers.txt");
            rename("temp.txt", "customers.txt");
            cout << "Customer " << customerToRemove << " removed successfully!" << endl;
            cout << "Returning to main menu..." << endl;
        	Sleep(2000); 
        	main();
        } else {
            cout << "Customer not found." << endl;
            remove("temp.txt");
            sleep(2000);
            main();
        }

    } else {
        cout << "Returning to main menu..." << endl;
        Sleep(2000); 
        main();
    }
}

void customerPanel() {
    cout << "Customer Panel: Welcome!" << endl;
    askForServices();
}

void askForServices() {
    char choice;
    system("cls");
    cout << "Do you want to use our travel services? (Y/N): ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        cout << "Choose your preference:\n1. Cheapest Route ($5)\n2. Fastest Route ($10)" << endl;
        int preference;
        cin >> preference;

        if (preference == 1 || preference == 2) {
            cout << "Enter 'yes' to confirm payment: ";
            string paymentConfirmation;
            cin >> paymentConfirmation;

            if (paymentConfirmation == "yes") {
                if (preference == 1) {
                    cout << "You chose the Cheapest Route. Payment of $5 successful!" << endl;
                } else {
                    cout << "You chose the Fastest Route. Payment of $10 successful!" << endl;
                }
                Sleep(2000);
                startTravelPlanner();
            } else {
                cout << "Payment not completed. Returning to main menu." << endl;
                Sleep(2000);
                main();
            }
        } else {
            cout << "Invalid choice. Returning to main menu." << endl;
            Sleep(2000);
            main();
        }
    } else {
        cout << "Thank you! Returning to main menu." << endl;
        Sleep(2000);
        main();
    }
}

void startTravelPlanner() {
    system("cls");
    int n = 11;
    vector<string> places = {
        "Lahore Railway Station", "Badshahi Mosque", "Shalimar Gardens",
        "Faisal Mosque", "Minar-e-Pakistan", "National Stadium Karachi",
        "Pakistan Monument", "Lahore Museum", "Hingol National Park",
        "Mohenjo-Daro", "Quaid-e-Azam's Mausoleum"
    };

    vector<vector<string>> paths = {
        {"Lahore Railway Station", "Badshahi Mosque", "3.5"}, 
        {"Lahore Railway Station", "Shalimar Gardens", "6"},
        {"Badshahi Mosque", "Faisal Mosque", "15"},
        {"Badshahi Mosque", "Minar-e-Pakistan", "8"},
        {"Badshahi Mosque", "Quaid-e-Azam's Mausoleum", "4.5"},
        {"Shalimar Gardens", "Pakistan Monument", "5"},
        {"Faisal Mosque", "National Stadium Karachi", "12"},
        {"Faisal Mosque", "Shalimar Gardens", "9"},
        {"Minar-e-Pakistan", "Lahore Museum", "8"},
        {"National Stadium Karachi", "Hingol National Park", "7"},
        {"Pakistan Monument", "Badshahi Mosque", "4"},
        {"Pakistan Monument", "Mohenjo-Daro", "4"},
        {"Pakistan Monument", "Lahore Museum", "4"},
        {"Pakistan Monument", "National Stadium Karachi", "6"},
        {"Lahore Museum", "Quaid-e-Azam's Mausoleum", "4.5"},
        {"Lahore Museum", "Minar-e-Pakistan", "8"},
        {"Lahore Museum", "National Stadium Karachi", "7"},
        {"Hingol National Park", "Badshahi Mosque", "5"},
        {"Mohenjo-Daro", "Pakistan Monument", "4"},
        {"Mohenjo-Daro", "Minar-e-Pakistan", "7"},
        {"Quaid-e-Azam's Mausoleum", "Lahore Railway Station", "6"}
    };

    TravelPlanner* tp = TravelPlanner::getTravelPlanner(n, places, paths);
    tp->displayLocations();
    tp->createEdgeVector();
    tp->createAdjacencyMatrix();

    string prompt;
    cout << "Do you want to get the shortest path between your source and destination? Type Y or y to proceed: ";
    cin >> prompt;
    while (prompt == "Y" || prompt == "y") {
        string source, destination;
        cout << "Enter source location: ";
        cin.ignore();
        getline(cin, source);
        cout << "Enter destination location: ";
        getline(cin, destination);
        tp->shortestPathWithMinimumStops(source, destination);
        cout << "Do you want to get the shortest path between your source and destination? (Y/N): ";
        cin >> prompt;
    }
    cout << "Thanks for using the application." << endl;
}
