#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
// Реализуйте функции и методы классов и при необходимости добавьте свои

using namespace std;

class Date {
public:
    Date() {
        year = 0;
        month = 0;
        day = 0;
    }
    Date(int new_year, int new_month, int new_day){
        if (new_month < 1 || new_month > 12)
            throw runtime_error("Month value is invalid: " + to_string(new_month));
        if (new_day < 1 || new_day > 31)
            throw runtime_error("Day value is invalid: " + to_string(new_day));
        year = new_year;
        month = new_month;
        day = new_day;
    }
    int GetYear() const{
        return year;
    }
    int GetMonth() const{
        return month;
    }
    int GetDay() const{
        return day;
    }

private:
    int year;
    int month;
    int day;
};

void GetDate(string& main_string, Date& d){
    stringstream ss(main_string);
    string str;
    int new_year;
    int new_month;
    int new_day;
    ss >> new_year;
    if (ss.fail()){
        throw runtime_error("Wrong date format: " + main_string);
    }
    if (ss.peek() != '-') {
        throw runtime_error("Wrong date format: " + main_string);
    }
    ss.ignore();
    ss >> new_month;
    if (ss.fail()){
        throw runtime_error("Wrong date format: " + main_string);
    }
    if (ss.peek() != '-') {
        throw runtime_error("Wrong date format: " + main_string);
    }
    ss.ignore();
    ss >> new_day;
    if (ss.fail()){
        throw runtime_error("Wrong date format: " + main_string);
    }
    if (!ss.eof() && ss.peek() != ' ' && ss.peek() != '\n') {
        throw runtime_error("Wrong date format: "  + main_string);
    }
    d = {new_year, new_month, new_day};
}
//    string str;
//    int new_year;
//    int new_month;
//    int new_day;
////    string string1;
////    stream >> string1;
////    cout << string1;
////    throw 111;
//    stream >> new_year;
//    if (stream.fail()){
//        stream.clear();
//        stream.unget();
//        stream >> str;
//        throw runtime_error("Wrong date format: " + str);
//    }
//    if (stream.peek() != '-') {
//        if (stream.peek() != ' '){
//            stream >> str;
//            throw runtime_error("Wrong date format: " + to_string(new_year) + str);
//        }else throw runtime_error("Wrong date format: " + to_string(new_year));
//    }
//    stream.ignore(1);
//    if (stream.peek() == ' '){
//        throw runtime_error("Wrong date format: " + to_string(new_year) + '-');
//    }
//    stream >> new_month;
//    if (stream.fail()){
//        stream.clear();
//        stream >> str;
//        throw runtime_error("Wrong date format: "  + to_string(new_year) + '-' + str);
//    }
//    if (stream.peek() != '-') {
//        if (stream.peek() != ' '){
//            stream >> str;
//            throw runtime_error("Wrong date format: " + to_string(new_year) + '-' + to_string(new_month) + str);
//        } else throw runtime_error("Wrong date format: " + to_string(new_year) + '-' + to_string(new_month));
//    }
//    stream.ignore(1);
//    if (stream.peek() == ' ') {
//        throw runtime_error("Wrong date format: " + to_string(new_year) + '-' + to_string(new_month) + '-');
//    }
//    stream >> new_day;
//    if (stream.fail()){
//        stream.clear();
//        stream >> str;
//        throw runtime_error("Wrong date format: "  + to_string(new_year) + '-' + to_string(new_month) + '-' + str);
//    }
//    //dich
//    if (!stream.eof() && stream.peek() != ' ' && stream.peek() != '\n') {
//        stream >> str;
//        throw runtime_error("Wrong date format: "  + to_string(new_year) + '-' + to_string(new_month) + '-' + to_string(new_day) + str);
//    }
//    d = {new_year, new_month, new_day};
//    return stream;
//}

ostream& operator<<(ostream& stream, const Date& r){
    stream << setfill('0') << setw(4) << r.GetYear() << '-' << setw(2) << r.GetMonth() << '-' << setw(2) << r.GetDay();
    return stream;
}

bool operator<(const Date& lhs, const Date& rhs){
    if (lhs.GetYear() != rhs.GetYear())
        return lhs.GetYear() < rhs.GetYear();
    else if (lhs.GetMonth() != rhs.GetMonth())
        return  lhs.GetMonth() < rhs.GetMonth();
    else return lhs.GetDay() < rhs.GetDay();
}

class Database {
public:
    void AddEvent(const Date& date, const string& event){
        if (m.count(date) > 0){
            m.at(date).insert(event);
        } else m[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event){
        if (m.count(date) > 0){
            set<string>::iterator iter;
            if ((iter = m.at(date).find(event)) != m.at(date).end()) {
                m.at(date).erase(iter);
                cout << "Deleted successfully" << endl;
                return 1;
            }
            else {
                cout << "Event not found" << endl;
                return 0;
            }
        } else {
            cout << "Event not found" << endl;
            return 0;
        }
    }
    int DeleteDate(const Date& date){
        int res = 0;
        if (m.count(date) > 0){
            res = m.at(date).size();
            m.erase(date);
        }
        cout << "Deleted " << res << " events" << endl;
        return res;
    }

    set<string> Find(const Date& date) const{
        if (m.count(date) > 0){
            return m.at(date);
        } else return {};
    }


    void Print() const{
        for (const auto& item: m){
            for (const auto& item1: item.second)
            cout << item.first << ' ' << item1 << endl;
        }
    }
private:
    map<Date, set<string>> m;
};

int main() {
    try {
        Database db;

        string command_line;
        while (getline(cin, command_line)) {
// Считайте команды с потока ввода и обработайте каждую
            stringstream ss(command_line);
            string command;
            ss >> command;
            if (command == "Add") {
                Date date;
                string event;
                string string_date;
                ss >> string_date;
                GetDate(string_date, date);
                ss >> event;
                db.AddEvent(date, event);
            } else if (command == "Del") {
                Date date;
                string string_date;
                ss >> string_date;
                GetDate(string_date, date);
                if (ss.eof())
                    db.DeleteDate(date);
                else {
                    string event;
                    ss >> event;
                    db.DeleteEvent(date, event);
                }
            } else if (command == "Find") {
                Date date;
                string string_date;
                ss >> string_date;
                GetDate(string_date, date);
                for (auto &item : db.Find(date))
                    cout << item << endl;
            } else if(command == "Print"){
                db.Print();
            } else if(command.empty()){
                continue;
            } else throw runtime_error("Unknown command: " + command_line + '\n');
        }
    }catch (const exception& ex){
        cout << ex.what() << endl;
    }
    return 0;
}
//    Date d = {};
//    cout << d << endl;
//    d = {1998, 12, 15};
//    cout << d << endl;
//    istringstream input("Add +2000-+07-26 event1");
//    input >> d;
//    cout << d << endl;
/*
 * Add 2000-7-26 birthofAnna
 * Add 1998-12-15 birthofIlia
 * Add 1998-12-15 birthofMe
 */