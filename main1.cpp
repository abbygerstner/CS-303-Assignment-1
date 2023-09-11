#include "main.h"

ArrayManager::ArrayManager() {
    // Initialize member variables
    dataArray = nullptr;
    dataSize = 0;
}

ArrayManager::~ArrayManager() {
    // Performs cleanup
    delete[] dataArray;
}

//A function to check if a certain integer exists in the array if the number is present return the index where the number is present
int findIntegerIndex(const int* arr, int size, int target) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            return i; // Return the index where the number is found
        }
    }
    return -1; // Return -1 if the number is not found
}

//A function that can modify the value of an integer when called with the index of the integer in the array and return the new value and old value back to the user.
int* modifyValue(int* arr, int size, int index, int newValue) {
    int* result = new int[2]; // Create an array to store old and new values
    try {
        if (index >= 0 && index < size) {
            result[0] = arr[index]; // Store the old value
            arr[index] = newValue;  // Modify the value
            result[1] = newValue;   // Store the new value
        } else {
            throw std::out_of_range("Index is out of bounds.");
        }
    } catch (const std::out_of_range& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        result[0] = -1;  // Old value is -1 as an indicator of error
        result[1] = -1;  // New value is -1 as an indicator of error
        exit(1); // Exit the program when an error occurs
    } catch (const std::exception& ex) {
        std::cerr << "Error: Invalid input. Please enter a valid index and value." << std::endl;
        result[0] = -1;  // Old value is -1 as an indicator of error
        result[1] = -1;  // New value is -1 as an indicator of error
        exit(1); // Exit the program when an error occurs
    }
    return result;
}

//A function that adds a new integer to the end of the array
int* addInteger(int* arr, int& size, int value) {
    try {
        int* newArr = new int[size + 1]; // Create a new dynamic array with increased size
        for (int i = 0; i < size; ++i) {
            newArr[i] = arr[i]; // Copy elements from the old array
        }
        newArr[size] = value; // Add the new integer to the end of the new array
        ++size; // Update the size
        delete[] arr; // Delete the old array
        return newArr;
    } catch (const std::bad_alloc& ex) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(1); // Exit the program when an error occurs
    } catch (const std::exception& ex) {
        std::cerr << "Error: Invalid input. Please enter a valid integer." << std::endl;
        exit(1); // Exit the program when an error occurs
    }
}

//A function which intakes an index of an array and removes the integer 
bool replaceOrRemove(int* arr, int& size, int index, bool remove) {
    if (index >= 0 && index < size) {
        if (remove) {
            for (int i = index; i < size - 1; ++i) {
                arr[i] = arr[i + 1]; // Shift elements to remove the integer
            }
            --size; // Update the size
        } else {
            arr[index] = 0; // Replace the value at the given index with 0
        }
        return true;
    }
    std::cerr << "Error: Index is out of bounds." << std::endl;
    exit(1); // Exit the program when an error occurs
}

//A function that prints the final modified array to the console
void printModifiedArrayToConsole(const int* arr, int size) {
    std::cout << "Modified Array:\n";
    if (size > 0) {
        std::cout << arr[0];
        for (int i = 1; i < size; ++i) {
            std::cout << ", " << arr[i]; // Print elements with commas
        }
    }
    std::cout << std::endl;
}

//Main function
int main() {
    // Open the input file
    std::ifstream inputFile("array.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1; // Return an error code
    }
    int* dataArray = nullptr; // Create a dynamic array to store the data
    int dataSize = 0; // Initialize the size to 0
    int value;
    // Read integers from the file and dynamically resize the array
    while (inputFile >> value) {
        dataArray = addInteger(dataArray, dataSize, value);
    }
    // Close the input file
    inputFile.close();
    // dataArray dynamic array contains the data read from the file

    int target; // The number you want to search for

    std::cout << "Enter the number you want to search for: ";
    if (!(std::cin >> target)) {
        std::cerr << "Error: Invalid input. Please enter a valid integer." << std::endl;
        exit(1); // Exit the program when an error occurs
    }

    int index = findIntegerIndex(dataArray, dataSize, target);

    if (index != -1) {
        std::cout << "Integer " << target << " found at index " << index << std::endl;

        // Example of modifying the value at index and getting old and new values
        int newIndex; // Replace the value
        std::cout << "Enter the new index: ";
        if (!(std::cin >> newIndex)) {
            std::cerr << "Error: Invalid input. Please enter a valid integer." << std::endl;
            exit(1); // Exit the program when an error occurs
        }
        int newValue; // Set the new value
        std::cout << "Enter a new value: ";
        if (!(std::cin >> newValue)) {
            std::cerr << "Error: Invalid input. Please enter a valid integer." << std::endl;
            exit(1); // Exit the program when an error occurs
        }
        int* result = modifyValue(dataArray, dataSize, newIndex, newValue);

        if (result[0] != -1) {
            std::cout << "Modified: Old value = " << result[0] << ", New value = " << result[1] << std::endl;
            delete[] result; // Delete the result array when done
                  } else {
            std::cout << "Index " << newIndex << " is out of bounds." << std::endl;
        }
    } else {
        std::cout << "Integer " << target << " not found in the array." << std::endl;
    }

    // Example of adding a new integer to the end of the array
    int newInteger; // Change this to the integer you want to add
    std::cout << "Enter an integer you want to add to the end of the array: ";
    if (!(std::cin >> newInteger)) {
        std::cerr << "Error: Invalid input. Please enter a valid integer." << std::endl;
        exit(1); // Exit the program when an error occurs
    }
    dataArray = addInteger(dataArray, dataSize, newInteger);
    std::cout << "Added integer " << newInteger << " to the end of the array." << std::endl;

    // Example of replacing or removing an integer at a specific index
    int replaceIndex; // User changes this to the index they want to replace or remove
    std::cout << "Enter the index you want to remove from the array: ";
    if (!(std::cin >> replaceIndex)) {
        std::cerr << "Error: Invalid input. Please enter a valid integer." << std::endl;
        exit(1); // Exit the program when an error occurs
    }
    bool removed = replaceOrRemove(dataArray, dataSize, replaceIndex, true); // Change 'true' to 'false' to replace with 0
    if (removed) {
        std::cout << "Removed integer at index " << replaceIndex << std::endl;
    } else {
        std::cout << "Index " << replaceIndex << " is out of bounds." << std::endl;
    }

    // Print the modified data to the console
    printModifiedArrayToConsole(dataArray, dataSize);

    // Delete the dynamic array when you're done to avoid memory leaks
    delete[] dataArray;

    return 0;
}

/*

*/