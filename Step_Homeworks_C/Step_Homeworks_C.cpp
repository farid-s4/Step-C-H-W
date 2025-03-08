#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Car
{
private:
    char _brand[20];
    int _cary;
    char _model[20];
    int _milage;
public:
    Car() 
    {
        strncpy(_brand, "Unknown", sizeof(_brand));
        _cary = 0;
        strncpy(_model, "Unknown", sizeof(_model));
        _milage = 0;
    }

    
    Car(const char* brand, const int cary, const char* model, const int milage)
    {
        setBrand(brand);
        setCary(cary);
        setModel(model);
        setMilage(milage);
    }
    
    const char* getBrand() const { return _brand; }
    int getCary() const{ return _cary; }
    const char* getModel() const { return _model; }
    int getMilage() const { return _milage; }
    
    
    void setBrand(const char* new_brand)
    {
        if (new_brand && _brand[0] != '\0')
        {
            strncpy(_brand, new_brand, sizeof(_brand));
            _brand[strlen(new_brand)] = '\0';
        }
    }

    void setCary(const int new_cary)
    {
        if (new_cary > _cary)
        {
            _cary = new_cary;
        }
    }

    void setModel(const char* new_model)
    {
        if (new_model && _model[0] != '\0')
        {
            strncpy(_model, new_model, sizeof(_model));
            _model[strlen(new_model)] = '\0';
        }
    }

    void setMilage(const int new_milage)
    {
        if (new_milage > _milage)
        {
            _milage = new_milage;
        }
    }

    void setNewMilage(int new_milage)
    {
        _milage = new_milage + _milage;
    }

    int getAge(int currentYear)
    {
        int result = 0;
        if (currentYear >= 1900)
        {
            result = currentYear - _cary;
        }
        return result;
    }
    
};

void DisplayInfo(const Car& user)
{
    std::cout<<"Brand: "<<user.getBrand()
    <<"\nCar age: "<<user.getCary()
    <<"\nModel: "<<user.getModel()
    <<"\nMilage: "<<user.getMilage()
    <<"\n";
}

int main()
{
    
    Car car("BMW", 2002, "M5F90", 111); 
    DisplayInfo(car);

    car.setNewMilage(50);

    std::cout<<std::endl;
    
    int get_age;
    get_age = car.getAge(2025);
    DisplayInfo(car);

    std::cout<<std::endl;
    std::cout<<"Car age: " <<get_age;
    
    return 0;       
}