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
            return *this;
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
            return *this;
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
        Head = Head->My_Next;
        Head->My_Prev = nullptr;
        Size--;
    }
    void PopBack()
    {
        if (Size == 0)
        {
            return;
        }
        Tail = Tail->My_Prev;
        Tail->My_Next = nullptr;
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
            Head = Head->My_Next;
            delete Node;
            Node = Head;
        }
        Head = nullptr;
        Tail = nullptr;
        Size = 0;
    }
    bool IsEmpty() const
    {
        if (Size != 0)
        {
            return false;
        }
        return true;
    }
    LinkedListNode<TType>& InsertAfter(const TType& Value, LinkedListNode<TType>* node)
    {
        auto NewNode = new LinkedListNode<TType>;
        NewNode->My_Value = Value;

        if (Size == 0)
        {
            Head = Tail = NewNode;
        }
        else
        {
            auto next_temp = node->My_Next;
            auto prev_temp = node->My_Prev;
            node->My_Next = NewNode;
            NewNode->My_Prev = node;
            NewNode->My_Next = next_temp;
            NewNode->My_Prev = prev_temp;
        }
        ++Size;
        return *NewNode;
    }
    void RemoveAtNode(LinkedListNode<TType>* node)
    {
        if (Size == 0)
        {
            return;
        }
        if (node->My_Next == nullptr)
        {
            Tail = Tail->My_Prev;
            Tail->My_Next = nullptr;
            Size--;
        }
        if (node->My_Prev == nullptr)
        {
            Head = Head->My_Next;
            Head->My_Prev = nullptr;
            Size--;
        }
        else
        {
            node->My_Prev->My_Next = node->My_Next;
            node->My_Next->My_Prev = node->My_Prev;
        }
        
        Size--;
    }
    void Reverse()
    {
        if (Size == 0)
        {
            return;
        }
        LinkedListNode<TType>* temp = nullptr;
        while (Head != nullptr) {
            temp = Head->My_Prev;
            Head->My_Prev = Head->My_Next;
            Head->My_Next = temp;
            Head = Head->My_Prev; 
        }
        
        if (temp != nullptr) {
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
        if (Size == 0)
        {
            return;
        }
        auto Node = Head;
        while (Node != nullptr)
        {
            Head = Head->My_Next;
            delete Node;
            Node = Head;
        }
        Head = nullptr;
        Tail = nullptr;
        Size = 0;
    }
};

int main(int argc, char* argv[])
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
    Test.Clear();

}
