class Node {
public:
    int key;
    Node** forward;
    Node(int key, int level) {
        this->key = key;
        forward = new Node*[level + 1];
        for (int i = 0; i <= level; i++)
            forward[i] = nullptr;
    }
    ~Node() {
        delete[] forward;
    }
};

class SkipList {
private:
    int maxLevel;
    int currentLevel;
    float probability;
    Node* header;

    int randomLevel() {
        int level = 0;
        while (((float)rand() / RAND_MAX) < probability && level < maxLevel)
            level++;
        return level;
    }

public:
    SkipList(int maxLevel, float probability) {
        this->maxLevel = maxLevel;
        this->probability = probability;
        this->currentLevel = 0;
        header = new Node(-1, maxLevel);
    }

    ~SkipList() {
        delete header;
    }

    void insert(int key) {
        Node* current = header;
        Node* update[maxLevel + 1];
        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key)
                current = current->forward[i];
            update[i] = current;
        }

        current = current->forward[0];
        if (current == nullptr || current->key != key) {
            int level = randomLevel();
            if (level > currentLevel) {
                for (int i = currentLevel + 1; i <= level; i++)
                    update[i] = header;
                currentLevel = level;
            }

            Node* newNode = new Node(key, level);
            for (int i = 0; i <= level; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }

    void remove(int key) {
        Node* current = header;
        Node* update[maxLevel + 1];
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key)
                current = current->forward[i];
            update[i] = current;
        }

        current = current->forward[0];
        if (current != nullptr && current->key == key) {
            for (int i = 0; i <= currentLevel; i++) {
                if (update[i]->forward[i] != current)
                    break;
                update[i]->forward[i] = current->forward[i];
            }

            delete current;
            while (currentLevel > 0 && header->forward[currentLevel] == nullptr)
                currentLevel--;
        }
    }

    bool search(int key) {
        Node* current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key)
                current = current->forward[i];
        }
        current = current->forward[0];
        return current != nullptr && current->key == key;
    }

    void display() {
        for (int i = 0; i <= currentLevel; i++) {
            Node* node = header->forward[i];
            std::cout << "Level " << i << ": ";
            while (node != nullptr) {
                std::cout << node->key << " ";
                node = node->forward[i];
            }
            std::cout << std::endl;
        }
    }


 std::map<int, int> getNodeLevels(int id) {
    std::map<int, int> nodeLevelMap; // Map to store node key and its level
    Node* current = header->forward[0]; // Start traversal from the first node at level 0

    while (current != nullptr) {
        // Check if the current node matches the ID
        if (current->key == id) {
            // Determine the highest level of this node
            int nodeLevel = 0;
            for (int i = 0; i <= currentLevel; i++) {
                if (header->forward[i] != nullptr) {
                    Node* temp = header;
                    while (temp->forward[i] != nullptr && temp->forward[i] != current) {
                        temp = temp->forward[i];
                    }
                    if (temp->forward[i] == current) {
                        nodeLevel = i + 1; // Levels are 1-indexed
                    }
                }
            }
            nodeLevelMap[current->key] = nodeLevel; // Add key and level to the map
            break; // Exit once the desired node is found
        }
        current = current->forward[0]; // Move to the next node
    }

    return nodeLevelMap;
}


};

void skip_list() {
    srand(time(0));

    SkipList skipList(5, 0.5);

    skipList.insert(3);
    skipList.insert(6);
    skipList.insert(7);
    skipList.insert(9);
    skipList.insert(12);
    skipList.insert(19);

    std::cout << "Skip List after insertion:" << std::endl;
    skipList.display();

    int id = 9; // Change ID as needed
    std::map<int, int> nodeLevelMap = skipList.getNodeLevels(id);

    if (!nodeLevelMap.empty()) {
        std::cout << "\nNode Level Map for ID " << id << ":\n";
        for (const auto& pair : nodeLevelMap) {
            std::cout << "Node " << pair.first << ": " << pair.second << " levels\n";
        }
    } else {
        std::cout << "\nNode with ID " << id << " not found.\n";
    }


    std::cout << "\nSearching for 6: " << (skipList.search(6) ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 15: " << (skipList.search(15) ? "Found" : "Not Found") << std::endl;

    skipList.remove(6);
    std::cout << "\nSkip List after deleting 6:" << std::endl;
    skipList.display();
    return;
}
