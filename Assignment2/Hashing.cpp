#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <string>

using namespace std;

class HashTable {
protected:
    int size; 
public:
    HashTable(int tableSize) : size(tableSize) {}
    virtual void insert(int key) = 0; 
    virtual void remove(int key) = 0;
    virtual void display() const = 0;
    virtual ~HashTable() = default; 
};

class SeparateChaining : public HashTable {
private:
    vector<list<int>> table;
public:
    SeparateChaining(int tableSize) : HashTable(tableSize), table(tableSize) {}

    void insert(int key) override {
        int hashValue = key % size;
        table[hashValue].push_back(key);
    }

    void remove(int key) override {
        int hashValue = key % size;
        table[hashValue].remove(key);
    }

    void display() const override {
        cout << "Separate Chaining Table:\n";
        for (int i = 0; i < size; i++) {
            cout << i << ": ";
            for (int key : table[i]) 
                cout << key << " -> ";
            cout << "NULL\n";
        }
    }
};

class LinearProbing : public HashTable {
private:
    vector<int> table;
public:
    LinearProbing(int tableSize) : HashTable(tableSize), table(tableSize, -1) {}

    void insert(int key) override {
        int hashValue = key % size;
        int i = 0;
        while (table[(hashValue + i) % size] != -1) i++; 
        table[(hashValue + i) % size] = key;
    }

    void remove(int key) override {
        int hashValue = key % size;
        int i = 0;
        while (table[(hashValue + i) % size] != -1) {
            if (table[(hashValue + i) % size] == key) {
                table[(hashValue + i) % size] = -1;
                return;
            }
            i++;
        }
    }

    // bool search(int key) const {
    //     int hashValue = key % size;
    //     int i = 0;
    //     while (table[(hashValue + i) % size] != -1) {
    //         if (table[(hashValue + i) % size] == key) 
    //             return true;
    //         i++;
    //         if (i == size) break; 
    //     }
    //     return false;
    // }

    void display() const override {
        cout << "Linear Probing Table:\n";
        for (int i = 0; i < size; i++) 
            if (table[i] != -1) 
                cout << i << ": " << table[i] << "\n";
            else 
                cout << i << ": EMPTY\n";
    }
};

class QuadraticProbing : public HashTable {
private:
    vector<int> table;
public:
    QuadraticProbing(int tableSize) : HashTable(tableSize), table(tableSize, -1) {}

    void insert(int key) override {
        int hashValue = key % size;
        int i = 0;
        while (table[(hashValue + i * i) % size] != -1) i++;
        table[(hashValue + i * i) % size] = key;
    }

    void remove(int key) override {
        int hashValue = key % size;
        int i = 0;
        while (table[(hashValue + i * i) % size] != -1) {
            if (table[(hashValue + i * i) % size] == key) {
                table[(hashValue + i * i) % size] = -1;
                return;
            }
            i++;
        }
    }

    // bool search(int key) const {
    //     int hashValue = key % size;
    //     int i = 0;
    //     while (table[(hashValue + i * i) % size] != -1) {
    //         if (table[(hashValue + i * i) % size] == key) 
    //             return true;
    //         i++;
    //         if (i == size) break; 
    //     }
    //     return false;
    // }

    void display() const override {
        cout << "Quadratic Probing Table:\n";
        for (int i = 0; i < size; i++) 
            if (table[i] != -1) 
                cout << i << ": " << table[i] << "\n";
            else 
                cout << i << ": EMPTY\n";
    }
};

class DoubleHashing : public HashTable {
private:
    vector<int> table;
    int PRIME; 

    int secondHash(int key) const {
        return PRIME - (key % PRIME);
    }

public:
    DoubleHashing(int tableSize, int prime) : HashTable(tableSize), table(tableSize, -1), PRIME(prime) {}

    void insert(int key) override {
        int hashValue = key % size;
        int i = 0;
        while (table[(hashValue + i * secondHash(key)) % size] != -1)  i++;
        table[(hashValue + i * secondHash(key)) % size] = key;
    }

    void remove(int key) override {
        int hashValue = key % size;
        int i = 0;
        while (table[(hashValue + i * secondHash(key)) % size] != -1) {
        if (table[(hashValue + i * secondHash(key)) % size] == key) {
            table[(hashValue + i * secondHash(key)) % size] = -1;
            return;
        }
        i++;
        }
    }

    void display() const override {
        cout << "Double Hashing Table:\n";
        for (int i = 0; i < size; i++) 
            if (table[i] != -1) 
                cout << i << ": " << table[i] << "\n";
            else 
                cout << i << ": EMPTY\n";
    }
};


class HashTableForMethods {
protected:
    int size;
    vector<int> table;
public:
    HashTableForMethods(int tableSize) : size(tableSize), table(tableSize, -1) {}
    virtual int hashFunction(int key) const = 0;
    virtual void insert(int key) {
        int hashValue = hashFunction(key);
        table[hashValue] = key; 
    }
    virtual void remove(int key) { 
        int hashValue = hashFunction(key); 
        if (table[hashValue] == key) 
        table[hashValue] = -1; 
    }
    virtual void display() const {
        cout << "Hash Table for Method Testing:\n";
        for (int i = 0; i < size; i++) {
            if (table[i] != -1)
                cout << i << ": " << table[i] << "\n";
            else
                cout << i << ": EMPTY\n";
        }
    }
    virtual ~HashTableForMethods() = default;
};

