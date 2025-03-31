
/*#include <iostream>
template <typename T>
class UniquePtr
{
private:
    T* ptr;
public:
    UniquePtr() : ptr(nullptr) {}
    UniquePtr(T* ptr) : ptr(ptr) {}
    UniquePtr(UniquePtr<T>&& other) noexcept 
    {
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    UniquePtr<T>& operator=(UniquePtr<T>&& other) noexcept
    {
        if (this != &other)
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    T* get () 
    {
        return ptr;
    }
    T& operator* () const 
    {
        return *ptr;
    }
    T* operator-> () const
    {
        return ptr;
    }
    void reset()
    {
        delete ptr;
        ptr = nullptr;
    }
    ~UniquePtr()
    {
        delete ptr;
    }
};

int main()
{
    UniquePtr<int> up1(new int(10));
    std::cout << *up1 << '\n'; 


    UniquePtr<int> up2(std::move(up1));
    if (!up1.get())
        std::cout << "up1 is empty\n"; 
    
    std::cout << *up2 << '\n'; 
    up2.reset();
    if (!up2.get())
        std::cout << "up2 is empty\n"; 

    return 0;
}*/

#include <iostream>
template <typename T>
class SharedPtr
{
private:
    T* ptr;
    unsigned int* count;
    
public:
    explicit SharedPtr() : ptr(nullptr), count(new unsigned int(1)) {}

    SharedPtr(const SharedPtr<T>& other)
    {
        ptr = other.ptr;
        count = other.count;
        ++(*count);
    }
    SharedPtr& operator=(const SharedPtr<T>& other)
    {
        if (this != &other)
        {
            delete count;
            count = other.count;
            delete ptr;
            ptr = other.ptr;
            --(*count);
            return SharedPtr<T>(*this);
        }
    }

    T* get()
    {
        return ptr;
    }
    T* operator->()
    {
        return ptr;
    }
    T& operator*()
    {
        return *ptr;
    }
    void reset()
    {
        delete ptr;
        delete count;
        ptr = nullptr;
        count = 0;
    }
    ~SharedPtr()
    {
        if (ptr && --(*count) == 0)
        {
            delete ptr;
            delete count;
        }
    }
};
int main()
{
    
}
