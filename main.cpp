#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include <stdbool.h>
#include <iomanip>
#include <fstream>
using namespace std;

// Forward declaration of classes
class Exception;
class Room;
class Customer;
class RoomCustomer;
class Employee;
class Hotel;
class RoomService;

void head()
{

	cout << "\n\n\t\t\t\t     XYZ Group of Hotels\n\n";
}

// exception for any inappropriate details
class Exception
{
public:
	int errNo;
	string msg;

public:
	Exception(int errNo, string msg)
	{
		// Use of this pointer
		this->errNo = errNo;
		this->msg = msg;
	}

	void what()
	{
		cout << "\t\t" << errNo << " :: " << msg << endl;
	}
};

// base class room : to add room information, see the room information & availability status
class Room
{
public:
	string roomType;
	int noOfBeds;
	double rent;
	int roomNo;
	int status;

public:
	Room(string roomType, int noOfBeds, double rent, int roomNo)
	{
		this->roomType = roomType;
		this->noOfBeds = noOfBeds;
		this->rent = rent;
		this->roomNo = roomNo;
		this->status = 0;
	}

	void setRoom()
	{
		cout << "Enter Room Type, No of beds, Rent, RoomNo\n";
		cin >> this->roomType;
		cin >> this->noOfBeds;
		cin >> this->rent;
		cin >> this->roomNo;
		status = 0;
	}

	Room() // Default Constructor
	{
	}

	bool isVacant(Room r)
	{
		if (r.status == 1)
			return false;
		else
			return true;
	}

	void displayDetail()
	{

		cout << "Room Type :: " << this->roomType << endl;
		cout << "Number of Beds :: " << this->noOfBeds << endl;
		cout << "Rent :: " << this->rent << endl;
		cout << "Room Number ::" << this->roomNo << endl;
		if (status == 1)
			cout << " Occupied \n";
		else
			cout << "Vacant \n";
	}

	void vacateRoom(int rno)
	{
		int i;
		for (i = 0; i < 6; i++)
		{
			if (this->roomNo == rno)
				this->status = 0;
		}
	}

	void displayAvailable(Room r[6])
	{
		int i;
		for (i = 0; i < 6; i++)
		{
			if (r[i].status == 0)
				r[i].displayDetail();
		}
	}
};

// base customer : to add customer details.
class Customer
{
public:
	string custName;
	string custAddress;
	string custID;
	long int custPhone;
	string custEmail;
	string checkInTime;
	int status;

public:
	// default constructor : to initialize the customer details.
	Customer()
	{
		time_t c = time(0);
		string dt = ctime(&c);
		this->custName = " ";
		this->custAddress = " ";
		this->custID = " ";
		this->custPhone = 0L;
		this->custEmail = " ";
		this->checkInTime = dt;
		status = 0;
	}

	// Member function of class Customer : to take customer details
	void setData()
	{
		time_t now = time(0);
		string dt = ctime(&now);
		this->checkInTime = dt;

		// To store customer details in a file using file handling concept
		ofstream customer;
		customer.open("Customer.txt", ios::ate);
		cout << "Enter your Name :\n";
		cin >> this->custName;
		customer << "Name ::" << this->custName << "\n";

		cout << "Enter your Address :\n";
		cin >> this->custAddress;
		customer << "Address ::" << this->custAddress << "\n";

		cout << "Enter your Phone number :\n";
		cin >> this->custPhone;
		customer << "Phone ::" << this->custPhone << "\n";

		cout << "Enter your Email :\n";
		cin >> this->custEmail;
		customer << "Email ::" << this->custEmail << "\n\n";
		customer.close();
	}

	// To display menu once entered the customer details
	int selectChoice()
	{
		int ch;
		cout << " Hello!\n";
		cout << "Enter \n1. Accomodation \n 2. Exit\n ";
		cin >> ch;
		return ch;
	}

