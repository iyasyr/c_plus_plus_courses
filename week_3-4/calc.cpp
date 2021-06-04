#include <iostream>
#include <exception>
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
        if (denominator == 0) {
            throw runtime_error("Invalid argument\n");
        }
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
    if (second.Numerator() == 0) {
        throw domain_error("Division by zero\n");
    }
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
        throw runtime_error("Invalid argument\n");
    }
    stream >> b;
    if (b == 0)
        throw runtime_error("Invalid argument\n");
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

Rational Calculations(istream& stream){
    Rational r1, r2;
    char c;
    stream >> r1;
    stream >> c;
    stream >> r2;
    if (c == '+')
        return r1 + r2;
    else if (c == '-')
        return r1 - r2;
    else if (c == '*')
        return r1 * r2;
    else if (c == '/')
        return r1 / r2;
}

int main() {
//    try {
//        istringstream input("1/2 + 1/3");
//        Calculations(input);
//    } catch (exception& ex) { cout << ex.what();
//    }
//    try {
//        istringstream input("1/2 + 5/0");
//        Calculations(input);
//        cout << "Doesn't throw in case of wrong argument" << endl;
//        return 1;
//    } catch (exception& ex) { cout << ex.what();
//    }
//    try {
//        istringstream input("4/5 / 0/8");
//        Calculations(input);
//        cout << "Doesn't throw in case of division by zero" << endl;
//        return 2;
//    } catch (exception& ex) { cout << ex.what();
//    }
    try {
        Rational r = Calculations(cin);
        cout << r;
    } catch (exception& ex) {
        cout << ex.what();
    }
    return 0;
}