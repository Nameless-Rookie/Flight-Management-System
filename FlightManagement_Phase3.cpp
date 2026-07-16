// ============================================
// Flight Management System
// Phase 3: Arrays & Object Collections
// OOP Concepts: Array of Objects, Searching,
//               Menu-Driven Interface, Collections
// ============================================

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ============================================
// PASSENGER CLASS
// ============================================
class Passenger {
private:
    int passengerId;
    string name;
    string phone;
    string passportNo;

public:
    Passenger() : passengerId(0), name(""), phone(""), passportNo("") {}

    // --- Getters ---
    int getPassengerId() { return passengerId; }
    string getName() { return name; }
    string getPhone() { return phone; }
    string getPassportNo() { return passportNo; }

    // --- Setters with Validation ---
    void setPassengerId(int id) {
        if (id > 0) passengerId = id;
        else cout << "  [!] Passenger ID must be positive." << endl;
    }

    void setName(string n) {
        if (n.length() > 0) name = n;
        else cout << "  [!] Name cannot be empty." << endl;
    }

    void setPhone(string p) {
        if (p.length() == 10) phone = p;
        else cout << "  [!] Phone must be exactly 10 digits." << endl;
    }

    void setPassportNo(string pp) {
        if (pp.length() >= 6 && pp.length() <= 12) passportNo = pp;
        else cout << "  [!] Passport number must be 6-12 characters." << endl;
    }

    // --- Input ---
    void input() {
        int id;
        string n, p, pp;

        cout << "  Enter Passenger ID: ";
        cin >> id;
        setPassengerId(id);

        cout << "  Enter Name: ";
        cin.ignore();
        getline(cin, n);
        setName(n);

        cout << "  Enter Phone (10 digits): ";
        cin >> p;
        setPhone(p);

        cout << "  Enter Passport No (6-12 chars): ";
        cin >> pp;
        setPassportNo(pp);
    }

    // --- Display ---
    void display() {
        cout << "  | " << left << setw(6) << passengerId
             << "| " << setw(20) << name
             << "| " << setw(12) << phone
             << "| " << setw(14) << passportNo << "|" << endl;
    }
};

// ============================================
// FLIGHT CLASS
// ============================================
class Flight {
private:
    int flightId;
    string airline;
    string origin;
    string destination;
    string departureTime;
    int availableSeats;

public:
    Flight() : flightId(0), airline(""), origin(""), destination(""), departureTime(""), availableSeats(0) {}

    // --- Getters ---
    int getFlightId() { return flightId; }
    string getAirline() { return airline; }
    string getOrigin() { return origin; }
    string getDestination() { return destination; }
    string getDepartureTime() { return departureTime; }
    int getAvailableSeats() { return availableSeats; }

    // --- Setters with Validation ---
    void setFlightId(int id) {
        if (id > 0) flightId = id;
        else cout << "  [!] Flight ID must be positive." << endl;
    }

    void setAirline(string a) {
        if (a.length() > 0) airline = a;
        else cout << "  [!] Airline name cannot be empty." << endl;
    }

    void setOrigin(string o) {
        if (o.length() > 0) origin = o;
        else cout << "  [!] Origin cannot be empty." << endl;
    }

    void setDestination(string d) {
        if (d.length() > 0) destination = d;
        else cout << "  [!] Destination cannot be empty." << endl;
    }

    void setDepartureTime(string t) {
        if (t.length() > 0) departureTime = t;
        else cout << "  [!] Departure time cannot be empty." << endl;
    }

    void setAvailableSeats(int s) {
        if (s >= 0 && s <= 500) availableSeats = s;
        else cout << "  [!] Seats must be 0-500." << endl;
    }

    // --- Book / Cancel Seat ---
    bool bookSeat() {
        if (availableSeats > 0) {
            availableSeats--;
            return true;
        }
        cout << "  [!] No seats available on this flight." << endl;
        return false;
    }

    void cancelSeat() {
        if (availableSeats < 500) availableSeats++;
    }

