
#include <iostream>
#include <cstring>
#include <numeric>

class Fraction {
private:
    int numerator;
    int denominator;

    void reduce() {
        int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
    }

public:
    Fraction(int n, int d) : numerator(n), denominator(d == 0 ? 1 : d) {
        reduce();
    }

    Fraction() : Fraction(0, 1) {}

    void print() const {
        std::cout << numerator << "/" << denominator << std::endl;
    }

    Fraction operator+(const Fraction& f) const {
        return Fraction(numerator * f.denominator + f.numerator * denominator, denominator * f.denominator);
    }

    Fraction operator-(const Fraction& f) const {
        return Fraction(numerator * f.denominator - f.numerator * denominator, denominator * f.denominator);
    }

    Fraction operator*(const Fraction& f) const {
        return Fraction(numerator * f.numerator, denominator * f.denominator);
    }

    Fraction operator+(int value) const {
        return Fraction(numerator + value * denominator, denominator);
    }

    Fraction operator-(int value) const {
        return Fraction(numerator - value * denominator, denominator);
    }

    Fraction operator*(int value) const {
        return Fraction(numerator * value, denominator);
    }
};

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
    Date() : Date(1, 1, 2000) {}

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    void setDay(int d) { day = d; }
    void setMonth(int m) { month = m; }
    void setYear(int y) { year = y; }

    void print() const {
        std::cout << day << "." << month << "." << year;
    }
};

class Person {
private:
    int id;
    char* lastName;
    char* firstName;
    char* patronymic;
    Date birthDate;

    static int instanceCount;

    void copyString(char*& dest, const char* src) {
        dest = new char[strlen(src) + 1];
        strcpy(dest, src);
    }

public:
    Person(int id, const char* ln, const char* fn, const char* p, const Date& date)
        : id(id), birthDate(date) {
        copyString(lastName, ln);
        copyString(firstName, fn);
        copyString(patronymic, p);
        ++instanceCount;
    }

    Person() : Person(0, "Невідомо", "Невідомо", "Невідомо", Date()) {}

    Person(const Person& other)
        : id(other.id), birthDate(other.birthDate) {
        copyString(lastName, other.lastName);
        copyString(firstName, other.firstName);
        copyString(patronymic, other.patronymic);
        ++instanceCount;
    }

    ~Person() {
        delete[] lastName;
        delete[] firstName;
        delete[] patronymic;
        --instanceCount;
    }

    int getId() const { return id; }
    const char* getLastName() const { return lastName; }
    const char* getFirstName() const { return firstName; }
    const char* getPatronymic() const { return patronymic; }
    Date getBirthDate() const { return birthDate; }

    void setId(int i) { id = i; }

    void setLastName(const char* ln) {
        delete[] lastName;
        copyString(lastName, ln);
    }

    void setFirstName(const char* fn) {
        delete[] firstName;
        copyString(firstName, fn);
    }

    void setPatronymic(const char* p) {
        delete[] patronymic;
        copyString(patronymic, p);
    }

    void setBirthDate(const Date& d) {
        birthDate = d;
    }

    static int getInstanceCount() {
        return instanceCount;
    }

    void print() const {
        std::cout << "ID: " << id << "\n";
        std::cout << "ПІБ: " << lastName << " " << firstName << " " << patronymic << "\n";
        std::cout << "Дата народження: ";
        birthDate.print();
        std::cout << std::endl;
    }
};

int Person::instanceCount = 0;

int main() {
    Fraction f1(1, 2), f2(1, 4);
    Fraction sum = f1 + f2;
    Fraction mul = f1 * 3;

    sum.print();
    mul.print();

    Date birth(10, 3, 1995);
    Person p1(1, "Іваненко", "Олег", "Петрович", birth);
    Person p2 = p1;

    p1.print();
    p2.print();

    std::cout << "Кількість об'єктів Person: " << Person::getInstanceCount() << std::endl;

    return 0;
}
