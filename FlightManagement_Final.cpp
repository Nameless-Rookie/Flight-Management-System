// ================================================================
// Flight Management System - Final Polished Version
// OOP Concepts: Classes, Encapsulation, Arrays, Inheritance
// ================================================================
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX = 50;

// ======================== PASSENGER ========================
class Passenger {
private:
    int id; string name, phone, passport;
public:
    Passenger():id(0){}
    int getId(){return id;} string getName(){return name;}
    string getPhone(){return phone;} string getPassport(){return passport;}
    bool setId(int i){if(i>0){id=i;return true;}cout<<"  [!] ID must be positive.\n";return false;}
    bool setName(string n){if(n.length()>0){name=n;return true;}cout<<"  [!] Name empty.\n";return false;}
    bool setPhone(string p){if(p.length()==10){for(int i=0;i<10;i++)if(p[i]<'0'||p[i]>'9'){cout<<"  [!] Digits only.\n";return false;}phone=p;return true;}cout<<"  [!] Must be 10 digits.\n";return false;}
    bool setPassport(string pp){if(pp.length()>=6&&pp.length()<=12){passport=pp;return true;}cout<<"  [!] 6-12 chars.\n";return false;}
    void input(){int i;string n,p,pp;cout<<"  Enter Passenger ID   : ";cin>>i;setId(i);cout<<"  Enter Name           : ";cin.ignore();getline(cin,n);setName(n);cout<<"  Enter Phone (10 dig) : ";cin>>p;setPhone(p);cout<<"  Enter Passport No    : ";cin>>pp;setPassport(pp);}
    void display(){cout<<"  | "<<left<<setw(6)<<id<<"| "<<setw(20)<<name<<"| "<<setw(12)<<phone<<"| "<<setw(14)<<passport<<"|"<<endl;}
    void displayCard(){cout<<"  +------------------------------------------+\n  | PASSENGER DETAILS                        |\n  +------------------------------------------+\n";cout<<"  | ID       : "<<left<<setw(30)<<id<<"|\n";cout<<"  | Name     : "<<left<<setw(30)<<name<<"|\n";cout<<"  | Phone    : "<<left<<setw(30)<<phone<<"|\n";cout<<"  | Passport : "<<left<<setw(30)<<passport<<"|\n";cout<<"  +------------------------------------------+\n";}
};

// ======================== FLIGHT ========================
class Flight {
private:
    int id,totalSeats,availSeats; string airline,origin,dest,depTime;
public:
    Flight():id(0),totalSeats(0),availSeats(0){}
    int getId(){return id;} string getAirline(){return airline;}
    string getOrigin(){return origin;} string getDest(){return dest;}
    string getDepTime(){return depTime;} int getAvailSeats(){return availSeats;}
    int getTotalSeats(){return totalSeats;}
    void setId(int i){if(i>0)id=i;else cout<<"  [!] ID must be positive.\n";}
    void setAirline(string a){if(a.length()>0)airline=a;}
    void setOrigin(string o){if(o.length()>0)origin=o;}
    void setDest(string d){if(d.length()>0)dest=d;}
    void setDepTime(string t){if(t.length()>0)depTime=t;}
    void setSeats(int s){if(s>=0&&s<=500){availSeats=s;totalSeats=s;}else cout<<"  [!] 0-500.\n";}
    bool bookSeat(){if(availSeats>0){availSeats--;return true;}cout<<"  [!] No seats.\n";return false;}
    void cancelSeat(){if(availSeats<totalSeats)availSeats++;}
    void input(){int i,s;string a,o,d,t;cout<<"  Enter Flight ID      : ";cin>>i;setId(i);cout<<"  Enter Airline        : ";cin.ignore();getline(cin,a);setAirline(a);cout<<"  Enter Origin         : ";getline(cin,o);setOrigin(o);cout<<"  Enter Destination    : ";getline(cin,d);setDest(d);cout<<"  Enter Departure Time : ";cin>>t;setDepTime(t);cout<<"  Enter Total Seats    : ";cin>>s;setSeats(s);}
    void display(){string r=origin+" -> "+dest;cout<<"  | "<<left<<setw(6)<<id<<"| "<<setw(14)<<airline<<"| "<<setw(22)<<r<<"| "<<setw(10)<<depTime<<"| "<<setw(5)<<availSeats<<"/"<<left<<setw(5)<<totalSeats<<"|"<<endl;}
};