    // --- Input ---
    void input() {
        int id, s;
        string a, o, d, t;

        cout << "  Enter Flight ID: ";
        cin >> id;
        setFlightId(id);

        cout << "  Enter Airline Name: ";
        cin.ignore();
        getline(cin, a);
        setAirline(a);

        cout << "  Enter Origin City: ";
        getline(cin, o);
        setOrigin(o);

        cout << "  Enter Destination City: ";
        getline(cin, d);
        setDestination(d);

        cout << "  Enter Departure Time (e.g. 6:30PM): ";
        cin >> t;
        setDepartureTime(t);

        cout << "  Enter Available Seats (0-500): ";
        cin >> s;
        setAvailableSeats(s);
    }

    // --- Display ---
    void display() {
        string route = origin + " -> " + destination;
        cout << "  | " << left << setw(6) << flightId
             << "| " << setw(14) << airline
             << "| " << setw(22) << route
             << "| " << setw(10) << departureTime
             << "| " << setw(6) << availableSeats << "|" << endl;
    }
};

// ============================================
// SEAT CLASS
// ============================================
class Seat {
private:
    int seatNo;
    string seatClass;
    float price;
    bool isAvailable;

public:
    Seat() : seatNo(0), seatClass(""), price(0), isAvailable(true) {}

    // --- Getters ---
    int getSeatNo() { return seatNo; }
    string getSeatClass() { return seatClass; }
    float getPrice() { return price; }
    bool getIsAvailable() { return isAvailable; }

    // --- Setters with Validation ---
    void setSeatNo(int s) {
        if (s > 0) seatNo = s;
        else cout << "  [!] Seat number must be positive." << endl;
    }

    void setSeatClass(string c) {
        if (c == "Economy" || c == "Business" || c == "First") seatClass = c;
        else cout << "  [!] Class must be Economy, Business, or First." << endl;
    }

    void setPrice(float p) {
        if (p > 0) price = p;
        else cout << "  [!] Price must be positive." << endl;
    }

    void setIsAvailable(bool a) { isAvailable = a; }

    // --- Mark Booked / Available ---
    void markBooked() {
        if (isAvailable) isAvailable = false;
        else cout << "  [!] Seat already booked." << endl;
    }

    void markAvailable() { isAvailable = true; }

    // --- Input ---
    void input() {
        int s;
        string c;
        float p;

        cout << "  Enter Seat No: ";
        cin >> s;
        setSeatNo(s);

        cout << "  Enter Seat Class (Economy/Business/First): ";
        cin >> c;
        setSeatClass(c);

        cout << "  Enter Seat Price (Rs.): ";
        cin >> p;
        setPrice(p);

        isAvailable = true;
    }

    // --- Display ---
    void display() {
        cout << "  | " << left << setw(6) << seatNo
             << "| " << setw(10) << seatClass
             << "| Rs." << setw(10) << fixed << setprecision(0) << price
             << "| " << setw(12) << (isAvailable ? "Available" : "Booked") << "|" << endl;
    }
};

// ============================================
// GLOBAL ARRAYS & COUNTERS
// ============================================
const int MAX_PASSENGERS = 50;
const int MAX_FLIGHTS = 20;
const int MAX_SEATS = 100;

Passenger passengers[MAX_PASSENGERS];
Flight flights[MAX_FLIGHTS];
Seat seats[MAX_SEATS];

int passengerCount = 0;
int flightCount = 0;
int seatCount = 0;

// ============================================
// UTILITY FUNCTIONS
// ============================================

void printLine() {
    cout << "  ";
    for (int i = 0; i < 66; i++) cout << "-";
    cout << endl;
}

void printDoubleLine() {
    cout << "  ";
    for (int i = 0; i < 66; i++) cout << "=";
    cout << endl;
}

// ============================================
// PASSENGER MANAGEMENT FUNCTIONS
// ============================================

void addPassenger() {
    if (passengerCount >= MAX_PASSENGERS) {
        cout << "  [!] Maximum passengers reached (" << MAX_PASSENGERS << ")." << endl;
        return;
    }

    cout << endl << "  --- Add New Passenger ---" << endl;
    passengers[passengerCount].input();

    // Check for duplicate ID
    int newId = passengers[passengerCount].getPassengerId();
    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].getPassengerId() == newId) {
            cout << "  [!] Passenger ID " << newId << " already exists. Cancelled." << endl;
            return;
        }
    }

    passengerCount++;
    cout << "  [+] Passenger added successfully! Total: " << passengerCount << endl;
}

