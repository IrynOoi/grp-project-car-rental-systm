//car rental.cpp
#include "car_rental.h"
#include "Sentinel.h"
#include <iostream>
#include <thread>
#include <iomanip> 
#include <fstream>
#include <vector>
using namespace std;

string input2;
string cartype;
double rentalfee;
int day;
int hour;
int halfday;

// Welcome class implementation
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

bool customer::isValidName(const string& name) 
{
    for (char c : name) {
        if (isdigit(c)) {
            return false; // Invalid if any character is a digit
        }
    }
    return true; // Valid if no digits found
}
// Car class methods
// Constructor for initializing a Car object with parameters
Car::Car(Car* n, string c, string d, string p, bool a)
{
    code = c;           // Initialize car code
    description = d;    // Initialize description
    price = p;          // Initialize price
    available = a;      // Initialize availability
    next = nullptr;     // Initialize next pointer
}

// Default constructor for Car class
Car::Car()
{
    next = nullptr;     // Initialize next pointer to nullptr
}

// Getter for retrieving price of a car
string Car::getPrice()
{
    return price;       // Return price of the car
}

// Getter for retrieving code of a car
string Car::getCode()
{
    return code;        // Return code of the car
}

// Getter for retrieving description of a car
string Car::getDescription()
{
    return description; // Return description of the car
}

// Getter for checking availability of a car
bool Car::isAvailable()
{
    return available;   // Return availability status of the car
}

// Getter for retrieving the next car in the list
Car* Car::getNext()
{
    return next;        // Return pointer to the next car in the list
}

// Setter for setting the next car in the list
void Car::setNext(Car* n)
{
    next = n;           // Set next pointer to point to another car
}

// Method to add a new car to the end of the linked list
void Car::addCar(Car** headPtr, string c, string d, string p, bool a)
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

class Car;
Car* SentinelSearch::sentinelSearch(string targetCategory, CManager* cm)
{
    // Check if the target category is valid (must be "M", "E1", or "E2")
    if (targetCategory != "M" && targetCategory != "E1" && targetCategory != "E2")
    {
        cout << "Invalid input" << endl;
        return nullptr; // Return nullptr if category is invalid
    }

    // Create a sentinel with a category-specific code and default values
    Car* sentinel = new Car(nullptr, targetCategory + "X", "", "", false);

    // Retrieve the head pointer of the specified category from the Car Manager
    Car* temp = cm->getHeadPtr(targetCategory);

    // Check if the head pointer is nullptr (no cars of this category)
    if (temp == nullptr)
    {
        cout << "Car type " << targetCategory << " not found." << endl;
        delete sentinel; // Delete the sentinel node
        return nullptr;  // Return nullptr if no cars found
    }

    // Traverse the list until the end to find the last node
    while (temp->getNext() != nullptr)
    {
        temp = temp->getNext();
    }

    // Set the next of the last node to point to the sentinel node
    temp->setNext(sentinel);

    // Reset temp to the head of the list to start searching for the category
    temp = cm->getHeadPtr(targetCategory);

    // Traverse the list until finding a node with the target category code
    while (!(temp->getCode().substr(0, 1) == targetCategory || temp->getCode().substr(0, 2) == targetCategory))
    {
        temp = temp->getNext(); // Move to the next car node
    }

    Car* found = nullptr;
    // Check if the found node is not the sentinel (valid car found)
    if (temp != sentinel)
    {
        found = temp; // Assign found car node
        cout << "Category " << targetCategory << " found!" << endl;
    }
    else
    {
        cout << "Category " << targetCategory << " not found." << endl;
    }

    // Reset the next of the last node to nullptr to detach the sentinel
    Car* last = cm->getHeadPtr(targetCategory);
    while (last->getNext() != sentinel)
    {
        last = last->getNext();
    }
    last->setNext(nullptr);

    // Delete the sentinel node after searching is complete
    delete sentinel;

    return found; // Return the found car node or nullptr
}




void Car::displayCars(Car* head)
{
    if (head == nullptr)
    {
        cout << "No cars available." << endl;
        return;
    }
}


// CManager class methods
CManager::CManager()
{
    headM = nullptr;
    headE1 = nullptr;
    headE2 = nullptr;
}

Car** CManager::getHead(string type)
{
    CarSorting carSorting; // Create an instance of CarSorting

    if (type == "M") {
        // Sort the linked list of type "M" before returning the head pointer
        carSorting.insertionSort(&headM);
        return &headM;
    }
    if (type == "E1") {
        // Sort the linked list of type "E1" before returning the head pointer
        carSorting.insertionSort(&headE1);
        return &headE1;
    }
    if (type == "E2") {
        // Sort the linked list of type "E2" before returning the head pointer
        carSorting.insertionSort(&headE2);
        return &headE2;
    }
    return nullptr;
}



