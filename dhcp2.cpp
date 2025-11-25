#include <iostream>
#include <vector>
#include <string>
using namespace std;

class DHCPServer {
private:
    vector<string> ipPool;
    vector<bool> allocated;

public:
    DHCPServer(string networkPrefix, int startHost, int endHost) {
        for (int i = startHost; i <= endHost; i++) {
            ipPool.push_back(networkPrefix + to_string(i));
            allocated.push_back(false);
        }
    }

    string requestIP(int clientID) {
        cout << "\nClient " << clientID << " → DHCP Discover\n";

        for (int i = 0; i < ipPool.size(); i++) {
            if (!allocated[i]) {
                cout << "Server → DHCP Offer: " << ipPool[i] << endl;
                cout << "Client " << clientID << " → DHCP Request: " << ipPool[i] << endl;

                allocated[i] = true;
                cout << "Server → DHCP ACK: " << ipPool[i] << " assigned.\n";

                return ipPool[i];
            }
        }

        cout << "No free IP available!\n";
        return "NULL";
    }

    void releaseIP(string ip) {
        for (int i = 0; i < ipPool.size(); i++) {
            if (ipPool[i] == ip) {
                allocated[i] = false;
                cout << "IP released: " << ip << endl;
                return;
            }
        }
        cout << "IP not found!\n";
    }

    void displayStatus() {
        cout << "\n--- DHCP IP Pool Status ---\n";
        for (int i = 0; i < ipPool.size(); i++) {
            cout << ipPool[i] << " → " 
                 << (allocated[i] ? "Allocated" : "Free") << endl;
        }
        cout << "---------------------------\n";
    }
};

int main() {
    string prefix;
    int startHost, endHost;

    cout << "Enter Network Prefix (e.g., 192.168.1.): ";
    cin >> prefix;

    cout << "Enter Start host number: ";
    cin >> startHost;

    cout << "Enter End host number: ";
    cin >> endHost;

    DHCPServer server(prefix, startHost, endHost);

    int choice;
    do {
        cout << "\n--- DHCP MENU ---\n";
        cout << "1. Request IP\n";
        cout << "2. Release IP\n";
        cout << "3. Display Pool Status\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        if (choice == 1) {
            int clientID;
            cout << "Enter client ID: ";
            cin >> clientID;
            server.requestIP(clientID);
        }
        else if (choice == 2) {
            string ip;
            cout << "Enter IP to release: ";
            cin >> ip;
            server.releaseIP(ip);
        }
        else if (choice == 3) {
            server.displayStatus();
        }
        else if (choice == 0) {
            cout << "Exiting...\n";
        }
        else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}

