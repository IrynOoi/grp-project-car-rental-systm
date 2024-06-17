#include "car_rental.h"
#include <iostream>
#include "BinarySearch.h"

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