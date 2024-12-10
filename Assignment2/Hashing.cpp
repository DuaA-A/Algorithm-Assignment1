#include<iostream>
#include<vector>
#include<list>
#include<algorithm>


using namespace std;
class HashTable {
private:
    vector<list<string>> table;
    int bucketCount;

    int hashFunction(const string& word) {
        string sortedWord = word;
        sort(sortedWord.begin(), sortedWord.end());

        int h = 0;
        for (char ch : sortedWord)
            h += ch;

        return h % bucketCount;
    }

public:
    HashTable(int size) : bucketCount(size) {
        table.resize(bucketCount);
    }

    void insert(const string& word) {
        int index = hashFunction(word);
        table[index].push_back(word);
    }
    int divisionMethod(int key, int tableSize) {
        return key % tableSize;
    }
    int multiplicationMethod(int key, int tableSize) {
        const double A = 0.6180339887; 
        return floor(tableSize * fmod(key * A, 1));
    }
    int midSquareMethod(int key, int tableSize) {
        int square = key * key;
        int middle = (square / 100) % 100; 
        return middle % tableSize;
    }

    int foldingMethod(int key, int tableSize) {
    int part1 = key / 1000; 
    int part2 = key % 1000; 
    int sum = part1 + part2;
    return sum % tableSize;
}

};
class HashTableLinearProbing {
private:
    vector<vector<string>> table;
    int bucketCount;

    int hashFunction(const string& word) {

        int hash = 0;
        for (char ch : word) {
            hash += ch;
        }
        return hash % bucketCount;
    }

public:
    HashTableLinearProbing(int size) : bucketCount(size) {
        table.resize(bucketCount);
    }

    void insert(const string& word) {
        string sortedWord = word;
        sort(sortedWord.begin(), sortedWord.end());

        int index = hashFunction(sortedWord);

        while (!table[index].empty() && table[index][0] != sortedWord) {
            index = (index + 1) % bucketCount;
        }
        if(table[index].empty())
            table[index].push_back(sortedWord);

        table[index].push_back(word);
    }

};