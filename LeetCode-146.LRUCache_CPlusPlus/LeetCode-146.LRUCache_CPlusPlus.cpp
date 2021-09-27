#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

class LRUCache {
private:

    struct Data
    {
    public:

        int value;
        list<short>::iterator iter;

        Data() {}

        Data(int val, list<short>::iterator it)
            :value(val), iter(it)
        {
        }
    };


    list<short> ls;
    map<short, Data> values = map<short, Data>();
    short cap = 0;
    map<short, Data>::iterator tempIter;
    list<short>::iterator lastIter;
public:
    LRUCache(int capacity) {
        cap = capacity;
        ls = list<short>(capacity);
    }

    int get(int key) {
        tempIter = values.find(key);
        if (tempIter == values.end())
            return -1;

        if (*lastIter != key)
        {
            ls.erase(tempIter->second.iter);
            ls.push_back(key);
            lastIter = --ls.end();
            tempIter->second.iter = lastIter;
        }

        return tempIter->second.value;
    }

    void put(int key, int value) {

        tempIter = values.find(key);
        if (tempIter != values.end())
        {
            if (*lastIter != key)
            {
                ls.erase(tempIter->second.iter);
                ls.push_back(key);
                lastIter = --ls.end();
                tempIter->second.iter = lastIter;
            }
            tempIter->second.value = value;
            return;
        }

        if (ls.size() == cap)
        {
            values.erase(*ls.begin());
            ls.pop_front();
        }

        ls.push_back(key);
        lastIter = --ls.end();
        values[key] = Data(value, lastIter);
    }
};

int main()
{
    LRUCache lru(2);
    printf("LRUCache:[%d]\n", 2);

    lru.put(1, 1);
    printf("put:[%d, %d]\n", 1, 1);

    lru.put(2, 2);
    printf("put:[%d, %d]\n", 2, 2);

    lru.get(1);
    printf("get:[%d]\n", 1);

    lru.put(3, 3);
    printf("put:[%d, %d]\n", 3, 3);

    lru.get(2);
    printf("get:[%d]\n", 2);

    lru.put(4, 4);
    printf("put:[%d, %d]\n", 4, 4);

    lru.get(1);
    printf("get:[%d]\n", 1);

    lru.get(3);
    printf("get:[%d]\n", 3);

    lru.get(4);
    printf("get:[%d]\n", 4);
}
