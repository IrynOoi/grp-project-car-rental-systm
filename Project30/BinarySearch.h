

#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

class CarBinarySearch
{
public:
    Car* binarySearchLinkedList(Car* head, string& targetModel);
private:
    int countNodes(Car* head);
    Car* getNodeAt(Car* head, int position);
};

#endif