	// Virtual Functions : 'printCustomer', 'viewTotalBill', 'allocateRoom', 'checkout' for implementing run time polymorphism
	virtual void printCustomer()
	{
		cout << "Name :: " << this->custName << endl;
		cout << "Address :: " << this->custAddress << endl;
		cout << "ID :: " << custID << endl;
		cout << "Phone Number :: " << custPhone << endl;
		cout << "Email :: " << custEmail << endl;
		cout << "Check-In Time ::" << this->checkInTime << endl;
	}
	virtual void viewTotalBill()
	{
	}
	virtual void allocateRoom(Room r1)
	{
	}
	virtual void checkout()
	{
	}
};

// derived class 'RoomCustomer' from base class 'Customer' for rooms realted activities
class RoomCustomer : public Customer
{
public:
	double rbill;
	Room r;
	int bookStatus;

public:
	void viewTotalbill()
	{
		cout << "Bill =" << rbill;
	}

	void allocateRoom(Room r1)
	{
		this->r = r1;
	}

	void printCustomer()
	{

		Customer ::printCustomer();
		if (r.status == 1 && bookStatus == 1)

		{
			cout << "Check-In Time :: " << checkInTime << endl;
			cout << "Room type :: " << r.roomType << endl;
			cout << "Room Number :: " << r.roomNo << endl;
		}
	}

	void viewTotalBill()
	{
		this->rbill = r.rent;
		cout << "Bill :: " << this->rbill << endl;
	}

	void checkOut()
	{
		cout << "Your bill is " << this->rbill << "/-" << endl;
		this->rbill = 0;
		this->r.status = 0;
		cout << "Thank You! Visit Again.\n"
			 << endl;
	}
};

// base employee
class Employee
{

public:
	// Virtual Functions :  for implementing run time polymorphism
	virtual void performDuty() = 0;
	virtual ~Employee() // destructor
	{
	}
};

// Hierarchical  Inheritance
// derived roomservice - base employee
class RoomService : public Employee
{
public:
	void performDuty()
	{
		cout << "Employee XYZ arriving at your doorstep...\n\n";
	}

	// virtual destructor
	virtual ~RoomService()
	{
	}
};

// derived waiter - base employee
class Waiter : public Employee
{
public:
	void performDuty()
	{

		cout << "\n\nEmployee ABC arriving at your table to take your Order\n\n";
	}

	// virtual destructor
	virtual ~Waiter()
	{
	}
};

// base SelectEmployee
class SelectEmployee
{
	Employee *e;

public:
	SelectEmployee(Employee *e1)
	{
		e = e1;
	}

	void performDuty()
	{
		e->performDuty();
	}
};

// base hotel
class Hotel
{
private:
	// static data member
	static Hotel *instanceHotel;
	string hotelName;
	string hotelAddress;

public:
	string roomType;
	int noOfBeds;
	double rent;
	int roomNo;
	int status;

	// Array of objects
	Employee *employee[5];
	Room room[6];
	Customer *customer[5];

private:
	Hotel(string hname, string add)
	{
		this->hotelName = hname;
		this->hotelAddress = add;
	}

public:
	// static member function
	static Hotel *getHotel()
	{
		if (!instanceHotel)
			instanceHotel = new Hotel("RENNAISSANCE", "HUBLI");
		return instanceHotel;
	}

	void setRoom()
	{
		cout << "Enter Room Type, No of beds, Rent, RoomNo\n";
		cin >> this->roomType;
		cin >> this->noOfBeds;
		cin >> this->rent;
		cin >> this->roomNo;
		status = 0;
	}
	
	void setHotel(Room rs[6])
	{
		int i;

		for (i = 0; i < 6; i++)
		{
			this->room[i] = rs[i];
		}
	}

	void generateID(Customer *c)
	{
		time_t t;
		static const char m[] = "abcdefghijklmnopqrstuvwxyz";
		int i;

		for (i = 0; i < 6; i++)
		{
			c->custID = c->custID + m[rand() % (sizeof(m) - 1)];
		}
	}

