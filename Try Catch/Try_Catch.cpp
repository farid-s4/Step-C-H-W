#include <iostream>
#include <fstream>
#include <bitset>
#include <stdexcept>
class FileViewer
{
protected:
    std::ifstream file;
public:
    virtual void Display(const char* path) = 0;
    virtual ~FileViewer(){}
};

class TextViewer : public FileViewer
{
    public:
    void Display(const char* path) override
    {
        file.open(path);
        if (!file.is_open())
        {
            throw std::exception("Could not open file");
        }
        char str[256]; 

        while (file.getline(str, 256)) {
            std::cout << str << '\n';
        }

        file.close();
        
    }
};
class AsciiViewer : public FileViewer
{
    public:
    void Display(const char* path) override
    {
        file.open(path);
        if (!file.is_open())
        {
            throw std::exception("Could not open file");
        }
        char str[256];
        while (file.getline(str, 256)) {
            for (int i = 0; i < std::strlen(str); i++)
            {
                std::cout << (int)(unsigned char)str[i] << ' ';
            }
            std::cout << '\n';
        }

        file.close();
    }
};
class BinaryViewer : public FileViewer
{
    public:
    void Display(const char* path) override
    {
        file.open(path);
        if (!file.is_open())
        {
            throw std::exception("Could not open file");
        }
        
        char str[256];
        while (file.getline(str, 256))
        {
            for (int i = 0; i < std::strlen(str); i++)
            {
                std::cout << std::bitset<8>(str[i]) << ' ';
            }
        }
        file.close();
    }
};

int main()
{
    const char* path = "file.txt";
    const char* path2 = "file.txt";
    const char* path3 = "file.txt";
    try
    {
        TextViewer p;
        p.Display(path);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what();
    }
    try
    {
        BinaryViewer p;
        p.Display(path2);
    }
    catch 
}
