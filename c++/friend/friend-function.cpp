#include <iostream>
#include <string>
using namespace std;

class Address; // 提前声明Address类

// 声明Student类
class Student
{
public:
    Student(std::string &name, int age, float score);

public:
    void show(Address &addr);
    // 将非成员函数operator<< 声明为friend
    friend std::ostream &operator<<(std::ostream &stream, const Student &s);

private:
    std::string m_name;
    int m_age;
    float m_score;
};

// 声明Address类
class Address
{
private:
    std::string m_province; // 省份
    std::string m_city;     // 城市
    std::string m_district; // 区（市区）
public:
    Address(std::string &province, string &city, string &district);
    // 将Student类中的成员函数show()声明为友元函数
    friend void Student::show(Address &addr);
};

// 实现Student类
Student::Student(string &name, int age, float score) : m_name(name), m_age(age), m_score(score) {}

// show
void Student::show(Address &addr)
{
    cout << m_name << "的年龄是 " << m_age << "，成绩是 " << m_score << endl;
    cout << "家庭住址："
         << addr.m_province << "省"
         << addr.m_city << "市"
         << addr.m_district << "区" << endl;
}

std::ostream &operator<<(std::ostream &stream, const Student &s)
{
    stream << "Student("
           << s.m_name << "," << s.m_age << "," << s.m_score << ")";
    return stream;
}

//-----------------------------------

// 实现Address类
Address::Address(std::string &province, std::string &city, std::string &district)
{
    m_province = province;
    m_city = city;
    m_district = district;
}

void test_Student()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    string name = "小明";
    Student stu(name, 16, 95.5f);
    cout << stu << endl;

    string province = "陕西";
    string city = "西安";
    string district = "雁塔";
    Address addr(province, city, district);
    stu.show(addr);
}

int main()
{
    test_Student();
}
