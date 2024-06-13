#ifndef CAR_RENTAL_H
#define CAR_RENTAL_H

#include <iostream>
#include <string>
using namespace std;

class Car {
private:
    string code;
    string description;
    bool available;
    Car* next;

public:
    Car();
    Car(string c, string d, bool a);
    string getCode();
    string getDescription();
    bool isAvailable();
    Car* getNext();
    void setNext(Car* n);
    void addCar(Car** headPtr, string c, string d, bool a);
    Car* sentinelSearch(string targetModel);
    void displayCars();
};

class CManager {
private:
    Car* headM;
    Car* headE1;
    Car* headE2;

public:
    CManager();
    Car** getHead(string type);
    Car* getHeadPtr(string type);
};

class CarSorting {
public:
    void insertionSort(Car** head);
};

class Rent {
public:
    void data();
};

class CarBinarySearch {
public:
    Car* binarySearchLinkedList(Car* head, const string& targetModel);
private:
    int countNodes(Car* head);
    Car* getNodeAt(Car* head, int position);
};

#endif
