#include "car_rental.h"
#include <iostream>
#include "InsertionSort.h"

// CarSorting class methods
void CarSorting::insertionSort(Car** head)
{
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


