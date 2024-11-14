#include <iostream> //FCFS DISK SCHED
#include <vector>
#include <cmath>

using namespace std;

void FCFS(vector<int> &requests, int head) {
    int seek_operations = 0;
    cout << "FCFS Order of execution: " << head;
    for (int request : requests) {
        cout << " -> " << request;
        seek_operations += abs(head - request);
        head = request;
    }
    cout << "\nTotal Seek Operations: " << seek_operations << endl;
}

int main() {
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    FCFS(requests, head);
    return 0;
}