// ======================== SEAT ========================
class Seat {
private:
    int no; string cls; float price; bool avail;
public:
    Seat():no(0),price(0),avail(true){}
    int getNo(){return no;} string getCls(){return cls;}
    float getPrice(){return price;} bool isAvail(){return avail;}
    void setNo(int n){if(n>0)no=n;} void setCls(string c){if(c=="Economy"||c=="Business"||c=="First")cls=c;else cout<<"  [!] Economy/Business/First.\n";}
    void setPrice(float p){if(p>0)price=p;} void setAvail(bool a){avail=a;}
    void markBooked(){if(avail)avail=false;else cout<<"  [!] Already booked.\n";}
    void markAvail(){avail=true;}
    void input(){int s;string c;float p;cout<<"  Enter Seat No  : ";cin>>s;setNo(s);cout<<"  Enter Class    : ";cin>>c;setCls(c);cout<<"  Enter Price Rs.: ";cin>>p;setPrice(p);avail=true;}
    void display(){cout<<"  | "<<left<<setw(6)<<no<<"| "<<setw(10)<<cls<<"| Rs."<<setw(10)<<fixed<<setprecision(0)<<price<<"| "<<setw(12)<<(avail?"Available":"Booked")<<"|"<<endl;}
};

// ======================== BOOKING BASE ========================
class Booking {
protected:
    int bId,pId; string pName,date,type; float amount;
public:
    Booking():bId(0),pId(0),amount(0){}
    int getBId(){return bId;} int getPId(){return pId;}
    string getPName(){return pName;} float getAmount(){return amount;}
    string getType(){return type;}
    void setBId(int i){if(i>0)bId=i;} void setPId(int i){if(i>0)pId=i;}
    void setPName(string n){pName=n;} void setDate(string d){if(d.length()>0)date=d;}
    void setAmount(float a){if(a>=0)amount=a;}
    void display(){cout<<"  Booking #"<<bId<<" | "<<type<<" | "<<pName<<" | Rs."<<fixed<<setprecision(0)<<amount<<endl;}
};

// ======================== FLIGHTBOOKING (Derived) ========================
class FlightBooking : public Booking {
private:
    string airline,origin,dest,depTime; int seatNum,flightId;
public:
    FlightBooking():seatNum(0),flightId(0){type="Flight";}
    int getSeatNum(){return seatNum;} int getFlightId(){return flightId;}
    void setAirline(string a){airline=a;} void setOrigin(string o){origin=o;}
    void setDest(string d){dest=d;} void setDepTime(string t){depTime=t;}
    void setSeatNum(int s){if(s>0)seatNum=s;} void setFlightId(int f){flightId=f;}
    void input(int b,int p,string nm){setBId(b);setPId(p);setPName(nm);string d;int s;float pr;cout<<"  Booking Date (DD/MM/YYYY): ";cin>>d;setDate(d);cout<<"  Seat Number              : ";cin>>s;setSeatNum(s);cout<<"  Ticket Price Rs.         : ";cin>>pr;setAmount(pr);}
    void display(){cout<<"  +--------------------------------------------+\n  |            ** FLIGHT TICKET **             |\n  +--------------------------------------------+\n";cout<<"  | Booking ID  : "<<left<<setw(29)<<bId<<"|\n";cout<<"  | Passenger   : "<<left<<setw(29)<<pName<<"|\n";cout<<"  | Date        : "<<left<<setw(29)<<date<<"|\n";cout<<"  +--------------------------------------------+\n";cout<<"  | Airline     : "<<left<<setw(29)<<airline<<"|\n";string r=origin+" -> "+dest;cout<<"  | Route       : "<<left<<setw(29)<<r<<"|\n";cout<<"  | Departure   : "<<left<<setw(29)<<depTime<<"|\n";cout<<"  | Seat No     : "<<left<<setw(29)<<seatNum<<"|\n";cout<<"  +--------------------------------------------+\n";cout<<"  | TOTAL       : Rs."<<left<<setw(25)<<fixed<<setprecision(0)<<amount<<"|\n";cout<<"  +--------------------------------------------+\n";}
    void displayRow(){cout<<"  | "<<left<<setw(6)<<bId<<"| "<<setw(8)<<pId<<"| "<<setw(12)<<pName<<"| "<<setw(14)<<airline<<"| "<<setw(10)<<depTime<<"| "<<setw(5)<<seatNum<<"| Rs."<<setw(8)<<fixed<<setprecision(0)<<amount<<"|"<<endl;}
};

