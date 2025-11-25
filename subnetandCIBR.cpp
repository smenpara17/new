#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

// Split IP into 4 octets
vector<int> splitIP(string ip) {
    vector<int> parts;
    string part;
    stringstream ss(ip);
    while (getline(ss, part, '.'))
        parts.push_back(stoi(part));
    return parts;
}

int main() {
    string ip;
    int cidr;

    cout << "Enter IP Address (Example: 192.168.10.5): ";
    cin >> ip;
    cout << "Enter CIDR (Example: 24 for /24): ";
    cin >> cidr;

    vector<int> octet = splitIP(ip);

    // Calculate subnet mask based on CIDR
    int mask[4] = {0, 0, 0, 0};
    for (int i = 0; i < cidr; i++)
        mask[i/8] |= (1 << (7 - (i % 8)));

    int network[4], broadcast[4];
    for (int i = 0; i < 4; i++) {
        network[i] = octet[i] & mask[i];
        broadcast[i] = network[i] | (~mask[i] & 255);
    }

    int hostBits = 32 - cidr;
    int totalHosts = pow(2, hostBits) - 2;   // usable hosts

    cout << "\n===== CIDR Subnet Calculation =====\n";
    cout << "IP Address:                " << ip << "/" << cidr << endl;

    cout << "Subnet Mask:               ";
    for (int i = 0; i < 4; i++) cout << mask[i] << (i < 3 ? "." : "");

    cout << "\nNetwork Address:           ";
    for (int i = 0; i < 4; i++) cout << network[i] << (i < 3 ? "." : "");

    cout << "\nBroadcast Address:         ";
    for (int i = 0; i < 4; i++) cout << broadcast[i] << (i < 3 ? "." : "");

    cout << "\nUsable Host Range:         ";
    cout << network[0] << "." << network[1] << "." << network[2] << "." << (network[3] + 1);
    cout << "  to  ";
    cout << broadcast[0] << "." << broadcast[1] << "." << broadcast[2] << "." << (broadcast[3] - 1);

    cout << "\nTotal Usable Hosts:        " << totalHosts << endl;
    cout << "Block Size:                " << (int)pow(2, hostBits % 8) << endl;

    cout << "\n====================================\n";
    return 0;
}