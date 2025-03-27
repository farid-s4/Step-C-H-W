#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class Animal {
protected:
    char _name[20];
    int _age;
    double _weight;
public:
    Animal() :  _age(0), _weight(0)
    {
        strcpy(_name, "Unknown");
    }
    Animal(const Animal& other)
    {
        strcpy(_name, other._name);
        _age = other._age;
        _weight = other._weight;
    }
    const char* getName() const {
        return _name;
    }
    int getAge() const {
        return _age;
    }
    double getWeight() const {
        return _weight;
    }
    void setName(const char* name) {
        strcpy(_name, name);
    }
    void setAge(int age) {
        if (age > 0)
        {
            _age = age;
        }
    }
    void setWeight(double weight) {
        if (weight > 0)
        {
            _weight = weight;
        }
    }
    void printInfo() const {
        std::cout << "Name: " << _name << " Age: " << _age << " Weight: " << _weight <<"\n";
    }
};

class Mammal : public Animal {
private:
    bool _hasFur;
public:
    Mammal(): Animal() , _hasFur(false){}
    Mammal(const Mammal& other) : Animal(other)
    {

        _hasFur = other._hasFur;
    }
    bool getHasFur() const {
        return _hasFur;
    }
    void setHasFur(bool fur) {
        _hasFur = fur;
    }
    void printInfo() const {
        std::cout << "Name: " << _name << " Age: " << _age << " Weight: " << _weight << "hasFur: " << _hasFur << "\n";
    }
};

class Bird : public Animal {
private:
    double _wingSpan;
public:
    
    Bird() : Animal() , _wingSpan(0.0){}
    Bird(const Bird& other) : Animal(other)
    {
        _wingSpan = other._wingSpan;
    }
    double getWingSpan() const
    {
        return _wingSpan;
    }
    void setWingSpan(double wingSpan)
    {
        if (wingSpan > 0.0)
        {
            _wingSpan = wingSpan;
        }
    }
    void printInfo() const {
        std::cout << "Name: " << _name << " Age: " << _age << " Weight: " << _weight << "_wingSpan: " << _wingSpan << "\n";
    }
};

class Reptile : public Animal {
private:
    bool _isVenomous;
public:
    Reptile() : Animal() , _isVenomous(false){}
    Reptile(const Reptile& other) : Animal(other)
    {

        _isVenomous = other._isVenomous;
    }
    bool getIsVenomous() const
    {
        return _isVenomous;
    }
    void setIsVenomous(bool venom)
    {
        _isVenomous = venom;
    }
    void printInfo() const
    {
        std::cout << "Name: " << _name << " Age: " << _age << " Weight: " << _weight << "IsVenomous"<< _isVenomous<<"\n";
    }
};

class ZooWorker {
private:
    char _name[30];
    int _experience;
public:
    ZooWorker(): _name("Unknown"), _experience(0) {}
    ZooWorker(const char* name, int exp)
    {
        strcpy(_name, name);
        _experience = exp;
    }
    ZooWorker(const ZooWorker& other)
    {
        strcpy(_name, other._name);
        _experience = other._experience;
    }
    const char* getName() const
    {
        return _name;
    }
    int getExperience() const
    {
        return _experience;
    }
    void setName(const char* name)
    {
        strcpy(_name, name);
    }
    void setExperience(int exp)
    {
        if (_experience > 0)
        {
            _experience = exp;
        }
    }
    void printInfo() const
    {
        std::cout << "Name: " << _name << " Experience: " << _experience << "\n";
    }
};

class Enclosure {
private:
    char _type[20];
    int _capacity;
    Animal* _animals;
    int _animalCount;
    ZooWorker _caretaker;
    void resize(double factor)
    {
        int NewCapacity = factor * _capacity;
        auto *TempData = new Animal[NewCapacity];
        for (int i = 0; i < _animalCount; i++)
        {
            TempData[i] = _animals[i];
        }
        delete[] _animals;
        _animals = TempData;
        _capacity = NewCapacity;
    }
public:
    Enclosure(): _type("Unknown") , _capacity(0),   _animals(nullptr), _animalCount(0), _caretaker(ZooWorker()) {}
    explicit Enclosure(int animalCount) : _animalCount(animalCount), _capacity(animalCount)
    {
        strcpy(_type, "Unknown");
        _animals = new Animal[animalCount];
    }
    Enclosure(const Enclosure& other)
    {
        _animals = new Animal[other._capacity];
        strcpy(_type, other._type);
        _capacity = other._capacity;
        _animalCount = other._animalCount;
        for (int i = 0; i < _animalCount; i++)
        {
            _animals[i] = other._animals[i];
        }
        _caretaker = other._caretaker;
    }
    