// ======================== SEATUPGRADE (Derived) ========================
class SeatUpgrade : public Booking {
private:
    int seatNo,flightId; string fromCls,toCls;
public:
    SeatUpgrade():seatNo(0),flightId(0){type="Upgrade";}
    int getSeatNo(){return seatNo;} int getFlightId(){return flightId;}
    void setSeatNo(int s){if(s>0)seatNo=s;} void setFlightId(int f){flightId=f;}
    void setFromCls(string f){fromCls=f;} void setToCls(string t){toCls=t;}
    void input(int b,int p,string nm){setBId(b);setPId(p);setPName(nm);string d,fc,tc;int s,f;float pr;cout<<"  Booking Date : ";cin>>d;setDate(d);cout<<"  Flight ID    : ";cin>>f;setFlightId(f);cout<<"  Seat No      : ";cin>>s;setSeatNo(s);cout<<"  From Class   : ";cin>>fc;setFromCls(fc);cout<<"  To Class     : ";cin>>tc;setToCls(tc);cout<<"  Upgrade Fee  : ";cin>>pr;setAmount(pr);}
    void display(){cout<<"  +--------------------------------------------+\n  |         ** SEAT UPGRADE RECEIPT **         |\n  +--------------------------------------------+\n";cout<<"  | Booking ID  : "<<left<<setw(29)<<bId<<"|\n";cout<<"  | Passenger   : "<<left<<setw(29)<<pName<<"|\n";cout<<"  | Date        : "<<left<<setw(29)<<date<<"|\n";cout<<"  | Flight ID   : "<<left<<setw(29)<<flightId<<"|\n";cout<<"  | Seat No     : "<<left<<setw(29)<<seatNo<<"|\n";string u=fromCls+" -> "+toCls;cout<<"  | Upgrade     : "<<left<<setw(29)<<u<<"|\n";cout<<"  +--------------------------------------------+\n";cout<<"  | FEE         : Rs."<<left<<setw(25)<<fixed<<setprecision(0)<<amount<<"|\n";cout<<"  +--------------------------------------------+\n";}
    void displayRow(){string u=fromCls+"->"+toCls;cout<<"  | "<<left<<setw(6)<<bId<<"| "<<setw(8)<<pId<<"| "<<setw(12)<<pName<<"| F"<<setw(5)<<flightId<<"| S"<<setw(4)<<seatNo<<"| "<<setw(12)<<u<<"| Rs."<<setw(8)<<fixed<<setprecision(0)<<amount<<"|"<<endl;}
};

// ======================== GLOBALS ========================
Passenger passengers[MAX]; Flight flights[MAX]; Seat seats[MAX];
FlightBooking fBookings[MAX]; SeatUpgrade uBookings[MAX];
int pCnt=0,fCnt=0,sCnt=0,fbCnt=0,ubCnt=0,nextBId=1001;

