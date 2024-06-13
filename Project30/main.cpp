#include "car_rental.h"
#include <iostream>
using namespace std;

int main() {
    string input2;
    Car car;
    CManager cm;
    string cartype;

    // Add cars to the respective lists
    car.addCar(cm.getHead("M"), "MA", "1 day - RM65", true);
    car.addCar(cm.getHead("M"), "MB", "Halfday - RM35", true);
    car.addCar(cm.getHead("M"), "MC", "1 hour - RM5.00", true);

    car.addCar(cm.getHead("E1"), "E1A", "4 Seater car - RM130.00", true);
    car.addCar(cm.getHead("E1"), "E1B", "6 Seater Car - RM250.00", true);

    car.addCar(cm.getHead("E2"), "E2A", "Small Lorry - RM200.00", true);
    car.addCar(cm.getHead("E2"), "E2B", "Big Lorry - RM350.00", true);

    cout << "\nAll cars sorted by Car Code\n";
    car.displayCars();

    // Binary search for a car model
    CarBinarySearch carBinarySearch;
    cout << "\nEnter the car model you want to search: ";
    cin >> cartype;
    Car* result = carBinarySearch.binarySearchLinkedList(cm.getHeadPtr("M"), cartype);
    if (result) 
    {
        cout << "Car model " << cartype << " found!" << endl;
    } else {
        cout << "Car model " << cartype << " not found." << endl;
    }

    return 0;
}