Car* CManager::getHeadPtr(string type)
{
    if (type == "M") return headM;
    if (type == "E1") return headE1;
    if (type == "E2") return headE2;
    return nullptr;
}

// CarSorting class methods
void CarSorting::insertionSort(Car** head)
{
    if (*head == nullptr) return;

    Car* sorted = nullptr;
    Car* current = *head;

    while (current != nullptr)
    {
        Car* next = current->getNext();
        if (sorted == nullptr || sorted->getCode() >= current->getCode())
        {
            current->setNext(sorted);
            sorted = current;
        }
        else
        {
            Car* temp = sorted;
            while (temp->getNext() != nullptr && temp->getNext()->getCode() < current->getCode())
            {
                temp = temp->getNext();
            }
            current->setNext(temp->getNext());
            temp->setNext(current);
        }
        current = next;
    }
    *head = sorted;
}

// Rent class methods

void Rent::data(CManager* cm, Car* head,const string& type)
{
    if (head == nullptr)
    {
        cout << "No cars available." << endl;
        return;
    }

    menu<string> vehicleMenu;
    cout << "\tPlease select a type of vehicle" << endl;
    cout << "\tType of vehicles : " << endl;

    if (type == "M") {
        vehicleMenu.displayVehicleOptions(cm, "M", "\t\033[4m1) Motorcycle Scooter (M)\033[0m");
    }
    else if (type == "E1") {
        vehicleMenu.displayVehicleOptions(cm, "E1", "\t\033[4m2） Economy car (1 day) (E1) \033[0m");
    }
    else if (type == "E2") {
        vehicleMenu.displayVehicleOptions(cm, "E2", "\t\033[4m3） Economy car (halfday) (E2) \033[0m");
    }
}

// CarBinarySearch class methods
int CarBinarySearch::countNodes(Car* head) {
    int count = 0;
    Car* current = head;
    while (current != nullptr) {
        count++;
        current = current->getNext();
    }
    return count;
}


Car* CarBinarySearch::getNodeAt(Car* head, int index) {
    int count = 0;
    Car* current = head;
    while (current != nullptr) {
        if (count == index) {
            return current;
        }
        count++;
        current = current->getNext();
    }
    return nullptr;
}
// CarBinarySearch class methods
Car* CarBinarySearch::binarySearchLinkedList(Car* head, string& targetCategory)
{
    int n = countNodes(head);
    int low = 0;
    int high = n - 1;

    // Convert target category to uppercase for case-insensitive comparison
    string target = targetCategory;
    for (char& c : target)
    {
        c = toupper(c);
    }

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        Car* midNode = getNodeAt(head, mid);

        // Convert midNode's code to uppercase for case-insensitive comparison
        string midCode = midNode->getCode();
        for (char& c : midCode)
        {
            c = toupper(c);
        }

        // Check if the category matches the target category
        if (midCode == target)
        {
            cout << "Car model " << targetCategory << " is found." << endl;
            return midNode;
        }
        else if (midCode < target)
        {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    cout << "Car model " << targetCategory << " is not found." << endl;
    return nullptr;
}


void Rent::calculate(string input2, double& total, int day, int hour, int halfday, double& rentalfee)
{
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << "Calculating rent. Please wait......" << endl;
    this_thread::sleep_for(std::chrono::seconds(2));

    // DAY CALCULATION
    if (input2 == "MA")
        rentalfee = day * 65;
    else if (input2 == "E1A")
        rentalfee = day * 130;
    else if (input2 == "E1B")
        rentalfee = day * 250;
    // HALF DAY CALCULATION
    else if (input2 == "MB")
        rentalfee = halfday * 35;
    else if (input2 == "E2A")
        rentalfee = halfday * 90;
    else if (input2 == "E2B")
        rentalfee = halfday * 190;
    // HOUR CALCULATION
    else if (input2 == "MC")
        rentalfee = hour * 5;
    else {}

    total += rentalfee;
    cout << "Your rental fee is RM " << fixed << setprecision(2) << total << endl;
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
            outputfile << "  | Car Model :" << "--------------------" << setw(10) << car->getCode() << endl;
            if (rental.cartype == "E1" || rental.cartype == "E2") {
                outputfile << "  | Car Detail. :" << "----------------------" << setw(10) << car->getDescription() << " |" << endl;
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