void pLine(int n=70){cout<<"  ";for(int i=0;i<n;i++)cout<<"-";cout<<endl;}
void dLine(int n=70){cout<<"  ";for(int i=0;i<n;i++)cout<<"=";cout<<endl;}
int findP(int id){for(int i=0;i<pCnt;i++)if(passengers[i].getId()==id)return i;return-1;}
int findF(int id){for(int i=0;i<fCnt;i++)if(flights[i].getId()==id)return i;return-1;}
int findS(int no){for(int i=0;i<sCnt;i++)if(seats[i].getNo()==no)return i;return-1;}

// ======================== CRUD FUNCTIONS ========================
void addPassenger(){if(pCnt>=MAX){cout<<"  [!] Max reached.\n";return;}cout<<"\n  --- Add Passenger ---\n";passengers[pCnt].input();int nid=passengers[pCnt].getId();for(int i=0;i<pCnt;i++)if(passengers[i].getId()==nid){cout<<"  [!] ID exists.\n";return;}pCnt++;cout<<"  [+] Added! Total: "<<pCnt<<endl;}
void viewPassengers(){if(!pCnt){cout<<"  [!] None.\n";return;}cout<<"\n  --- Passengers ("<<pCnt<<") ---\n";pLine();cout<<"  | "<<left<<setw(6)<<"ID"<<"| "<<setw(20)<<"Name"<<"| "<<setw(12)<<"Phone"<<"| "<<setw(14)<<"Passport"<<"|"<<endl;pLine();for(int i=0;i<pCnt;i++)passengers[i].display();pLine();}
void searchPassenger(){int id;cout<<"  Enter ID: ";cin>>id;int i=findP(id);if(i!=-1){passengers[i].displayCard();int fb=0,ub=0;for(int j=0;j<fbCnt;j++)if(fBookings[j].getPId()==id)fb++;for(int j=0;j<ubCnt;j++)if(uBookings[j].getPId()==id)ub++;cout<<"  Bookings: "<<fb<<" flight, "<<ub<<" upgrade\n";}else cout<<"  [!] Not found.\n";}
void deletePassenger(){int id;cout<<"  Enter ID to delete: ";cin>>id;int i=findP(id);if(i!=-1){for(int j=0;j<fbCnt;j++)if(fBookings[j].getPId()==id){cout<<"  [!] Has active bookings.\n";return;}cout<<"  Deleting: "<<passengers[i].getName()<<endl;for(int j=i;j<pCnt-1;j++)passengers[j]=passengers[j+1];pCnt--;cout<<"  [+] Deleted.\n";}else cout<<"  [!] Not found.\n";}

void addFlight(){if(fCnt>=MAX)return;cout<<"\n  --- Add Flight ---\n";flights[fCnt].input();int nid=flights[fCnt].getId();for(int i=0;i<fCnt;i++)if(flights[i].getId()==nid){cout<<"  [!] ID exists.\n";return;}fCnt++;cout<<"  [+] Added! Total: "<<fCnt<<endl;}
void viewFlights(){if(!fCnt){cout<<"  [!] None.\n";return;}cout<<"\n  --- Flights ("<<fCnt<<") ---\n";pLine();cout<<"  | "<<left<<setw(6)<<"ID"<<"| "<<setw(14)<<"Airline"<<"| "<<setw(22)<<"Route"<<"| "<<setw(10)<<"Departure"<<"| "<<setw(11)<<"Seats"<<"|"<<endl;pLine();for(int i=0;i<fCnt;i++)flights[i].display();pLine();}

