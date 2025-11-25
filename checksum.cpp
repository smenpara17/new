#include <iostream>
#include <vector>
using namespace std;

// Function to perform 1's complement binary addition of two equal-length bit strings
string onesComplementAdd(string a, string b) {
    int n = a.size();
    string result(n, '0');
    int carry = 0;

    // Add from right to left
    for (int i = n - 1; i >= 0; i--) {
        int bit1 = a[i] - '0';
        int bit2 = b[i] - '0';
        int sum = bit1 + bit2 + carry;

        result[i] = (sum % 2) + '0';
        carry = sum / 2;
    }

    // End-around carry (if any)
    while (carry) {
        // Add carry to the result (1's complement)
        for (int i = n - 1; i >= 0; i--) {
            if (result[i] == '0') {
                result[i] = '1';
                carry = 0;
                break;
            } else {
                result[i] = '0';
                carry = 1;
            }
        }
    }

    return result;
}

// Function to compute checksum (1's complement of sum of all segments)
string computeChecksum(const vector<string> &segments) {
    string sum = segments[0];

    for (int i = 1; i < segments.size(); i++) {
        sum = onesComplementAdd(sum, segments[i]);
    }

    // 1's complement of sum
    for (int i = 0; i < sum.size(); i++) {
        sum[i] = (sum[i] == '0') ? '1' : '0';
    }

    return sum;
}

// Check if all bits are 1 (for receiver validation)
bool isAllOnes(const string &s) {
    for (char c : s) {
        if (c != '1')
            return false;
    }
    return true;
}

int main() {
    int n;
    cout << "---- Sender Side ----\n";
    cout << "Enter number of data segments: ";
    cin >> n;

    vector<string> data(n);
    cout << "Enter the data segments (equal length binary strings):\n";
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    // Compute checksum
    string checksum = computeChecksum(data);
    cout << "\nComputed Checksum: " << checksum << endl;

    cout << "\n---- Receiver Side ----\n";
    int m;
    cout << "Enter number of segments received (including checksum): ";
    cin >> m;

    vector<string> received(m);
    cout << "Enter the received segments:\n";
    for (int i = 0; i < m; i++) {
        cin >> received[i];
    }

    // Add all received segments (including checksum)
    string sum = received[0];
    for (int i = 1; i < m; i++) {
        sum = onesComplementAdd(sum, received[i]);
    }

    cout << "\nSum at Receiver: " << sum << endl;

    if (isAllOnes(sum))
        cout << "Result: No error detected in received data.\n";
    else
        cout << "Result: Error detected in received data!\n";

    return 0;
}