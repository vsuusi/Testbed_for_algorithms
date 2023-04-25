#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <string>

using namespace std;

enum
{
    keyFailure = -1,
    funcFailure = 2,
};

// function to measure time
void getDuration(chrono::steady_clock::time_point start,
                    chrono::steady_clock::time_point end) 
{
    double duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    int millisecs = round(duration/1000);
    cout << "Elapsed time: " << duration << " microseconds or " 
         << millisecs << " milliseconds (rounded)." << endl;
}

int searchFunction(int dataSize, int key, int searchType)
{
    // generate data
    vector<int> data(dataSize);
    for (int i = 0; i < dataSize; i++) {
        data[i] = 2*i + 1;
    }
    int comparisions = 0;

    // hop inside of sequential search scope
    if (searchType == 1)
    {
        // search for the key
        for(int i = 0; i <data.size(); i++){
            if (data[i] == key)
            {
                return i+1;
            }
        }
        return keyFailure; // key not found
    }

    // hop inside of binary search scope
    if (searchType == 2)
    {
        int left = 0;
        int right = data.size() - 1;
        while (left <= right) 
        {
            int mid = (left + right) / 2;
            if (data[mid] == key) {
                return mid + 1;
            } 
            else if (data[mid] < key) {
                left = mid + 1;
            } 
            else {
                right = mid - 1;
            }
        }
        return keyFailure; // key not found
        
    }
    return funcFailure;
}
    //overload
int searchFunction(int dataSize, int key, int searchType, int& comparisions)
{
    // generate data
    vector<int> data(dataSize);
    for (int i = 0; i < dataSize; i++) {
        data[i] = 2*i + 1;
    }

    // hop inside of sequential search scope
    if (searchType == 1)
    {
        // search for the key
        for(int i = 0; i <data.size(); i++){
            comparisions++;
            if (data[i] == key)
            {
                return i+1;
            }
        }
        return keyFailure; 
    }

    // hop inside of binary search scope
    if (searchType == 2)
    {
        int left = 0;
        int right = data.size() - 1;
        while (left <= right) 
        {
            int mid = (left + right) / 2;
            comparisions++;
            if (data[mid] == key) {
                return mid + 1;
            } 
            else if (data[mid] < key) {
                left = mid + 1;
            } 
            else {
                right = mid - 1;
            }
        }
        return keyFailure;
        
    }
    return funcFailure;
}


void compare_search_algorithms(int dataSize, int num_repetitions) 
{
    // initialize random seed
    srand(time(nullptr));

    int totalSeqComparisons = 0;
    int totalBinComparisons = 0;

    for (int i = 0; i < num_repetitions; i++) {
        
        int key = rand() % dataSize + 1; // generate random key

        int seq_comparisons = 0;
        int bin_comparisons = 0;

        // sequential search
        auto startSeq = chrono::steady_clock::now();
        int seq_status = searchFunction(dataSize, key, 1, seq_comparisons);
        string seq_status_char;
        if (seq_status != -1){
            seq_status_char = "Success";
        }
        else seq_status_char = "Failure";
        totalSeqComparisons += seq_comparisons;
        auto endSeq = chrono::steady_clock::now();
        auto timeSeq = chrono::duration_cast<chrono::microseconds>(endSeq - startSeq).count();

        // binary search
        auto startBin = chrono::steady_clock::now();
        int bin_status = searchFunction(dataSize,key, 2, bin_comparisons);
        string bin_status_char;
        if (bin_status != -1){
            bin_status_char = "Success";
        }
        else bin_status_char = "Failure";
        totalBinComparisons += bin_comparisons;
        auto endBin = chrono::steady_clock::now();
        auto timeBin = chrono::duration_cast<chrono::microseconds>(endBin - startBin).count();
        
        cout << "\nSearch #" << i+1 << " with key " << key << ":" << endl;
        cout << "--------------------------------------" << endl;

        cout << "Sequential:\nStatus: " << seq_status_char << endl;
        cout << "Time elapsed: " << timeSeq << " microseconds" << endl;
        cout << "Comparisions: " << seq_comparisons << endl;

        cout << "Binary:\nStatus: " << bin_status_char << endl;
        cout << "Time elapsed: " << timeBin << " microseconds" << endl;
        cout << "Comparisions: " << bin_comparisons << endl;
    }
}


    /*--------------------------- SORTING FUNCTIONS -----------------------------*/


    // function to help print vector data types
