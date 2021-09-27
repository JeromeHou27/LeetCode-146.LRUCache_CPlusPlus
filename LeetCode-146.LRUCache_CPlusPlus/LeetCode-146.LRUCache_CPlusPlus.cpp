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
        list<int>::iterator iter;

        Data() {}

        Data(int val, list<int>::iterator it)
            :value(val), iter(it)
        {
        }
    };


    list<int> ls;
    map<int, Data> values = map<int, Data>();
    short cap = 0;
    map<int, Data>::iterator tempIter;
public:
    LRUCache(int capacity) {
        cap = capacity;
        ls = list<int>(capacity);
    }

    int get(int key) {
        tempIter = values.find(key);
        if (tempIter == values.end())
            return -1;

        ls.erase(tempIter->second.iter);

        ls.push_back(key);
        tempIter->second.iter = --ls.end();

        return tempIter->second.value;
    }

    void put(int key, int value) {

        tempIter = values.find(key);
        if (tempIter != values.end())
        {
            ls.erase(tempIter->second.iter);
            ls.push_back(key);
            tempIter->second.value = value;
            tempIter->second.iter = --ls.end();
            return;
        }

        if (ls.size() == cap)
        {
            values.erase(*ls.begin());
            ls.pop_front();
        }

        ls.push_back(key);
        values[key] = Data(value, --ls.end());
    }
};

string ArrayToString(const vector<int>& input)
{
    string output = "";
    char buffer[16] = "";

    for (int i = 0; i < input.size(); ++i)
    {
        if (i != 0)
            output += ", ";

        _itoa_s(input[i], buffer, 10);
        output += buffer;
    }

    return output;
}

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
