#include <iostream>
#include <string>
#include <stdexcept>

template<typename T>
class Stack {
private:
    T* data;         
    size_t capacity;   
    size_t size;     

public:

    Stack() : data(nullptr), capacity(0), size(0) {
        capacity = 10; 
        data = new T[capacity];
    }
    
    Stack(const Stack& other) : capacity(other.capacity), size(other.size) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }


    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    Stack(Stack&& other) noexcept : data(other.data), capacity(other.capacity), size(other.size) {
        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }
    
    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            capacity = other.capacity;
            size = other.size;
            other.data = nullptr;
            other.capacity = 0;
            other.size = 0;
        }
        return *this;
    }
    
    ~Stack() {
        delete[] data;
    }
    
    T& Top() {
        if (Empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data[size - 1];
    }

    const T& Top() const {
        if (Empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data[size - 1];
    }
    
    T Pop() {
        if (Empty()) {
            throw std::runtime_error("Stack is empty");
        }
        T element = data[size - 1];
        --size;
        return element;
    }

    
    void Push(const T& element) {
        if (size >= capacity) {
           
            capacity *= 2;
            T* newData = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size] = element;
        ++size;
    }


    size_t Size() const {
        return size;
    }
    
    bool Empty() const {
        return size == 0;
    }

    void PrintStack() const {
        std::cout << "Stack contents (top to bottom): ";
        if (Empty()) {
            std::cout << "empty";
        } else {
            for (int i = size - 1; i >= 0; --i) {
                std::cout << data[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};

template<typename T>
void PrintStackContents(const Stack<T>& stack) {
    Stack<T> tempStack = stack; 
    std::cout << "Stack contents (top to bottom): ";
    
    if (tempStack.Empty()) {
        std::cout << "empty";
    } else {
        Stack<T> reverseStack;
        while (!tempStack.Empty()) {
            reverseStack.Push(tempStack.Pop());
        }
        
        while (!reverseStack.Empty()) {
            std::cout << reverseStack.Pop() << " ";
        }
    }
    std::cout << std::endl;
}

bool CheckBrackets(const std::string& str) {
    Stack<char> bracketStack;
    
    for (char ch : str) {
        if (ch == '(' || ch == '{' || ch == '[') {
            bracketStack.Push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (bracketStack.Empty()) {
                return false; 
            }
            
            char topBracket = bracketStack.Pop();
            
            if ((ch == ')' && topBracket != '(') ||
                (ch == '}' && topBracket != '{') ||
                (ch == ']' && topBracket != '[')) {
                return false;
            }
        }

    }

    return bracketStack.Empty();
}

int main() {
    system("chcp 65001");
    std::cout << "=== Тестирование класса Stack ===\n";
    
    Stack<int> intStack;
    
    intStack.Push(1);
    intStack.Push(2);
    intStack.Push(3);
    
    std::cout << "Размер стека: " << intStack.Size() << std::endl;
    std::cout << "Стек пуст? " << (intStack.Empty() ? "Да" : "Нет") << std::endl;
    
    PrintStackContents(intStack);
    
    std::cout << "Элемент на вершине: " << intStack.Top() << std::endl;
    
    int poppedElement = intStack.Pop();
    std::cout << "Удален элемент: " << poppedElement << std::endl;
    std::cout << "Новый размер: " << intStack.Size() << std::endl;
    
    PrintStackContents(intStack);
    
    std::cout << "\n=== Тестирование проверки скобок ===\n";
    
    std::string testStrings[] = {
        "(1{2[test]})",      
        "(1{2[test}])",   
        "((()))",            
        "([{}])",         
        "([)]",           
        "",                 
        "abc",            
        "(((",               
        ")))",               
        "(a[b{c}d]e)"        
    };
    
    for (const std::string& test : testStrings) {
        bool result = CheckBrackets(test);
        std::cout << "\"" << test << "\" -> " 
                  << (result ? "OK" : "NOT OK") << std::endl;
    }
    
    return 0;
}