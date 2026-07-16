// ============================================
// Flight Management System
// Phase 4: Inheritance
// OOP Concepts: Base & Derived Classes,
//               Code Reuse, Method Overriding
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
    int getPassengerId() { return passengerId; }
    string getName() { return name; }
    string getPhone() { return phone; }
    string getPassportNo() { return passportNo; }
    void setPassengerId(int id) { if (id > 0) passengerId = id; else cout << "  [!] ID must be positive." << endl; }
    void setName(string n) { if (n.length() > 0) name = n; else cout << "  [!] Name cannot be empty." << endl; }
    void setPhone(string p) { if (p.length() == 10) phone = p; else cout << "  [!] Phone must be 10 digits." << endl; }
    void setPassportNo(string pp) { if (pp.length() >= 6 && pp.length() <= 12) passportNo = pp; else cout << "  [!] Passport must be 6-12 chars." << endl; }
    void input() {
        int id; string n, p, pp;
        cout << "  Enter Passenger ID: "; cin >> id; setPassengerId(id);
        cout << "  Enter Name: "; cin.ignore(); getline(cin, n); setName(n);
        cout << "  Enter Phone (10 digits): "; cin >> p; setPhone(p);
        cout << "  Enter Passport No: "; cin >> pp; setPassportNo(pp);
    }
    void display() {
        cout << "  | " << left << setw(6) << passengerId << "| " << setw(20) << name
             << "| " << setw(12) << phone << "| " << setw(14) << passportNo << "|" << endl;
    }
};

// ============================================
// FLIGHT CLASS
// ============================================
class Flight {
private:
    int flightId; string airline, origin, destination, departureTime; int availableSeats;
public:
    Flight() : flightId(0), airline(""), origin(""), destination(""), departureTime(""), availableSeats(0) {}
    int getFlightId() { return flightId; }
    string getAirline() { return airline; }
    string getOrigin() { return origin; }
    string getDestination() { return destination; }
    string getDepartureTime() { return departureTime; }
    int getAvailableSeats() { return availableSeats; }
    void setFlightId(int id) { if (id > 0) flightId = id; else cout << "  [!] Flight ID must be positive." << endl; }
    void setAirline(string a) { if (a.length() > 0) airline = a; }
    void setOrigin(string o) { if (o.length() > 0) origin = o; }
    void setDestination(string d) { if (d.length() > 0) destination = d; }
    void setDepartureTime(string t) { if (t.length() > 0) departureTime = t; }
    void setAvailableSeats(int s) { if (s >= 0 && s <= 500) availableSeats = s; }
    bool bookSeat() { if (availableSeats > 0) { availableSeats--; return true; } cout << "  [!] No seats available." << endl; return false; }
    void cancelSeat() { if (availableSeats < 500) availableSeats++; }
    void input() {
        int id, s; string a, o, d, t;
        cout << "  Enter Flight ID: "; cin >> id; setFlightId(id);
        cout << "  Enter Airline: "; cin.ignore(); getline(cin, a); setAirline(a);
        cout << "  Enter Origin: "; getline(cin, o); setOrigin(o);
        cout << "  Enter Destination: "; getline(cin, d); setDestination(d);
        cout << "  Enter Departure Time: "; cin >> t; setDepartureTime(t);
        cout << "  Enter Available Seats: "; cin >> s; setAvailableSeats(s);
    }
    void display() {
        string route = origin + " -> " + destination;
        cout << "  | " << left << setw(6) << flightId << "| " << setw(14) << airline
             << "| " << setw(22) << route << "| " << setw(10) << departureTime
             << "| " << setw(6) << availableSeats << "|" << endl;
    }
};

