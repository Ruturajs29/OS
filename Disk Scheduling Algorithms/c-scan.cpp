#include <iostream> //C-SCAN 
#include <vector>
#include <algorithm>

using namespace std;

void CSCAN(vector<int> &requests, int head, int disk_size) {
    int seek_operations = 0;
    requests.push_back(0);
    requests.push_back(disk_size - 1);
    sort(requests.begin(), requests.end());

    int pos = distance(requests.begin(), lower_bound(requests.begin(), requests.end(), head));
    cout << "C-SCAN Order of execution: " << head;

    for (int i = pos; i < requests.size(); ++i) {
        cout << " -> " << requests[i];
        seek_operations += abs(head - requests[i]);
        head = requests[i];
    }

    // Jump to the beginning of the disk
    head = 0;
    seek_operations += requests.back();
    cout << " -> " << head;

    for (int i = 0; i < pos; ++i) {
        cout << " -> " << requests[i];
        seek_operations += abs(head - requests[i]);
        head = requests[i];
    }

    cout << "\nTotal Seek Operations: " << seek_operations << endl;
}

int main() {
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    int disk_size = 200;
    CSCAN(requests, head, disk_size);
    return 0;
}
