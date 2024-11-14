#include <iostream> //SCAN 
#include <vector>
#include <algorithm>

using namespace std;

void SCAN(vector<int> &requests, int head, int disk_size, string direction) {
    int seek_operations = 0;
    requests.push_back(0);
    requests.push_back(disk_size - 1);
    sort(requests.begin(), requests.end());

    int pos = distance(requests.begin(), lower_bound(requests.begin(), requests.end(), head));
    cout << "SCAN Order of execution: " << head;

    if (direction == "left") {
        for (int i = pos; i >= 0; --i) {
            cout << " -> " << requests[i];
            seek_operations += abs(head - requests[i]);
            head = requests[i];
        }
        for (int i = pos + 1; i < requests.size(); ++i) {
            cout << " -> " << requests[i];
            seek_operations += abs(head - requests[i]);
            head = requests[i];
        }
    } else if (direction == "right") {
        for (int i = pos; i < requests.size(); ++i) {
            cout << " -> " << requests[i];
            seek_operations += abs(head - requests[i]);
            head = requests[i];
        }
        for (int i = pos - 1; i >= 0; --i) {
            cout << " -> " << requests[i];
            seek_operations += abs(head - requests[i]);
            head = requests[i];
        }
    }

    cout << "\nTotal Seek Operations: " << seek_operations << endl;
}

int main() {
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    int disk_size = 200;
    string direction = "left";
    SCAN(requests, head, disk_size, direction);
    return 0;
}
