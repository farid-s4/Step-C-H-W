#include <iostream>
#include <string>
#include <fstream>
template <typename T>
class SuperVector
{
private:
    T* _data;
    int _size;
    int _capacity;
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

    void Pop()
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
    
    void Remove(size_t index)
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
    

    void Insert(T index, T value)
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

    void PushBack(T value)
    {

        if (_size == _capacity && _capacity == 0 )
        {
            ResizeArray(_capacity * 2);
            ResizeArray(_capacity + 1);
        }
        
        _data[_size] = value;
        _size++;
        
    }
    void Set(T index, T value)
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


class expedition {
protected:
    std::string _target;
    unsigned short _year;
    int _temp;
public:
    expedition() : _target("unknown"), _year(0), _temp(0) {}
    expedition(std::string target, unsigned short y, int temp) : _target(target), _year(y), _temp(temp) {}
    expedition(const expedition& other) {
        _target = other._target;
        _year = other._year;
        _temp = other._temp;
    }
    void setTarget(const std::string& target) {
        _target = target;
    }

    void setYear(unsigned short year) {
        _year = year;
    }

    void setTemp(int temp) {
        _temp = temp;
    }
    virtual void print_info() = 0;
    virtual void writeEXP(const std::string& fileName) = 0;

    virtual ~expedition() {}
};

class northPex : public expedition {
public:
    void print_info() override {
        std::cout << "NORTH\n"
            << "Target: "<< _target 
            << "\nYear: " << _year 
            << "\nTemperature: " << _temp;
    }
    void writeEXP(const std::string& fileName) override
    {
        
        std::ofstream outFile(fileName);

        if (!outFile)
        {
            return;
        }
        
        outFile << "NORTH\n" << _target << '\n' << _year << '\n' << _temp;

        outFile.close();
    }

};
class southPex : public expedition {
public:
    void print_info() override {
        std::cout << "SOUTH\n"
            << "Target: " << _target
            << "\nYear: " << _year
            << "\nTemperature: " << _temp;
    }
    void writeEXP(const std::string& fileName) override
    {

        std::ofstream outFile(fileName);

        if (!outFile)
        {
            return;
        }

        outFile << "SOUTH\n" << _target << '\n' << _year << '\n' << _temp;

        outFile.close();
    }
};

expedition* readFile(const std::string& filename)
{
    std::ifstream fin(filename);
    if (!fin)
    {
        return nullptr;
    }
    std::string name, type, target;
    unsigned short year;
    int temp;
    fin >> name;
    if (name == "NORTH")
    {
        auto* ex = new northPex();
        fin >> target >> year >> temp;
        ex->setTarget(target);
        ex->setYear(year);
        ex->setTemp(temp);
        return ex;
    }
    else if (name == "SOUTH")
    {
        auto* ex = new southPex();
        fin >> target >> year >> temp;
        ex->setTarget(target);
        ex->setYear(year);
        ex->setTemp(temp);
        return ex;
    }
    else
    {
        return nullptr;
    }
}

int main()
{
    SuperVector<expedition*> ex = {};
    expedition* a = readFile("expedition.txt");

    northPex* north = dynamic_cast<northPex*>(a);
    
    ex.PushBack(a);
    ex[0]->print_info();
    
    northPex* n = static_cast<northPex*>(ex[0]);
    ex[0]->writeEXP("expOut.txt");
}
 
