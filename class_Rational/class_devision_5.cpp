#include <iostream>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <map>
#include <set>
#include <vector>
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
    Rational res;
    res = {first.Numerator() * second.Numerator(), first.Denominator() * second.Denominator()};
    return res;
}

Rational operator/(const Rational& first, const Rational& second) {
    Rational res;
    res = {first.Numerator() * second.Denominator(), second.Numerator() * first.Denominator()};
    return res;
}

istream& operator>>(istream& stream, Rational& r) {
    if (stream.eof())
        return stream;
    char c;
    int flag = 0;
    stream >> r.p;
    if (stream.fail())
        flag++;
    stream >> c;
    if (c != '/') {
        flag++;
    }
    stream >> r.q;
    if (stream.fail())
        flag++;
    if (flag == 0)
        r = {r.p, r.q};
    else r = {};
    return stream;
}

ostream& operator<<(ostream& stream, const Rational& r) {
    stream << r.Numerator() << '/' << r.Denominator();
    return stream;
}

bool operator<(const Rational& first, const Rational& second){
    int tmp = lcm(first.Denominator(), second.Denominator());
    int ftmp = tmp / first.Denominator();
    int stmp = tmp / second.Denominator();
    return (ftmp * first.Numerator() < (stmp * second.Numerator()));
}


// Вставьте сюда реализацию класса Rational из первой части

// Вставьте сюда реализацию operator == для класса Rational из второй части

// � еализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}