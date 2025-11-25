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

    // Track which frames have been successfully received (ACKed)
    vector<bool> received(totalFrames, false);

    int base = 0;  // left edge of the sliding window

    while (base < totalFrames) {

        cout << "\n--- Sending Window (from frame " << base
             << " to " << min(base + windowSize - 1, totalFrames - 1) << ") ---\n";

        // 1) Send only the frames in the current window that are NOT yet ACKed
        for (int i = base; i < base + windowSize && i < totalFrames; i++) {
            if (!received[i]) {
                cout << "Sending frame " << i << endl;
            } else {
                cout << "Frame " << i << " already ACKed earlier. Skipping send.\n";
            }
        }

        // 2) Simulate channel behavior (loss or success) only for unsent/unACKed frames
        for (int i = base; i < base + windowSize && i < totalFrames; i++) {
            if (received[i]) continue;  // already ACKed, nothing to do

            int x = rand() % 10;   // random number 0–9

            if (x < 2) {           // ~20% probability of loss
                cout << "Frame " << i << " lost! Will retransmit later.\n";
            } else {
                cout << "Frame " << i << " received. Sending ACK...\n";
                received[i] = true;
            }
        }

        // 3) Slide the window forward over consecutively ACKed frames
        while (base < totalFrames && received[base]) {
            base++;
        }
    }

    cout << "\nAll frames successfully transmitted (Selective Repeat)!\n";

    return 0;
}

