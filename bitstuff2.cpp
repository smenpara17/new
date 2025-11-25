#include <iostream>
#include <string>
using namespace std;

// Sender side: Bit Stuffing based on delimiter
string bitStuff(string data, string delimiter) {
    string stuffed = "";
    int matchIndex = 0;

    for (char bit : data) {
        stuffed += bit;

        // check match with delimiter
        if (bit == delimiter[matchIndex]) {
            matchIndex++;
        } else {
            matchIndex = (bit == delimiter[0]) ? 1 : 0;
        }

        // If full delimiter matched → stuff a '0'
        if (matchIndex == delimiter.size()) {
            stuffed += '0';   // Stuffed bit
            matchIndex = 0;
        }
    }
    return stuffed;
}

// Receiver side: Bit De-Stuffing based on delimiter
string bitDeStuff(string data, string delimiter) {
    string destuff = "";
    int matchIndex = 0;

    for (int i = 0; i < data.size(); i++) {
        destuff += data[i];

        if (data[i] == delimiter[matchIndex])
            matchIndex++;
        else
            matchIndex = (data[i] == delimiter[0]) ? 1 : 0;

        // When delimiter matched → skip stuffed '0'
        if (matchIndex == delimiter.size()) {
            i++;           // skip stuffed bit
            matchIndex = 0;
        }
    }
    return destuff;
}

int main() {
    string data, delimiter;

    cout << "Enter binary data: ";
    cin >> data;

    cout << "Enter delimiter pattern for framing: ";
    cin >> delimiter;

    string stuffed = bitStuff(data, delimiter);
    cout << "Stuffed Data: " << stuffed << endl;

    string destuffed = bitDeStuff(stuffed, delimiter);
    cout << "De-stuffed Data: " << destuffed << endl;

    return 0;
}

