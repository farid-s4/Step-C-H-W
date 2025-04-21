#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
class directory
{
    protected:
    std::string _name;
    std::string _owner;
    std::string _tel_num;
    std::string _adress;
    public:
    directory() : _name("unknown"), _owner("unknown"), _tel_num("unknown"), _adress("unknown") {}
    directory(std::string name, std::string owner, std::string tel_num, std::string adress ) : _name(name), _owner(owner), _tel_num(tel_num), _adress(adress) {}
    directory(const directory& other)
    {
        _name = other._name;
        _owner = other._owner;
        _tel_num = other._tel_num;
        _adress = other._adress;
    }
    directory& operator=(const directory& other)
    {
        _name = other._name;
        _owner = other._owner;
        _tel_num = other._tel_num; 
        _adress = other._adress;
        return *this;
    }
    std::string get_name()
    {
        return _name;
    }
    std::string get_owner()
    {
        return _owner;
    }
    std::string get_tel_num()
    {
        return _tel_num;
    }
    std::string get_adress()
    {
        return _adress;
    }
};

class dir_array 
{
private:
    std::vector<directory> _dir;
public:
    dir_array() : _dir() {}
    
    dir_array(const std::vector<directory>& dir) : _dir(dir) {}
    dir_array(const dir_array& other)
    {
        _dir = other._dir;
    }
    dir_array& operator=(const dir_array& other)
    {
        _dir = other._dir;
        return *this;
    }
    void find_by_name(const std::string& name)
    {
        for (size_t i = 0; i < _dir.size(); i++)
        {
            if (_dir[i].get_name() == name)
            {
                std::cout << _dir[i].get_name() << '\n';
                std::cout << _dir[i].get_owner() << '\n';
                std::cout << _dir[i].get_tel_num() << '\n';
                std::cout << _dir[i].get_adress() << '\n';
            }
        }
    }
    void find_by_owner(const std::string& owner)
    {
        for (size_t i = 0; i < _dir.size(); i++)
        {
            if (_dir[i].get_owner() == owner)
            {
                std::cout << _dir[i].get_name() << '\n';
                std::cout << _dir[i].get_owner() << '\n';
                std::cout << _dir[i].get_tel_num() << '\n';
                std::cout << _dir[i].get_adress() << '\n';
            }
        }
    }
    void find_by_tel_num(const std::string& tel_num)
    {
        for (size_t i = 0; i < _dir.size(); i++)
        {
            if (_dir[i].get_tel_num() == tel_num)
            {
                std::cout << _dir[i].get_name() << '\n';
                std::cout << _dir[i].get_owner() << '\n';
                std::cout << _dir[i].get_tel_num() << '\n';
                std::cout << _dir[i].get_adress() << '\n';
            }
        }
    }
    void find_by_adress(const std::string& adress)
    {
        for (size_t i = 0; i < _dir.size(); i++)
        {
            if (_dir[i].get_adress() == adress)
            {
                std::cout << _dir[i].get_name() << '\n';
                std::cout << _dir[i].get_owner() << '\n';
                std::cout << _dir[i].get_tel_num() << '\n';
                std::cout << _dir[i].get_adress() << '\n';
            }
        }
    }
    void add_directory(const directory& dir) {
        _dir.push_back(dir);
    }
    void write_toFile(const std::string& filename)
    {
        std::ofstream out(filename, std::ios::binary);
        if (!out) {
            throw std::runtime_error("Cannot open file for writing");
        }

        size_t count = _dir.size();
        out.write(reinterpret_cast<char*>(&count), sizeof(size_t));

        for (size_t i = 0; i < _dir.size(); i++)
        {
            size_t name_size = _dir[i].get_name().size();
            size_t owner_size = _dir[i].get_owner().size();
            size_t tel_num_size = _dir[i].get_tel_num().size();
            size_t adress_size = _dir[i].get_adress().size();
            out.write(reinterpret_cast<char*>(&name_size), sizeof(size_t));
            out.write(_dir[i].get_name().c_str(), name_size);
            out.write(reinterpret_cast<char*>(&owner_size), sizeof(size_t));
            out.write(_dir[i].get_owner().c_str(), owner_size);
            out.write(reinterpret_cast<char*>(&tel_num_size), sizeof(size_t));
            out.write(_dir[i].get_tel_num().c_str(), tel_num_size);
            out.write(reinterpret_cast<char*>(&adress_size), sizeof(size_t));
            out.write(_dir[i].get_adress().c_str(), adress_size);
            
        }
        out.close();
    }
    void read_fromFile(const std::string& filename)
    {
        std::ifstream fin(filename, std::ios::binary);
        if (!fin) {
            throw std::runtime_error("Cannot open file for writing");
        }

        size_t count = _dir.size();
        fin.read(reinterpret_cast<char*>(&count), sizeof(size_t));
        _dir.clear();
        for (size_t i = 0; i < count; i++)
        {
            size_t name_size, owner_size, tel_num_size, adress_size;
            std::string name, owner, tel_num, adress;


            fin.read(reinterpret_cast<char*>(&name_size), sizeof(size_t));
            name.resize(name_size);
            fin.read(&name[0], name_size);


            fin.read(reinterpret_cast<char*>(&owner_size), sizeof(size_t));
            owner.resize(owner_size);
            fin.read(&owner[0], owner_size);


            fin.read(reinterpret_cast<char*>(&tel_num_size), sizeof(size_t));
            tel_num.resize(tel_num_size);
            fin.read(&tel_num[0], tel_num_size);


            fin.read(reinterpret_cast<char*>(&adress_size), sizeof(size_t));
            adress.resize(adress_size);
            fin.read(&adress[0], adress_size);
            
            _dir.emplace_back(name, owner, tel_num, adress);
        }
    }
};

int main()
{

    directory d1("Cafe", "Alice", "+12345678", "123");
    directory d2("Bar", "Bob", "+98765432", "456");
    directory d3("home", "Carl", "+11223344", "789");


    std::vector<directory> dirs = { d1, d2, d3 };
    std::vector<directory> d = { };
    dir_array original(dirs);
    
    /*
    original.write_toFile("dir.bin");
    */

    dir_array loaded(d);
    loaded.read_fromFile("dir.bin");

    
    
    std::string search;
    std::cout << "Write name for search: ";
    std::getline(std::cin, search);
    
    loaded.find_by_name(search);
    
    return 0;
}

