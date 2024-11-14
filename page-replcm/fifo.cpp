#include <iostream>  //FIFO PAGE REPLM
#include <queue>
#include <unordered_set>
using namespace std;

void fifoPageReplacement(int pages[], int n, int capacity) {
    unordered_set<int> s;
    queue<int> indexes;
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        if (s.size() < capacity) {
            if (s.find(pages[i]) == s.end()) {
                s.insert(pages[i]);
                indexes.push(pages[i]);
                pageFaults++;
            }
        } else { 
            if (s.find(pages[i]) == s.end()) {
                int val = indexes.front();
                indexes.pop();
                s.erase(val);
                s.insert(pages[i]);
                indexes.push(pages[i]);
                pageFaults++;
            }
        }
    }
    cout << "Total Page Faults (FIFO): " << pageFaults << endl;
}

int main() {
    int pages[] = {7, 1, 0, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;
    fifoPageReplacement(pages, n, capacity);
    return 0;
}
