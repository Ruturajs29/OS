#include <iostream> //next fit
using namespace std;

void nextFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int j = 0; // To keep track of the last allocated block

    for(int i = 0; i < n; i++) 
        allocation[i] = -1;

    for(int i = 0; i < n; i++) {
        int start = j;  // Store the starting position for each process
        bool allocated = false;

        while (true) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                allocated = true;
                break;
            }
            j = (j + 1) % m;

            // If we return to the start, that means we've tried all blocks
            if (j == start) {
                break;
            }
        }

        // Move to the next block for the next process
        if (allocated) {
            j = (j + 1) % m;
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < n; i++) {
        cout << "   " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1 << endl;
        else
            cout << "Not Allocated" << endl;
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    nextFit(blockSize, m, processSize, n);

    return 0;
}
