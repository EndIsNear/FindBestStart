#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

template<class T>
class Heap
{
    struct HeapNode
    {
        HeapNode(){}
        int weight;
        T val;
    };

    HeapNode * nodes;
    size_t size;
    size_t max_size;

    int LeftChildIndex(int index)const
    {
        return index * 2;
    }
    int RightChildIndex(int index)const
    {
        return index * 2 + 1;
    }
    int ParentIndex(int index)const
    {
        if(index > 1)
            return index/2;
        else
            return 1;
    }

    void Swap (int left, int right)
    {
        HeapNode tmp;
        tmp = this->nodes[left];
        this->nodes[left] = this->nodes[right];
        this->nodes[right] = tmp;
    }

    bool Resize(size_t newSize)
    {
        if(newSize < size)
            return false;

        HeapNode* newArr = new HeapNode[newSize + 1];
        if(!newArr)
        {
            return false;
        }

        for(int i = 1; i <= size; ++i)
        {
            newArr[i] = this->nodes[i];
        }

        delete[] this->nodes;
        this->nodes = newArr;

        return true;
    }
public:

    Heap()
    {
        this->size = 0;
        this->max_size = 20;
        this->nodes = new HeapNode[this->max_size + 1];
    }
    ~Heap()
    {
        delete[] this->nodes;
    }
    bool Push(const T& val, int weight)
    {
        if(this->IsEmpty())
        {
            this->nodes[1].val = val;
            this->nodes[1].weight = weight;
            this->size++;
            return true;
        }

        if(size + 1 <= max_size)
        {
            this->Resize(max_size*2);
        }

        int iter = size + 1;
        this->nodes[iter].val = val;
        this->nodes[iter].weight = weight;
        this->size++;

        while(iter > 1 && this->nodes[iter].weight < this->nodes[ParentIndex(iter)].weight)
        {
            this->Swap(iter, ParentIndex(iter));
            iter = ParentIndex(iter);
        }

        return true;
    }

    T& Pop ()
    {
        if(this->IsEmpty())
        {
            //TODO:handle this shit!
        }

        T tmp = this->nodes[1].val;
        this->Swap(1, this->size);
        this->size--;

        int iter = 1;

        while((this->nodes[iter].weight > this->nodes[LeftChildIndex(iter)].weight && LeftChildIndex(iter) <= size)
              || (this->nodes[iter].weight > this->nodes[RightChildIndex(iter)].weight) && RightChildIndex(iter) <= size)
        {
            if(this->nodes[iter].weight > this->nodes[LeftChildIndex(iter)].weight && LeftChildIndex(iter) <= size
               && this->nodes[iter].weight > this->nodes[RightChildIndex(iter)].weight && RightChildIndex(iter) <= size)
            {
                if(this->nodes[LeftChildIndex(iter)].weight > this->nodes[RightChildIndex(iter)].weight)
                {
                    this->Swap(iter, RightChildIndex(iter));
                    iter = RightChildIndex(iter);
                }
                else
                {
                    this->Swap(iter, LeftChildIndex(iter));
                    iter = LeftChildIndex(iter);
                }
            }
            else if(this->nodes[iter].weight > this->nodes[LeftChildIndex(iter)].weight)
            {
                this->Swap(iter, LeftChildIndex(iter));
                iter = LeftChildIndex(iter);
            }
            else
            {
                this->Swap(iter, RightChildIndex(iter));
                iter = RightChildIndex(iter);
            }
        }

        if(max_size > 2 * size)
            this->Resize(max_size/2);
        return tmp;
    }

    bool IsEmpty()const
    {
        return this->size <= 0;
    }

    size_t GetSize()const
    {
        return this->size;
    }

    void print()
    {
        for(int i = 1; i <= this->size; ++i)
        {
            cout << this->nodes[i].val << endl;
        }
    }
};

#endif // HEAP_H_INCLUDED
