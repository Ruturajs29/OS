#include <iostream>
#include <vector>
using namespace std;

void clockPageReplacement(int pages[], int n, int capacity) {
    vector<int> frames(capacity, -1);
    vector<bool> secondChance(capacity, false);
    int pointer = 0, pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;

        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                secondChance[j] = true;
                found = true;
                break;
            }
        }

        if (!found) {
            while (secondChance[pointer]) {
                secondChance[pointer] = false;
                pointer = (pointer + 1) % capacity;
            }
            frames[pointer] = page;
            secondChance[pointer] = true;
            pointer = (pointer + 1) % capacity;
            pageFaults++;
        }
    }
    cout << "Total Page Faults (Clock): " << pageFaults << endl;
}

int main() {
    int pages[] = {7, 1, 0, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;
    clockPageReplacement(pages, n, capacity);
    return 0;
}
