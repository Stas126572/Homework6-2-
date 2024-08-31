#pragma once
template<typename ElementType=int>
class Vector
{
private:
    ElementType* values;
    size_t size;
    size_t capacity;

public:
    Vector(const Vector& vc)
    {
        values = new ElementType[vc.size];
        size = vc.size;
        capacity = size;
        for (int i = 0; i<size; i++)
        {
            values[i] = vc.values[i];
        }
    }

    size_t get_size() {return size;};
    Vector() {size = 0; capacity = 0; values = new ElementType[0];}

    ElementType GetElementOfIndex(size_t index)
    {
        return values[index];
    }
    void reserve(size_t capacity)
    {
        this->capacity = capacity;
        ElementType* new_values;
        new_values = new ElementType[capacity];
        for (int i = 0; i<size; i++)
        {
            new_values[i] = values[i];
        }
        delete[] values;
        values = new_values;
    };
    void insert(size_t index, ElementType element)
    {
        ElementType* new_values;
        if (capacity<=size)
        {
            capacity = (size+1)*2;
            new_values = new ElementType[capacity];
            int plus_new_index = 0;
            for (int i = 0; i<=size; i++)
            {

                if (i==index) {
                    new_values[i+plus_new_index] = element;

                    plus_new_index++;
                }
                else {
                    new_values[i+plus_new_index] = values[i];

                }
            }
            delete[] values;
            values = new_values;
        }
        else
        {
            ElementType element2;
            ElementType element = values[index];
            values[index] = element;
            for (size_t i = index+1; i<size+1; i++)
            {
                element2 = values[i];
                values[i] = element;
                element = element2;
            }
        }
        

        size++;
    }

    ~Vector()
    {
        delete[] values;
    }

    ElementType erase(size_t index)
    {
        ElementType element = values[index];
        ElementType* new_values = new ElementType[size-1];
        int minas_new_index = 0;
        for (int i = 0; i<size; i++)
        {
            if (i==index) {
                minas_new_index++;
            }
            else {
                new_values[i-minas_new_index] = values[i];
            }
        }
        delete[] values;
        values = new_values;
        size--;
        capacity = size;
        return element;
    };
    ElementType operator [] (size_t index) {return values[index];};
    void push_back(ElementType element)
    {
        ElementType* new_values;
        if (capacity<=size)
        {
            capacity = (size+1)*2;
            new_values = new ElementType[capacity];
            for (int i = 0; i<=size; i++)
            {
                new_values[i] = values[i];
            }
            new_values[size] = element;
            delete[] values;
            values = new_values;
        }
        else
        {
            values[size] = element;
        }
        

        size++;
    }
    ElementType pop_back()
    {
        size--;
        ElementType* new_values = new ElementType[size];
        for (int i = 0; i<size; i++)
        {
            new_values[i] = values[i];
        }
        ElementType element = values[size];
        delete[] values;
        values = new_values;
        capacity = size;
        return element;
    }
};