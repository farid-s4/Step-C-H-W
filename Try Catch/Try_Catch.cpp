#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <bitset>
#include <stdexcept>

class FileException : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "FileException";
    }
};
class FileOpenException : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "FileOpenException";
    }
};
class FileReadException : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "FileReadException";
    }
};


class FileViewer
{
protected:
    FILE* file;
public:
    virtual void Display(const char* path) = 0;
    ~FileViewer() {
        if (file) {
            fclose(file);
        }
    }
};
class TextViewer : public FileViewer
{
public:
    void Display(const char* path) override
    {
        char str[256];
        if (file == fopen("file.txt", "r")) {
            throw FileOpenException();
        };


        if (file == nullptr) {
            throw FileException();
        }

        while (int count = fread(str, sizeof(char), sizeof(str), file)) {
            str[count] = '\0';
            std::cout << str;
        }

        if (ferror(file)) {
            throw FileReadException();
        }

        fclose(file);
    }
};

class AsciViewer : public FileViewer
{
public:
    void Display(const char* path) override
    {
        char str[256];
        if (file == fopen("file.txt", "r")) {
            throw FileOpenException();
        };


        if (file == nullptr) {
            throw FileException();
        }

        while (int count = fread(str, sizeof(char), sizeof(str), file)) {
            str[count] = '\0';
            for (size_t i = 0; i < count; i++)
            {
                std::cout << static_cast<int>(str[i]);
            }
        }

        if (ferror(file)) {
            throw FileReadException();
        }

        fclose(file);
    }
};

class BinaryViewer : public FileViewer
{
public:
    void Display(const char* path) override
    {
        char str[256];
        if (file == fopen("file.txt", "r")) {
            throw FileOpenException();
        };

        if (file == nullptr) {
            throw FileException();
        }

        while (int count = fread(str, sizeof(char), sizeof(str), file)) {
            str[count] = '\0';
            for (size_t i = 0; i < count; i++)
            {
                std::cout << std::bitset<8>(str[i]);
            }
        }

        if (ferror(file)) {
            throw FileReadException();
        }

        fclose(file);
    }
};

int main() {
    TextViewer f;
    try
    {
        f.Display("file.txt");
    }
    catch (const FileOpenException& e)
    {
        std::cout << e.what();
    }
    
}

