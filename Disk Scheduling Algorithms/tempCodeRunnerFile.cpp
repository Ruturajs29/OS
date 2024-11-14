#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits.h>

using namespace std;

void SSTF(vector<int> &requests, int head) {
    int seek_operations = 0;
    vector<bool> visited(requests.size(), false);

    cout << "SSTF Order of execution: " << head;
    for (int i = 0; i < requests.size(); ++i) {
        int min_distance = INT_MAX;
        int index = -1;

        for (int j = 0; j < requests.size(); ++j) {
            if (!visited[j] && abs(requests[j] - head) < min_distance) {
                min_distance = abs(requests[j] - head);
                index = j;
            }
        }

        visited[index] = true;
        cout << " -> " << requests[index];
        seek_operations += abs(head - requests[index]);
        head = requests[index];
    }
    cout << "\nTotal Seek Operations: " << seek_operations << endl;
}

int main() {
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    SSTF(requests, head);
    return 0;
}
