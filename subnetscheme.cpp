#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

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
    int subnets;

    cout << "Enter Network Address (e.g., 192.168.1.0): ";
    cin >> ip;
    cout << "Enter Required Number of Subnets: ";
    cin >> subnets;

    vector<int> octet = splitIP(ip);

    // Find bits to borrow
    int bits = ceil(log2(subnets));
    int cidr = 24 + bits; // default class C assumption
    int hostBits = 32 - cidr;
    int subnetSize = pow(2, hostBits);

    cout << "\n===== Subnetting Scheme =====\n";
    cout << "Network Address:         " << ip << endl;
    cout << "Required Subnets:        " << subnets << endl;
    cout << "Borrowed Bits:           " << bits << endl;
    cout << "New CIDR:                /" << cidr << endl;
    cout << "Hosts per Subnet:        " << subnetSize - 2 << " usable hosts" << endl;

    cout << "\n--- Subnets List ---\n";

    int networkStart = octet[3]; // host part
    int subnetCount = pow(2, bits);

    for(int i = 0; i < subnetCount; i++) {
        int net = i * subnetSize;
        int bcast = net + subnetSize - 1;

        cout << "\nSubnet " << i + 1 << ":\n";
        cout << "Network ID     : " << octet[0] << "." << octet[1] << "." << octet[2] << "." << net << endl;
        cout << "First Host     : " << octet[0] << "." << octet[1] << "." << octet[2] << "." << net + 1 << endl;
        cout << "Last Host      : " << octet[0] << "." << octet[1] << "." << octet[2] << "." << bcast - 1 << endl;
        cout << "Broadcast ID   : " << octet[0] << "." << octet[1] << "." << octet[2] << "." << bcast << endl;
    }

    cout << "\n==============================\n";
    return 0;
}