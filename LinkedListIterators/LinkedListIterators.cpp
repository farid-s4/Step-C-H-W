#include <iostream>

template <typename TType>
struct LinkedListNode
{
    TType My_Value{};
    LinkedListNode* My_Next{};
    LinkedListNode* My_Prev{};
};

template <typename TType>
class LinkedList
{
public:
    class Iterator
    {
    private:
        LinkedListNode<TType>* NodePtr;
    public:
        explicit Iterator(LinkedListNode<TType>* ptr = nullptr) : NodePtr(ptr) {}
        
        Iterator& operator++()
        {
            if (NodePtr) NodePtr = NodePtr->My_Next;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--()
        {
            if (NodePtr) NodePtr = NodePtr->My_Prev;
            return *this;
        }
        Iterator operator--(int)
        {
            Iterator temp = *this;
            --(*this);
            return temp;
        }
        Iterator operator+(int n) const
        {
            Iterator temp = *this;
            if (n >= 0)
            {
                for (int i = 0; i < n; ++i)
                {
                    if (temp.NodePtr) temp.NodePtr = temp.NodePtr->My_Next;
                    else break;
                }
            }
            else 
            {
                for (int i = 0; i < -n; ++i)
                {
                    if (temp.NodePtr) temp.NodePtr = temp.NodePtr->My_Prev;
                    else break;
                }
            }
            return temp;
        }
        Iterator operator-(int n) const
        {
            return (*this) + (-n);
        }
        
        TType& operator*() const
        {
            return NodePtr->My_Value;
        }
        
        bool operator==(const Iterator& other) const
        {
            return NodePtr == other.NodePtr;
        }
        bool operator!=(const Iterator& other) const
        {
            return NodePtr != other.NodePtr;
        }
    };

private:
    LinkedListNode<TType>* Head{};
    LinkedListNode<TType>* Tail{};
    int Size{};

public:
    LinkedList() : Size(0), Head(nullptr), Tail(nullptr) {}
    LinkedList(LinkedListNode<TType>* head, LinkedListNode<TType>* tail, int size) : Head(head), Tail(tail), Size(size) {}
    LinkedList(const LinkedList<TType>& other) : Head(other.Head), Tail(other.Tail), Size(other.Size) {}
    LinkedList& operator=(const LinkedList<TType>& other)
    {
        if (this != &other)
        {
            this->Head = other.Head;
            this->Tail = other.Tail;
            this->Size = other.Size;
        }
        return *this;
    }
    LinkedList(LinkedList&& other) noexcept : Head(std::move(other.Head)), Tail(std::move(other.Tail)), Size(std::move(other.Size)) {}
    LinkedList& operator=(LinkedList&& other) noexcept 
    {
        if (this != &other)
        {
            this->Head = std::move(other.Head);
            this->Tail = std::move(other.Tail);
            this->Size = std::move(other.Size);
        }
        return *this;
    }
    LinkedListNode<TType>& InsertAtEnd(const TType& Value)
    {
        auto NewNode = new LinkedListNode<TType>;
        NewNode->My_Value = Value;

        if (Size == 0)
        {
            Head = Tail = NewNode;
        }
        else
        {
            Tail->My_Next = NewNode;
            NewNode->My_Prev = Tail;
            Tail = NewNode;
        }
        ++Size;
        return *NewNode;
    }
    void PopFront()
    {
       if (Size == 0)
       {
           return;
       }
        auto temp = Head;
        Head = Head->My_Next;
        if (Head)
            Head->My_Prev = nullptr;
        else
            Tail = nullptr; 
        delete temp;
        Size--;
    }
    void PopBack()
    {
        if (Size == 0)
        {
            return;
        }
        auto temp = Tail;
        Tail = Tail->My_Prev;
        if (Tail)
            Tail->My_Next = nullptr;
        else
            Head = nullptr; 
        delete temp;
        Size--;
    }
    void Clear()
    {
        if (Size == 0)
        {
            return;
        }
        auto Node = Head;
        while (Node != nullptr)
        {
            auto temp = Node;
            Node = Node->My_Next;
            delete temp;
        }
        Head = nullptr;
        Tail = nullptr;
        Size = 0;
    }
    bool IsEmpty() const
    {
        return Size == 0;
    }
    LinkedListNode<TType>& InsertAfter(const TType& Value, LinkedListNode<TType>* node)
    {
        auto NewNode = new LinkedListNode<TType>;
        NewNode->My_Value = Value;

        if (Size == 0 || node == nullptr)
        {
            Head = Tail = NewNode;
        }
        else
        {
            auto next_temp = node->My_Next;
            node->My_Next = NewNode;
            NewNode->My_Prev = node;
            NewNode->My_Next = next_temp;
            if (next_temp)
                next_temp->My_Prev = NewNode;
            else
                Tail = NewNode;
        }
        ++Size;
        return *NewNode;
    }
    void RemoveAtNode(LinkedListNode<TType>* node)
    {
        if (Size == 0 || node == nullptr)
        {
            return;
        }
        if (node->My_Prev)
            node->My_Prev->My_Next = node->My_Next;
        else
            Head = node->My_Next;

        if (node->My_Next)
            node->My_Next->My_Prev = node->My_Prev;
        else
            Tail = node->My_Prev;

        delete node;
        Size--;
    }
    void Reverse()
    {
        if (Size == 0)
        {
            return;
        }
        LinkedListNode<TType>* current = Head;
        LinkedListNode<TType>* temp = nullptr;
        while (current != nullptr)
        {
            temp = current->My_Prev;
            current->My_Prev = current->My_Next;
            current->My_Next = temp;
            current = current->My_Prev;
        }
        if (temp != nullptr)
        {
            Tail = Head;
            Head = temp->My_Prev;
        }
    }
    void Print() const
    {
        auto Current = Head;
        while (Current != nullptr)
        {
            std::cout << Current->My_Value << " ";
            Current = Current->My_Next;
        }
        std::cout << std::endl;
    }

    ~LinkedList()
    {
        Clear();
    }
    
    Iterator begin() { return Iterator(Head); }
    Iterator end() { return Iterator(nullptr); }
    Iterator begin() const { return Iterator(Head); }
    Iterator end() const { return Iterator(nullptr); }
};

int main()
{
    LinkedList<int> Test;
    Test.InsertAtEnd(10);
    auto second = &Test.InsertAtEnd(20);
    auto third = &Test.InsertAtEnd(30);
    Test.InsertAtEnd(40);
    Test.InsertAtEnd(50);

    Test.PopFront();
    Test.Print();
    Test.PopBack();
    Test.Print();
    std::cout << Test.IsEmpty() << '\n';
    Test.InsertAfter(9999, second);
    Test.Print();
    Test.RemoveAtNode(third);
    Test.Print();
    Test.Reverse();
    Test.Print();
    
    for (auto it = Test.begin(); it != Test.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    auto it = Test.begin();
    it = it + 2;
    std::cout << *it << std::endl;

    Test.Clear();
}