// ============================================
// SEAT CLASS
// ============================================
class Seat {
private:
    int seatNo; string seatClass; float price; bool isAvailable;
public:
    Seat() : seatNo(0), seatClass(""), price(0), isAvailable(true) {}
    int getSeatNo() { return seatNo; }
    string getSeatClass() { return seatClass; }
    float getPrice() { return price; }
    bool getIsAvailable() { return isAvailable; }
    void setSeatNo(int s) { if (s > 0) seatNo = s; }
    void setSeatClass(string c) { if (c == "Economy" || c == "Business" || c == "First") seatClass = c; else cout << "  [!] Must be Economy/Business/First." << endl; }
    void setPrice(float p) { if (p > 0) price = p; }
    void setIsAvailable(bool a) { isAvailable = a; }
    void markBooked() { if (isAvailable) isAvailable = false; else cout << "  [!] Seat already booked." << endl; }
    void markAvailable() { isAvailable = true; }
    void input() {
        int s; string c; float p;
        cout << "  Enter Seat No: "; cin >> s; setSeatNo(s);
        cout << "  Enter Class (Economy/Business/First): "; cin >> c; setSeatClass(c);
        cout << "  Enter Price (Rs.): "; cin >> p; setPrice(p);
        isAvailable = true;
    }
    void display() {
        cout << "  | " << left << setw(6) << seatNo << "| " << setw(10) << seatClass
             << "| Rs." << setw(10) << fixed << setprecision(0) << price
             << "| " << setw(12) << (isAvailable ? "Available" : "Booked") << "|" << endl;
    }
};

// ============================================
// BOOKING BASE CLASS (Phase 4 - Inheritance)
// ============================================
class Booking {
protected:
    int bookingId;
    int passengerId;
    string date;
    float totalAmount;
    string bookingType;
public:
    Booking() : bookingId(0), passengerId(0), date(""), totalAmount(0), bookingType("") {}
    int getBookingId() { return bookingId; }
    int getPassengerId() { return passengerId; }
    string getDate() { return date; }
    float getTotalAmount() { return totalAmount; }
    string getBookingType() { return bookingType; }
    void setBookingId(int id) { if (id > 0) bookingId = id; }
    void setPassengerId(int id) { if (id > 0) passengerId = id; }
    void setDate(string d) { if (d.length() > 0) date = d; }
    void setTotalAmount(float a) { if (a >= 0) totalAmount = a; }
    void display() {
        cout << "  Booking ID   : " << bookingId << endl;
        cout << "  Passenger ID : " << passengerId << endl;
        cout << "  Date         : " << date << endl;
        cout << "  Type         : " << bookingType << endl;
        cout << "  Amount       : Rs." << fixed << setprecision(0) << totalAmount << endl;
    }
};

// ============================================
// FLIGHTBOOKING - DERIVED FROM BOOKING
// Demonstrates: Inheritance, Code Reuse
// ============================================
class FlightBooking : public Booking {
private:
    string airline;
    string origin;
    string destination;
    string departureTime;
    int seatNumber;
public:
    FlightBooking() : airline(""), origin(""), destination(""), departureTime(""), seatNumber(0) {
        bookingType = "Flight";
    }
    string getAirline() { return airline; }
    int getSeatNumber() { return seatNumber; }
    void setAirline(string a) { airline = a; }
    void setOrigin(string o) { origin = o; }
    void setDestination(string d) { destination = d; }
    void setDepartureTime(string t) { departureTime = t; }
    void setSeatNumber(int s) { if (s > 0) seatNumber = s; }

    void input(int bId, int pId) {
        string d; int seat; float price;
        setBookingId(bId);
        setPassengerId(pId);
        cout << "  Enter Booking Date (DD/MM/YYYY): "; cin >> d; setDate(d);
        cout << "  Enter Seat Number: "; cin >> seat; setSeatNumber(seat);
        cout << "  Enter Ticket Price (Rs.): "; cin >> price; setTotalAmount(price);
    }

    // Method Overriding - flight-specific display
    void display() {
        cout << "  +-----------------------------------------+" << endl;
        cout << "  |        FLIGHT TICKET                    |" << endl;
        cout << "  +-----------------------------------------+" << endl;
        cout << "  | Booking ID  : " << left << setw(26) << bookingId << "|" << endl;
        cout << "  | Passenger   : " << left << setw(26) << passengerId << "|" << endl;
        cout << "  | Date        : " << left << setw(26) << date << "|" << endl;
        cout << "  | Airline     : " << left << setw(26) << airline << "|" << endl;
        string route = origin + " -> " + destination;
        cout << "  | Route       : " << left << setw(26) << route << "|" << endl;
        cout << "  | Departure   : " << left << setw(26) << departureTime << "|" << endl;
        cout << "  | Seat No     : " << left << setw(26) << seatNumber << "|" << endl;
        cout << "  | Amount      : Rs." << left << setw(22) << fixed << setprecision(0) << totalAmount << "|" << endl;
        cout << "  +-----------------------------------------+" << endl;
    }
};

