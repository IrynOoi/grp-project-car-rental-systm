#include "car_rental.h"
#include <iostream>
#include "InsertionSort.h"

// CarSorting class methods
void CarSorting::insertionSort(Car** head)
{
    if (*head == nullptr) return;  // If head is nullptr, return (no sorting needed)

    Car* sorted = nullptr;  // Initialize sorted sublist
    Car* current = *head;   // Initialize current node to iterate through the list

    while (current != nullptr)
    {
        Car* next = current->getNext();  // Store the next node to process
        if (sorted == nullptr || sorted->getCode() >= current->getCode())
        {
            // If sorted list is empty or current node belongs at the beginning
            current->setNext(sorted);  // Insert current node into sorted sublist
            sorted = current;  // Update sorted to point to current node
        }
        else
        {
            // Find the correct position to insert current node in sorted sublist
            Car* temp = sorted;
            while (temp->getNext() != nullptr && temp->getNext()->getCode() < current->getCode())
            {
                temp = temp->getNext();  // Move to the next node in sorted sublist
            }
            current->setNext(temp->getNext());  // Insert current node into sorted sublist
            temp->setNext(current);  // Adjust the link in sorted sublist
        }
        current = next;  // Move to the next node in the original list
    }

    *head = sorted;  // Update head pointer to point to the sorted list
}



