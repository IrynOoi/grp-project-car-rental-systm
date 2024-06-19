#include "car_rental.h"
#include <iostream>
#include "Sentinel.h"


Car* SentinelSearch::sentinelSearch(string targetCategory, CManager* cm)//OOI XIEN XIEN
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