// ============================================
// SEATUPGRADEBOOKING - DERIVED FROM BOOKING
// Demonstrates: Inheritance, Code Reuse
// ============================================
class SeatUpgradeBooking : public Booking {
private:
    int seatNo;
    string fromClass;
    string toClass;
    int flightId;
public:
    SeatUpgradeBooking() : seatNo(0), fromClass(""), toClass(""), flightId(0) {
        bookingType = "Seat Upgrade";
    }
    int getSeatNo() { return seatNo; }
    int getFlightId() { return flightId; }
    void setSeatNo(int s) { if (s > 0) seatNo = s; }
    void setFromClass(string f) { fromClass = f; }
    void setToClass(string t) { toClass = t; }
    void setFlightId(int f) { if (f > 0) flightId = f; }

    void input(int bId, int pId) {
        string d, fc, tc; int seat, fid; float price;
        setBookingId(bId);
        setPassengerId(pId);
        cout << "  Enter Booking Date (DD/MM/YYYY): "; cin >> d; setDate(d);
        cout << "  Enter Flight ID: "; cin >> fid; setFlightId(fid);
        cout << "  Enter Seat No: "; cin >> seat; setSeatNo(seat);
        cout << "  Enter Current Class (Economy/Business/First): "; cin >> fc; setFromClass(fc);
        cout << "  Enter Upgrade To (Business/First): "; cin >> tc; setToClass(tc);
        cout << "  Enter Upgrade Fee (Rs.): "; cin >> price; setTotalAmount(price);
    }

    // Method Overriding - upgrade-specific display
    void display() {
        cout << "  +-----------------------------------------+" << endl;
        cout << "  |        SEAT UPGRADE RECEIPT             |" << endl;
        cout << "  +-----------------------------------------+" << endl;
        cout << "  | Booking ID  : " << left << setw(26) << bookingId << "|" << endl;
        cout << "  | Passenger   : " << left << setw(26) << passengerId << "|" << endl;
        cout << "  | Date        : " << left << setw(26) << date << "|" << endl;
        cout << "  | Flight ID   : " << left << setw(26) << flightId << "|" << endl;
        cout << "  | Seat No     : " << left << setw(26) << seatNo << "|" << endl;
        string upgrade = fromClass + " -> " + toClass;
        cout << "  | Upgrade     : " << left << setw(26) << upgrade << "|" << endl;
        cout << "  | Fee         : Rs." << left << setw(22) << fixed << setprecision(0) << totalAmount << "|" << endl;
        cout << "  +-----------------------------------------+" << endl;
    }
};

// ============================================
// GLOBAL ARRAYS & COUNTERS
// ============================================
const int MAX = 50;
Passenger passengers[MAX];
Flight flights[MAX];
Seat seats[MAX];
FlightBooking flightBookings[MAX];
SeatUpgradeBooking upgradeBookings[MAX];

int passengerCount = 0, flightCount = 0, seatCount = 0;
int flightBookingCount = 0, upgradeBookingCount = 0;
int nextBookingId = 1001;

// ============================================
// UTILITY
// ============================================
void printLine() { cout << "  "; for (int i = 0; i < 66; i++) cout << "-"; cout << endl; }
void printDoubleLine() { cout << "  "; for (int i = 0; i < 66; i++) cout << "="; cout << endl; }

int findPassenger(int id) { for (int i = 0; i < passengerCount; i++) if (passengers[i].getPassengerId() == id) return i; return -1; }
int findFlight(int id) { for (int i = 0; i < flightCount; i++) if (flights[i].getFlightId() == id) return i; return -1; }
int findSeat(int no) { for (int i = 0; i < seatCount; i++) if (seats[i].getSeatNo() == no) return i; return -1; }