    int getAnimalCount() const
    {
        return _animalCount;
    }
    const char* GetType() const
    {
        return _type;
    }
    void addAnimal(const Animal& animal)
    {
        if (_animalCount == _capacity)
        {
            resize(1.5);
        }
        _animals[_animalCount++] = animal;
    }
    bool removeAnimal(int index)
    {
        if (index >= 0 && index < _animalCount) {
            _animals[index] = _animals[_animalCount - 1]; 
            _animalCount--;

            if (_animalCount <= _capacity / 2 && _capacity > 1) {  
                resize(0.5);
            }
            return true;
        }
        return false;
    }
    void printEnclosureInfo() const
    {
        for (int i = 0; i < _animalCount; i++)
        {
            _animals[i].printInfo();
        }
        _caretaker.printInfo();
        std::cout << "Type: "<< _type << '\n';
        
    }

    ~Enclosure()
    {
        delete[] _animals;
    }
    
};

class Zoo {
private:
    Enclosure* _enclosures;
    int _enclosureCount;
    int _capacity;
    void resize(double factor)
    {
        int NewCapacity = factor * _capacity;
        auto* TempData = new Enclosure[NewCapacity];
        for (int i = 0; i < _enclosureCount; i++)
        {
            TempData[i] = _enclosures[i];
        }
        delete[] _enclosures;
        _enclosures = TempData;
        _capacity = NewCapacity;
    }
public:
    Zoo () :_enclosures(nullptr), _enclosureCount(0), _capacity(0) {}
    explicit Zoo(int enclosureCount) : _enclosureCount(enclosureCount) , _capacity(enclosureCount)
    {
        _enclosures = new Enclosure[_capacity];
    }
    Zoo(const Zoo& other) : _enclosureCount(other._enclosureCount), _capacity(other._capacity)
    {
        _enclosures = new Enclosure[other._capacity];
        for (int i = 0; i < other._enclosureCount; i++)
        {
            _enclosures[i] = other._enclosures[i];
        }
    }
    
    bool addEnclosure(const Enclosure& enclosure)
    {
        if (_enclosureCount == _capacity)
        {
            resize(2);
        }
        _enclosures[_enclosureCount++] = enclosure;
        return true;
    }
    
    void printZooInfo() const
    {
        for (int i = 0; i < _enclosureCount; i++)
        {
            std::cout << "Animal count: " << _enclosures[i].getAnimalCount() << " Name: " << _enclosures[i].GetType() << '\n';
        }
    }

    ~Zoo()
    {
        delete[] _enclosures;
    }
};
int main() {
    
    Animal animal1;
    animal1.printInfo();
    animal1.setName("Lion");
    animal1.setAge(5);
    animal1.setWeight(180.5);
    animal1.printInfo();

    Animal animal2 = animal1;  
    animal2.printInfo();


    Mammal mammal;
    mammal.setName("Tiger");
    mammal.setAge(3);
    mammal.setWeight(220.7);
    mammal.setHasFur(true);
    mammal.printInfo();

    Bird bird;
    bird.setName("Eagle");
    bird.setAge(2);
    bird.setWeight(5.3);
    bird.setWingSpan(2.1);
    bird.printInfo();


    Reptile reptile;
    reptile.setName("Snake");
    reptile.setAge(4);
    reptile.setWeight(12.8);
    reptile.setIsVenomous(true);
    reptile.printInfo();


    ZooWorker worker("John Doe", 10);
    worker.printInfo();


    Enclosure enclosure(2);
    enclosure.addAnimal(animal1);
    enclosure.addAnimal(mammal);
    enclosure.printEnclosureInfo();

    enclosure.removeAnimal(0);  
    enclosure.printEnclosureInfo();


    Zoo zoo(2);
    zoo.addEnclosure(enclosure);
    zoo.printZooInfo();
}