	Room getRoom(int rno)
	{
		int i;
		for (i = 0; i < 6; i++)
		{
			if (room[i].roomNo == rno)
				return room[i];
		}
	}

	void displayAvailble()
	{
		int i;
		cout << "\n\n--------------------------------------Room Details------------------------------------\n\n";

		// Use of manipulator
		cout << setw(25) << "Room Type" << setw(25) << "Number of Beds" << setw(25) << "Rent" << setw(25) << "Room Number\n";
		for (i = 0; i < 6; i++)
		{
			if (room[i].status == 0)
			{
				cout << setw(25) << room[i].roomType;
				cout << setw(25) << room[i].noOfBeds;
				cout << setw(25) << room[i].rent;
				cout << setw(25) << room[i].roomNo << "\n";
			}
		}
		cout << "\n\n";
	}

	void bookRoom(int r)
	{
		int i;
		for (i = 0; i < 6; i++)
		{
			if (room[i].roomNo == r)
				room[i].status = 1;
		}
	}

	void askFeedback()
	{
		int f;
		string cname;

		// To store feedback details in a file using file handling concept
		ofstream feedback;
		feedback.open("feedback.txt", ios::app);
		feedback << "Customer Name\t : ";
		cout << "Enter your Name\n";
		cin >> cname;
		feedback << cname << "\t\t\t";
		cout << " Thanks for your time! \n How likely are you to recommend Hotel Rennaisance to a Friend or Colleague? \n Rate on a scale of 1-10\n";
		cin >> f;
		feedback << "Feedback\t: ";
		feedback << f << "\n";
		feedback.close();
		cout << " Thanks for your valuable feedback!" << endl;
	}

	void getCustomerData(Customer *c)
	{
		cout << " Name :: " << c->custName << endl;
		cout << " Address :: " << c->custAddress << endl;
		cout << " Phone :: " << c->custPhone << endl;
		cout << " Email :: " << c->custEmail << endl;
		cout << " Check-In Time:: " << c->checkInTime << endl;
	}

	void vacateRoom(int rno)
	{
		int i, j = 0;
		for (i = 0; i < 6; i++)
		{

			if (room[i].roomNo == rno)
			{
				j = 1;
				room[i].status = 0;
				cout << "Thank You! Visit Again.\n"
					 << endl;
			}
		}
		if (j == 0)
			throw Exception(8, "Sorry! Room Not Found, or occupied at the moment\n");
	}
};

// Global declaration of static data member
Hotel *Hotel ::instanceHotel = 0;

