// ============================================
// Flight Management System
// Phase 2: Encapsulation
// OOP Concepts: Private Members, Getters/Setters,
//               Data Hiding, Input Validation
// ============================================

#include <iostream>
#include <string>
using namespace std;

// ============================================
// PASSENGER CLASS (Encapsulated)
// ============================================
class Passenger {
private:
    int passengerId;
    string name;
    string phone;
    string passportNo;

public:
    // --- Getters ---
    int getPassengerId() { return passengerId; }
    string getName() { return name; }
    string getPhone() { return phone; }
    string getPassportNo() { return passportNo; }

    // --- Setters with Validation ---
    void setPassengerId(int id) {
        if (id > 0) {
            passengerId = id;
        } else {
            cout << "Error: Passenger ID must be positive." << endl;
        }
    }

    void setName(string n) {
        if (n.length() > 0) {
            name = n;
        } else {
            cout << "Error: Name cannot be empty." << endl;
        }
    }

    void setPhone(string p) {
        if (p.length() == 10) {
            phone = p;
        } else {
            cout << "Error: Phone number must be exactly 10 digits." << endl;
        }
    }

    void setPassportNo(string pp) {
        if (pp.length() >= 6 && pp.length() <= 12) {
            passportNo = pp;
        } else {
            cout << "Error: Passport number must be 6-12 characters." << endl;
        }
    }

    // --- Input Method (uses setters for validation) ---
    void input() {
        int id;
        string n, p, pp;

        cout << "Enter Passenger ID: ";
        cin >> id;
        setPassengerId(id);

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, n);
        setName(n);

        cout << "Enter Phone (10 digits): ";
        cin >> p;
        setPhone(p);

        cout << "Enter Passport No (6-12 chars): ";
        cin >> pp;
        setPassportNo(pp);
    }

    // --- Display Method ---
    void display() {
        cout << "  Passenger ID : " << passengerId << endl;
        cout << "  Name         : " << name << endl;
        cout << "  Phone        : " << phone << endl;
        cout << "  Passport No  : " << passportNo << endl;
    }
};

// ============================================
// FLIGHT CLASS (Encapsulated)
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
    // --- Getters ---
    int getFlightId() { return flightId; }
    string getAirline() { return airline; }
    string getOrigin() { return origin; }
    string getDestination() { return destination; }
    string getDepartureTime() { return departureTime; }
    int getAvailableSeats() { return availableSeats; }

    // --- Setters with Validation ---
    void setFlightId(int id) {
        if (id > 0) {
            flightId = id;
        } else {
            cout << "Error: Flight ID must be positive." << endl;
        }
    }

    void setAirline(string a) {
        if (a.length() > 0) {
            airline = a;
        } else {
            cout << "Error: Airline name cannot be empty." << endl;
        }
    }

    void setOrigin(string o) {
        if (o.length() > 0) {
            origin = o;
        } else {
            cout << "Error: Origin cannot be empty." << endl;
        }
    }

    void setDestination(string d) {
        if (d.length() > 0) {
            destination = d;
        } else {
            cout << "Error: Destination cannot be empty." << endl;
        }
    }

    void setDepartureTime(string t) {
        if (t.length() > 0) {
            departureTime = t;
        } else {
            cout << "Error: Departure time cannot be empty." << endl;
        }
    }

    void setAvailableSeats(int s) {
        if (s >= 0 && s <= 500) {
            availableSeats = s;
        } else {
            cout << "Error: Seats must be between 0 and 500." << endl;
        }
    }

    // --- Book a Seat ---
    bool bookSeat() {
        if (availableSeats > 0) {
            availableSeats--;
            return true;
        } else {
            cout << "Error: No seats available on this flight." << endl;
            return false;
        }
    }

    // --- Cancel a Seat ---
    void cancelSeat() {
        if (availableSeats < 500) {
            availableSeats++;
        }
    }

    // --- Input Method ---
    void input() {
        int id, s;
        string a, o, d, t;

        cout << "Enter Flight ID: ";
        cin >> id;
        setFlightId(id);

        cout << "Enter Airline Name: ";
        cin.ignore();
        getline(cin, a);
        setAirline(a);

        cout << "Enter Origin City: ";
        getline(cin, o);
        setOrigin(o);

        cout << "Enter Destination City: ";
        getline(cin, d);
        setDestination(d);

        cout << "Enter Departure Time (e.g. 6:30PM): ";
        cin >> t;
        setDepartureTime(t);

        cout << "Enter Available Seats (0-500): ";
        cin >> s;
        setAvailableSeats(s);
    }

    // --- Display Method ---
    void display() {
        cout << "  Flight ID   : " << flightId << endl;
        cout << "  Airline     : " << airline << endl;
        cout << "  Origin      : " << origin << endl;
        cout << "  Destination : " << destination << endl;
        cout << "  Departure   : " << departureTime << endl;
        cout << "  Seats Left  : " << availableSeats << endl;
    }
};

