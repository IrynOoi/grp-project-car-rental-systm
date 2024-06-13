#include "car_rental.h"

// Car class methods
Car::Car(string c, string d, bool a)
{
    code = c;
    description = d;
    available = a;
    next = nullptr;
}

Car::Car() {
    next = nullptr;
}

string Car::getCode() {
    return code;
}

string Car::getDescription() {
    return description;
}

bool Car::isAvailable() {
    return available;
}

Car* Car::getNext() {
    return next;
}

void Car::setNext(Car* n) {
    next = n;
}

void Car::addCar(Car** headPtr, string c, string d, bool a) {
    Car* newCar = new Car(c, d, a);
    if (!*headPtr) {
        *headPtr = newCar;
    }
    else {
        Car* temp = *headPtr;
        Car* prev = nullptr;
        while (temp && temp->getCode() < c) {
            prev = temp;
            temp = temp->getNext();
        }
        newCar->setNext(temp);
        if (prev) {
            prev->setNext(newCar);
        }
        else {
            *headPtr = newCar;
        }
    }
}

Car* Car::sentinelSearch(string targetModel) {
    if (next == nullptr) return nullptr;

    Car* sentinel = new Car(targetModel, "", false);
    Car* temp = next;

    while (temp->getNext() != nullptr) {
        temp = temp->getNext();
    }
    temp->setNext(sentinel);

    temp = next;

    while (temp->getCode() != targetModel) {
        temp = temp->getNext();
    }

    Car* found = nullptr;
    if (temp != sentinel) {
        found = temp;
        cout << "Car model " << targetModel << " found!" << endl;
    }
    else {
        cout << "Car model " << targetModel << " not found." << endl;
    }

    Car* last = next;
    while (last->getNext() != sentinel) {
        last = last->getNext();
    }
    last->setNext(nullptr);
    delete sentinel;

    return found;
}

void Car::displayCars() {
    Car* temp = next;
    while (temp != nullptr) {
        cout << "Car model: " << temp->getCode() << endl;
        cout << "Car description: " << temp->getDescription() << endl;
        cout << "Car availability: " << (temp->isAvailable() ? "Available" : "Not available") << endl;
        temp = temp->getNext();
    }
}

// CManager class methods
CManager::CManager() {
    headM = nullptr;
    headE1 = nullptr;
    headE2 = nullptr;
}

Car** CManager::getHead(string type) {
    if (type == "M") return &headM;
    if (type == "E1") return &headE1;
    if (type == "E2") return &headE2;
    return nullptr;
}

Car* CManager::getHeadPtr(string type) {
    if (type == "M") return headM;
    if (type == "E1") return headE1;
    if (type == "E2") return headE2;
    return nullptr;
}

// CarSorting class methods
void CarSorting::insertionSort(Car** head) {
    if (*head == nullptr || (*head)->getNext() == nullptr) {
        return;
    }

    Car* sorted = nullptr;
    Car* current = *head;

    while (current != nullptr) {
        Car* next = current->getNext();
        if (sorted == nullptr || sorted->getCode() >= current->getCode()) {
            current->setNext(sorted);
            sorted = current;
        }
        else {
            Car* temp = sorted;
            while (temp->getNext() != nullptr && temp->getNext()->getCode() < current->getCode()) {
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
void Rent::data() {
    cout << "List of car models:\n";
    cout << "M: MA, MB, MC\n";
    cout << "E1: E1A, E1B\n";
    cout << "E2: E2A, E2B\n";
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

Car* CarBinarySearch::getNodeAt(Car* head, int position) {
    Car* current = head;
    int count = 0;
    while (current != nullptr) {
        if (count == position) {
            return current;
        }
        count++;
        current = current->getNext();
    }
    return nullptr;
}

Car* CarBinarySearch::binarySearchLinkedList(Car* head, const string& targetModel) {
    int n = countNodes(head);
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        Car* midNode = getNodeAt(head, mid);

        if (midNode->getCode() == targetModel) {
            return midNode;
        }
        else if (midNode->getCode() < targetModel) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return nullptr;
}


