#include <iostream>

class Fraction
{
private:
    double _numerator;
    double _denominator;
    int gcd(int a, int b)
    {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    
public:
    Fraction(): _numerator(0), _denominator(1){}
    
    Fraction(double numerator, double denominator) : _numerator(numerator), _denominator(denominator)
    {
        if (_denominator == 0)
        {
            std::cout << "ERROR" << std::endl;
        }
    }
    
    Fraction(const Fraction& fraction)
    {
        _numerator = fraction._numerator;
        _denominator = fraction._denominator;
    }
    
    
    
    
    Fraction operator+(const Fraction& fraction) 
    {
        int GCD = gcd(_denominator, fraction._denominator);

        int LCM = (_denominator * fraction._denominator) / GCD;

        int new_numerator = (LCM / _denominator)*_numerator + LCM / (fraction._denominator)*fraction._numerator;
        
        return Fraction(new_numerator, LCM);
        
    }

    Fraction operator-(const Fraction& fraction) 
    {
        int GCD = gcd(_denominator, fraction._denominator);

        int LCM = (_denominator * fraction._denominator) / GCD;

        int new_numerator = (LCM / _denominator)*_numerator - LCM / (fraction._denominator)*fraction._numerator;
        
        return Fraction(new_numerator, LCM);
        
    }

    Fraction operator*(const Fraction& fraction) 
    {
        return Fraction(_numerator*fraction._numerator, _denominator*fraction._denominator);
    }

    Fraction operator/(const Fraction& fraction) 
    {
        return Fraction(_numerator*fraction._denominator, _denominator*fraction._numerator);
    }

    bool operator==(const Fraction& fraction)
    {
        if (_numerator == fraction._numerator && _denominator == fraction._denominator)
        {
            return true;
        }
        return false;
    }
    bool operator!=(const Fraction& fraction)
    {
        if (_numerator != fraction._numerator && _denominator != fraction._denominator)
        {
            return true;
        }
        return false;
    }
    
    bool operator<(const Fraction& fraction)
    {
        int GCD = gcd(_denominator, fraction._denominator);

        int LCM = (_denominator * fraction._denominator) / GCD;

        if ( (LCM / _denominator)*_numerator < LCM / (fraction._denominator)*fraction._numerator ){
            return true;
        }
        return false;
    }

    bool operator>(const Fraction& fraction)
    {
        int GCD = gcd(_denominator, fraction._denominator);

        int LCM = (_denominator * fraction._denominator) / GCD;

        if ( (LCM / _denominator)*_numerator > LCM / (fraction._denominator)*fraction._numerator ){
            return true;
        }
        return false;
    }

    bool operator<=(const Fraction& fraction)
    {
        int GCD = gcd(_denominator, fraction._denominator);

        int LCM = (_denominator * fraction._denominator) / GCD;

        if ( (LCM / _denominator)*_numerator <= LCM / (fraction._denominator)*fraction._numerator ){
            return true;
        }
        return false;
    }

    bool operator>=(const Fraction& fraction)
    {
        int GCD = gcd(_denominator, fraction._denominator);

        int LCM = (_denominator * fraction._denominator) / GCD;

        if ( (LCM / _denominator)*_numerator >= LCM / (fraction._denominator)*fraction._numerator ){
            return true;
        }
        return false;
    }

    operator double()
    {
        return double(_numerator / _denominator);
    }

    void Simplify()
    {
        int GCD = gcd(_numerator, _denominator);
        _numerator /= GCD;
        _denominator /= GCD;
    }
    
    
    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
};

std::ostream& operator<<(std::ostream& os, const Fraction& fraction)
{
    os << fraction._numerator << "/" << fraction._denominator;
    return os;
}

int main()
{
    Fraction a(2, 3);
    Fraction b(1,2);

    Fraction c = a + b;
    std::cout << c << std::endl;
    std::cout << (double)c << std::endl;
    
}