// ============================================
// PASSENGER MANAGEMENT
// ============================================
void addPassenger() {
    if (passengerCount >= MAX) { cout << "  [!] Max passengers reached." << endl; return; }
    cout << endl << "  --- Add New Passenger ---" << endl;
    passengers[passengerCount].input();
    int newId = passengers[passengerCount].getPassengerId();
    for (int i = 0; i < passengerCount; i++) if (passengers[i].getPassengerId() == newId) { cout << "  [!] ID exists." << endl; return; }
    passengerCount++;
    cout << "  [+] Passenger added! Total: " << passengerCount << endl;
}
void viewAllPassengers() {
    if (passengerCount == 0) { cout << "  [!] No passengers." << endl; return; }
    cout << endl << "  --- All Passengers (" << passengerCount << ") ---" << endl;
    printLine();
    cout << "  | " << left << setw(6) << "ID" << "| " << setw(20) << "Name" << "| " << setw(12) << "Phone" << "| " << setw(14) << "Passport" << "|" << endl;
    printLine();
    for (int i = 0; i < passengerCount; i++) passengers[i].display();
    printLine();
}
void searchPassenger() {
    int id; cout << "  Enter Passenger ID: "; cin >> id;
    int idx = findPassenger(id);
    if (idx != -1) { cout << "  [+] Found:" << endl; printLine(); passengers[idx].display(); printLine(); }
    else cout << "  [!] Not found." << endl;
}
void deletePassenger() {
    int id; cout << "  Enter Passenger ID to delete: "; cin >> id;
    int idx = findPassenger(id);
    if (idx != -1) {
        cout << "  Deleting: " << passengers[idx].getName() << endl;
        for (int j = idx; j < passengerCount - 1; j++) passengers[j] = passengers[j + 1];
        passengerCount--; cout << "  [+] Deleted." << endl;
    } else cout << "  [!] Not found." << endl;
}

// ============================================
// FLIGHT & SEAT MANAGEMENT
// ============================================
void addFlight() {
    if (flightCount >= MAX) { cout << "  [!] Max flights reached." << endl; return; }
    cout << endl << "  --- Add New Flight ---" << endl;
    flights[flightCount].input();
    int newId = flights[flightCount].getFlightId();
    for (int i = 0; i < flightCount; i++) if (flights[i].getFlightId() == newId) { cout << "  [!] ID exists." << endl; return; }
    flightCount++; cout << "  [+] Flight added! Total: " << flightCount << endl;
}
void viewAllFlights() {
    if (flightCount == 0) { cout << "  [!] No flights." << endl; return; }
    cout << endl << "  --- All Flights (" << flightCount << ") ---" << endl;
    printLine();
    cout << "  | " << left << setw(6) << "ID" << "| " << setw(14) << "Airline" << "| " << setw(22) << "Route" << "| " << setw(10) << "Departure" << "| " << setw(6) << "Seats" << "|" << endl;
    printLine();
    for (int i = 0; i < flightCount; i++) flights[i].display();
    printLine();
}
void addSeat() {
    if (seatCount >= MAX) { cout << "  [!] Max seats reached." << endl; return; }
    cout << endl << "  --- Add New Seat ---" << endl;
    seats[seatCount].input();
    int newNo = seats[seatCount].getSeatNo();
    for (int i = 0; i < seatCount; i++) if (seats[i].getSeatNo() == newNo) { cout << "  [!] Seat exists." << endl; return; }
    seatCount++; cout << "  [+] Seat added! Total: " << seatCount << endl;
}
void viewAllSeats() {
    if (seatCount == 0) { cout << "  [!] No seats." << endl; return; }
    printLine();
    cout << "  | " << left << setw(6) << "Seat" << "| " << setw(10) << "Class" << "| " << setw(14) << "Price" << "| " << setw(12) << "Status" << "|" << endl;
    printLine();
    for (int i = 0; i < seatCount; i++) seats[i].display();
    printLine();
}
void viewAvailableSeats() {
    if (seatCount == 0) { cout << "  [!] No seats." << endl; return; }
    printLine();
    int found = 0;
    for (int i = 0; i < seatCount; i++) if (seats[i].getIsAvailable()) { seats[i].display(); found++; }
    printLine();
    cout << "  Available: " << found << " / " << seatCount << endl;
}

