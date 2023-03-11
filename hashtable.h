#pragma once

struct wordCount
{
    std::string word;
    int count;
};

template<class elemType>
class hashtable {
public:

    elemType* table;
    int size{};

    explicit hashtable(int size) // constructor
    { 
        this->size = size;
        table = new wordCount[size];

        for (int i = 0; i < size; i++) {
            table[i].word = "";
            table[i].count = -1;

        }
    }
    ~hashtable() // destructor
    {
        delete[] table;
    }

    void insert(std::string& word, int count_);

    void remove(const std::string& stopWord);

    void winners();
};




template <class elemType>
void hashtable<elemType>::insert(std::string& word, const int count_)
{
    int key = 0;
    int probingIteration = 0;


    
        for (char i : word)
    {
        key += i * i * 2 +1; // ascii values sum
    }

        


    while (probingIteration < size)
    {

        if (table[(key + (probingIteration * probingIteration)) % size].word == word)
        {
            table[(key + (probingIteration * probingIteration)) % size].count += count_;
            return;
        }

        else
        {
            if (table[(key + (probingIteration * probingIteration)) % size].count == -1)
            {
                table[(key + (probingIteration * probingIteration)) % size].word = word;
                table[(key + (probingIteration * probingIteration)) % size].count = count_;
                return;
            }
            else { probingIteration++; }
        }
    }
}

template <class elemType>
void hashtable<elemType>::remove(const std::string& stopWord)
{
    for (int i = 0; i < size; i++) {
        if (table[i].word == stopWord) {
            table[i].word = "";
            table[i].count = -1;
            return;
        }
    }
}



template <class elemType>
void hashtable<elemType>::winners()
{
    auto* schneidersList = new wordCount[10];
    int max,pos;

        for (int i = 0; i < 10; i++) {

        max = 0; pos = 0;

        for (int j = 0; j < size; j++) {
            if (table[j].count > max) {
                max = table[j].count;
                pos = j;
            }
        }
        schneidersList[i].word = table[pos].word;
        schneidersList[i].count = table[pos].count;

            table[pos].count = -1;
            table[pos].word = "";
    }

        for (int i = 0; i < 10; i++) { std::cout << schneidersList[i].word << " " << schneidersList[i].count << std::endl; }
        delete[] schneidersList;
}

