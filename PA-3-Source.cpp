// Daniel Forbes
// Donald Moor
// Michael Zuppardo


#include <iostream> // for I/O
#include <fstream> // for outputing text to csv files
#include <chrono> // for measuring time intervals
#include <math.h> // for rounding and calculating logarithms


std::ofstream fout; // outputs to open file
std::chrono::steady_clock::time_point t1; // start time
std::chrono::steady_clock::time_point t2; // end time
int t3; // time delta

int fibR(int); // recursive Fibonacci method
int fibDP(int); // dynamic programming Fibonacci method


int main()
{
    int method = -1;
    while ((method != 1 && method != 2) && method != 3)
    {
        std::cout << "Use recursive method (1), the dynamic programming method (2), or exit (3)?\n";
        std::cin >> method;
        if ((method != 1 && method != 2) && method != 3)
        {
            std::cout << "Invlaid input.\n";
        }
    }
    if (method == 3)
    {
        std::cout << "Exiting.\n";
        return 0;
    }
    int fibNum = -1;
    while (fibNum < 0)
    {
        std::cout << "Enter the desired*, nonnegative Fibonacci number:\n*Note that input '0' will return the first value in the Fibonacci sequence, input '1' the second, and so forth.\n";
        std::cin >> fibNum;
        if (fibNum < 0)
        {
            std::cout << "Invlaid input.\n";
        }
    }
    if (method == 1)
    {
        std::cout << "Fibonacci number " << fibNum << " is " << fibR(fibNum) << "\n";
    }
    if (method == 2)
    {
        std::cout << "Fibonacci number " << fibNum << " is " << fibDP(fibNum) << "\n";
    }

    return 0;
}


/********************************** methods **********************************/

// recurssive Fibonacci method. Note that n = 0 will return the first value in the Fibonacci sequence, n = 1 the second, and so forth
int fibR(int n)
{
    if (n == 0 || n == 1) { return 1; }
    return fibR(n - 1) + fibR(n - 2);
}

// TODO: Implement DP Algorithm
int fibDP(int n)
{
    return -1;
}