void printVector(const vector<int> &vec, int size) 
{
    for (int i = 0; i < size; ++i) {
        cout << vec[i] << " ";
        if ((i+1) % 10 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

    // swap positions of two elements in an array or vector
void swap(int& a, int& b) 
{
    int temp = a;
    a = b;
    b = temp;
}

    // partitions the array into two parts by pivot, elements that are
    // smaller than pivot go left and higher go right, then loop this
int partition(vector<int> &arr, int low, int high) 
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

void quicksort(vector<int> &arr, int low, int high) 
{
    if (low < high) {
        int prt = partition(arr, low, high);
        quicksort(arr, low, prt - 1);
        quicksort(arr, prt + 1, high);
    }
}

void insertionSort(vector<int> &data) 
{
    for (int i = 1; i < data.size(); ++i) {
        int j = i;
        while (j > 0 && data[j-1] > data[j]) {
            swap(data[j], data[j-1]);
            j--;
        }
    }
}

void bubblesort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < n-1-i; j++){
            if (arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void merge(vector<int> &arr, int left, int mid, int right) 
{
    int i, j, k;
    
    int ArrLeft = mid - left + 1;
    int ArrRight = right - mid;
    // create temp arrays
    vector<int> subVecLeft(ArrLeft);
    vector<int> subVecRight(ArrRight);

    // copy data to temp arrays
    for (i = 0; i < ArrLeft; i++) {
        subVecLeft[i] = arr[left + i];
    }
    for (j = 0; j < ArrRight; j++) {
        subVecRight[j] = arr[mid + 1 + j];
    }

    // merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < ArrLeft && j < ArrRight) {
        if (subVecLeft[i] <= subVecRight[j]) {
            arr[k] = subVecLeft[i];
            i++;
        }
        else {
            arr[k] = subVecRight[j];
            j++;
        }
        k++;
    }
    // copy the remaining elements of subVecLeft
    while (i < ArrLeft) {
        arr[k] = subVecLeft[i];
        i++;
        k++;
    }
    // copy the remaining elements of subVecRight
    while (j < ArrRight) {
        arr[k] = subVecRight[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int> &arr, int left, int right)
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right); // merge sorted halves
    }
}

void compare_sort_algorithms(vector<int> &arr, vector<int> &arr2, int alg1, int alg2)
{
   int time1, time2, compare1, compare2;
   string algname1, algname2;

    switch(alg1){
        case 1:{
            algname1 = "Insertion sort";
            auto start1 = chrono::steady_clock::now();
            bubblesort(arr);
            auto end1 = chrono::steady_clock::now();
            time1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
            compare1 = arr.size() * (arr.size() - 1) / 2;
        }
        break;
        case 2:{
            algname1 = "Quicksort";
            auto start1 = chrono::steady_clock::now();
            quicksort(arr, 0, arr.size() - 1);
            auto end1 = chrono::steady_clock::now();
            time1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
            compare1 = arr.size() * (arr.size() - 1) / 2;
        }
        break;   
        case 3:{
            algname1 = "Bubblesort";
            auto start1 = chrono::steady_clock::now();
            bubblesort(arr);
            auto end1 = chrono::steady_clock::now();
            time1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
            compare1 = arr.size() * (arr.size() - 1) / 2;
        }
        break;
        case 4:{
            algname1 = "Merge sort";
            auto start1 = chrono::steady_clock::now();
            mergeSort(arr, 0, arr.size() - 1);
            auto end1 = chrono::steady_clock::now();
            time1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
            compare1 = arr.size() * log2(arr.size());
        }
        break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            return;
    }

    switch(alg2){
        case 1:{
            algname2 = "Insertion sort";
            auto start2 = chrono::steady_clock::now();
            bubblesort(arr2);
            auto end2 = chrono::steady_clock::now();
            time2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
            compare2 = arr2.size() * (arr2.size() - 1) / 2;
        }
        break;
        case 2:{
            algname2 = "Quicksort";
            auto start2 = chrono::steady_clock::now();
            quicksort(arr2, 0, arr2.size() - 1);
            auto end2 = chrono::steady_clock::now();
            time2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
            compare2 = arr2.size() * (arr2.size() - 1) / 2;
        }
        break;   
        case 3:{
            algname2 = "Bubblesort";
            auto start2 = chrono::steady_clock::now();
            bubblesort(arr2);
            auto end2 = chrono::steady_clock::now();
            time2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
            compare2 = arr2.size() * (arr2.size() - 1) / 2;
        }
        break;
        case 4:{
            algname2 = "Merge sort";
            auto start2 = chrono::steady_clock::now();
            mergeSort(arr2, 0, arr2.size() - 1);
            auto end2 = chrono::steady_clock::now();
            time2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
            compare2 = arr2.size() * log2(arr2.size());
        }
        break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            return;
    }

        //print compare statistics
        cout << "--------------------------------------" << endl;

        cout << "Data amount: " << arr.size() << endl;
        cout << algname1 << ": " << endl;
        cout << "Time elapsed: " << time1 << " microseconds or "
             << time1/1000 << " milliseconds" << endl;
        cout << "Comparisions: " << compare1 << endl;

        cout << algname2 << ": " << endl;
        cout << "Time elapsed: " << time2 << " microseconds or " 
             << time2/1000 << " milliseconds" << endl;
        cout << "Comparisions: " << compare2 << endl;

}
// function introductions
void group1();  // Sequential search
void group2();  // Binary search and comparision
void group3();  // Insertion sort
void group4();  // Quicksort
void group5();  // Bubblesort, merge sort and comparision

int main() 
{
    int choice;
        cout << "1. Sequential search" << endl;
        cout << "2. Binary search and comparision" << endl;
        cout << "3. Insertion sort" << endl;
        cout << "4. Quicksort" << endl;
        cout << "5. Bubblesort, merge sort and comparision" << endl;
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

// Sequential search
void group1() 
{
    int dataSize, key;
    cout << "Enter the size of data to be searched: ";
    cin >> dataSize;
    if (dataSize <= 0){
        cout << "False data size. Please provide a number greater than 0" << endl;
        return;
    }

    cout << "Enter the key: ";
    cin >> key; 
    if (key > dataSize*2){
        cout << "False key size. Please provide a key size that is on range of data." << endl;
        return;
    }

    auto start = chrono::steady_clock::now(); 

    const int searchType = 1;
    int result = searchFunction(dataSize, key, searchType);
    if (result != keyFailure)
    {
        cout << "Success! The key is: " << key
             << "\nThe location of the key in the list is: " << result << endl;
    }
    else{
        cout << "Failure! The key was not on the list" << endl;
    }
    auto end = chrono::steady_clock::now();
    getDuration(start, end);
}

 // Binary search and comparision
void group2()
{
    int dataSize, key;
    cout << "Enter the size of data to be searched: ";
    cin >> dataSize;
    if (dataSize <= 0){
        cout << "False data size. Please provide a number greater than 0" << endl;
        return;
    }

    char response;
    cout << "Do performance comparision to group 1? (y/n): ";
    cin >> response;

    if (response == 'y' || response == 'Y') {
        compare_search_algorithms(dataSize, 10); //second parameter is number of comparitions
    } 
    else {
        cout << "Enter the key: ";
        cin >> key;
        if (key > dataSize*2){
        cout << "False key size. Please provide a key size that is on range of data." << endl;
        return;
    }

        const int searchType = 2;
        auto start = chrono::steady_clock::now();
        int result = searchFunction(dataSize, key, searchType);
        if (result != keyFailure)
    {
        cout << "Success! The key is: " << key
             << "\nThe location of the key in the list is: " << result << endl;
    }
    else{
        cout << "Failure! The key was not on the list" << endl;
    }
        auto end = chrono::steady_clock::now(); 
        getDuration(start, end);
    }    
}

// Insertion sort
void group3() 
{
    int dataSize, printSize;
    cout << "Enter the size of data to be sorted: ";
    cin >> dataSize; 
    if (dataSize <= 0){
        cout << "False data size. Please provide a number greater than 0" << endl;
        return;
    }

    cout << "Enter the number of items to be printed before and after sorting: ";
    cin >> printSize; 
    if (printSize > dataSize){
        cout << "False print size. Print size cannot be greater than data size" << endl;
        return;
    }

    bool printAll;
    char response;
    cout << "Do you want to print the entire sorted data? (y/n): ";
    cin >> response; 
    

    if (response == 'y' || response == 'Y') {
        printAll = true;
    } else {
        printAll = false;
    }

    //generate data
    vector<int> data(dataSize);
    srand(time(0));
    for (int i = 0; i < data.size(); i++) {
        data[i] = rand() % (10 * data.size()); // range of random integers is 10 x given size
    }
    
    cout << "Before sorting:" << endl;
    printVector(data, printSize);

    auto start = chrono::steady_clock::now(); // start measuring time
    insertionSort(data);
    auto end = chrono::steady_clock::now(); // stop measuring time

    cout << "After sorting:" << endl;
    if (printAll) {
        printVector(data, dataSize);
    } else {
        printVector(data, printSize);
    }

    getDuration(start, end); // calculate and print time of algorithm
}

// Quicksort
void group4() 
{
    int dataSize, print_size;
    cout << "Enter size of data to be sorted: ";
    cin >> dataSize; 
    if (dataSize <= 0){
        cout << "False data size. Please provide a number greater than 0" << endl;
        return;
    }

    cout << "Enter the number of items to be printed before and after sorting: ";
    cin >> print_size;
    if (print_size > dataSize){
        cout << "False print size. Print size cannot be greater than data size" << endl;
        return;
    }

    bool printAll;
    char response;
    cout << "Do you want to print the entire sorted data? (y/n): ";
    cin >> response; 
    
    if (response == 'y' || response == 'Y') { // not case sensitive
        printAll = true;
    } else {
        printAll = false;
    }

    //generate data
    vector<int> data(dataSize);
    srand(time(0));
    for (int i = 0; i < data.size(); i++) {
        data[i] = rand() % (10 * data.size()); // range of random integers is 10 x given size
    }

    cout << "Before sorting: \n";
    for (int i = 0; i < print_size; i++) {
    cout << data[i] << " ";
    }
    cout << endl;

    auto start = chrono::steady_clock::now(); // start measuring time
    quicksort(data, 0, dataSize - 1);
    auto end = chrono::steady_clock::now(); // stop measuring time

    cout << "\nAfter sorting: \n";
    if(printAll){
        for (int i = 0; i < dataSize; i++) {
        cout << data[i] << " ";
        }
    }
    else {
        for (int i = 0; i < print_size; i++) {
        cout << data[i] << " ";
        }
    }
    cout << endl;
    getDuration(start, end); // calculate and print time of algorithm
}

// Bubblesort, merge sort and comparision
void group5()
{
    int dataSize, printSize;
    cout << "Enter the size of data to be sorted: ";
    cin >> dataSize; 
    if (dataSize <= 0){
        cout << "False data size. Please provide a number greater than 0" << endl;
        return;
    }
    
    int choice1, choice2;
    cout << "Which two algorithms you want to compare?" << endl;
    cout << "1. Insertion sort" << endl;
    cout << "2. Quicksort" << endl;
    cout << "3. Bubblesort" << endl;
    cout << "4. Merge sort" << endl;
    cout << "Your choices (seperate with space): ";
    
    cin >> choice1 >> choice2;
    /*if (choice1 == choice2) {
        cout << "Please choose two diffirent algorithms. Try again." << endl;
        return;
    }*/
    if (choice1 > 4 || choice2 > 4){
        cout << "Invalid choice. Please try again." << endl;
        return;
    }

    //generate data
    vector<int> data(dataSize);
    srand(time(0));
    for (int i = 0; i < data.size(); i++) {
        data[i] = rand() % (10 * data.size()); // range of random integers is 10 x given size
    }
    vector<int>data2 = data;

    compare_sort_algorithms(data, data2, choice1, choice2);
}