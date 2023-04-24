#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

    // function to measure time by calling it at start and end of 
    // code you want to measure
void getDuration(chrono::steady_clock::time_point start,
                    chrono::steady_clock::time_point end) 
{
    double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Elapsed time: " << duration << "ms" << endl;
}
    // searchType: 1 = sequential, 2 = binary
void searchFunction(int dataSize, int key, int searchType)
{
    // generate data
    vector<int> data(dataSize);
    for (int i = 0; i < dataSize; i++) {
        data[i] = 2*i + 1;
    }

    // hop inside of scope depending on searchtype
    if (searchType == 1)
    {
        // start measuring time for sequential search
        auto startSequential = chrono::steady_clock::now(); 

        // search for the key
        bool keyIsFound = false;
        int index;
        for(int i = 0; i <data.size(); i++){
            index = 2*i + 1;
            if (data[i] == key)
            {
                keyIsFound = true;
                cout << "Success! The key is: " << key << endl
                    << "The index of the key in list is: " << i << endl;
            }
        }
        if (keyIsFound == false){
            cout << "The key was not found in the list." << endl;
        }
        // stop measuring time for sequential search
        auto endSequential = chrono::steady_clock::now(); 
        // calculate and print time of algorithm
        getDuration(startSequential, endSequential); 
    }
}

    // function to help print vector data types
void printVector(const vector<int>& vec, int size) 
{
    for (int i = 0; i < size; ++i) {
        cout << vec[i] << " ";
        if ((i+1) % 10 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

void sortWithInsertionSort(int dataSize, int printSize, bool printAll) 
{
    vector<int> data(dataSize);
    srand(time(0));

    for (int i = 0; i < dataSize; i++) {
        data[i] = rand() % (10 * dataSize); // range of random integers is 10 x given size
    }

    cout << "Before sorting:" << endl;
    if (printAll) {
        printVector(data, dataSize);
    } else {
        printVector(data, printSize);
    }

    auto start = chrono::steady_clock::now(); // start measuring time
    for (int i = 1; i < data.size(); ++i) {
        int j = i;
        while (j > 0 && data[j-1] > data[j]) {
            swap(data[j], data[j-1]);
            j--;
        }
    }
    auto end = chrono::steady_clock::now(); // stop measuring time

    cout << "After sorting:" << endl;
    if (printAll) {
        printVector(data, dataSize);
    } else {
        printVector(data, printSize);
    }
    getDuration(start, end); // calculate and print time of algorithm
}

    // swap positions of two elements in an array
void swap(int& a, int& b) 
{
    int temp = a;
    a = b;
    b = temp;
}

    // partitions the array into two parts by pivot, elements that are
    // smaller than pivot go left and higher go right, then loop this
int partition(int arr[], int low, int high) 
{
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksort(int arr[], int low, int high) 
{
    if (low < high) {
        int prt = partition(arr, low, high);
        quicksort(arr, low, prt - 1);
        quicksort(arr, prt + 1, high);
    }
}


// function introductions
void group1();  // Sequential search
void group2();  // Binary search
void group3();  // Insertion sort
void group4();  // Quicksort
void group5();  //

int main() 
{
    int choice;
        cout << "1. Sequential search" << endl;
        cout << "2. Binary search" << endl;
        cout << "3. Insertion sort" << endl;
        cout << "4. Quicksort" << endl;
        cout << "5. " << endl;
        cout << "6. Quit the program" << endl;
        cout << "Your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                group1();
                break;
            case 2:
                group2();
                break;
            case 3:
                group3();
                break;
            case 4:
                group4();
                break;
            case 5:
                group5();
                break;
            case 6:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        } 
    return 0;
}

void group1()
{
    int dataSize, key;
    cout << "Enter the size of data to be searched: ";
    cin >> dataSize;

    cout << "Enter the key: ";
    cin >> key; 

    const int searchType = 1;
    searchFunction(dataSize, key, searchType);
}
void group2()
{

}

void group3()
{
    int dataSize, printSize;
    cout << "Enter the size of data to be sorted: ";
    cin >> dataSize; 
    

    cout << "Enter the number of items to be printed before and after sorting: ";
    cin >> printSize; 

    bool printAll;
    char response;
    cout << "Do you want to print the entire sorted data? (y/n): ";
    cin >> response; 
    

    if (response == 'y' || response == 'Y') {
        printAll = true;
    } else {
        printAll = false;
    }

    sortWithInsertionSort(dataSize, printSize, printAll);
}

void group4()
{
    int size, print_size;
    cout << "Enter size of data to be sorted: ";
    cin >> size; 

    cout << "Enter the number of items to be printed before and after sorting: ";
    cin >> print_size; 

    bool printAll;
    char response;
    cout << "Do you want to print the entire sorted data? (y/n): ";
    cin >> response; 
    

    if (response == 'y' || response == 'Y') { // not case sensitive
        printAll = true;
    } else {
        printAll = false;
    }

    int* arr = new int[size];
    srand(time(0)); // time functions as seed for srand
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (10 * size); // range of random integers is 10 x given size
    }

    cout << "Before sorting: \n";
    if(printAll){
        for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
        }
    }
    else {
        for (int i = 0; i < print_size; i++) {
        cout << arr[i] << " ";
        }
    }
    cout << endl;

    auto start = chrono::steady_clock::now(); // start measuring time
    quicksort(arr, 0, size - 1);
    auto end = chrono::steady_clock::now(); // stop measuring time

    cout << "\nAfter sorting: \n";
    if(printAll){
        for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
        }
    }
    else {
        for (int i = 0; i < print_size; i++) {
        cout << arr[i] << " ";
        }
    }
    cout << endl;
    getDuration(start, end); // calculate and print time of algorithm

    delete[] arr;
}
void group5()
{

}