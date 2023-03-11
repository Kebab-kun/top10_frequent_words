#pragma once

struct node
{
    std::string data;
    node* link;
};

template <class elemType>
class linkedList
{
private:

    elemType* first;
    elemType* last;
    elemType* current;

    int count;

public:

    linkedList() // constructor
    {
        first = nullptr;
        last = nullptr;
        current = nullptr;
        count = 0;

    }

    ~linkedList() // destructor
    {
        deleteAllNodes();
    }

    void deleteAllNodes();

    int getCount() const;

    void insert(std::string newData);

    std::string at(int position) const;

    const std::string& moveToNextAndGetData();

};



template<class elemType>
void linkedList<elemType>::deleteAllNodes()
{
    node* nodeIterator = first;
    while (nullptr != nodeIterator)
    {
        node* nodeToDelete = nodeIterator;
        nodeIterator = nodeIterator->link;
        delete nodeToDelete;
    }

}


template<class elemType>
int linkedList<elemType>::getCount()const
{
    return count;
}



template<class elemType>
void linkedList<elemType>::insert(std::string newData)
{
    node* newNode = new node;
    newNode->data = newData;
    newNode->link = nullptr;

    if (last != nullptr)
    {
        last->link = newNode;
        last = newNode;
    }
    else
    {
        first = newNode;
        last = newNode;
        current = newNode;
        newNode->link = nullptr;
    }
    count++;
    return;
}


template<class elemType>
std::string linkedList<elemType>::at(int position) const
{
    node* temp = first;
    for (int i = 0; i < position; i++)
    {
        temp = temp->link;
    }
    return temp->data;
}

template<class elemType>
const std::string& linkedList<elemType>::moveToNextAndGetData() {
    if (current->link != nullptr)
    {
        std::string& data = current->data;
        current = current->link;
        return data;
    }

}


