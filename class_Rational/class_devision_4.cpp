#include <iostream>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <cctype>
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
    friend istream& operator>>(istream& stream, Rational& r);
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

Rational operator*(const Rational& first, const Rational& second) {
    return {first.Numerator() * second.Numerator(), first.Denominator() * second.Denominator()};
}

Rational operator/(const Rational& first, const Rational& second) {
    long int a, b;
    int a1, b1;
    a = first.Numerator() * second.Denominator();
    b = first.Denominator() * second.Numerator();
    int g = gcd(abs(a), abs(b));
    a1 = a /g;
    b1 = b / g;
    return {a1, b1};
}

istream& operator>>(istream& stream, Rational& r) {
    if (!bool(stream)){
        return stream;
    }
    char c;
    int a, b;
    stream >> a;
    if (stream.fail()){
        return stream;
    }
    stream >> c;
    if (c != '/') {
        return stream;
    }
    stream >> b;
    if (stream.fail()){
        return stream;
    }
    r = {a, b};
    return stream;
}

ostream& operator<<(ostream& stream, const Rational& r) {
    stream << r.Numerator() << '/' << r.Denominator();
    return stream;
}

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    cout << "OK" << endl;
    return 0;
}