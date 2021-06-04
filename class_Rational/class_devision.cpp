#include <iostream>
#include <numeric>
using namespace std;

int sign(int a, int b){
    return (a * b < 0) ? 1 : 0;
}

class Rational {
public:
    Rational() {
        // � еализуйте конструктор по умолчанию
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
        // � еализуйте конструктор
        int g = gcd(abs(numerator), abs(denominator));
        if (numerator == 0)
            denominator = 1;
        else if (sign(numerator, denominator)){
            numerator = - abs(numerator);
            denominator = abs(denominator);
        } else if (numerator < 0) {
                numerator *= -1;
                denominator *= -1;
            }
        if (numerator != 0){
            p = numerator / g;
            q = denominator / g;
        } else {
            p = numerator;
            q = denominator;
        }
    }

    int Numerator() const {
        // � еализуйте этот метод
        return p;
    }

    int Denominator() const {
        // � еализуйте этот метод
        return q;
    }

private:
    // Добавьте поля
    int p;
    int q;
};

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}