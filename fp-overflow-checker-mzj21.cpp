#include <iostream>
#include <iomanip>
#include <cstdlib> //for stof
#include <climits> //for INT_MAX, INT_MIN
#include <cmath> //for pow
#include <bitset>   // for bitset
using namespace std;


//printIEEE prints the bits in IEEE format
void printIEEE(unsigned int bits) {
    bitset<32> b(bits);
    //sign
    cout << b.to_string().substr(0, 1) << " ";
    //exponent
    cout << b.to_string().substr(1, 8) << " ";
    //fraction
    cout << b.to_string().substr(9, 23) << endl;
}

//getExponent gets the exponent of input bit value
int getExponent(unsigned int bits) {
    //masks around 23–30
    unsigned int mask = 0x7F800000;
    //masks the bits, then moves so it only shows relevant ones.
    unsigned int outcome = (bits & mask) >> 23;
    
    return outcome;
}

int main(int argc, char* argv[])
{
    //check number of arguments, end program and output issue if wrong.
    //argc contains the file name and inputs from the command line, so one more
    //than the number of inputs we should have.
    if (argc != 3) {
        cout << "usage:" << endl;
        cout << "       ./fp_overflow_checker loop_bound loop_counter" << endl;
        cout << endl;
        cout << "       loop_bound is a positive floating-point value" << endl;
        cout << "       loop_counter is a positive floating-point value";
        cout << endl << endl;
        
        return 1;
    }
    
    //overflow tracking boolean
    bool overflowing = false;
    
    //converts arguments to float
    float loopBound;
    float loopIncrement;
    try 
    {
        loopBound = stof(argv[1]);
        loopIncrement = stof(argv[2]);
    }
    catch (const invalid_argument&) 
    {
        cout << "usage:" << endl;
        cout << "       ./fp_overflow_checker loop_bound loop_counter" << endl;
        cout << endl;
        cout << "       loop_bound is a positive floating-point value" << endl;
        cout << "       loop_counter is a positive floating-point value";
        cout << endl << endl;
        
        return 1;
    }
    
    //converts float to 32 bit int
    //unsigned int bits = *reinterpret_cast<unsigned int*>(&value);
    //does not change the original float variables
    unsigned int boundBits = *reinterpret_cast<unsigned int*>(&loopBound);
    unsigned int incBits = *reinterpret_cast<unsigned int*>(&loopIncrement);
    
    //prints the IEEE formatting
    cout << "Loop bound:   ";
    printIEEE(boundBits);
    cout << "Loop counter: ";
    printIEEE(incBits);
    cout << endl;
    
    //checking for increment overflow
    unsigned int boundExp = getExponent(boundBits);
    unsigned int incExp = getExponent(incBits);
    //calculates difference
    if (incExp < boundExp - 23) 
    {
        overflowing = true;
    }

    
    //checking for unsigned integer overflow
    unsigned int unintLoopBound = static_cast<unsigned int>(loopBound);
    unsigned int unintLoopIncrement = static_cast<unsigned int>(loopIncrement);

    if (unintLoopBound + unintLoopIncrement < unintLoopBound) { overflowing = true; }
    
    //checking for signed integer overflow
    int sintLoopBound = static_cast<int>(loopBound);
    int sintLoopIncrement = static_cast<int>(loopIncrement);

    if ((sintLoopIncrement > 0 && sintLoopBound > INT_MAX - sintLoopIncrement) ||
        (sintLoopIncrement < 0 && sintLoopBound < INT_MIN - sintLoopIncrement)) 
        { overflowing = true; }
    
    if (overflowing == true) { cout << "Warning: Possible overflow!" << endl; }
    else
    {
        cout << "There is no overflow!" << endl;
        
        return 0;
    }
    
    //calculate the threshold
    boundExp -= 127;
    incExp -= 127;
    int thresholdExp = boundExp - incExp - 2;
    unsigned int threshBits = (thresholdExp + 127) << 23;
    float threshold = *reinterpret_cast<float*>(&threshBits);
    
    //return threshold in IEEE AND base 10
    //base 10
    cout << "Overflow threshold:" << endl;
    cout << "        " << threshold << endl;

    //IEEE
    cout << "        ";
    printIEEE(threshBits);
    
    return 0;
}