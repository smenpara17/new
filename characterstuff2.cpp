#include <iostream>
#include <string>
using namespace std;

string escapeChar; // escape sequence (ex: "DLE")
string startFlag;  // start delimiter (ex: "STX")
string endFlag;    // end delimiter (ex: "ETX")

// Sender: Character Stuffing
string charStuff(string data) {
    string stuffed = escapeChar + startFlag;  // Start frame

    for (int i = 0; i < data.length(); i++) {
        // If escape appears in data → stuff another escape
        if (data.substr(i, escapeChar.size()) == escapeChar) {
            stuffed += escapeChar;
        }
        stuffed += data[i];
    }

    stuffed += escapeChar + endFlag; // End frame
    return stuffed;
}

// Receiver: De-stuffing
string charDeStuff(string data) {
    string destuff = "";

    // Skip start flag (escape + start)
    int i = escapeChar.size() + startFlag.size();

    // End boundary (exclude escape + end flag)
    int endLimit = data.size() - (escapeChar.size() + endFlag.size());

    while (i < endLimit) {
        // If "escape escape" → skip one
        if (data.substr(i, escapeChar.size()) == escapeChar &&
            data.substr(i + escapeChar.size(), escapeChar.size()) == escapeChar) {

            i += escapeChar.size(); // Skip stuffed escape
        }

        destuff += data[i];
        i++;
    }

    return destuff;
}

int main() {
    string data;

    cout << "Enter Escape Sequence (e.g., DLE): ";
    cin >> escapeChar;

    cout << "Enter Start Flag (e.g., STX): ";
    cin >> startFlag;

    cout << "Enter End Flag (e.g., ETX): ";
    cin >> endFlag;

    cin.ignore(); // Clear leftover newline
    
    cout << "Enter data string: ";
    getline(cin, data);

    string stuffed = charStuff(data);
    cout << "Stuffed Data: " << stuffed << endl;

    string destuffed = charDeStuff(stuffed);
    cout << "De-stuffed Data: " << destuffed << endl;

    return 0;
}