void addSeat(){if(sCnt>=MAX)return;cout<<"\n  --- Add Seat ---\n";seats[sCnt].input();int nn=seats[sCnt].getNo();for(int i=0;i<sCnt;i++)if(seats[i].getNo()==nn){cout<<"  [!] Exists.\n";return;}sCnt++;cout<<"  [+] Added! Total: "<<sCnt<<endl;}
void viewSeats(){if(!sCnt){cout<<"  [!] None.\n";return;}pLine();cout<<"  | "<<left<<setw(6)<<"Seat"<<"| "<<setw(10)<<"Class"<<"| "<<setw(14)<<"Price"<<"| "<<setw(12)<<"Status"<<"|"<<endl;pLine();for(int i=0;i<sCnt;i++)seats[i].display();pLine();}
void viewAvailSeats(){if(!sCnt){cout<<"  [!] None.\n";return;}pLine();int f=0;for(int i=0;i<sCnt;i++)if(seats[i].isAvail()){seats[i].display();f++;}pLine();cout<<"  Available: "<<f<<"/"<<sCnt<<endl;}

// ======================== BOOKING FUNCTIONS ========================
void bookFlight(){if(fbCnt>=MAX||!pCnt||!fCnt){cout<<"  [!] Need passengers & flights first.\n";return;}cout<<"\n  --- Book Flight ---\n";int pid;cout<<"  Passenger ID: ";cin>>pid;int pi=findP(pid);if(pi==-1){cout<<"  [!] Not found.\n";return;}cout<<"  Passenger: "<<passengers[pi].getName()<<endl;cout<<endl;viewFlights();int fid;cout<<"\n  Flight ID: ";cin>>fid;int fi=findF(fid);if(fi==-1){cout<<"  [!] Not found.\n";return;}if(flights[fi].getAvailSeats()<=0){cout<<"  [!] No seats.\n";return;}
cout<<"\n  Booking: "<<flights[fi].getAirline()<<" "<<flights[fi].getOrigin()<<"->"<<flights[fi].getDest()<<" at "<<flights[fi].getDepTime()<<endl<<endl;
fBookings[fbCnt].input(nextBId,pid,passengers[pi].getName());fBookings[fbCnt].setAirline(flights[fi].getAirline());fBookings[fbCnt].setOrigin(flights[fi].getOrigin());fBookings[fbCnt].setDest(flights[fi].getDest());fBookings[fbCnt].setDepTime(flights[fi].getDepTime());fBookings[fbCnt].setFlightId(fid);flights[fi].bookSeat();cout<<"\n  [+] Booked!\n\n";fBookings[fbCnt].display();fbCnt++;nextBId++;}

void cancelFlight(){if(!fbCnt){cout<<"  [!] None.\n";return;}int bid;cout<<"  Booking ID: ";cin>>bid;for(int i=0;i<fbCnt;i++)if(fBookings[i].getBId()==bid){fBookings[i].display();int fi=findF(fBookings[i].getFlightId());if(fi!=-1)flights[fi].cancelSeat();for(int j=i;j<fbCnt-1;j++)fBookings[j]=fBookings[j+1];fbCnt--;cout<<"  [+] Cancelled.\n";return;}cout<<"  [!] Not found.\n";}

void bookUpgrade(){if(ubCnt>=MAX||!pCnt){cout<<"  [!] Need passengers.\n";return;}cout<<"\n  --- Seat Upgrade ---\n";int pid;cout<<"  Passenger ID: ";cin>>pid;int pi=findP(pid);if(pi==-1){cout<<"  [!] Not found.\n";return;}cout<<"  Passenger: "<<passengers[pi].getName()<<endl;uBookings[ubCnt].input(nextBId,pid,passengers[pi].getName());cout<<"\n  [+] Upgrade booked!\n\n";uBookings[ubCnt].display();ubCnt++;nextBId++;}

void cancelUpgrade(){if(!ubCnt){cout<<"  [!] None.\n";return;}int bid;cout<<"  Booking ID: ";cin>>bid;for(int i=0;i<ubCnt;i++)if(uBookings[i].getBId()==bid){uBookings[i].display();for(int j=i;j<ubCnt-1;j++)uBookings[j]=uBookings[j+1];ubCnt--;cout<<"  [+] Cancelled.\n";return;}cout<<"  [!] Not found.\n";}

