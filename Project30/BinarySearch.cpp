#include "car_rental.h"
#include <iostream>
#include "BinarySearch.h"

// CarBinarySearch class methods
int CarBinarySearch::countNodes(Car* head)//OOI XIEN XIEN
{
    int count = 0;  // Initialize count of nodes to 0
    Car* current = head;  // Start from the head of the linked list

    // Traverse the linked list and count nodes
    while (current != nullptr)
    {
        count++;  // Increment count for each node
        current = current->getNext();  // Move to the next node
    }
    return count;  // Return the total number of nodes in the linked list
}

Car* CarBinarySearch::getNodeAt(Car* head, int index)//OOI XIEN XIEN
{
    int count = 0;  // Initialize count of nodes to 0
    Car* current = head;  // Start from the head of the linked list

    // Traverse the linked list until the index or end is reached
    while (current != nullptr) {
        if (count == index) {
            return current;  // Return the node at the specified index
        }
        count++;  // Increment count for each node
        current = current->getNext();  // Move to the next node
    }
    return nullptr;  // Return nullptr if index is out of bounds
}

Car* CarBinarySearch::binarySearchLinkedList(Car* head, string& targetCategory) //OOI XIEN XIEN
{
    int n = countNodes(head);  // Get the number of nodes in the linked list
    int low = 0;  // Initialize the low index of the search range
    int high = n - 1;  // Initialize the high index of the search range

    // Convert target category to uppercase for case-insensitive comparison
    string target = targetCategory;
    for (char& c : target) {
        c = toupper(c);  // Convert each character to uppercase
    }

    // Perform binary search on the linked list
    while (low <= high) {
        int mid = low + (high - low) / 2;  // Calculate the middle index
        Car* midNode = getNodeAt(head, mid);  // Get the node at the middle index

        // Convert midNode's code to uppercase for case-insensitive comparison
        string midCode = midNode->getCode();
        for (char& c : midCode) {
            c = toupper(c);  // Convert each character to uppercase
        }

        // Compare the category of the middle node with the target category
        if (midCode == target) {
            cout << "Car model " << targetCategory << " is found." << endl;
            return midNode;  // Return the node if category matches
        }
        else if (midCode < target) {
            low = mid + 1;  // Adjust the search range to the upper half
        }
        else {
            high = mid - 1;  // Adjust the search range to the lower half
        }
    }

    
    return nullptr;  // Return nullptr if target category is not found
}
