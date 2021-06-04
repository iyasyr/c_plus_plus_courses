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

bool operator==(const Rational& first, const Rational& second){
    return (first.Numerator() == second.Numerator()) && (first.Denominator() == second.Denominator());
}

Rational operator+(const Rational& first, const Rational& second){
    Rational res;
    int tmp = lcm(first.Denominator(), second.Denominator());
    int ftmp = tmp / first.Denominator();
    int stmp = tmp / second.Denominator();
    res = {ftmp * first.Numerator() + stmp * second.Numerator(), tmp};
    return res;
}

Rational operator-(const Rational& first, const Rational& second){
    Rational res;
    int tmp = lcm(first.Denominator(), second.Denominator());
    int ftmp = tmp / first.Denominator();
    int stmp = tmp / second.Denominator();
    res = {ftmp * first.Numerator() - stmp * second.Numerator(), tmp};
    return res;
}

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}