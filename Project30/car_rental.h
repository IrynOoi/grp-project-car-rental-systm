//car rental.h
#ifndef CAR_RENTAL_H
#define CAR_RENTAL_H

#include <iostream>
#include <string>
using namespace std;

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
    Car* sentinelSearch(string targetCategory, CManager* cm);
    void addCar(Car** headPtr, string c, string d, string p, bool a);
    void displayCars(Car* head);
    // Declare  friend class
    friend class CManager;
    friend class CarBinarySearch;

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


class CarSorting {
public:
    void insertionSort(Car** head);
};

class Rent
{
public:
    void data(CManager* cm, Car* head, const string& type);
    void calculate(string input2, double& total, int day, int hour, int halfday, double& rentalfee);
    void showrent(string customername, string cartype, int day, double rentalfee, CManager* cm, int order, double total);
};
class CarBinarySearch 
{
public:
    Car* binarySearchLinkedList(Car* head,string& targetModel);
private:
    int countNodes(Car* head);
    Car* getNodeAt(Car* head, int position);
};



#endif




