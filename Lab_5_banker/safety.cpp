#include <iostream>  // sAFETY DEAD DET
#include <vector>
using namespace std;

bool isSystemSafe(vector<vector<int>> &allocatedResources, vector<vector<int>> &neededResources, vector<int> &availableResources) {
    int processCount = allocatedResources.size();
    int resourceCount = availableResources.size();
    vector<bool> isProcessFinished(processCount, false);
    vector<int> safeSequence(processCount);
    vector<int> workResources = availableResources;
    int completedProcesses = 0;

    while (completedProcesses < processCount) {
        bool foundSafeProcess = false;
        for (int i = 0; i < processCount; i++) {
            if (!isProcessFinished[i]) {
                bool canAllocate = true;
                for (int j = 0; j < resourceCount; j++) {
                    if (neededResources[i][j] > workResources[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < resourceCount; j++) {
                        workResources[j] += allocatedResources[i][j];
                    }
                    safeSequence[completedProcesses++] = i;
                    isProcessFinished[i] = true;
                    foundSafeProcess = true;
                }
            }
        }
        if (!foundSafeProcess) {
            cout << "System is not in a safe state.\n";
            return false;
        }
    }

    cout << "System is in a safe state.\nSafe Sequence: ";
    for (int i = 0; i < processCount; i++) {
        cout << safeSequence[i] << " ";
    }
    cout << endl;

    return true;
}

int main() {
    int processCount, resourceCount;

    cout << "Enter the number of processes: ";
    cin >> processCount;

    cout << "Enter the number of resources: ";
    cin >> resourceCount;

    vector<vector<int>> allocatedResources(processCount, vector<int>(resourceCount));
    vector<vector<int>> maxResources(processCount, vector<int>(resourceCount));
    vector<vector<int>> neededResources(processCount, vector<int>(resourceCount));
    vector<int> availableResources(resourceCount);

    cout << "Enter the allocation matrix (process-wise):\n";
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < resourceCount; j++) {
            cin >> allocatedResources[i][j];
        }
    }

    cout << "Enter the maximum matrix (process-wise):\n";
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < resourceCount; j++) {
            cin >> maxResources[i][j];
        }
    }

    cout << "Enter the available resources:\n";
    for (int i = 0; i < resourceCount; i++) {
        cin >> availableResources[i];
    }

    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < resourceCount; j++) {
            neededResources[i][j] = maxResources[i][j] - allocatedResources[i][j];
        }
    }

    isSystemSafe(allocatedResources, neededResources, availableResources);

    return 0;
}