// main function
int main()
{
	head();

	cout << "\n";
	int ch, i, o, ch1, ch2, r, rno, rcount = 0, dcount = 0;
	Room r2;
	Hotel *Rennaisance = Rennaisance->getHotel();

	Customer *c[5];

	Room rm[6] =
		{
			Room("Deluxe", 2, 3500, 1),
			Room("AC", 1, 5500, 2),
			Room("Non AC", 2, 2500, 3),
			Room("AC", 2, 3500, 4),
			Room("Deluxe", 2, 3500, 5),
			Room("Deluxe", 3, 4500, 6)};

	SelectEmployee *e;

	Rennaisance->setHotel(rm);
	while (1)
	{
		for (i = 0; i < 5; i++)
		{
			try
			{

			level2:
				cout << "Enter \n\t1. Accomadation\n\t2. Exit\n";
				cin >> ch;
				if (ch == 1)
				{
					Rennaisance->customer[i] = new RoomCustomer;
					Rennaisance->generateID(Rennaisance->customer[i]);
					cout << "Enter Your details\n";
					Rennaisance->customer[i]->setData();
				level1:
					cout << "Enter \n\t\t1. To Display Rooms \n\t\t2. To Book a Room \n\t\t3. To Vacate Room \n\t\t4. To Get Invoice  \n\t\t5. Not Satisfied? \n\t\t6. Cancel Booking \n\t\t7. Give Feedback \n\t\t8. Back\n\n";
					cin >> ch1;
					switch (ch1)
					{
					case 1:
						Rennaisance->displayAvailble();
						goto level1;

					case 2:
						if (Rennaisance->customer[i]->status)
						{
							cout << "\n\n-----------------------------------------------------------------------------------------\n\n";
							throw Exception(1, "Sorry! You Cannot Book more than one room!\n");
							cout << "\n\n-----------------------------------------------------------------\n\n";
						}
						else
						{
							Rennaisance->customer[i]->status = 1;
							Rennaisance->displayAvailble();
							cout << "Enter Room No\n";
							cin >> rno;
							Rennaisance->bookRoom(rno);
							r2 = Rennaisance->getRoom(rno);
							Rennaisance->customer[i]->allocateRoom(r2);
						}

						goto level1;

					case 3:
						if (!Rennaisance->customer[i]->status)
						{
							cout << "\n\n-----------------------------------------------------------------------------------------\n\n";
							throw Exception(3, "Cannot vacate a book unless booked\n");
							cout << "\n\n-----------------------------------------------------------------\n\n";
						}

						else
						{
							Rennaisance->customer[i]->status = 0;
							cout << "Enter Room No\n";
							cin >> rno;
							Rennaisance->vacateRoom(rno);
							cout << "Room vacated\n";
						}
						goto level1;

					case 4:
						if (!Rennaisance->customer[i]->status)
						{
							cout << "\n\n------------------------------------------------------------------------------------------\n\n";
							throw Exception(2, "Cannot get Invoice Details unless you book a Room\n");
							cout << "\n\n-----------------------------------------------------------------\n\n";
						}

						else
						{
							cout << "\n\n-----------------------------------------------------------------\n\n";
							Rennaisance->customer[i]->printCustomer();
							Rennaisance->customer[i]->viewTotalBill();
							cout << "\n\n-----------------------------------------------------------------\n\n";
							goto level1;
						}

					case 5:
						if (!Rennaisance->customer[i]->status)

						{
							cout << "\n\n--------------------------------------------------------------------------------------------\n\n";
							throw Exception(2, "Cannot call Room Service Unless you book a Room\n");
							cout << "\n\n-----------------------------------------------------------------\n\n";
						}

						else
						{
							e = new SelectEmployee(new RoomService);
							e->performDuty();
							// Rennaisance->employee->performDuty()
						}
						goto level1;
					case 6:
						if (!Rennaisance->customer[i]->status)
						{
							cout << "\n\n-----------------------------------------------------------------------------------\n\n";
							throw Exception(2, "No Room Booked\n");
						}

						else
						{
							Rennaisance->customer[i]->status = 0;
							cout << "Enter Room No\n";
							cin >> rno;
							Rennaisance->vacateRoom(rno);
							cout << "Cancellation Successful!\n";
						}
						goto level1;

					case 7:
						if (!Rennaisance->customer[i]->status)
						{
							cout << "\n\n-----------------------------------------------------------------------------------\n\n";
							throw Exception(2, "Cannot give feedback unless you order a Dish\n");
						}
						else

							Rennaisance->askFeedback();
						goto level1;
					case 8:
						goto level2;
					}
				}

				else if (ch == 2)
					exit(0);
				else
				{
					cout << "-----------------------------------------------------------------------------------\n\n";
					throw Exception(5, "INVALID INPUT\n");
				}
				goto level2;
			}

			catch (Exception eh)
			{
				eh.what();
				cout << "-----------------------------------------------------------------------------------\n\n";
			}
		}
	}
	return 0;
}

/*

Concept used:
- forward declaration of classes
- functions
- base class
- Inline functions and default argument functions
- derived class : inheritance - single and hierarchial
- default constructor
- virtual distructor
- array of objects
- static data member and member function
- Use of this pointer
- File handling
- Virtual functions : run time polymorphism
- Manipulators
- Exception Handling

*/