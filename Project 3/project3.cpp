
//Compile using: g++ project3_letsinger_awl0024.cpp
//Sources: 
//-Used a tutorials point website to review bubble sort
//-Used Dr. Li's Hints File Provided
//-used c++ documentation to remember how to type cast and read in files properly
//-talked with a class mate about strategies to combine files, advantages/disadvantages of using arrays vs vectors.
//-talked with a class mate about advantages/disadvantages to merging files sorting as values are being added vs
//just sorting the output array once everything is combined
//-used other students posts on piazza to troubleshoot errors I was getting

#include <fstream>
#include <iostream>
using namespace std;

//This number can be changed to accomodate different text file sizes. was provided in dr. Li's hints
//the way the program works is by only utilizing parts of arrays all defined with size MAX_SIZE
//This way arrays do not need to be resized.
const int MAX_SIZE = 100; 

//readFile reads in the contents of the text file. Is pass by reference so populates array.
int readFile(int inputArray[], ifstream& instream) {
    int index = 0;
    instream >> inputArray[index];
    while (!instream.eof()) {
        index++;
        instream >> inputArray[index];
    }
    return index;
}
//checkFile makes sure that the file opened correctly and can be read
bool checkFile(string file) {
    
    ifstream stream;
    stream.open(file.c_str());
    
    if(stream.fail()) {
        stream.close();
        return false;
    }
    stream.close();
    return true;
}
//writeFile writes the contents to the new file. Will create new file if needed
void writefile(int outputArray[], int outputArraySize) {
    
    ofstream outstream;
    string outputFile;
    
    cout << "Enter the output file name: ";
    cin >> outputFile;
    //need to type cast the name of the file
    outstream.open((char*)outputFile.c_str());
    if (outstream.fail()) {
		cout << "Error: Unable to Write to File";
	}
	else { 	
        for (int i = 0; i < outputArraySize; i++) {
            outstream << outputArray[i] << "endl";
        }
    }
    outstream.close();

    cout << "*** Please check the file - " << outputFile << " ***\n";
}

//sorts an array using bubble sort. Not the most efficient but easy to implement and debug  
void bubbleSort(int array[], int size) {
    
    int temp;  
    for (int i = 0; i < size-1; i++) {     
      
    // Last i elements are already in place  
        for (int j = 0; j < size-i-1; j++) {
            if (array[j] > array[j+1]) { 
                temp = array[j];
                array[j]= array[j+1];
                array[j+1]= temp;
            }
        }
    }
} 
//merge arrays combines the contents of the input arrays into an output arrays
int mergeArrays(int inputArray1[], int inputArray1Size, int inputArray2[], int inputArray2Size, int outputArray[]) {
    int outputArraySize = inputArray1Size + inputArray2Size;
    //the following for loops put all of the values into a single array
    for (int i = 0; i < inputArray1Size; i++) {
        outputArray[i] = inputArray1[i];
    }
    //following for loop picks up where the previous left off but pulls from second file.
    for (int i = 0; i < inputArray2Size; i++) {
        outputArray[i+inputArray1Size] = inputArray2[i];
    }

    return outputArraySize;
}

//main is used to call all functions and organize data to be printed.
//starts with file1, then file2, and then the output file
int main() {
    int inputArray1[MAX_SIZE];
    int inputArray1Size;
    int inputArray2[MAX_SIZE];
    int inputArray2Size;
    cout << endl << "*** Welcome to Alec's sorting program ***\n";

    ifstream instream;
    string fileName1;
    //used a do while loop so automatically runs at least once
    do {
        cout << "Enter the first input file name: ";
        cin >> fileName1;
        instream.open((char*)fileName1.c_str()); //casts fileName1 to a string
        if (cin.fail() || !checkFile(fileName1)) {
            cout << "Error: Please try again\n";
            cout << endl;
        }
    } while (cin.fail() || !checkFile(fileName1));
    
    inputArray1Size = readFile(inputArray1, instream);
    instream.close();

    cout << "The list of " << inputArray1Size << " numbers in file " << fileName1 << " is:\n";
    for (int i = 0; i < inputArray1Size; i++) {
        cout << inputArray1[i] << "\n";
    }
    cout << endl;

    string fileName2;
    do {
        cout << "Enter the second input file name: ";
        cin >> fileName2;
        instream.open((char*)fileName2.c_str());
        if (cin.fail() || !checkFile(fileName2)) {
            cout << "Error: Please try again\n";
            cout << endl;
        }
    } while (cin.fail() || !checkFile(fileName2));
    
    inputArray2Size = readFile(inputArray2, instream);
    instream.close();

    cout << "The list of " << inputArray2Size << " numbers in file " << fileName2 << " is:\n";
    for (int i = 0; i < inputArray2Size; i++) {
        cout << inputArray2[i] << "\n";
    }
    cout << endl;

    //defines the output array as the largest possible size, so don't need to resize.
    int outputArray[MAX_SIZE];
    int outputArraySize = mergeArrays(inputArray1, inputArray1Size, inputArray2, inputArray2Size, outputArray);
    //now that all values are in a single array, they can be sorted.
    bubbleSort(outputArray, outputArraySize);
    //only prints the needed values from the output array.
    cout << "The sorted list of " << outputArraySize << " numbers is:";
    for (int i = 0; i < outputArraySize; i++) {
        cout << " " << outputArray[i];
    }
    cout << endl;

    writefile(outputArray, outputArraySize);

    cout << "*** Goodbye. ***" << endl;
}