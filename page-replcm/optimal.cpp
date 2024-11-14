#include <iostream> //OPTIMAL 
#include <vector>
#include <algorithm>  
using namespace std;

int predict(int pages[], vector<int>& frame, int n, int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < frame.size(); i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n) return i;
    }
    return (res == -1) ? 0 : res;
}

void optimalPageReplacement(int pages[], int n, int capacity) {
    vector<int> frame;
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        if (find(frame.begin(), frame.end(), pages[i]) == frame.end()) {
            if (frame.size() < capacity) {
                frame.push_back(pages[i]);
            } else {
                int j = predict(pages, frame, n, i + 1);
                frame[j] = pages[i];
            }
            pageFaults++;
        }
    }
    cout << "Total Page Faults (Optimal): " << pageFaults << endl;
}

int main() {
    int pages[] = {7, 1, 0, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;
    optimalPageReplacement(pages, n, capacity);
    return 0;
}

