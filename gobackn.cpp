#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    int totalFrames, windowSize;

    cout << "Enter total number of frames: ";
    cin >> totalFrames;

    cout << "Enter window size: ";
    cin >> windowSize;

    srand(time(NULL));

    int sent = 0;

    while (sent < totalFrames) {

        cout << "\n--- Sending Window ---\n";

        // Send frames in the current window
        for (int i = 0; i < windowSize && sent + i < totalFrames; i++) {
            cout << "Sending Frame " << sent + i << endl;
        }

        // Simulate ACK/NACK
        int lostFrame = -1;

        // Randomly decide whether a frame is lost (10% chance)
        for (int i = 0; i < windowSize && sent + i < totalFrames; i++) {
            int x = rand() % 10;
            if (x < 2) {   // 20% probability of loss
                lostFrame = sent + i;
                break;
            }
        }

        if (lostFrame == -1) {
            // All frames received successfully
            cout << "All frames acknowledged.\n";
            sent += windowSize;   // Move window
        } else {
            // A frame is lost → Go-Back-N retransmission
            cout << "Frame " << lostFrame << " lost! No ACK received.\n";
            cout << "Retransmitting window starting from Frame " << lostFrame << "...\n";
            sent = lostFrame;
        }
    }

    cout << "\nAll frames successfully transmitted!\n";

    return 0;
}
