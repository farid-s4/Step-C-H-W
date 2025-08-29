#include <iostream>
#include <vector>
#include <functional>

template<typename K, typename V>
class HashTable
{
private:
    struct HashNode
    {
        K key;
        V value;
        bool occupied = false;
        bool deleted = false;
    };

    std::vector<HashNode> table;
    size_t elementCount = 0;
    size_t capacity;

    float maxLoadFactor = 0.7f;

    void Rehash()
    {
        size_t oldCapacity = capacity;
        capacity *= 2;
        std::vector<HashNode> oldTable = std::move(table);
        table = std::vector<HashNode>(capacity);
        elementCount = 0;

        for (size_t i = 0; i < oldCapacity; ++i)
        {
            if (oldTable[i].occupied && !oldTable[i].deleted)
            {
                Add(oldTable[i].key, oldTable[i].value);
            }
        }
    }

    size_t HashFunc(const K& key) const
    {
        return std::hash<K>{}(key) % capacity;
    }

public:
    HashTable(size_t initialCapacity = 16) : capacity(initialCapacity), table(initialCapacity) {}
    
    HashTable(const HashTable& other)
        : table(other.table), elementCount(other.elementCount), capacity(other.capacity) {}
    
    HashTable& operator=(const HashTable& other)
    {
        if (this != &other)
        {
            table = other.table;
            elementCount = other.elementCount;
            capacity = other.capacity;
        }
        return *this;
    }
    
    HashTable(HashTable&& other) noexcept
        : table(std::move(other.table)), elementCount(other.elementCount), capacity(other.capacity)
    {
        other.elementCount = 0;
        other.capacity = 0;
    }
    
    HashTable& operator=(HashTable&& other) noexcept
    {
        if (this != &other)
        {
            table = std::move(other.table);
            elementCount = other.elementCount;
            capacity = other.capacity;
            other.elementCount = 0;
            other.capacity = 0;
        }
        return *this;
    }
    
    ~HashTable() = default;


    void Add(const K& key, const V& value)
    {
        if (GetLoadFactor() >= maxLoadFactor)
        {
            Rehash();
        }

        size_t idx = HashFunc(key);
        size_t originalIdx = idx;
        size_t i = 0;

        while (table[idx].occupied && !table[idx].deleted)
        {
            if (table[idx].key == key)
            {
                table[idx].value = value;
                return;
            }
            idx = (originalIdx + ++i) % capacity;
        }

        table[idx].key = key;
        table[idx].value = value;
        table[idx].occupied = true;
        table[idx].deleted = false;
        elementCount++;
    }
    
    V& operator()(const K& key)
    {
        if (GetLoadFactor() >= maxLoadFactor)
        {
            Rehash();
        }

        size_t idx = HashFunc(key);
        size_t originalIdx = idx;
        size_t i = 0;

        while (table[idx].occupied)
        {
            if (!table[idx].deleted && table[idx].key == key)
            {
                return table[idx].value;
            }
            idx = (originalIdx + ++i) % capacity;
            if (i == capacity)
                break;
        }
        
        Add(key, V{});
        return (*this)(key);
    }
    
    void Remove(const K& key)
    {
        size_t idx = HashFunc(key);
        size_t originalIdx = idx;
        size_t i = 0;

        while (table[idx].occupied)
        {
            if (!table[idx].deleted && table[idx].key == key)
            {
                table[idx].deleted = true;
                elementCount--;
                return;
            }
            idx = (originalIdx + ++i) % capacity;
            if (i == capacity)
                return; 
        }
    }
    
    float GetLoadFactor() const
    {
        return static_cast<float>(elementCount) / static_cast<float>(capacity);
    }
    
    void Print() const
    {
        std::cout << "HashTable contents:\n";
        for (size_t i = 0; i < capacity; ++i)
        {
            if (table[i].occupied && !table[i].deleted)
            {
                std::cout << "[" << i << "] " << table[i].key << " : " << table[i].value << "\n";
            }
        }
        std::cout << "Load factor: " << GetLoadFactor() << "\n";
    }
};


int main()
{
    HashTable<std::string, int> ht;

    ht.Add("one", 1);
    ht.Add("two", 2);
    ht.Add("three", 3);

    ht.Print();

    std::cout << "Value for 'two': " << ht("two") << "\n";

    ht("four") = 4; 

    ht.Print();

    ht.Remove("two");
    ht.Print();

    std::cout << "Load factor: " << ht.GetLoadFactor() << std::endl;

    return 0;
}
