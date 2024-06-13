//car rental.cpp
#include "car_rental.h"
#include <iostream>
using namespace std;

// Car class methods
Car::Car(Car* n, string c, string d, string p, bool a)
{
    code = c;
    description = d;
    price = p;
    available = a;
    next = nullptr;
}

Car::Car()
{
    next = nullptr;
}
string Car::getPrice()
{
    return price;
}
string Car::getCode()
{
    return code;
}
string Car::getDescription()
{
    return description;
}

bool Car::isAvailable()
{
    return available;
}

Car* Car::getNext()
{
    return next;
}

void Car::setNext(Car* n)
{
    next = n;
}

void Car::addCar(Car** headPtr, string c, string d, string p, bool a)
{
    Car* newCar = new Car(nullptr, c, d, p, a);  // Corrected constructor call
    if (*headPtr == nullptr)
    {
        *headPtr = newCar;
    }
    else
    {
        Car* temp = *headPtr;
        while (temp->getNext() != nullptr)
        {
            temp = temp->getNext();
        }
        temp->setNext(newCar);
    }
}
Car* Car::sentinelSearch(string targetCategory, CManager* cm)
{
    if (targetCategory != "M" && targetCategory != "E1" && targetCategory != "E2")
    {
        cout << "Invalid input" << endl;
        return nullptr;
    }

    // Create a sentinel with a category-specific code and all other arguments set to default values
    Car* sentinel = new Car(nullptr, targetCategory + "X", "", "", false);

    Car* temp = cm->getHeadPtr(targetCategory);

    if (temp == nullptr)
    {
        cout << "Car type " << targetCategory << " not found." << endl;
        delete sentinel;
        return nullptr;
    }

    // Traverse until the end of the list to find the last node
    while (temp->getNext() != nullptr)
    {
        temp = temp->getNext();
    }

    // Set the next of the last node to the sentinel
    temp->setNext(sentinel);

    // Reset temp to the head of the list
    temp = cm->getHeadPtr(targetCategory);

    // Traverse the list until finding a node with the target category code
    while (!(temp->getCode().substr(0, 1) == targetCategory || temp->getCode().substr(0, 2) == targetCategory)) {
        temp = temp->getNext();
    }

    Car* found = nullptr;
    if (temp != sentinel)
    {
        found = temp;
        cout << "Category " << targetCategory << " found!" << endl;
    }
    else
    {
        cout << "Category " << targetCategory << " not found." << endl;
    }

    // Reset the next of the last node to nullptr
    Car* last = cm->getHeadPtr(targetCategory);
    while (last->getNext() != sentinel) {
        last = last->getNext();
    }
    last->setNext(nullptr);

    // Delete the sentinel node
    delete sentinel;

    return found;
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
void CarSorting::insertionSort(Car** head) {
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
void Rent::data(CManager* cm, Car* head, const string& type)
{
    if (head == nullptr) {
        cout << "No cars available." << endl;
        return;
    }

    // Display the options directly based on the type
    cout << "\tPlease select a type of vehicle" << endl;
    cout << "\tType of vehicles : " << endl;

    if (type == "M") {
        cout << "\t\033[4m1) Motorcycle Scooter (M)\033[0m" << endl;
        cout << "\t  (MA) " << cm->getHeadPtr("M")->getDescription() << " - " << cm->getHeadPtr("M")->getPrice() << endl;
        cout << "\t  (MB) " << cm->getHeadPtr("M")->getNext()->getDescription() << " - " << cm->getHeadPtr("M")->getNext()->getPrice() << endl;
        cout << "\t  (MC) " << cm->getHeadPtr("M")->getNext()->getNext()->getDescription() << " - " << cm->getHeadPtr("M")->getNext()->getNext()->getPrice() << endl;
    }
    else if (type == "E1") {
        cout << "\t\033[4m Economy car (1 day) (E1) \033[0m" << endl;
        cout << "\t(E1A) " << cm->getHeadPtr("E1")->getDescription() << " - " << cm->getHeadPtr("E1")->getPrice() << endl;
        cout << "\t(E2B) " << cm->getHeadPtr("E1")->getNext()->getDescription() << " - " << cm->getHeadPtr("E1")->getNext()->getPrice() << endl;
    }
    else if (type == "E2") {
        cout << "\t\033[4m Economy car (halfday) (E2) \033[0m" << endl;
        cout << "\t(E2A) " << cm->getHeadPtr("E2")->getDescription() << " - " << cm->getHeadPtr("E2")->getPrice() << endl;
        cout << "\t(E2B) " << cm->getHeadPtr("E2")->getNext()->getDescription() << " - " << cm->getHeadPtr("E2")->getNext()->getPrice() << endl;
    }

    cout << endl;
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
Car* CarBinarySearch::binarySearchLinkedList(Car* head, const string& targetCategory) {
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

    return nullptr;
}


