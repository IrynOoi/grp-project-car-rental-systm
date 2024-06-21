//car rental.cpp
#include "car_rental.h"
#include "Sentinel.h"
#include "InsertionSort.h"
#include <iostream>
#include <thread>
#include <iomanip> 
#include <fstream>
#include <conio.h>
#include <vector>
using namespace std;

string input2;
string cartype;
double rentalfee;
int day;
int hour;
int halfday;


// Welcome class implementation PRIYADASHWINI 
void Welcome::displayWelcomeMessage() 
{
    readFromFile("welcome.txt");
}
void Welcome::readFromFile(const std::string& filename) 
{
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

void login() //IRDINA SYAFIAH BINTI NORAZMAN
{
    string pass = "";
    char ch;
    cout << "\n\n\STELLAR CAR RENTAL \n\n";
    cout << "\t------------------------------";
    cout << "\n\tLOGIN \n";
    cout << "\t------------------------------\n\n";
    cout << "\tEnter Password: ";

    // Read characters until Enter (ASCII code 13) is pressed
    while (true) {
        ch = _getch();  // Read the next character of the password without echoing it

        if (ch == 13) {  // Check if Enter key is pressed
            break;  // Exit the loop if Enter is pressed
        }
        else if (ch == 8) {  // Check if Backspace key is pressed
            if (!pass.empty()) {  // Check if password string is not empty
                pass.pop_back();  // Remove the last character from password
                cout << "\b \b";  // Move cursor back, print space to erase, move cursor back again
            }
        }
        else {  // For regular characters
            pass.push_back(ch);  // Append the character to the password string
            cout << '*';  // Print an asterisk to mask the password character on the screen
        }
    }

    // Check if the entered password matches the expected password "admin"
    if (pass == "admin") {
        cout << "\n\n\n\tAccess Granted! \n";
        system("PAUSE");  // Pause the program to allow user to read the message
        system("CLS");  // Clear the screen for security after successful login
    }
    else {
        cout << "\n\n\tAccess Denied...\n\tPlease Try Again\n\n";
        system("PAUSE");  // Pause the program to allow user to read the message
        system("CLS");  // Clear the screen for security after failed login
        login();  // Recursively call login() function to allow user to retry login
    }
}


bool customer::isValidName(const string& name) //OOI XIEN XIEN
{
    for (char c : name) 
    {
        if (isdigit(c)) 
        {
            return false; // Invalid if any character is a digit
        }
    }
    return true; // Valid if no digits found
}
// Car class methods
// Constructor for initializing a Car object with parameters
Car::Car(Car* n, string c, string d, string p, bool a)//OOI XIEN XIEN
{
    code = c;           // Initialize car code
    description = d;    // Initialize description
    price = p;          // Initialize price
    available = a;      // Initialize availability
    next = nullptr;     // Initialize next pointer
}

// Default constructor for Car class
Car::Car()//OOI XIEN XIEN
{
    next = nullptr;     // Initialize next pointer to nullptr
}

// Getter for retrieving price of a car
string Car::getPrice()//OOI XIEN XIEN
{
    return price;       // Return price of the car
}

// Getter for retrieving code of a car
string Car::getCode()//OOI XIEN XIEN
{
    return code;        // Return code of the car
}

// Getter for retrieving description of a car
string Car::getDescription()//OOI XIEN XIEN
{
    return description; // Return description of the car
}

// Getter for checking availability of a car
bool Car::isAvailable()//OOI XIEN XIEN
{
    return available;   // Return availability status of the car
}

// Getter for retrieving the next car in the list
Car* Car::getNext()//OOI XIEN XIEN
{
    return next;        // Return pointer to the next car in the list
}

// Setter for setting the next car in the list
void Car::setNext(Car* n)//OOI XIEN XIEN
{
    next = n;           // Set next pointer to point to another car
}

// Method to add a new car to the end of the linked list
void Car::addCar(Car** headPtr, string c, string d, string p, bool a)//OOI XIEN XIEN
{
    Car* newCar = new Car(nullptr, c, d, p, a);  // Create a new car object

    if (*headPtr == nullptr)
    {
        *headPtr = newCar;  // If list is empty, make new car the head
    }
    else
    {
        Car* temp = *headPtr;
        while (temp->getNext() != nullptr)
        {
            temp = temp->getNext(); // Traverse to the end of the list
        }
        temp->setNext(newCar); // Append new car to the end of the list
    }
}

void Car::displayCars(Car* head)//OOI XIEN XIEN
{
    if (head == nullptr)
    {
        cout << "No cars available." << endl;
        return;
    }
}


// CManager class methods
CManager::CManager()//OOI XIEN XIEN
{
    headM = nullptr;  // Initialize head pointer for type "M" cars to null
    headE1 = nullptr;  // Initialize head pointer for type "E1" cars to null
    headE2 = nullptr;  // Initialize head pointer for type "E2" cars to null
}

Car*CManager::getHeadPtr(string type)//OOI XIEN XIEN
{
    if (type == "M") return headM;
    if (type == "E1") return headE1;
    if (type == "E2") return headE2;
    return nullptr;
}



Car** CManager::getHead(string type)//OOI XIEN XIEN
{
    CarSorting carSorting;  // Create an instance of CarSorting to sort the linked lists

    if (type == "M") {
        carSorting.insertionSort(&headM);  // Sort the linked list of motorcycles
        return &headM;  // Return a pointer to the head pointer of motorcycles
    }
    if (type == "E1") {
        carSorting.insertionSort(&headE1);  // Sort the linked list of economy cars (1 day)
        return &headE1;  // Return a pointer to the head pointer of economy cars (1 day)
    }
    if (type == "E2") {
        carSorting.insertionSort(&headE2);  // Sort the linked list of economy cars (half day)
        return &headE2;  // Return a pointer to the head pointer of economy cars (half day)
    }
    return nullptr;  // Return nullptr if the type is invalid
}



 

// Rent class methods

void Rent::data(CManager* cm, Car* head, const string& type)//OOI XIEN XIEN
{
    // Check if there are cars available for the specified type
    if (head == nullptr)
    {
        cout << "No cars available." << endl;  // Display message if no cars are found
        return;  // Exit the function early if no cars are available
    }

    menu<string> vehicleMenu;  // Create a menu object for displaying vehicle options

    cout << "\tPlease select a type of vehicle" << endl;  // Prompt user to select a vehicle type
    cout << "\tType of vehicles : " << endl;  // Display header for vehicle types

    // Display vehicle options based on the provided type
    if (type == "M") {
        vehicleMenu.displayVehicleOptions(cm, "M", "\t\033[4m1) Motorcycle Scooter (M)\033[0m");  // Display options for motorcycles
    }
    else if (type == "E1") {
        vehicleMenu.displayVehicleOptions(cm, "E1", "\t\033[4m2) Economy car (1 day) (E1) \033[0m");  // Display options for economy cars (1 day)
    }
    else if (type == "E2") {
        vehicleMenu.displayVehicleOptions(cm, "E2", "\t\033[4m3) Economy car (halfday) (E2) \033[0m");  // Display options for economy cars (half day)
    }
}





void Rent::calculate(string input2, double& total, int day, int hour, int halfday, double& rentalfee)//OOI XIEN XIEN
{
    this_thread::sleep_for(std::chrono::seconds(1));  // Pause execution for 1 second for simulation purposes
    cout << "Calculating rent. Please wait......" << endl;  // Inform the user about the ongoing calculation
    this_thread::sleep_for(std::chrono::seconds(2));  // Pause execution for 2 seconds for simulation purposes

    // DAY CALCULATION
    if (input2 == "MA")
        rentalfee = day * 65;  // Calculate rental fee for Motorcycle Scooter (M) for full day
    else if (input2 == "E1A")
        rentalfee = day * 130;  // Calculate rental fee for Economy car (1 day) type A (E1A)
    else if (input2 == "E1B")
        rentalfee = day * 250;  // Calculate rental fee for Economy car (1 day) type B (E1B)

    // HALF DAY CALCULATION
    else if (input2 == "MB")
        rentalfee = halfday * 35;  // Calculate rental fee for Motorcycle Scooter (M) for half day
    else if (input2 == "E2A")
        rentalfee = halfday * 90;  // Calculate rental fee for Economy car (half day) type A (E2A)
    else if (input2 == "E2B")
        rentalfee = halfday * 190;  // Calculate rental fee for Economy car (half day) type B (E2B)

    // HOUR CALCULATION
    else if (input2 == "MC")
        rentalfee = hour * 5;  // Calculate rental fee for Motorcycle Scooter (M) per hour

    total += rentalfee;  // Update total rental fee with the calculated rental fee
    cout << "Your rental fee is RM " << fixed << setprecision(2) << total << endl;  // Display the total rental fee to the user
}



//receipt copy function
void Rent::receiptcopy(vector<RentalInfo>& rentals, string& customername, CManager* cm, double total)
{
    // Open the output file in append mode
    ofstream outputfile("Invoice.txt", ios::out | ios::app);
    if (!outputfile.is_open()) {
        cerr << "Error: Unable to open file Invoice.txt for writing." << endl;
        return;
    }

    // Write header and customer information
    outputfile << "\n                       Car Rental - Customer Invoice                  " << endl;
    outputfile << "  ***********************************************************************" << endl;
    outputfile << "   Invoice No. :" << "------------------" << setw(10) << "#CNB12345" << endl;
    outputfile << "   Customer Name:" << "-----------------" << setw(10) << customername << endl;

    for (const auto& rental : rentals)
    {
        string cartypename;

        // Determine vehicle type name based on cartype
        if (rental.cartype == "M") {
            cartypename = "Motorcycle Scooter";
        }
        else if (rental.cartype == "E1" || rental.cartype == "E2") {
            cartypename = "Economy Car";
        }

        // Write vehicle type and model details
        outputfile << " Vehicle Type : " << "--------------------" << setw(10) << cartypename << endl;
        Car* car = cm->getHeadPtr(rental.cartype);
        if (car != nullptr) {
            outputfile << "   Car Model :" << "--------------------" << setw(10) << car->getCode() << endl;
            if (rental.cartype == "E1" || rental.cartype == "E2") {
                outputfile << "   Car Detail. :" << "----------------------" << setw(10) << car->getDescription()  << endl;
            }
        }
        else {
            cerr << "Error: No car found for cartype " << rental.cartype << endl;
        }

        // Write rental details based on input2 (type of rental)
        if (rental.input2 == "MA" || rental.input2 == "E1A" || rental.input2 == "E1B") {
            outputfile << "   Number of days :" << "---------------" << setw(10) << rental.day << endl;
        }
        else if (rental.input2 == "MB" || rental.input2 == "E2A" || rental.input2 == "E2B") {
            outputfile << "   Number of days :" << "---------------" << setw(10) << rental.halfday << endl;
        }
        else if (rental.input2 == "MC") {
            outputfile << "   Number of days :" << "---------------" << setw(10) << rental.hour << endl;
        }
        outputfile << "   Your Rental Amount is :" << "--------" << setw(10) << rental.rentalfee << " " << endl;
    }

    // Write footer and close the file
    outputfile << "   Caution Money :" << "----------------" << setw(10) << "0" << " " << endl;
    outputfile << "   Advanced :" << "---------------------" << setw(10) << "0" << " " << endl;
    outputfile << "   ________________________________________________________" << endl;
    outputfile << "\n";
    outputfile << "   Total Rental Amount is :" << "-------" << setw(10) << total << " " << endl;
    outputfile << "   ________________________________________________________" << endl;
    outputfile << "   # This is a computer generated invoice and it does not" << endl;
    outputfile << "   require an authorised signature #" << endl;
    outputfile << " " << endl;
    outputfile << " ***********************************************************************" << endl;
    outputfile << "  You are advised to pay up the amount before due date." << endl;
    outputfile << "  Otherwise penalty fee will be applied" << endl;
    outputfile << " ***********************************************************************" << endl;

    outputfile.close(); // Close the output file
    cout << "Invoice generated successfully." << endl;
}
