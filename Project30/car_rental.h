//car rental.h
#ifndef CAR_RENTAL_H
#define CAR_RENTAL_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct RentalInfo 
{
    string customername;
    string input2;
    string cartype;
    double rentalfee;
    int day;
    int hour;
    int halfday;
    string prev_cartype; // New field for previous car type
    string prev_input2;  // New field for previous car model
};

// Welcome class definition
class Welcome {
public:
    void displayWelcomeMessage();
private:
    void readFromFile(const std::string& filename);
};

// Forward declaration of CManager
class CManager;

class Car
{
private:
    string code;
    string price;
    string description;
    bool available;
    Car* next;

public:
    Car();
    Car(Car* n, string c, string d, string p, bool a);

    // Getter methods
    string getCode();
    string getDescription();
    string getPrice();
    bool isAvailable();
    Car* getNext();

    // Setter method
    void setNext(Car* n);
    void addCar(Car** headPtr, string c, string d, string p, bool a);
    void displayCars(Car* head);
    // Declare  friend class
    friend class CManager;
    friend class CarBinarySearch;
    friend class SentinelSearch;
};




class CManager
{
private:
    Car* headM;
    Car* headE1;
    Car* headE2;
    friend class CarSorting; // Allow CarSorting to access private members

public:
    CManager(); // Constructor declaration without a return type
    Car** getHead(string type);
    Car* getHeadPtr(string type);
};


class CarSorting
{
public:
    void insertionSort(Car** head);
};

class Rent
{
public:
    void data(CManager* cm, Car* head, const string& type);
    void calculate(string input2, double& total, int day, int hour, int halfday, double& rentalfee);
    void receiptcopy(vector<RentalInfo>& rentals, string& customername, CManager* cm, double total);
};
class CarBinarySearch 
{
public:
    Car* binarySearchLinkedList(Car* head,string& targetModel);
private:
    int countNodes(Car* head);
    Car* getNodeAt(Car* head, int position);
};

class customer 
{
    public:
        bool isValidName(const string& name);
        void customer_input(string& customername, CManager& cm, customer & customer, Car& car, CarBinarySearch & BS, vector<RentalInfo>& rentals, double& total);
};

#endif




