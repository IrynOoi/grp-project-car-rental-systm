// main.cpp
#include "car_rental.h"
#include <iostream>


using namespace std;

int main()
{
    int day, halfday,hour;
    string cartype, input2;
    char carmodel, input3 = 'a';
    CManager cm;
    Car car;
    CarSorting sort;

    // Add cars to the respective lists
    car.addCar(cm.getHead("M"), "MA", "1 day", "RM65", true); //(MA)Motorcycle Scooter - 1 day
    car.addCar(cm.getHead("M"), "MB", "Halfday", "RM35", true);//(MB)Motorcycle Scooter - halfday
    car.addCar(cm.getHead("M"), "MC", "1 hour", "RM5.00", true);//(MC)Motorcycle Scooter-1 hour
    //1 day
    car.addCar(cm.getHead("E1"), "E1B", "6 Seater Car", "RM250.00", true); //(E1A) Axia / Kelisa Auto
    car.addCar(cm.getHead("E1"), "E1A", "4 Seater Car", "RM130.00", true); //(E1B) 6 Seater Car
    //halfday
    car.addCar(cm.getHead("E2"), "E2A", "4 Seater Car", "RM90.00", true);//(E2A) Axia / Kelisa Auto
    car.addCar(cm.getHead("E2"), "E2B", "6 Seater Car", "RM190.00", true);//(E2B) Axia / Kelisa Auto

    // Sort each list
    sort.insertionSort(cm.getHead("M"));
    sort.insertionSort(cm.getHead("E1"));
    sort.insertionSort(cm.getHead("E2"));
    Rent rent;

    // Display all cars
    cout << "\nAll cars sorted by Car Code\n";
    rent.data(&cm, cm.getHeadPtr("M"), "M");
    rent.data(&cm, cm.getHeadPtr("E1"), "E1");
    rent.data(&cm, cm.getHeadPtr("E2"), "E2");

    do
    {
        do
        {
            cout << "\nEnter the car type you want to search (M, E1, E2): ";
            cin >> cartype;
            // Convert cartype to uppercase
            for (char& c : cartype) 
            {
                c = toupper(c);
            }
        } while (cartype != "M" && cartype != "E1" && cartype != "E2");

        // Call sentinelSearch for the given cartype
        car.sentinelSearch(cartype, &cm);

        do
        {
            cout << "\nEnter the car model you want to search (MA, MB, MC, etc): ";
            cin >> input2;
            // Convert input2 to uppercase
            for (char& c : input2)
            {
                c = toupper(c);
            }

        } while (input2 != "MA" && input2 != "MB" && input2 != "MC" &&
            input2 != "E1A" && input2 != "E1B" && input2 != "E1C" &&
            input2 != "E2A" && input2 != "E2B" && input2 != "E2C");

        CarBinarySearch BS;
        Car* result2 = BS.binarySearchLinkedList(cm.getHeadPtr(cartype), input2);

        if (result2)
        {
            cout << "Car model " << input2 << " is found!" << endl;

            if (cartype == "E1" || cartype == "E2")
            {
                do {
                    cout << "Choose Axia (A) or Kelisa (K)? " << endl;
                    cin >> carmodel;
                    // Convert input char to uppercase
                    carmodel = toupper(static_cast<unsigned char>(carmodel));

                    if ((input2 == "E1A" || input2 == "E2A") && (carmodel == 'A'))
                    {
                        string modelA = "Axia";
                        cout << modelA << " is selected" << endl;
                    }
                    else if ((input2 == "E1B" || input2 == "E2B") && (carmodel == 'K'))
                    {
                        string modelB = "Kelisa";
                        cout << modelB << " is selected" << endl;
                    }
                    else
                    {
                        cout << "Invalid input. Please try again." << endl;
                    }
                } while (((input2 == "E1A" || input2 == "E2A") && carmodel != 'A') ||
                    ((input2 == "E1B" || input2 == "E2B") && carmodel != 'K'));
            }
            else
            {
              
                    
            } while (((input2 == "E1A" || input2 == "E2A") && carmodel != 'A') ||
                ((input2 == "E1B" || input2 == "E2B") && carmodel != 'K'));
        }
        else
        {    
            cout << "Car model " << input2 << " not found." << endl;
        } 
   
        if (input2 == "MA" || input2 == "E1A" || input2 == "E1B") 
        {
            cout << "Please key in the number of days you want to rent: ";
            while (!(cin >> day) || day <= 0) {
                cout << "Invalid input. Please enter a positive number for days: ";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
            }
        }
        else if (input2 == "MB" || input2 == "E2A" || input2 == "E2B") 
        {
            cout << "Please key in the number of halfdays you want to rent: ";
            while (!(cin >> halfday) || halfday <= 0) {
                cout << "Invalid input. Please enter a positive number for halfdays: ";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
            }
        }
        else if (input2 == "MC") 
        {
            cout << "Please key in the number of hours you want to rent: ";
            while (!(cin >> hour) || hour <= 0) {
                cout << "Invalid input. Please enter a positive number for hours: ";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
            }
        }
       

        cout << "Do you want to add more cars to your cart? (Y/N): ";
        cin >> input3;
        cout << endl;

        
    } while (input3 == 'Y' || input3 == 'y');
    cout << "1" << endl;
    return 0;

}

