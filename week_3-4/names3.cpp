#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

string search_name(const map<int, string>& m, int year) {
    string res = "";
    for (auto& item: m){
        if (item.first <= year)
        {
            res = item.second;
        }
        else break;
    }
    return res;
}

string search_history(const map<int, string>& m, int year){
    string res = "";
    string tmp;
    int flg = 0;
    vector <string> history;
    for (auto& item: m) {
        if (item.first <= year) {
            history.push_back(item.second);
            res = item.second;
        } else break;
    }
    if (history.empty() != true) {
        history.pop_back();
        tmp = res;
        if (history.empty() != true){
            res += " (";
            reverse(history.begin(), history.end());
            for (auto item1: history) {
                if (tmp != item1) {
                    res += item1 + ", ";
                    flg = 1;
                }
                tmp = item1;
            }
            if (flg) {
                res.erase(res.end() - 2, res.end());
                res += ")";
            } else res.erase(res.end() - 2, res.end());
        }
    }
    return res;
}

class Person {
public:
    Person (string first, string last, int birthday){
        birth = birthday;
        ChangeFirstName(birthday, first);
        ChangeLastName(birthday, last);
    };

    void ChangeFirstName(int year, const string& first_name) {
        // добавить факт изменения имени на first_name в год year
        if (year >= birth)
            fn[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        // добавить факт изменения фамилии на last_name в год year
        if (year >= birth)
            ln[year] = last_name;
    }

    string GetFullName (int year) const{
        // получить имя и фамилию по состоянию на конец года year
        if (year < birth){
            return "No person";
        }
        else{
            string res;
            string first_name  = "";
            string last_name   = "";
            first_name = search_name(fn, year);
            last_name = search_name(ln, year);
            if (first_name.empty() && last_name.empty()) {
                return "Incognito";

                // если неизвестно только имя
            } else if (first_name.empty()) {
                return last_name + " with unknown first name";

                // если неизвестна только фамилия
            } else if (last_name.empty()) {
                return first_name + " with unknown last name";

                // если известны и имя, и фамилия
            } else {
                return first_name + " " + last_name;
            }
        }
    }

    string GetFullNameWithHistory(int year) const {
        // получить все имена и фамилии по состоянию на конец года year
        if (year < birth) {
            return "No person";
        } else {
            string res = "";
            string comma = ", ";
            string first_name = "";
            string last_name = "";
            first_name = search_history(fn, year);
            last_name = search_history(ln, year);
            if (first_name.empty() && last_name.empty()) {
                return "Incognito";

                // если неизвестно только имя
            } else if (first_name.empty()) {
                return last_name + " with unknown first name";

                // если неизвестна только фамилия
            } else if (last_name.empty()) {
                return first_name + " with unknown last name";

                // если известны и имя, и фамилия
            } else return first_name + " " + last_name;
        }
    }
private:
    map<int, string> fn;
    map<int, string> ln;
    int birth;
    // приватные поля
};


int main() {
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }
    return 0;
}



