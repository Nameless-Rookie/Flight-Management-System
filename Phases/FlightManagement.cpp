// ============================================
// Flight Management System
// Phase 1: Basic Classes & Objects
// OOP Concepts: Classes, Objects, Methods, I/O
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Passenger {
public:
    int passengerId;
    string name;
    string phone;
    string passportNo;

    void input() {
        cout << "Enter Passenger ID: ";
        cin >> passengerId;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Phone: ";
        cin >> phone;
        cout << "Enter Passport No: ";
        cin >> passportNo;
    }

    void display() {
        cout << "Passenger ID: " << passengerId << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Passport No: " << passportNo << endl;
    }
};

class Flight {
public:
    int flightId;
    string airline;
    string origin;
    string destination;
    string departureTime;
    int availableSeats;

    void input() {
        cout << "Enter Flight ID: ";
        cin >> flightId;
        cout << "Enter Airline Name: ";
        cin.ignore();
        getline(cin, airline);
        cout << "Enter Origin City: ";
        getline(cin, origin);
        cout << "Enter Destination City: ";
        getline(cin, destination);
        cout << "Enter Departure Time (e.g. 6:30PM): ";
        cin >> departureTime;
        cout << "Enter Available Seats: ";
        cin >> availableSeats;
    }

    void display() {
        cout << "Flight ID: " << flightId << endl;
        cout << "Airline: " << airline << endl;
        cout << "Origin: " << origin << endl;
        cout << "Destination: " << destination << endl;
        cout << "Departure: " << departureTime << endl;
        cout << "Seats Available: " << availableSeats << endl;
    }
};

class Seat {
public:
    int seatNo;
    string seatClass; // Economy, Business, First
    float price;
    bool isAvailable;

    void input() {
        cout << "Enter Seat No: ";
        cin >> seatNo;
        cout << "Enter Seat Class (Economy/Business/First): ";
        cin >> seatClass;
        cout << "Enter Seat Price: ";
        cin >> price;
        isAvailable = true; // New seats are available by default
    }

    void display() {
        cout << "Seat No: " << seatNo << endl;
        cout << "Class: " << seatClass << endl;
        cout << "Price: Rs." << price << endl;
        cout << "Status: " << (isAvailable ? "Available" : "Booked") << endl;
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "      Flight Management System" << endl;
    cout << "  Phase 1 - Basic Classes & Objects" << endl;
    cout << "========================================" << endl << endl;

    // --- Passenger ---
    Passenger p;
    cout << "--- Enter Passenger Details ---" << endl;
    p.input();
    cout << endl;

    // --- Flight ---
    Flight f;
    cout << "--- Enter Flight Details ---" << endl;
    f.input();
    cout << endl;

    // --- Seat ---
    Seat s;
    cout << "--- Enter Seat Details ---" << endl;
    s.input();
    cout << endl;

    // --- Display All ---
    cout << "========================================" << endl;
    cout << "            Summary" << endl;
    cout << "========================================" << endl;

    cout << endl << "--- Passenger Info ---" << endl;
    p.display();

    cout << endl << "--- Flight Info ---" << endl;
    f.display();

    cout << endl << "--- Seat Info ---" << endl;
    s.display();

    cout << endl << "========================================" << endl;
    cout << "  Phase 1 Complete!" << endl;
    cout << "========================================" << endl;

    return 0;
}