void viewAllPassengers() {
    if (passengerCount == 0) {
        cout << "  [!] No passengers registered yet." << endl;
        return;
    }

    cout << endl << "  --- All Passengers (" << passengerCount << ") ---" << endl;
    printLine();
    cout << "  | " << left << setw(6) << "ID"
         << "| " << setw(20) << "Name"
         << "| " << setw(12) << "Phone"
         << "| " << setw(14) << "Passport" << "|" << endl;
    printLine();

    for (int i = 0; i < passengerCount; i++) {
        passengers[i].display();
    }
    printLine();
}

void searchPassenger() {
    if (passengerCount == 0) {
        cout << "  [!] No passengers to search." << endl;
        return;
    }

    int id;
    cout << "  Enter Passenger ID to search: ";
    cin >> id;

    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].getPassengerId() == id) {
            cout << "  [+] Passenger found:" << endl;
            printLine();
            cout << "  | " << left << setw(6) << "ID"
                 << "| " << setw(20) << "Name"
                 << "| " << setw(12) << "Phone"
                 << "| " << setw(14) << "Passport" << "|" << endl;
            printLine();
            passengers[i].display();
            printLine();
            return;
        }
    }
    cout << "  [!] Passenger ID " << id << " not found." << endl;
}

void deletePassenger() {
    if (passengerCount == 0) {
        cout << "  [!] No passengers to delete." << endl;
        return;
    }

    int id;
    cout << "  Enter Passenger ID to delete: ";
    cin >> id;

    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].getPassengerId() == id) {
            cout << "  Deleting: " << passengers[i].getName() << " (ID: " << id << ")" << endl;

            // Shift remaining passengers left
            for (int j = i; j < passengerCount - 1; j++) {
                passengers[j] = passengers[j + 1];
            }
            passengerCount--;
            cout << "  [+] Passenger deleted. Remaining: " << passengerCount << endl;
            return;
        }
    }
    cout << "  [!] Passenger ID " << id << " not found." << endl;
}

// ============================================
// FLIGHT MANAGEMENT FUNCTIONS
// ============================================

void addFlight() {
    if (flightCount >= MAX_FLIGHTS) {
        cout << "  [!] Maximum flights reached (" << MAX_FLIGHTS << ")." << endl;
        return;
    }

    cout << endl << "  --- Add New Flight ---" << endl;
    flights[flightCount].input();

    // Check for duplicate ID
    int newId = flights[flightCount].getFlightId();
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].getFlightId() == newId) {
            cout << "  [!] Flight ID " << newId << " already exists. Cancelled." << endl;
            return;
        }
    }

    flightCount++;
    cout << "  [+] Flight added successfully! Total: " << flightCount << endl;
}

void viewAllFlights() {
    if (flightCount == 0) {
        cout << "  [!] No flights available yet." << endl;
        return;
    }

    cout << endl << "  --- All Flights (" << flightCount << ") ---" << endl;
    printLine();
    cout << "  | " << left << setw(6) << "ID"
         << "| " << setw(14) << "Airline"
         << "| " << setw(22) << "Route"
         << "| " << setw(10) << "Departure"
         << "| " << setw(6) << "Seats" << "|" << endl;
    printLine();

    for (int i = 0; i < flightCount; i++) {
        flights[i].display();
    }
    printLine();
}

void searchFlight() {
    if (flightCount == 0) {
        cout << "  [!] No flights to search." << endl;
        return;
    }

    int id;
    cout << "  Enter Flight ID to search: ";
    cin >> id;

    for (int i = 0; i < flightCount; i++) {
        if (flights[i].getFlightId() == id) {
            cout << "  [+] Flight found:" << endl;
            printLine();
            cout << "  | " << left << setw(6) << "ID"
                 << "| " << setw(14) << "Airline"
                 << "| " << setw(22) << "Route"
                 << "| " << setw(10) << "Departure"
                 << "| " << setw(6) << "Seats" << "|" << endl;
            printLine();
            flights[i].display();
            printLine();
            return;
        }
    }
    cout << "  [!] Flight ID " << id << " not found." << endl;
}

