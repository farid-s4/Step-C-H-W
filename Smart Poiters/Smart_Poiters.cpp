/*#include <iostream>
template <typename T>
class UniquePtr
{
private:
    T* ptr;
public:
    UniquePtr() noexcept : ptr(nullptr) {}
    explicit UniquePtr(T* ptr) noexcept : ptr(ptr) {}
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& other) noexcept
    {
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    ~UniquePtr()
    {
        delete ptr;
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
    void reset(T* p = nullptr)  noexcept
    {
        if (p != ptr)
        {
            delete ptr;
            ptr = p;
        }
    }
};


int main() {
    return 0;
}

/////////////////////////////////////////////////////////*/
#include <iostream>
#include <cassert>
template <typename T>
class SharedPtr
{
private:
    T* ptr;
    int* count;
public:
    SharedPtr() noexcept : ptr(nullptr), count(new int(0)) {}
    explicit SharedPtr(T* ptr) noexcept : ptr(ptr) {}
    SharedPtr(const SharedPtr& other)
    {
        ptr = other.ptr;
        count++;
    }
    SharedPtr& operator=(const SharedPtr& other)
    {
        if (this != &other)
        {
            ptr = other.ptr;
            count++;
        }
    }
    SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), count(other.count)
    {
        other.ptr = nullptr;
        count = nullptr;
    }
    SharedPtr& operator=(SharedPtr&& other) noexcept
    {
        ptr = other.ptr;
        count = other.count;
    }
    ~SharedPtr()
    {
        if (count != 0)
        {
            count--;
        }
        if (count == 0)
        {
            delete ptr;
        }
    }
    int GetCount() const noexcept
    {
        return *count;
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
    void reset(T* p = nullptr)  noexcept
    {
        if (p != ptr)
        {
            delete ptr;
            ptr = p;
            count--;
        }
    }
};


int main() {
    return 0;
}