void viewAllBookings(){int t=fbCnt+ubCnt;if(!t){cout<<"  [!] No bookings.\n";return;}cout<<endl;dLine();cout<<"        All Bookings ("<<t<<" total)\n";dLine();
if(fbCnt){cout<<"\n  FLIGHT BOOKINGS ("<<fbCnt<<"):\n";pLine(75);cout<<"  | "<<left<<setw(6)<<"BkID"<<"| "<<setw(8)<<"PID"<<"| "<<setw(12)<<"Name"<<"| "<<setw(14)<<"Airline"<<"| "<<setw(10)<<"Departure"<<"| "<<setw(5)<<"Seat"<<"| "<<setw(12)<<"Amount"<<"|"<<endl;pLine(75);for(int i=0;i<fbCnt;i++)fBookings[i].displayRow();pLine(75);}
if(ubCnt){cout<<"\n  UPGRADE BOOKINGS ("<<ubCnt<<"):\n";pLine(70);cout<<"  | "<<left<<setw(6)<<"BkID"<<"| "<<setw(8)<<"PID"<<"| "<<setw(12)<<"Name"<<"| "<<setw(7)<<"Flight"<<"| "<<setw(6)<<"Seat"<<"| "<<setw(12)<<"Upgrade"<<"| "<<setw(12)<<"Amount"<<"|"<<endl;pLine(70);for(int i=0;i<ubCnt;i++)uBookings[i].displayRow();pLine(70);}
float fr=0,ur=0;for(int i=0;i<fbCnt;i++)fr+=fBookings[i].getAmount();for(int i=0;i<ubCnt;i++)ur+=uBookings[i].getAmount();
cout<<endl;dLine();cout<<"  Revenue: Flights Rs."<<fixed<<setprecision(0)<<fr<<" + Upgrades Rs."<<ur<<" = Rs."<<(fr+ur)<<endl;dLine();}

// ======================== MENU ========================
void menu(){cout<<endl;dLine();cout<<"      Flight Management System\n      Final Version | All OOP Concepts\n";dLine();cout<<"\n  PASSENGER\n    1. Add  2. View  3. Search  4. Delete\n\n  FLIGHT\n    5. Add Flight  6. View Flights\n    7. Add Seat  8. View Seats  9. Available Seats\n\n  BOOKINGS (Inheritance)\n    10. Book Flight  11. Cancel Flight Booking\n    12. Book Upgrade  13. Cancel Upgrade\n    14. View All Bookings\n\n    0. Exit\n";dLine();cout<<"  Choice: ";}

int main(){
    int c;cout<<endl;dLine();cout<<"  Welcome to Flight Management System!\n  OOP Concepts: Classes, Encapsulation, Arrays, Inheritance\n";dLine();
    do{menu();cin>>c;if(cin.fail()){cin.clear();cin.ignore(10000,'\n');cout<<"  [!] Invalid.\n";continue;}cout<<endl;
    switch(c){case 1:addPassenger();break;case 2:viewPassengers();break;case 3:searchPassenger();break;case 4:deletePassenger();break;case 5:addFlight();break;case 6:viewFlights();break;case 7:addSeat();break;case 8:viewSeats();break;case 9:viewAvailSeats();break;case 10:bookFlight();break;case 11:cancelFlight();break;case 12:bookUpgrade();break;case 13:cancelUpgrade();break;case 14:viewAllBookings();break;
    case 0:cout<<endl;dLine();cout<<"  OOP Concepts Demonstrated:\n    [CO1] Classes & Objects\n    [CO2] Encapsulation\n    [CO3] Arrays of Objects\n    [CO4] Inheritance (Booking->FlightBooking,SeatUpgrade)\n    [CO5] UML Diagrams (documented separately)\n";dLine();break;default:cout<<"  [!] Invalid.\n";}
    }while(c!=0);return 0;}