class DivisionMethod : public HashTableForMethods {
public:
    DivisionMethod(int tableSize) : HashTableForMethods(tableSize) {}
    int hashFunction(int key) const override {
        return key % size;
    }
};

class MultiplicationMethod : public HashTableForMethods {
private:
    const double A = 0.6180339887; 
public:
    MultiplicationMethod(int tableSize) : HashTableForMethods(tableSize) {}
    int hashFunction(int key) const override {
        double fractionalPart = (key * A) - floor(key * A);
        return floor(size * fractionalPart);
    }
};

class MidSquareMethod : public HashTableForMethods {
public:
    MidSquareMethod(int tableSize) : HashTableForMethods(tableSize) {}
    int hashFunction(int key) const override {
        int square = key * key;
        string squareStr = to_string(square);
        int mid = squareStr.length() / 2;
        return stoi(squareStr.substr(mid - 1, 2)) % size;
    }
};


class FoldingMethod : public HashTableForMethods {
private:
    enum FoldingType {BOUNDARY, SHIFTING };
    FoldingType foldingType;

    int foldingBoundary(int key) const {
        string keyStr = to_string(key);
        int boundary = size / 2, sum = 0, part;
        for (size_t i = 0; i < keyStr.size(); i += 2) {
            part = stoi(keyStr.substr(i, 2));
            sum += part % boundary;
        }
        return sum % size;
    }

    int foldingShifting(int key) const {
        string keyStr = to_string(key);
        int sum = 0, shiftValue;
        for (size_t i = 0; i < keyStr.size(); i++) {
            shiftValue = keyStr[i] - '0'; 
            sum = (sum << shiftValue) | (sum >> (sizeof(int) * 8 - shiftValue));
        }
        return abs(sum) % size;
    }

public:
    FoldingMethod(int tableSize, const string& type) : HashTableForMethods(tableSize) {
        if (type == "boundary") 
            foldingType = BOUNDARY;
        else if (type == "shifting") 
            foldingType = SHIFTING;
    }

    int hashFunction(int key) const override {
        switch (foldingType) {
            case BOUNDARY:
                return foldingBoundary(key);
            case SHIFTING:
                return foldingShifting(key);
        }
    }
};

int main() {
    int tableSize, choice = 0, resolutionChoice = 0, n, key;
    char delChoice;
    string foldingType;
    cout << "Enter table size: ";
    cin >> tableSize;

    while (choice != 4) {
        cout << "\nChoose a hashing method to test:\n";
        cout << "1. Division Method\n";
        cout << "2. Multiplication Method\n";
        cout << "3. Mid Square Method\n";
        cout << "4. Folding Method\n";
        cout << "0. Exit\n";
        cin >> choice;
        if (choice == 0) break;

        HashTableForMethods* hashTableMethod = nullptr;
        switch (choice) {
            case 1:
                hashTableMethod = new DivisionMethod(tableSize);
                break;
            case 2:
                hashTableMethod = new MultiplicationMethod(tableSize);
                break;
            case 3:
                hashTableMethod = new MidSquareMethod(tableSize);
                break;
            case 4:
                cout << "Choose Folding Method Type (boundary/shifting): ";
                cin >> foldingType;
                hashTableMethod = new FoldingMethod(tableSize,foldingType);
                break;
            default:
                cout << "Invalid choice!\n";
                continue;
        }
        cout << "Enter the number of keys to insert: ";
        cin >> n;
        while(n--) {
            cout << "Enter key: ";
            cin >> key;
            hashTableMethod->insert(key);
        }
        hashTableMethod->display();
        delete hashTableMethod;
    }

    while (resolutionChoice != 5) {
        cout << "\nChoose collision resolution method:\n";
        cout << "1. Separate Chaining\n";
        cout << "2. Linear Probing\n";
        cout << "3. Double Hashing\n";
        cout << "4. Quadratic Probing\n";
        cout << "5. Exit\n";
        cin >> resolutionChoice;
        if (resolutionChoice == 5) break;

        HashTable* hashTable = nullptr;
        switch (resolutionChoice) {
            case 1:
                hashTable = new SeparateChaining(tableSize);
                break;
            case 2:
                hashTable = new LinearProbing(tableSize);
                break;
            case 3: {
                int prime;
                cout << "Enter a prime number for Double Hashing: ";
                cin >> prime;
                hashTable = new DoubleHashing(tableSize, prime);
                break;
            }
            case 4:
                hashTable = new QuadraticProbing(tableSize);
                break;
            default:
                cout << "Invalid choice!\n";
                continue;
        }
        cout << "Enter the number of keys to insert: ";
        cin >> n;
        while(n--) {
            cout << "Enter key: ";
            cin >> key;
            hashTable->insert(key);
        }
        hashTable->display();
        cout << "Do you want to delete a key? (y/n): ";
        cin >> delChoice;
        if (delChoice == 'y' || delChoice == 'Y') {
            cout << "Enter key to delete: ";
            cin >> key;
            hashTable->remove(key);
            hashTable->display();
        }
        delete hashTable;
    }

    return 0;
}