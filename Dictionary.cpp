#include "Dictionary.h"

Dictionary::Dictionary() { // Initialize the node
    root = new Node();
}

Dictionary::~Dictionary() { // Clean up the dictionary data
    MakeEmpty();
}

Dictionary::Dictionary(const Dictionary& otherDict) {
    // Copy constructor
    copyOther(otherDict);
}

Dictionary::Dictionary(string filename) {
    // Load the dictionary from a file
    root = new Node(); // creat a root node
    LoadDictionaryFile(filename);
}

Dictionary& Dictionary::operator=(const Dictionary& otherDict) {
    // clear the current dict
    if (this != &otherDict) {
        MakeEmpty();
        copyOther(otherDict); // Copy the other dictionary
    }
    return *this;
}
// Load words from a file into the dictionary
void Dictionary::LoadDictionaryFile(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string word;
        while (file >> word) {
            AddWord(word); // Add each word from the file
        }
        file.close();
    } else {
        throw DictionaryError("Failed to open the file: " + filename);
    }
}

void Dictionary::SaveDictionaryFile(string filename) {
    //saving words to a file
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw DictionaryError(filename + " failed to open");
    }
    string prefix = " ";
    SaveDictionaryHelper(root, prefix, outFile);
    outFile.close();

}

void Dictionary::AddWord(string word) {
    for (char letter : word) {
        if (letter < 'a' || letter > 'z') {
            throw DictionaryError("Invalid character");
        }
    }
    // Add a word to the dictionary
    Node* current = root;

    for (char letter : word) {
        int index = letter - 'a'; // Get the index of the character
        if (current->children[index] == nullptr) {
            current->children[index] = new Node(letter);
        }
        current = current->children[index];
    }

    if (!current->isEndOfWord) {
        current->isEndOfWord = true;
        numWords++;
    }

}

void Dictionary::MakeEmpty() {
    // Recursively delete all nodes
    destroyHelper(root);
    root = new Node(); // Create a new root node
    numWords = 0; //
}

bool Dictionary::IsWord(string word) {
    Node* current = root;
    // Check if a word exists in the dictionary
    for (char letter : word) {
        int index = letter - 'a';
        if (current->children[index] == nullptr) {
            return false; // Word not found
        }
        current = current->children[index];
    }

    // Check if the current node marks the end of a word
    return current != nullptr && current->isEndOfWord;
}
bool Dictionary::IsPrefix(string word) {
    // Check if the word is a prefix of any dictionary word
    Node* current = root;

    for (char letter : word) {
        int index = letter - 'a';
        if (current->children[index] == nullptr) {
            return false; // Prefix not found
        }
        current = current->children[index];
    }

    return true;
}
// Return the total number of words in the dictionary
int Dictionary::WordCount() {
    return numWords;
}

void Dictionary::copyOther(const Dictionary& otherDict) {
    // Implement a deep copy of another dictionary
    root = new Node();
    numWords = otherDict.numWords;
    copyHelper(root, otherDict.root);
}

void Dictionary::destroyHelper(Node* thisTree) {
    // Recursively delete nodes in the trie
}

void Dictionary::copyHelper(Node*& thisTree, Node* otherTree) {
    // Recursively copy nodes from another dictionary
    if (otherTree == nullptr) {
        return;
    }

    // Copy the letter and end-of-word flag
    thisTree->letter = otherTree->letter;
    thisTree->isEndOfWord = otherTree->isEndOfWord;

    //copy child nodes
    for (int i = 0; i < NUM_CHARS; i++) {
        if (otherTree->children[i] != nullptr) {
            thisTree->children[i] = new Node();
            copyHelper(thisTree->children[i], otherTree->children[i]);
        }
    }
}
//save the dictionary to a file
void Dictionary::SaveDictionaryHelper(Node *curr, string& currPrefix, ofstream& outFile) {
    if (curr->isEndOfWord) {
        outFile << currPrefix << endl;
    }
    for (int i = 0; i < NUM_CHARS; ++i) {
        if (curr->children[i] != nullptr) {
            string nextPrefix = currPrefix + curr->children[i]->letter;
            SaveDictionaryHelper(curr->children[i], nextPrefix, outFile);
        }
    }
}