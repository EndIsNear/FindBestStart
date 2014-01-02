#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <cstdlib>
#include <iostream>
using namespace std;

template <class T>
struct LLnode
{
    LLnode();
    LLnode(T _val){ val = _val; pNext = pPrev = NULL; }
    T val;
    LLnode* pNext;
    LLnode* pPrev;
};

template<class T>
class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    bool AddAtBegin(T val);
    bool AddAtEnd(T val);

    LLnode<T> * GetBegin(){return this->pFirst;}
    LLnode<T> * GetEnd(){return this->pLast;}

    bool Remove(LLnode<T> * node);
    bool RemoveFromBegin(){return this->Remove(this->GetBegin());}
    bool RemoveFromEnd(){return this->Remove(this->GetEnd());}

    bool IsEmpty(){return size <= 0;}
    size_t GetSeize(){return this->size;}
    void print();
private:
    LLnode<T> * pFirst;
    LLnode<T> * pLast;
    size_t size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    this->size = 0;
    this->pFirst = this->pLast = NULL;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    while(!this->IsEmpty())
    {
        this->Remove(this->pFirst);
    }
}

template<class T>
bool LinkedList<T>::AddAtBegin(T val)
{
    LLnode<T>* tmp = new(nothrow) LLnode<T>(val);
    if(!tmp)
    {
        return false;
    }
    if(this->IsEmpty())
    {
        this->pFirst = this->pLast = tmp;
    }
    else
    {
        tmp->pNext = this->pFirst;
        this->pFirst->pPrev = tmp;
        this->pFirst = tmp;
    }
    this->size++;

    return true;
}

template<class T>
bool LinkedList<T>::AddAtEnd(T val)
{
    LLnode<T>* tmp = new(nothrow) LLnode<T>(val);
    if(!tmp)
    {
        return false;
    }

    if(this->IsEmpty())
    {
        this->pFirst = this->pLast = tmp;
    }
    else
    {
        tmp->pPrev = this->pLast;
        this->pLast->pNext = tmp;
        this->pLast = tmp;
    }

    this->size++;

    return true;
}

template <class T>
bool LinkedList<T>::Remove(LLnode<T> * node)
{
    if(this->IsEmpty())
    {
        return false;
    }
    if(node->pNext)
    {
        node->pNext->pPrev = node->pPrev;
    }
    else
    {
        this->pLast = node->pPrev;
    }
    if(node->pPrev)
    {
        node->pPrev->pNext = node->pNext;
    }
    else
    {
        this->pFirst = node->pNext;
    }
    delete node;
    this->size--;
    return true;
}

template<class T>
void LinkedList<T>::print()
{
    LLnode<T>* tmp;
    if(this->IsEmpty())
    {
        return;
    }
    tmp = this->GetBegin();
    cout << tmp->val;
    tmp = tmp->pNext;
    while(tmp)
    {
        cout << ", "<< tmp->val;
        tmp = tmp->pNext;
    }
    cout << endl;
}

#endif // LIST_H_INCLUDED
