#include <iostream>
using namespace std;

/*  
    XOR operation between the current dividend window 
    and the divisor/generator polynomial.
*/
void xorGen(string &dividend, const string &divisor) {
    for(int i = 0; i < divisor.size(); i++) {
        dividend[i] = (dividend[i] == divisor[i]) ? '0' : '1';
    }
}

/*
    CRC generator function:
    Performs modulo-2 division and returns the remainder.
*/
string crcGenerator(string data, string gen) {
    int n = gen.size();                   // length of generator
    string temp = data.substr(0, n);      // initial window of size 'n'

    // Perform division until all bits are used
    for(int i = n; i < data.size(); i++) {
        // If leftmost bit is 1, XOR with generator
        if(temp[0] == '1')
            xorGen(temp, gen);
        else
            xorGen(temp, string(n, '0'));   // else XOR with 000..0

        // Remove first bit and append the next bit from data
        temp.erase(0, 1);
        temp.push_back(data[i]);
    }

    // Final XOR for the last window
    if(temp[0] == '1')
        xorGen(temp, gen);
    else
        xorGen(temp, string(n, '0'));

    // Return remainder (last n-1 bits)
    return temp.substr(1);
}

int main() {
    string data, gen;
    
    cout << "\nEnter data bits: ";
    cin >> data;

    cout << "Enter generator bits: ";
    cin >> gen;

    int r = gen.size() - 1;                // degree of generator

    // Append zeros (polynomial multiplication)
    string dataWithZeroes = data + string(r, '0');

    // Generate CRC remainder
    string rem = crcGenerator(dataWithZeroes, gen);

    // Encoded frame = data + remainder
    string encodedData = data + rem;

    cout << "\nCRC Remainder: " << rem;
    cout << "\nEncoded Data (data + CRC): " << encodedData << endl;

    // ---- Receiver side check ----
    string received;
    cout << "\nEnter received data: ";
    cin >> received;

    // Recalculate CRC for received bits
    string check = crcGenerator(received, gen);

    bool error = false;
    for(char c : check) {
        if(c != '0') {
            error = true;
            break;
        }
    }

    if(error)
        cout << "\nError detected in received data!\n";
    else
        cout << "\nNo error detected.\n";

    return 0;
}
