// main.cpp
#include "car_rental.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib> // For exit()
#include "Sentinel.h"
using namespace std;

int main()
{
    // Create a Welcome object
    Welcome welcome;

    // Display the welcome message
    welcome.displayWelcomeMessage();

    int day=0, halfday=0,hour=0;
    double total = 0,rentalfee=0.0;
    string input2;
    char carmodel, input3 = 'a';
    CManager cm;
    string customername;
    string cartype;
    Car car;
    CarSorting sort;
    CarBinarySearch BS;
    SentinelSearch SS;
    int order=0;
    customer customer;
 
    vector<RentalInfo> rentals; // Vector to store all rental information

    // Add cars to the respective lists
    car.addCar(cm.getHead("M"), "MA", "1 day", "RM65",false); //(MA)Motorcycle Scooter - 1 day
    car.addCar(cm.getHead("M"), "MB", "Halfday", "RM35", true);//(MB)Motorcycle Scooter - halfday
    car.addCar(cm.getHead("M"), "MC", "1 hour", "RM5.00", true);//(MC)Motorcycle Scooter-1 hour
    //1 day
    car.addCar(cm.getHead("E1"), "E1B", "6 Seater Car", "RM250.00", true); //(E1B) 6 Seater Car
    car.addCar(cm.getHead("E1"), "E1A", "4 Seater Car", "RM130.00", true); //(E1A) Axia / Kelisa Auto
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

  
    do {
        cout << "\tPlease Enter your Name: "; // Customer name input loop
        getline(cin, customername);

        // Check if the name contains any numbers
        if (!customer.isValidName(customername)) {
            cout << "Invalid name. Please enter a name without numbers." << endl;
        }
        else {
            break; // Valid name entered, exit loop
        }
    } while (true);


    do 
    {
        RentalInfo rental; // Create a new RentalInfo object for each rental
        
        // Car type selection loop
       
            do
            {
                cout << "\nEnter the car type you want to search (M, E1, E2): ";
                cin >> cartype;
                // Convert cartype to uppercase
                for (char& c : cartype)
                {
                    c = toupper(c);
                }
                // Search and select car model loop
                SS.sentinelSearch(cartype, &cm);

                do
                {
                    cout << "\nEnter the car model you want to search (MA, MB, MC, etc): ";
                    cin >> input2;

                    // Convert input2 to uppercase
                    for (char& c : input2)
                    {
                        c =toupper(c); // Convert each character to uppercase
                    }

                } while (input2 != "MA" && input2 != "MB" && input2 != "MC" &&
                    input2 != "E1A" && input2 != "E1B" &&
                    input2 != "E2A" && input2 != "E2B");

                // Perform binary search for the car model
                Car* result2 = BS.binarySearchLinkedList(cm.getHeadPtr(cartype), input2);

                // Check if result2 is nullptr (not found) or if the found car does not match the selected category
                    if (!result2->isAvailable())
                    {
                        cout << "However,Car model " << input2 << " is not available for now." << endl;

                        cout << "Do you want to add more cars to your cart? (Y/N): ";
                        cin >> input3;
                        cout << endl;
                        if (input3 != 'Y' && input3 != 'y') {
                            exit(0); // Exit the loop if the user does not want to add more cars
                        }
                        
                    }
                    else 
                        break;
                
            } while (input3=='Y'|| input3 == 'y');

        // Additional logic for selecting car details (Axia/Kelisa)
        if (cartype == "E1" || cartype == "E2")
        {
            do {
                cout << "Choose Axia (A) or Kelisa (K)? " << endl;
                cin >> carmodel;
                // Convert input char to uppercase
                carmodel = toupper(static_cast<unsigned char>(carmodel));

                if ((input2 == "E1A" || input2 == "E2A") && (carmodel == 'A')) {
                    string modelA = "Axia";
                    cout << modelA << " is selected" << endl;
                    break; // Exit loop on valid input
                }
                else if ((input2 == "E1A" || input2 == "E2A") && (carmodel == 'K')) {
                    string modelB = "Kelisa";
                    cout << modelB << " is selected" << endl;
                    break; // Exit loop on valid input
                }
                else {
                    cout << "Invalid input. Please try again." << endl;
                }
            } while (true); // Continue loop until valid input is given
        }

        // Ask for rental period based on car model type
        if (input2 == "MA" || input2 == "E1A" || input2 == "E1B") {
            cout << "Please key in the number of days you want to rent: ";
            while (!(cin >> day) || day <= 0) 
            {
                cout << "Invalid input. Please enter a positive number for days: ";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
            }
        }
        else if (input2 == "MB" || input2 == "E2A" || input2 == "E2B") {
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

        // Calculate rental fee based on rental period and car model
        rent.calculate(input2, total, day, hour, halfday, rentalfee);

        // Store rental details in RentalInfo object
        rental.customername = customername;
        rental.input2 = input2;
        rental.cartype = cartype;
        rental.rentalfee = rentalfee;
        rental.day = day;
        rental.halfday = halfday;
        rental.hour = hour;

        // Add rental info to vector
        rentals.push_back(rental);

        // Prompt to add more cars to cart
        cout << "Do you want to add more cars to your cart? (Y/N): ";
        cin >> input3;
        cout << endl;

        // Clear cin buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (input3 == 'Y' || input3 == 'y');
  
    // Generate receiptcopy for all rentals made
    
    rent.receiptcopy(rentals, customername, &cm, total);
    //print out thanks.txt
    ifstream in("thanks.txt");
    string line;
    while (getline(in, line)) 
    {
        cout << line << endl;
    }
    return 0;
}