// ============================================
// FLIGHT BOOKING (Phase 4 - Inheritance)
// ============================================
void bookFlightTicket() {
    if (flightBookingCount >= MAX) { cout << "  [!] Max bookings reached." << endl; return; }
    if (passengerCount == 0) { cout << "  [!] Add a passenger first." << endl; return; }
    if (flightCount == 0) { cout << "  [!] Add a flight first." << endl; return; }

    cout << endl << "  --- Book Flight Ticket ---" << endl;
    int pId; cout << "  Enter Passenger ID: "; cin >> pId;
    int pIdx = findPassenger(pId);
    if (pIdx == -1) { cout << "  [!] Passenger not found." << endl; return; }
    cout << "  Passenger: " << passengers[pIdx].getName() << endl;

    viewAllFlights();
    int fId; cout << "  Enter Flight ID to book: "; cin >> fId;
    int fIdx = findFlight(fId);
    if (fIdx == -1) { cout << "  [!] Flight not found." << endl; return; }
    if (flights[fIdx].getAvailableSeats() <= 0) { cout << "  [!] No seats on this flight." << endl; return; }

    flightBookings[flightBookingCount].input(nextBookingId, pId);
    flightBookings[flightBookingCount].setAirline(flights[fIdx].getAirline());
    flightBookings[flightBookingCount].setOrigin(flights[fIdx].getOrigin());
    flightBookings[flightBookingCount].setDestination(flights[fIdx].getDestination());
    flightBookings[flightBookingCount].setDepartureTime(flights[fIdx].getDepartureTime());
    flights[fIdx].bookSeat();

    cout << endl << "  [+] Flight booked successfully!" << endl << endl;
    flightBookings[flightBookingCount].display();
    flightBookingCount++; nextBookingId++;
}

void cancelFlightBooking() {
    if (flightBookingCount == 0) { cout << "  [!] No flight bookings." << endl; return; }
    int bId; cout << "  Enter Booking ID to cancel: "; cin >> bId;
    for (int i = 0; i < flightBookingCount; i++) {
        if (flightBookings[i].getBookingId() == bId) {
            cout << "  Cancelling:" << endl; flightBookings[i].display();
            for (int j = i; j < flightBookingCount - 1; j++) flightBookings[j] = flightBookings[j + 1];
            flightBookingCount--; cout << "  [+] Flight booking cancelled." << endl; return;
        }
    }
    cout << "  [!] Booking not found." << endl;
}

// ============================================
// SEAT UPGRADE BOOKING (Phase 4 - Inheritance)
// ============================================
void bookSeatUpgrade() {
    if (upgradeBookingCount >= MAX) { cout << "  [!] Max upgrades reached." << endl; return; }
    if (passengerCount == 0) { cout << "  [!] Add a passenger first." << endl; return; }

    cout << endl << "  --- Book Seat Upgrade ---" << endl;
    int pId; cout << "  Enter Passenger ID: "; cin >> pId;
    int pIdx = findPassenger(pId);
    if (pIdx == -1) { cout << "  [!] Passenger not found." << endl; return; }
    cout << "  Passenger: " << passengers[pIdx].getName() << endl;

    upgradeBookings[upgradeBookingCount].input(nextBookingId, pId);

    cout << endl << "  [+] Seat upgrade booked!" << endl << endl;
    upgradeBookings[upgradeBookingCount].display();
    upgradeBookingCount++; nextBookingId++;
}

