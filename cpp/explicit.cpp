/**
 * explicit 关键字 
 */
 
#include <iostream>

using namespace std;

class Fraction
{
public:
    explicit Fraction(int num, int den = 1)
        : m_nNumerator(num)
        , m_nDenominator(den)
        {}

    Fraction operator+(const Fraction& other)
    {
        int nNumerator = this->m_nNumerator + other.m_nNumerator;
        int nDenominator = this->m_nDenominator + other.m_nDenominator;
        return Fraction(nNumerator, nDenominator);  
    }

    operator double() const
    {
        return (double)(m_nNumerator) / m_nDenominator;
    }

private:
    int m_nNumerator;
    int m_nDenominator;
};


int main()
{
    Fraction f(2, 3);
    //Fraction f2 = f + 3;
    double d = f + 3;


    return 0;
}
