#include <iostream>

class SuperVector
{
private:
    int* _data;
    size_t _size;
    size_t _capacity;
public:
    SuperVector() : _data(nullptr), _size(0), _capacity(0){}

    
    SuperVector(size_t size) : _size(size), _capacity(size)
    {
        
        _data = new int[_capacity];
        
    }

    SuperVector(const SuperVector& other): _size(other._size), _capacity(other._capacity)
    {
        _data = new int[_capacity]; 
        for (size_t i = 0; i < _size; i++)
        {
            _data[i] = other._data[i]; 
        }
    }
    
    int Get(size_t index) const
    {
        if (index < _size)
        {
            return _data[index];
        }
        return 0;
    }

    size_t Size() const
    {
        return _size;
    }

    ~SuperVector()
    {
        delete[] _data;
        
    }
    
    void ResizeArray(size_t NewCapacity)
    {
        int *TempData = new int[NewCapacity];
        for (size_t i = 0; i < _size; i++)
        {
            TempData[i] = _data[i];
        }
        delete[] _data;
        _data = TempData;
        _capacity = NewCapacity;
        
    }

    void Pop(SuperVector other)
    {
        if (_size > 0)
        {
            _size--;
            if (_size < _capacity / 2)
            {
                ResizeArray(_capacity/2);
            }
        }
    }
    
    void Remove(SuperVector &other, size_t index)
    {
        for (size_t i = index; i < _size; i++)
        {
            _data[i] = _data[i + 1];
        }
        
        if (_size > 0)
        {
            _size--;
            if (_size < _capacity / 2)
            {
                ResizeArray(_capacity/2);
            }
        }
    }
    
    void FillArray(SuperVector *other)
    {
        for (size_t i = 0; i < _size; ++i)
        {
            _data[i] = i + 1;
        }

    }

    void Insert(SuperVector &other, size_t index, int value)
    {
        if (_size == _capacity)
        {
            ResizeArray(_capacity * 2);
        }
        index  -= 1;
        int* temp_data = new int [_capacity];

        for (size_t i = 0; i < index; i++)
        {
            temp_data[i] = _data[i];
        }
        
        temp_data[index] = value;

        for (size_t i = index; i < _size; i++)
        {
            temp_data[i + 1] = _data[i];
        }
        delete[] _data;
        _data = temp_data;
        _size++;
    }

    void PushBack(SuperVector &other, int value)
    {
        if (_size == _capacity)
        {
            ResizeArray(_capacity * 2);
        }
        
        _data[_size] = value;
        _size++;
        
    }
    void Set(SuperVector &other ,size_t index, int value)
    {
        _data[index - 1] = value;
    }

    size_t operator[](size_t index)
    {
        return _data[index];
    }

    SuperVector& operator+(SuperVector &other)
    {
        for (size_t i = 0; i < _size; i++)
        {
            _data[i] += other._data[i];
        }
        return *this;
    }
    SuperVector& operator-(SuperVector &other)
    {
        for (size_t i = 0; i < _size; i++)
        {
            _data[i] -= other._data[i];
        }
        return *this;
    }
    SuperVector& operator*(SuperVector &other)
    {
        for (size_t i = 0; i < _size; i++)
        {
            _data[i] *= other._data[i];
        }
        return *this;
    }
    SuperVector& operator/(SuperVector &other)
    {
        for (size_t i = 0; i < _size; i++)
        {
            _data[i] /= other._data[i];
        }
        return *this;
    }

    
    
};

void DisplayVector(const SuperVector& vector)
{
    for (size_t i = 0; i < vector.Size(); ++i)
    {
        std::cout<<vector.Get(i)<< " ";
    }
}



int main()
{

    SuperVector temp(5);
    
    SuperVector other(5);

    temp.FillArray(&temp);
    
    other.FillArray(&other);
    
    DisplayVector(other /  temp);
    
    
    return 0;       
}