void cancelUpgradeBooking() {
    if (upgradeBookingCount == 0) { cout << "  [!] No upgrade bookings." << endl; return; }
    int bId; cout << "  Enter Booking ID to cancel: "; cin >> bId;
    for (int i = 0; i < upgradeBookingCount; i++) {
        if (upgradeBookings[i].getBookingId() == bId) {
            cout << "  Cancelling:" << endl; upgradeBookings[i].display();
            for (int j = i; j < upgradeBookingCount - 1; j++) upgradeBookings[j] = upgradeBookings[j + 1];
            upgradeBookingCount--; cout << "  [+] Upgrade cancelled." << endl; return;
        }
    }
    cout << "  [!] Booking not found." << endl;
}

// ============================================
// VIEW ALL BOOKINGS
// ============================================
void viewAllBookings() {
    int total = flightBookingCount + upgradeBookingCount;
    if (total == 0) { cout << "  [!] No bookings yet." << endl; return; }
    cout << endl; printDoubleLine();
    cout << "        All Bookings (" << total << " total)" << endl; printDoubleLine();
    if (flightBookingCount > 0) {
        cout << endl << "  FLIGHT BOOKINGS (" << flightBookingCount << "):" << endl;
        for (int i = 0; i < flightBookingCount; i++) { cout << endl; flightBookings[i].display(); }
    }
    if (upgradeBookingCount > 0) {
        cout << endl << "  SEAT UPGRADE BOOKINGS (" << upgradeBookingCount << "):" << endl;
        for (int i = 0; i < upgradeBookingCount; i++) { cout << endl; upgradeBookings[i].display(); }
    }
    cout << endl; printDoubleLine();
    cout << "  Summary: " << flightBookingCount << " flight + " << upgradeBookingCount << " upgrade = " << total << " bookings" << endl;
    printDoubleLine();
}

// ============================================
// MAIN MENU
// ============================================
void displayMenu() {
    cout << endl; printDoubleLine();
    cout << "        Flight Management System" << endl;
    cout << "        Phase 4 - Inheritance" << endl;
    printDoubleLine(); cout << endl;
    cout << "  PASSENGER MANAGEMENT" << endl;
    cout << "    1.  Add Passenger" << endl;
    cout << "    2.  View All Passengers" << endl;
    cout << "    3.  Search Passenger" << endl;
    cout << "    4.  Delete Passenger" << endl;
    cout << endl;
    cout << "  FLIGHT MANAGEMENT" << endl;
    cout << "    5.  Add Flight" << endl;
    cout << "    6.  View All Flights" << endl;
    cout << "    7.  Add Seat" << endl;
    cout << "    8.  View All Seats" << endl;
    cout << "    9.  View Available Seats" << endl;
    cout << endl;
    cout << "  BOOKINGS (Inheritance)" << endl;
    cout << "    10. Book Flight Ticket" << endl;
    cout << "    11. Cancel Flight Booking" << endl;
    cout << "    12. Book Seat Upgrade" << endl;
    cout << "    13. Cancel Upgrade Booking" << endl;
    cout << "    14. View All Bookings" << endl;
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
        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "  [!] Invalid input." << endl; continue; }
        cout << endl;
        switch (choice) {
            case 1: addPassenger(); break;
            case 2: viewAllPassengers(); break;
            case 3: searchPassenger(); break;
            case 4: deletePassenger(); break;
            case 5: addFlight(); break;
            case 6: viewAllFlights(); break;
            case 7: addSeat(); break;
            case 8: viewAllSeats(); break;
            case 9: viewAvailableSeats(); break;
            case 10: bookFlightTicket(); break;
            case 11: cancelFlightBooking(); break;
            case 12: bookSeatUpgrade(); break;
            case 13: cancelUpgradeBooking(); break;
            case 14: viewAllBookings(); break;
            case 0:
                cout << endl; printDoubleLine();
                cout << "  Thank you for using Flight Management System!" << endl;
                cout << "  Phase 4 Complete - Inheritance Applied:" << endl;
                cout << "    - Booking (base class)" << endl;
                cout << "    - FlightBooking (derived, inherits Booking)" << endl;
                cout << "    - SeatUpgradeBooking (derived, inherits Booking)" << endl;
                printDoubleLine(); break;
            default: cout << "  [!] Invalid choice." << endl;
        }
    } while (choice != 0);
    return 0;
}
