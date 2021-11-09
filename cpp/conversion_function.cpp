/**
 * 转换函数   
 */
 
#include <iostream>

using namespace std;

class Fraction
{
public:
    Fraction(int num, int den = 1)
        : m_nNumerator(num)
        , m_nDenominator(den)
        {}

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
    double d = 3 + f;

    std::cout << d << std::endl;

    return 0;
}