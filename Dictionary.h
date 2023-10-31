#ifndef BOGGLE_DICTIONARY_H
#define BOGGLE_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const int NUM_CHARS = 26;

class DictionaryError{
public:
    explicit DictionaryError(string msg) {
        this->msg = msg; //error message
    }
    string Msg(){
        return msg;  // returns king of flavor
    }
private:
    string msg;
};

class Dictionary
{

public:
    Dictionary();
    ~Dictionary();  // I will not require this
    Dictionary(const Dictionary& otherDict);    // copy constructor
    explicit Dictionary(string filename);       // The keyword explicit is used to tell the compiler
                                                // that this is not a conversion constructor.

    Dictionary& operator=(const Dictionary& otherDict);
    void LoadDictionaryFile(string filename);
    void SaveDictionaryFile(string filename);

    void AddWord(string word);
    void MakeEmpty(); //Empties the dictionary structure

    bool IsWord(string word);
    bool IsPrefix(string word); // Check if the given word is a prefix
    int WordCount();  // Returns total number of words in dictionary

private:

    class Node {
    public:
        char letter;          // The letter represented by this node
        Node* children[NUM_CHARS]; // Array of pointers to child nodes
        bool isEndOfWord;     // Flag to indicate if a word ends at this node

        Node(char letter = '\0') : letter(letter), isEndOfWord(false) {
            for (int i = 0; i < NUM_CHARS; i++) {
                children[i] = nullptr;
            }
        }
        // Your node structure here.
        // You can also use a struct if you like.

        // It is strongly recommended you create a constructor
        // to set default values
    };

    Node* root{};
    int numWords{};

    // This function is used by the
    // copy constructor and the assignment operator.
    void copyOther(const Dictionary& otherDict);

    // Any private methods you need/want
    // You may change these helpers if you want, but you don't need to.
    void destroyHelper(Node* thisTree);
    void copyHelper(Node*& thisTree, Node* otherTree);
    void SaveDictionaryHelper(Node* curr, const string& currPrefix, ofstream& outFile);

    void SaveDictionaryHelper(Node *curr, string &currPrefix, ofstream &outFile);
};

#endif //BOGGLE_DICTIONARY_H