// ============================================
// SEAT CLASS (Encapsulated)
// ============================================
class Seat {
private:
    int seatNo;
    string seatClass;    // Economy, Business, First
    float price;
    bool isAvailable;

public:
    // --- Getters ---
    int getSeatNo() { return seatNo; }
    string getSeatClass() { return seatClass; }
    float getPrice() { return price; }
    bool getIsAvailable() { return isAvailable; }

    // --- Setters with Validation ---
    void setSeatNo(int s) {
        if (s > 0) {
            seatNo = s;
        } else {
            cout << "Error: Seat number must be positive." << endl;
        }
    }

    void setSeatClass(string c) {
        if (c == "Economy" || c == "Business" || c == "First") {
            seatClass = c;
        } else {
            cout << "Error: Seat class must be Economy, Business, or First." << endl;
        }
    }

    void setPrice(float p) {
        if (p > 0) {
            price = p;
        } else {
            cout << "Error: Price must be positive." << endl;
        }
    }

    void setIsAvailable(bool a) {
        isAvailable = a;
    }

    // --- Mark Seat as Booked ---
    void markBooked() {
        if (isAvailable) {
            isAvailable = false;
        } else {
            cout << "Error: Seat is already booked." << endl;
        }
    }

    // --- Mark Seat as Available ---
    void markAvailable() {
        isAvailable = true;
    }

    // --- Input Method ---
    void input() {
        int s;
        string c;
        float p;

        cout << "Enter Seat No: ";
        cin >> s;
        setSeatNo(s);

        cout << "Enter Seat Class (Economy/Business/First): ";
        cin >> c;
        setSeatClass(c);

        cout << "Enter Seat Price (Rs.): ";
        cin >> p;
        setPrice(p);

        isAvailable = true; // New seats are available by default
    }

    // --- Display Method ---
    void display() {
        cout << "  Seat No     : " << seatNo << endl;
        cout << "  Class       : " << seatClass << endl;
        cout << "  Price       : Rs." << price << endl;
        cout << "  Status      : " << (isAvailable ? "Available" : "Booked") << endl;
    }
};

// ============================================
// MAIN - Demonstrating Encapsulation
// ============================================
int main() {
    cout << "========================================" << endl;
    cout << "      Flight Management System" << endl;
    cout << "  Phase 2 - Encapsulation" << endl;
    cout << "========================================" << endl << endl;

    // --- Passenger Demo ---
    Passenger p;
    cout << "--- Enter Passenger Details ---" << endl;
    p.input();
    cout << endl;

    // Demonstrate that validation works
    cout << "--- Testing Validation ---" << endl;
    cout << "Setting phone to '123' (should fail):" << endl;
    p.setPhone("123");  // Will print error

    cout << "Setting phone to '9876543210' (should pass):" << endl;
    p.setPhone("9876543210");  // Will succeed
    cout << "Phone is now: " << p.getPhone() << endl;
    cout << endl;

    // --- Flight Demo ---
    Flight f;
    cout << "--- Enter Flight Details ---" << endl;
    f.input();
    cout << endl;

    // Demonstrate seat booking
    cout << "--- Testing Seat Booking ---" << endl;
    cout << "Seats before booking: " << f.getAvailableSeats() << endl;
    f.bookSeat();
    cout << "Seats after booking 1: " << f.getAvailableSeats() << endl;
    f.cancelSeat();
    cout << "Seats after cancelling: " << f.getAvailableSeats() << endl;
    cout << endl;

    // --- Seat Demo ---
    Seat s;
    cout << "--- Enter Seat Details ---" << endl;
    s.input();
    cout << endl;

    // Demonstrate seat booking
    cout << "--- Testing Seat Booking ---" << endl;
    cout << "Seat status: " << (s.getIsAvailable() ? "Available" : "Booked") << endl;
    s.markBooked();
    cout << "After booking: " << (s.getIsAvailable() ? "Available" : "Booked") << endl;
    s.markAvailable();
    cout << "After freeing: " << (s.getIsAvailable() ? "Available" : "Booked") << endl;
    cout << endl;

    // Demonstrate invalid class
    cout << "--- Testing Invalid Seat Class ---" << endl;
    cout << "Setting class to 'Premium' (should fail):" << endl;
    s.setSeatClass("Premium");  // Will print error
    cout << endl;

    // --- Display All ---
    cout << "========================================" << endl;
    cout << "         Final Summary" << endl;
    cout << "========================================" << endl;

    cout << endl << "--- Passenger Info ---" << endl;
    p.display();

    cout << endl << "--- Flight Info ---" << endl;
    f.display();

    cout << endl << "--- Seat Info ---" << endl;
    s.display();

    cout << endl << "========================================" << endl;
    cout << "  Phase 2 Complete!" << endl;
    cout << "  Encapsulation Applied:" << endl;
    cout << "  - All attributes are now PRIVATE" << endl;
    cout << "  - Access only through getters/setters" << endl;
    cout << "  - Input validation in setters" << endl;
    cout << "========================================" << endl;

    return 0;
}
