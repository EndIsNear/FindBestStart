#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <cstdlib>
#include <iostream>
using namespace std;

template <class T>
class LinkedList;

template <class T>
struct LLnode
{
    LLnode(){}
    LLnode(T _val){ val = _val; pNext = pPrev = NULL; }
    T val;
    LLnode* pNext;
    LLnode* pPrev;
};

template<class T>
class LLiterator
{
    friend class LinkedList<T>;
public:
    LLiterator(LLnode<T>* _ptr = NULL){this->ptr = _ptr;}

    LLiterator<T> operator++();
    LLiterator<T> operator--();
    LLiterator<T> operator++(int);
    LLiterator<T> operator--(int);

    T& operator*()const;
    bool operator== (LLiterator<T>& right)const;
    bool operator!= (LLiterator<T>& right)const{return !(*this == right);}
private:
    LLnode<T>* ptr;
};

template<class T>
LLiterator<T> LLiterator<T>::operator++()
{
    if(this->ptr != NULL)
    {
        this->ptr = this->ptr->pNext;
    }
    return *this;
}

template<class T>
LLiterator<T> LLiterator<T>::operator--()
{
    if(this->ptr != NULL)
    {
        this->ptr = this->ptr->pPrev;
    }
    return *this;
}

template<class T>
LLiterator<T> LLiterator<T>::operator++(int)
{
    LLiterator<T> iter = *this;
    ++(*this);
    return iter;
}

template<class T>
LLiterator<T> LLiterator<T>::operator--(int)
{
    LLiterator<T> iter = *this;
    --(*this);
    return iter;
}

template<class T>
T& LLiterator<T>::operator*()const
{
    return this->ptr->val;
}

template<class T>
bool LLiterator<T>::operator==(LLiterator<T>& right)const
{
    return this->ptr == right.ptr;
}

template<class T>
class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    bool AddAtBegin(T val);
    bool AddAtEnd(T val);

    LLiterator<T> GetItBegin(){return LLiterator<T>(this->pivot.pNext);}
    LLiterator<T> GetItEnd(){return LLiterator<T> (&this->pivot);}

    bool Remove(LLiterator<T> iter);
    bool RemoveFromBegin(){return this->Remove(this->GetItBegin());}
    bool RemoveFromEnd(){return this->Remove(this->GetItEnd());}

    bool IsEmpty(){return size <= 0;}
    size_t GetSeize(){return this->size;}
    void print();
private:
    LLnode<T> pivot;
    size_t size;
    bool InsertBetween(LLnode<T>* left, LLnode<T>* right, const T& val);
};

template<class T>
LinkedList<T>::LinkedList()
{
    this->size = 0;
    this->pivot.pNext = &this->pivot;
    this->pivot.pPrev = &this->pivot;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    LLiterator<T> it = this->GetItBegin();
    while(this->Remove(it++));
}

template<class T>
bool LinkedList<T>::AddAtBegin(T val)
{
    return this->InsertBetween(&this->pivot, this->pivot.pNext, val);
}

template<class T>
bool LinkedList<T>::AddAtEnd(T val)
{
    return this->InsertBetween(this->pivot.pPrev, &this->pivot, val);
}

template<class T>
bool LinkedList<T>::Remove(LLiterator<T> iter)
{
    if(iter.ptr == &this->pivot)
    {
        return false;
    }
    LLnode<T>* tmp = iter.ptr;

    tmp->pNext->pPrev = tmp->pPrev;
    tmp->pPrev->pNext = tmp->pNext;
    delete tmp;
    return true;
}

template<class T>
void LinkedList<T>::print()
{
    LLiterator<T> tmp = this->GetItBegin();
    LLiterator<T> itEnd = this->GetItEnd();
    if(tmp == itEnd)
        return;
    cout << *tmp;
    tmp++;
    while(tmp != itEnd)
    {
        cout << ", " << *tmp;
        tmp++;
    }
}

template<class T>
bool LinkedList<T>::InsertBetween(LLnode<T>* left, LLnode<T>* right, const T& val)
{
    LLnode<T>* tmp = new LLnode<T>(val);
    if(!tmp)
    {
        return false;
    }
    tmp->pPrev = left;
    tmp->pNext = right;
    left->pNext = tmp;
    right->pPrev = tmp;
    this->size++;
    return true;
}

#endif // LIST_H_INCLUDED