// ============================================
// SEAT MANAGEMENT FUNCTIONS
// ============================================

void addSeat() {
    if (seatCount >= MAX_SEATS) {
        cout << "  [!] Maximum seats reached (" << MAX_SEATS << ")." << endl;
        return;
    }

    cout << endl << "  --- Add New Seat ---" << endl;
    seats[seatCount].input();

    // Check for duplicate seat number
    int newNo = seats[seatCount].getSeatNo();
    for (int i = 0; i < seatCount; i++) {
        if (seats[i].getSeatNo() == newNo) {
            cout << "  [!] Seat No " << newNo << " already exists. Cancelled." << endl;
            return;
        }
    }

    seatCount++;
    cout << "  [+] Seat added successfully! Total: " << seatCount << endl;
}

void viewAllSeats() {
    if (seatCount == 0) {
        cout << "  [!] No seats available yet." << endl;
        return;
    }

    cout << endl << "  --- All Seats (" << seatCount << ") ---" << endl;
    printLine();
    cout << "  | " << left << setw(6) << "Seat"
         << "| " << setw(10) << "Class"
         << "| " << setw(14) << "Price"
         << "| " << setw(12) << "Status" << "|" << endl;
    printLine();

    for (int i = 0; i < seatCount; i++) {
        seats[i].display();
    }
    printLine();
}

void viewAvailableSeats() {
    if (seatCount == 0) {
        cout << "  [!] No seats registered yet." << endl;
        return;
    }

    cout << endl << "  --- Available Seats ---" << endl;
    printLine();
    cout << "  | " << left << setw(6) << "Seat"
         << "| " << setw(10) << "Class"
         << "| " << setw(14) << "Price"
         << "| " << setw(12) << "Status" << "|" << endl;
    printLine();

    int found = 0;
    for (int i = 0; i < seatCount; i++) {
        if (seats[i].getIsAvailable()) {
            seats[i].display();
            found++;
        }
    }

    if (found == 0) {
        cout << "  | No available seats at the moment.                            |" << endl;
    }
    printLine();
    cout << "  Available: " << found << " / " << seatCount << " seats" << endl;
}

// ============================================
// MAIN MENU
// ============================================

void displayMenu() {
    cout << endl;
    printDoubleLine();
    cout << "        Flight Management System" << endl;
    cout << "        Phase 3 - Menu-Driven Interface" << endl;
    printDoubleLine();
    cout << endl;
    cout << "  PASSENGER MANAGEMENT" << endl;
    cout << "    1.  Add Passenger" << endl;
    cout << "    2.  View All Passengers" << endl;
    cout << "    3.  Search Passenger" << endl;
    cout << "    4.  Delete Passenger" << endl;
    cout << endl;
    cout << "  FLIGHT MANAGEMENT" << endl;
    cout << "    5.  Add Flight" << endl;
    cout << "    6.  View All Flights" << endl;
    cout << "    7.  Search Flight" << endl;
    cout << endl;
    cout << "  SEAT MANAGEMENT" << endl;
    cout << "    8.  Add Seat" << endl;
    cout << "    9.  View All Seats" << endl;
    cout << "    10. View Available Seats" << endl;
    cout << endl;
    cout << "    0.  Exit" << endl;
    printDoubleLine();
    cout << "  Enter your choice: ";
}

int main() {
    int choice;

    do {
        displayMenu();
        cin >> choice;

        // Handle invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "  [!] Invalid input. Please enter a number." << endl;
            continue;
        }

        cout << endl;

        switch (choice) {
            case 1:  addPassenger(); break;
            case 2:  viewAllPassengers(); break;
            case 3:  searchPassenger(); break;
            case 4:  deletePassenger(); break;
            case 5:  addFlight(); break;
            case 6:  viewAllFlights(); break;
            case 7:  searchFlight(); break;
            case 8:  addSeat(); break;
            case 9:  viewAllSeats(); break;
            case 10: viewAvailableSeats(); break;
            case 0:
                cout << "  Thank you for using Flight Management System!" << endl;
                cout << "  Phase 3 Complete!" << endl;
                printDoubleLine();
                break;
            default:
                cout << "  [!] Invalid choice. Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
