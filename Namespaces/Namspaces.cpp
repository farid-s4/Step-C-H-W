#include <iostream>
#include <stdexcept>

template<typename T>
class Queue {
private:
    T* data;          
    size_t capacity;   
    size_t size;       
    size_t front_idx; 
    size_t back_idx;   


    void resize() {
        size_t new_capacity = capacity * 2;
        T* new_data = new T[new_capacity];

        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[(front_idx + i) % capacity];
        }
        
        delete[] data;
        data = new_data;
        capacity = new_capacity;
        front_idx = 0;
        back_idx = size > 0 ? size - 1 : 0;
    }

public:
    Queue() : data(nullptr), capacity(10), size(0), front_idx(0), back_idx(0) {
        data = new T[capacity];
    }
    
    Queue(const Queue& other) : capacity(other.capacity), size(other.size), 
                               front_idx(0), back_idx(other.size > 0 ? other.size - 1 : 0) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[(other.front_idx + i) % other.capacity];
        }
    }
    
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            front_idx = 0;
            back_idx = size > 0 ? size - 1 : 0;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[(other.front_idx + i) % other.capacity];
            }
        }
        return *this;
    }
    
    Queue(Queue&& other) noexcept : data(other.data), capacity(other.capacity), 
                                   size(other.size), front_idx(other.front_idx), 
                                   back_idx(other.back_idx) {
        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
        other.front_idx = 0;
        other.back_idx = 0;
    }
    
    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            capacity = other.capacity;
            size = other.size;
            front_idx = other.front_idx;
            back_idx = other.back_idx;
            
            other.data = nullptr;
            other.capacity = 0;
            other.size = 0;
            other.front_idx = 0;
            other.back_idx = 0;
        }
        return *this;
    }
    
    ~Queue() {
        delete[] data;
    }
    
    T& Front() {
        if (Empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return data[front_idx];
    }

    const T& Front() const {
        if (Empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return data[front_idx];
    }
    
    T& Back() {
        if (Empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return data[back_idx];
    }

    const T& Back() const {
        if (Empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return data[back_idx];
    }
    
    T Dequeue() {
        if (Empty()) {
            throw std::runtime_error("Queue is empty");
        }
        
        T element = data[front_idx];
        front_idx = (front_idx + 1) % capacity;
        --size;
        
        return element;
    }
    
    void Enqueue(const T& element) {
        if (size >= capacity) {
            resize();
        }
        
        if (Empty()) {
            front_idx = 0;
            back_idx = 0;
        } else {
            back_idx = (back_idx + 1) % capacity;
        }
        
        data[back_idx] = element;
        ++size;
    }
    
    size_t Count() const {
        return size;
    }
    
    bool Empty() const {
        return size == 0;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Queue<T>& queue) {
        os << "Queue (front to back): [";
        
        if (queue.Empty()) {
            os << "empty";
        } else {
            for (size_t i = 0; i < queue.size; ++i) {
                if (i > 0) os << ", ";
                os << queue.data[(queue.front_idx + i) % queue.capacity];
            }
        }
        
        os << "]";
        return os;
    }
};

int main() {
    Queue<int> intQueue;
    
    std::cout << intQueue << std::endl;
    std::cout << "Empty? " << (intQueue.Empty() ? "Yes" : "No") << std::endl;
    std::cout << "Size: " << intQueue.Count() << std::endl;
    
    intQueue.Enqueue(10);
    intQueue.Enqueue(20);
    intQueue.Enqueue(30);
    intQueue.Enqueue(40);
    intQueue.Enqueue(50);
    
    std::cout << intQueue << std::endl;
    std::cout << "Size: " << intQueue.Count() << std::endl;
    std::cout << "Front: " << intQueue.Front() << std::endl;
    std::cout << "Back: " << intQueue.Back() << std::endl;
    
    std::cout << "Dequeued: " << intQueue.Dequeue() << std::endl;
    std::cout << "Dequeued: " << intQueue.Dequeue() << std::endl;
    std::cout << intQueue << std::endl;
    std::cout << "Size: " << intQueue.Count() << std::endl;
    
    intQueue.Enqueue(60);
    intQueue.Enqueue(70);
    std::cout << intQueue << std::endl;
    
    Queue<int> copiedQueue = intQueue;
    std::cout << "Original: " << intQueue << std::endl;
    std::cout << "Copy:     " << copiedQueue << std::endl;
    
    copiedQueue.Enqueue(80);
    std::cout << "Original: " << intQueue << std::endl;
    std::cout << "Copy:     " << copiedQueue << std::endl;
    
    Queue<std::string> stringQueue;
    
    stringQueue.Enqueue("Hello");
    stringQueue.Enqueue("World");
    stringQueue.Enqueue("Queue");
    stringQueue.Enqueue("Test");
    
    std::cout << stringQueue << std::endl;
    std::cout << "First: " << stringQueue.Front() << std::endl;
    std::cout << "Last: " << stringQueue.Back() << std::endl;
    
    while (!stringQueue.Empty()) {
        std::cout << "Dequeued: \"" << stringQueue.Dequeue() << "\"" << std::endl;
        std::cout << "Remains: " << stringQueue << std::endl;
    }
    
    Queue<int> queue1;
    Queue<int> queue2;
    
    queue1.Enqueue(100);
    queue1.Enqueue(200);
    queue1.Enqueue(300);
    
    std::cout << "Queue1: " << queue1 << std::endl;
    std::cout << "Queue2: " << queue2 << std::endl;
    
    queue2 = queue1;
    std::cout << "Queue1: " << queue1 << std::endl;
    std::cout << "Queue2: " << queue2 << std::endl;
    
    Queue<int> bigQueue;
    
    for (int i = 1; i <= 15; ++i) {
        bigQueue.Enqueue(i * 10);
    }
    std::cout << bigQueue << std::endl;
    std::cout << "Size: " << bigQueue.Count() << std::endl;
    
    return 0;
}