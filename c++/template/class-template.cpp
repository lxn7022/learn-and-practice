#include <iostream>
#include <string>
using namespace std;

// 类模板
template <class T1, class T2>
class Pair
{
public:
    Pair(T1 k, T2 v) : m_key(k), m_value(v){};
    bool operator<(const Pair<T1, T2> &p) const;

    // 友元函数模板
    template <class T3, class T4>
    friend ostream &operator<<(ostream &o, const Pair<T3, T4> &p);

private:
    T1 m_key;
    T2 m_value;
};

// 类模板里成员函数的写法
template <class T1, class T2>
bool Pair<T1, T2>::operator<(const Pair<T1, T2> &p) const
{
    return m_value < p.m_value;
}

// 函数模板
template <class T3, class T4>
ostream &operator<<(ostream &o, const Pair<T3, T4> &p)
{
    o << "(" << p.m_key << "," << p.m_value << ")";
    return o;
}

void test_Pair()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    Pair<string, int> Astudent("Jay", 20);
    Pair<string, int> Bstudent("Tom", 21);
    cout << Astudent << ", " << Bstudent << endl;
    cout << (Astudent < Bstudent) << endl;
}

int main()
{
    test_Pair();
    return 0;
}