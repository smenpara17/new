#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int a, b, c, d;          // IP octets
    int basePrefix = 24;     // we assume /24 base network
    int n;                   // number of subnets

    cout << "Enter Base Network (Class C) as four octets (e.g., 192 168 1 0): ";
    cin >> a >> b >> c >> d;   // d should be 0 usually for network id

    cout << "Enter number of subnets: ";
    cin >> n;

    vector<int> hosts(n);
    cout << "Enter required hosts for each subnet:\n";
    for (int i = 0; i < n; i++) {
        cout << "Subnet " << i + 1 << " hosts: ";
        cin >> hosts[i];
    }

    // Subnet IDs (to keep track of original order)
    vector<int> id(n);
    for (int i = 0; i < n; i++) id[i] = i + 1;

    // Sort by hosts descending, but keep IDs aligned
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (hosts[i] < hosts[j]) {
                swap(hosts[i], hosts[j]);
                swap(id[i], id[j]);
            }
        }
    }

    int current = d;          // start of free address space in last octet (usually 0)
    int totalAddresses = 256; // total addresses in a /24 block

    cout << "\n=========== Simple VLSM (Class C /24) ===========\n";
    cout << "Base Network: " << a << "." << b << "." << c << ".0"
         << "/" << basePrefix << "\n\n";

    for (int i = 0; i < n; i++) {
        int needed = hosts[i] + 2; // include network + broadcast
        int blockSize = 1;
        int hostBits = 0;

        // Find smallest power of 2 >= needed
        while (blockSize < needed && hostBits <= 8) {
            blockSize *= 2;
            hostBits++;
        }

        if (hostBits > 8) {
            cout << "Cannot allocate subnet " << id[i]
                 << " (too many hosts for /24).\n\n";
            continue;
        }

        // Check if enough space left in this /24
        if (current + blockSize > totalAddresses) {
            cout << "Not enough address space left in /24 for subnet "
                 << id[i] << ".\n\n";
            continue;
        }

        int net = current;
        int bcast = current + blockSize - 1;
        int firstHost = net + 1;
        int lastHost = bcast - 1;

        int prefix = 32 - hostBits; // new CIDR

        cout << "Subnet " << id[i] << " (required hosts: " << hosts[i] << ")\n";
        cout << "  Network ID : " << a << "." << b << "." << c << "." << net
             << "/" << prefix << "\n";
        cout << "  First Host : " << a << "." << b << "." << c << "." << firstHost << "\n";
        cout << "  Last Host  : " << a << "." << b << "." << c << "." << lastHost << "\n";
        cout << "  Broadcast  : " << a << "." << b << "." << c << "." << bcast << "\n";
        cout << "  Block Size : " << blockSize
             << " addresses (usable: " << blockSize - 2 << ")\n\n";

        current += blockSize; // move pointer for next subnet
    }

    cout << "=================================================\n";
    return 0;
}

