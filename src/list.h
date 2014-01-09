#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <cstdlib>
#include <iostream>
using namespace std;

template<class T>
class LinkedList
{
    struct LLnode
    {
        LLnode(){}
        LLnode(T _val){val = _val; pNext = pPrev = NULL;}
        T val;
        LLnode* pNext;
        LLnode* pPrev;
    };

    LinkedList<T>::LLnode pivot;
    size_t size;

    bool InsertBetween(LinkedList<T>::LLnode* const left, LinkedList<T>::LLnode* const right, const T& val)
    {
        LinkedList<T>::LLnode* tmp = new(nothrow) LinkedList<T>::LLnode(val);
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

public:
    LinkedList()
    {
        this->size = 0;
        this->pivot.pNext = &this->pivot;
        this->pivot.pPrev = &this->pivot;
    }

    ~LinkedList()
    {
        this->delList();
    }

    void delList()
    {
        LinkedList<T>::LLiterator it = this->GetItBegin();
        while(this->Remove(it++));
    }

    bool AddAtBegin(const T& val)
    {
        return this->InsertBetween(&this->pivot, this->pivot.pNext, val);
    }

    bool AddAtEnd(const T& val)
    {
        return this->InsertBetween(this->pivot.pPrev, &this->pivot, val);
    }

    class LLiterator
    {
        friend class LinkedList<T>;
    public:
        LLiterator(LinkedList<T>::LLnode* _ptr = NULL){this->ptr = _ptr;}

        LinkedList<T>::LLiterator& operator++()
        {
            if(this->ptr != NULL)
            {
                this->ptr = this->ptr->pNext;
            }
            return *this;
        }

        LinkedList<T>::LLiterator& operator--()
        {
            if(this->ptr != NULL)
            {
                this->ptr = this->ptr->pPrev;
            }
            return *this;
        }

        LinkedList<T>::LLiterator operator++(int)
        {
            LinkedList<T>::LLiterator iter = *this;
            ++(*this);
            return iter;
        }

        LinkedList<T>::LLiterator operator--(int)
        {
            LinkedList<T>::LLiterator iter = *this;
            --(*this);
            return iter;
        }

        T& operator*()const{return this->ptr->val;}
        T* operator->()const{return &this->ptr->val;}
        bool operator== (LinkedList<T>::LLiterator& right)const{return this->ptr == right.ptr;}
        bool operator!= (LinkedList<T>::LLiterator& right)const{return !(*this == right);}
    private:
        LinkedList<T>::LLnode* ptr;
    };

    LinkedList<T>::LLiterator GetItBegin(){return LinkedList<T>::LLiterator(this->pivot.pNext);}
    LinkedList<T>::LLiterator GetItEnd(){return LinkedList<T>::LLiterator(&this->pivot);}

    bool Remove(LinkedList<T>::LLiterator iter)
    {
        if(iter.ptr == &this->pivot)
        {
            return false;
        }
        LinkedList<T>::LLnode* tmp = iter.ptr;

        tmp->pNext->pPrev = tmp->pPrev;
        tmp->pPrev->pNext = tmp->pNext;
        delete tmp;
        return true;
    }
    bool RemoveFromBegin(){return this->Remove(this->GetItBegin());}

    bool IsEmpty()const{return size <= 0;}
    size_t GetSeize()const{return this->size;}
    void print(ostream& stream)
    {
        LinkedList<T>::LLiterator iter = this->GetItBegin();
        LinkedList<T>::LLiterator iterEnd = this->GetItEnd();
        if(this->IsEmpty())
            return;
        stream << *iter;
        ++iter;
        while(iter != iterEnd)
        {
            stream << ", " << *iter;
            ++iter;
        }
    }
};
#endif // LIST_H_INCLUDED
