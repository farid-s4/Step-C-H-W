#include <iostream>
#include <initializer_list>
template <typename T>

class SuperVector
{
private:
    T* _data;
    T _size;
    T _capacity;
public:
    SuperVector() : _data(nullptr), _size(0), _capacity(0){}
    SuperVector(std::initializer_list<T> init_list) : _size(init_list.size()), _capacity(init_list.size())
    {
        
        _data = new T[_capacity];
        size_t i = 0;
        for (auto value : init_list)
        {
            _data[i++] = value;
        }
        
    }
    
    SuperVector(T size) : _size(size), _capacity(size)
    {
        
        _data = new T[_capacity];
        
    }

    SuperVector(const SuperVector& other): _size(other._size), _capacity(other._capacity)
    {
        _data = new T[_capacity]; 
        for (size_t i = 0; i < _size; i++)
        {
            _data[i] = other._data[i]; 
        }
    }
    
    T Get(int index) const
    {
        if (index < _size)
        {
            return _data[index];
        }
        return T();
    }

    T Size() const
    {
        return _size;
    }

    ~SuperVector()
    {
        delete[] _data;
        
    }
    
    void ResizeArray(size_t NewCapacity)
    {
        T *TempData = new T[NewCapacity];
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
    

    void Insert(SuperVector &other, T index, T value)
    {
        if (_size == _capacity)
        {
            ResizeArray(_capacity * 2);
        }
        index  -= 1;
        T* temp_data = new T[_capacity];

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

    void PushBack(SuperVector &other, T value)
    {
        if (_size == _capacity)
        {
            ResizeArray(_capacity * 2);
        }
        
        _data[_size] = value;
        _size++;
        
    }
    void Set(SuperVector &other ,T index, T value)
    {
        _data[index - 1] = value;
    }

    T operator[](int index)
    {
        if (index < _size)
        {
            return _data[index];
        }
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
        bool flag = true;
        for (size_t i = 0; i < other._size; i++)
        {
            if (other._data[i] == 0) {
                flag = false;
                
            }
        }
        if (flag == true) {
            if (_size <= other._size) {
                for (size_t i = 0; i < _size; i++)
                {
                    _data[i] /= other._data[i];
                }
                return *this;
            }
            else {
                for (size_t i = 0; i < other._size; i++)
                {
                    _data[i] /= other._data[i];
                }
                return *this;
            }
        }
        else {
            return other;
        }
    }
    

    
    
};
template <typename T>
void DisplayVector(const SuperVector<T> &vector)
{
    for (int i = 0; i < vector.Size(); ++i)
    {
        std::cout<<vector.Get(i)<< " ";
    }
}



int main()
{

    SuperVector<float> vector = {1.2, 2.2, 3.1, 4.7, 5.2};
    SuperVector<float> vector2 = {4.5, 0.2, 9.1, 21.7, 32.2};

    DisplayVector(vector + vector2);

    
    
    
    return 0;       
}
