// Daniel Forbes
// Donald Moor
// Michael Zuppardo

#include <iostream>     // for I/O
#include <fstream>      // for outputing text to csv files
#include <chrono>       // for measuring time intervals
#include <math.h>       // for rounding and calculating logarithms
#include <string>
using namespace std;

ofstream fout;                          // outputs to open file
chrono::steady_clock::time_point t1;    // start time
chrono::steady_clock::time_point t2;    // end time

int fibR(int);  // recursive Fibonacci method
int fibDP(int); // dynamic programming Fibonacci method
void sheet();   // fill out the spreadsheet

// This program allows a user to choose between the recursive or dynamic programming algorithms
// to calculate the value of a Fibonacci sequence. It first asks which algorithm the user wishes
// to use, and asks for the sequence value. Continues to run until the user specifies that they
// wish to quit; user can cycle between both methods in the same run instance.
int main()
{
    string prompt = "Use recursive method(1), the dynamic programming method(2), or exit(3) ? \n";
    string input;       // User's raw input
    int method = -1;    // User's algorithm selection input.
    int fibNum = -1;    // User's Fibonacci number input.

    // Generate the template spreadsheet.
    cout << "Creating template spreadsheet..." << endl;
    sheet();
    cout << "Spreadsheet created!\n" << endl;
    cout << prompt;

    // Asks user for their desired algorithm method.
    while (method == -1) {
        getline(cin, input);

        // Ensures there are no non-digits in the input.
        if (input.find_first_not_of("0123456789") == string::npos) {
            method = stoi(input);
        }

        // Ensures input is either 1 or 2.
        switch (method) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                cout << "Exiting.\n";
                return 0;
            default:
                cout << "Invalid input.\n";
                method = -1;
                continue;
        }

        cout << "Enter the desired non-negative Fibonacci number (input \"..\" to exit)\n"
            "(Note that input '0' will return the first value in the Fibonacci sequence, input '1' the second, and so forth).\n";
        fibNum = -1;

        // Asks user for their desired Fibonacci number.
        while (fibNum == -1) {
            getline(cin, input);

            // Go back to method selection if input = ".."
            if (input == "..") {
                cout << prompt;
                method = -1;
                break;
            }

            // Ensures there are no non-digits in the input.
            if (input.find_first_not_of("0123456789") == string::npos) {
                fibNum = stoi(input);
            }

            // If fibNum = -1, that means the input was invalid somehow.
            // Otherwise, run the program.
            switch (fibNum) {
                case -1:
                    cout << "Invalid input.\n";
                    break;
                default:
                    method == 1 ?
                        cout << "Fibonacci number " << fibNum << " is " << fibR(fibNum) << "\n" :   // method == 1
                        cout << "Fibonacci number " << fibNum << " is " << fibDP(fibNum) << "\n";   // method == 2
                    fibNum = -1;
                    break;
            }
        }   
    }
    return 0;
}


/********************************** methods **********************************/

// Recursive Fibonacci method. Note that n = 0 will return the first value in the Fibonacci sequence, n = 1 the second, and so forth
int fibR(int n)
{
    if (n == 0 || n == 1) { return 1; }
    return fibR(n - 1) + fibR(n - 2);
}

// Dynamic Programming algorithm.
int fibDP(int maxNum)
{
    int fib1 = 0;
    int fib2 = 1;
    int sum;

    if (maxNum == 1 || maxNum == 0) {
        return 1;
    }
    else {
        for (int i = 0; i < maxNum - 1; i++) {
            sum = fib1 + fib2;
            fib1 = fib2; // changes the first num to the latest
            fib2 = sum; // changes the second num to the newest
        }
        return sum;
    }
}

// Method to generate the excel spreadsheet as specified
// by the instructions.
void sheet() {
    int values[7] = { 10, 12, 15, 20, 23, 25, 30 }; // n values
    int result = -1;    // Stores algorithm calculations
    int timeR = -1;     // Time for recursive algorithm
    int timeDP = -1;    // Time for dp algorithm
    
    fout.open("Fibonacci_Time.csv");
    fout << "n,"
        << "F(n),"
        << "T1: Time spent on the recursive algorithm (nanoseconds),"
        << "T2: Time spent on the DP algorithm (nanoseconds),"
        << "Value of (2^n)/n,"
        << "Value of T1/T2\n";

    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        // Run recursive algorithm and time how long it takes.
        t1 = chrono::steady_clock::now();
        result = fibR(values[i]);
        t2 = chrono::steady_clock::now();
        timeR = std::chrono::duration_cast<std::chrono::duration<int64_t, std::ratio<1, 1000000000/*nanoseconds*/>>>(t2 - t1).count();

        // Run DP algorithm and time how long it takes.
        t1 = chrono::steady_clock::now();
        result = fibDP(values[i]);
        t2 = chrono::steady_clock::now();
        timeDP = std::chrono::duration_cast<std::chrono::duration<int64_t, std::ratio<1, 1000000000/*nanoseconds*/>>>(t2 - t1).count();

        // Format results to spreadsheet.
        fout << values[i] << ","
            << result << ","
            << timeR << "ns,"
            << timeDP << "ns,";
        fout.precision(0);
        fout << scientific << (pow(2, values[i]) / values[i]) << ","
            << scientific << (timeR / timeDP) << "e+00\n";
    }
    fout.close();
}
