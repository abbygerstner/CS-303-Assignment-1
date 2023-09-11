//Header file
#ifndef MAIN_H
#define MAIN_H

#include <iostream> //Include input/output stream
#include <fstream> //Include file stream: create files, write information to files, and read information from files
#include <exception>

class ArrayManager {
public:
    ArrayManager(); // Constructor
    ~ArrayManager(); // Destructor

    void readFile(const std::string& filename);
    void printModifiedArrayToConsole() const;

    // Public member functions for manipulating the array
    int findIntegerIndex(int target) const;
    bool modifyValue(int index, int newValue);
    bool addInteger(int value);
    bool replaceOrRemove(int index, bool remove);

private:
    int* dataArray;
    int dataSize;

    // Private member functions
    void resizeArray(int newSize);
};

#endif // MAIN_H



