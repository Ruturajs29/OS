#include <iostream> //LRU
#include <unordered_map>
#include <list>
using namespace std;

void lruPageReplacement(int pages[], int n, int capacity)
{
    unordered_map<int, list<int>::iterator> indexes;
    list<int> pageList;
    int pageFaults = 0;

    for (int i = 0; i < n; i++)
    {
        if (indexes.find(pages[i]) == indexes.end())
        {
            if (pageList.size() == capacity)
            {
                int last = pageList.back();
                pageList.pop_back();
                indexes.erase(last);
            }
            pageList.push_front(pages[i]);
            indexes[pages[i]] = pageList.begin();
            pageFaults++;
        }
        else
        {
            pageList.erase(indexes[pages[i]]);
            pageList.push_front(pages[i]);
            indexes[pages[i]] = pageList.begin();
        }
    }
    cout << "Total Page Faults (LRU): " << pageFaults << endl;
}

int main()
{
    int pages[] = {7, 1, 0, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;
    lruPageReplacement(pages, n, capacity);
    return 0;
}
